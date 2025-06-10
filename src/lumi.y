%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

// 1. INCLUIR A DEFINIÇÃO DA AST E DECLARAR A RAIZ GLOBAL
#include "ast.h"

void yyerror(const char *s);
int  yylex(void);
extern FILE *yyin;
extern int yyrestart(FILE *);

// A raiz da nossa árvore sintática. O parser irá preenchê-la.
NodeList* ast_root = NULL;

// Protótipos das funções auxiliares para criar nós
AstNode* create_strip_decl(int count);
AstNode* create_assignment(char* id, AstNode* expr);
AstNode* create_if_stmt(AstNode* cond, NodeList* if_block, NodeList* else_block);
AstNode* create_while_stmt(AstNode* cond, NodeList* block);
AstNode* create_for_stmt(char* id, AstNode* start, AstNode* end, NodeList* block);
AstNode* create_loop_forever(NodeList* block);
AstNode* create_set_cmd(AstNode* index, AstNode* color);
AstNode* create_wait_cmd(char* time_lit);
AstNode* create_rotate_cmd(AstNode* steps, DirectionType dir);
AstNode* create_fade_cmd(AstNode* amount);
AstNode* create_binary_op(int op, AstNode* left, AstNode* right);
AstNode* create_unary_op(int op, AstNode* operand);
AstNode* create_integer(int value);
AstNode* create_identifier(char* name);
AstNode* create_color_hex(char* hex_code);
AstNode* create_hsv_color(AstNode* h, AstNode* s, AstNode* v);
NodeList* add_to_list(NodeList* list, AstNode* node);
%}

/* 2. ATUALIZAR A UNION E OS TIPOS DE TOKEN/REGRA */
%union {
  int           ival;
  char* sval;
  AstNode* node;       /* Ponteiro para um nó genérico da AST */
  NodeList* list;       /* Ponteiro para uma lista de statements */
  DirectionType dir_val;    /* Enum para direção (left/right) */
}

%define parse.error verbose

/* Tokens */
%token <ival> INT
%token <sval> ID COLOR_HEX TIME_LIT
%token T_STRIP T_IF T_ELSE T_WHILE T_FOR T_LOOP T_FOREVER
%token T_SET T_COLOR T_WAIT T_ROTATE T_DIR T_FADE
%token T_HSV T_LEFT T_RIGHT
%token EQ NEQ LE GE AND OR DOTDOT
%token NEWLINE

/* Tipos para as regras (não-terminais) */
%type <node> statement assignment if_stmt while_stmt for_stmt loop_forever command
%type <node> expression bool_expr rel_expr eq_expr color_expr
%type <list> program block statements
%type <dir_val> direction

/* Precedência (inalterada) */
%left OR
%left AND
%left EQ NEQ
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!'
%right UMINUS

%start program
%%

/* 3. ADICIONAR AÇÕES ÀS REGRAS PARA CONSTRUIR A ÁRVORE */

program
  : statements
    { ast_root = $1; }  // Armazena a lista final de statements na raiz da AST
  ;

statements
  : /* vazio */
    { $$ = NULL; }
  | statements statement
    { $$ = add_to_list($1, $2); } // Adiciona o novo statement à lista
  ;

statement
  : T_STRIP INT NEWLINE
    { $$ = create_strip_decl($2); }
  | assignment NEWLINE
    { $$ = $1; }
  | if_stmt
    { $$ = $1; }
  | while_stmt
    { $$ = $1; }
  | for_stmt
    { $$ = $1; }
  | loop_forever
    { $$ = $1; }
  | command NEWLINE
    { $$ = $1; }
  | NEWLINE
    { $$ = NULL; }
  ;

block
  : '{' statements '}'
    { $$ = $2; }
  ;

assignment
  : ID '=' expression
    { $$ = create_assignment($1, $3); }
  ;

if_stmt
  : T_IF '(' bool_expr ')' block
    { $$ = create_if_stmt($3, $5, NULL); }
  | T_IF '(' bool_expr ')' block T_ELSE block
    { $$ = create_if_stmt($3, $5, $7); }
  ;

while_stmt
  : T_WHILE '(' bool_expr ')' block
    { $$ = create_while_stmt($3, $5); }
  ;

for_stmt
  : T_FOR ID '=' expression DOTDOT expression block
    { $$ = create_for_stmt($2, $4, $6, $7); }
  ;

loop_forever
  : T_LOOP T_FOREVER block
    { $$ = create_loop_forever($3); }
  ;

command
  : T_SET expression T_COLOR color_expr
    { $$ = create_set_cmd($2, $4); }
  | T_WAIT TIME_LIT
    { $$ = create_wait_cmd($2); }
  | T_ROTATE expression T_DIR direction
    { $$ = create_rotate_cmd($2, $4); }
  | T_FADE expression
    { $$ = create_fade_cmd($2); }
  ;

direction
  : T_LEFT  { $$ = DIR_LEFT; }
  | T_RIGHT { $$ = DIR_RIGHT; }
  ;

/* Expressões são construídas de baixo para cima */
expression
  : expression '+' expression { $$ = create_binary_op('+', $1, $3); }
  | expression '-' expression { $$ = create_binary_op('-', $1, $3); }
  | expression '*' expression { $$ = create_binary_op('*', $1, $3); }
  | expression '/' expression { $$ = create_binary_op('/', $1, $3); }
  | expression '%' expression { $$ = create_binary_op('%', $1, $3); }
  | '-' expression %prec UMINUS { $$ = create_unary_op('-', $2); }
  | '!' expression %prec '!'    { $$ = create_unary_op('!', $2); }
  | INT                         { $$ = create_integer($1); }
  | ID                          { $$ = create_identifier($1); }
  | '(' expression ')'          { $$ = $2; } // Apenas passa o nó interno
  | color_expr                  { $$ = $1; }
  ;

/* Expressões booleanas criam nós de operação binária */
bool_expr
  : rel_expr
    { $$ = $1; }
  | bool_expr OR rel_expr
    { $$ = create_binary_op(OR, $1, $3); }
  ;

rel_expr
  : eq_expr
    { $$ = $1; }
  | rel_expr AND eq_expr
    { $$ = create_binary_op(AND, $1, $3); }
  ;

eq_expr
  : expression
    { $$ = $1; }
  | eq_expr EQ expression
    { $$ = create_binary_op(EQ, $1, $3); }
  | eq_expr NEQ expression
    { $$ = create_binary_op(NEQ, $1, $3); }
  | eq_expr '<' expression
    { $$ = create_binary_op('<', $1, $3); }
  | eq_expr '>' expression
    { $$ = create_binary_op('>', $1, $3); }
  | eq_expr LE expression
    { $$ = create_binary_op(LE, $1, $3); }
  | eq_expr GE expression
    { $$ = create_binary_op(GE, $1, $3); }
  ;

color_expr
  : COLOR_HEX
    { $$ = create_color_hex($1); }
  | T_HSV '(' expression ',' expression ',' expression ')'
    { $$ = create_hsv_color($3, $5, $7); }
  ;
%%

/* 4. IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES */

// Função para alocar memória e checar erros
void* safe_malloc(size_t size) {
  void* ptr = malloc(size);
  if (!ptr) {
    fprintf(stderr, "Erro fatal: falha na alocação de memória.\n");
    exit(1);
  }
  return ptr;
}

// Construtor para lista de statements
NodeList* add_to_list(NodeList* list, AstNode* node) {
  if (!node) return list; // Não adiciona nós nulos (ex: linhas em branco)

  NodeList* new_item = (NodeList*) safe_malloc(sizeof(NodeList));
  new_item->node = node;
  new_item->next = NULL;

  if (!list) { // Se a lista está vazia, este é o primeiro item
      return new_item;
  }

  NodeList* current = list;
  while (current->next != NULL) {
      current = current->next;
  }
  current->next = new_item;
  return list;
}

// Construtores para cada tipo de nó
AstNode* create_strip_decl(int count) {
  StripDeclNode* node = (StripDeclNode*) safe_malloc(sizeof(StripDeclNode));
  node->type = NODE_TYPE_STRIP_DECL;
  node->led_count = count;
  return (AstNode*) node;
}

AstNode* create_assignment(char* id, AstNode* expr) {
  AssignmentNode* node = (AssignmentNode*) safe_malloc(sizeof(AssignmentNode));
  node->type = NODE_TYPE_ASSIGNMENT;
  node->identifier = id;
  node->expression = expr;
  return (AstNode*) node;
}

AstNode* create_if_stmt(AstNode* cond, NodeList* if_block, NodeList* else_block) {
  IfStmtNode* node = (IfStmtNode*) safe_malloc(sizeof(IfStmtNode));
  node->type = NODE_TYPE_IF_STMT;
  node->condition = cond;
  node->if_block = if_block;
  node->else_block = else_block;
  return (AstNode*) node;
}

AstNode* create_while_stmt(AstNode* cond, NodeList* block) {
  WhileStmtNode* node = (WhileStmtNode*) safe_malloc(sizeof(WhileStmtNode));
  node->type = NODE_TYPE_WHILE_STMT;
  node->condition = cond;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_for_stmt(char* id, AstNode* start, AstNode* end, NodeList* block) {
  ForStmtNode* node = (ForStmtNode*) safe_malloc(sizeof(ForStmtNode));
  node->type = NODE_TYPE_FOR_STMT;
  node->identifier = id;
  node->start_expr = start;
  node->end_expr = end;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_loop_forever(NodeList* block) {
  LoopForeverNode* node = (LoopForeverNode*) safe_malloc(sizeof(LoopForeverNode));
  node->type = NODE_TYPE_LOOP_FOREVER;
  node->block = block;
  return (AstNode*) node;
}

AstNode* create_set_cmd(AstNode* index, AstNode* color) {
  SetCmdNode* node = (SetCmdNode*) safe_malloc(sizeof(SetCmdNode));
  node->type = NODE_TYPE_SET_CMD;
  node->index_expr = index;
  node->color_expr = color;
  return (AstNode*) node;
}

// Converte "50ms" para 50, "2s" para 2000
int parse_time_literal(char* time_lit) {
  int len = strlen(time_lit);
  int value = atoi(time_lit);
  if (strcmp(&time_lit[len-2], "ms") == 0) {
      return value;
  }
  if (time_lit[len-1] == 's') {
      return value * 1000;
  }
  return value; // Fallback
}

AstNode* create_wait_cmd(char* time_lit) {
  WaitCmdNode* node = (WaitCmdNode*) safe_malloc(sizeof(WaitCmdNode));
  node->type = NODE_TYPE_WAIT_CMD;
  node->value_ms = parse_time_literal(time_lit);
  free(time_lit); // Liberamos a string copiada pelo Flex
  return (AstNode*) node;
}

AstNode* create_rotate_cmd(AstNode* steps, DirectionType dir) {
  RotateCmdNode* node = (RotateCmdNode*) safe_malloc(sizeof(RotateCmdNode));
  node->type = NODE_TYPE_ROTATE_CMD;
  node->steps_expr = steps;
  node->direction = dir;
  return (AstNode*) node;
}

AstNode* create_fade_cmd(AstNode* amount) {
  FadeCmdNode* node = (FadeCmdNode*) safe_malloc(sizeof(FadeCmdNode));
  node->type = NODE_TYPE_FADE_CMD;
  node->amount_expr = amount;
  return (AstNode*) node;
}

AstNode* create_binary_op(int op, AstNode* left, AstNode* right) {
  BinaryOpNode* node = (BinaryOpNode*) safe_malloc(sizeof(BinaryOpNode));
  node->type = NODE_TYPE_BINARY_OP;
  node->op = op;
  node->left = left;
  node->right = right;
  return (AstNode*) node;
}

AstNode* create_unary_op(int op, AstNode* operand) {
  UnaryOpNode* node = (UnaryOpNode*) safe_malloc(sizeof(UnaryOpNode));
  node->type = NODE_TYPE_UNARY_OP;
  node->op = op;
  node->operand = operand;
  return (AstNode*) node;
}

AstNode* create_integer(int value) {
  IntegerNode* node = (IntegerNode*) safe_malloc(sizeof(IntegerNode));
  node->type = NODE_TYPE_INTEGER;
  node->value = value;
  return (AstNode*) node;
}

AstNode* create_identifier(char* name) {
  IdentifierNode* node = (IdentifierNode*) safe_malloc(sizeof(IdentifierNode));
  node->type = NODE_TYPE_IDENTIFIER;
  node->name = name;
  return (AstNode*) node;
}

AstNode* create_color_hex(char* hex_code) {
  ColorHexNode* node = (ColorHexNode*) safe_malloc(sizeof(ColorHexNode));
  node->type = NODE_TYPE_COLOR_HEX;
  node->hex_code = hex_code;
  return (AstNode*) node;
}

AstNode* create_hsv_color(AstNode* h, AstNode* s, AstNode* v) {
  HsvColorNode* node = (HsvColorNode*) safe_malloc(sizeof(HsvColorNode));
  node->type = NODE_TYPE_COLOR_HSV;
  node->h_expr = h;
  node->s_expr = s;
  node->v_expr = v;
  return (AstNode*) node;
}

void yyerror(const char *s) {
  fprintf(stderr, "Erro sintático: %s\n", s);
}