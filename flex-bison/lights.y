%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int  yylex(void);

/* yyin é declarado pelo Flex */
extern FILE *yyin;
%}

/* ---- valores semânticos ---- */
%union {
  int   ival;   /* números inteiros               */
  char *sval;   /* identificadores, literais etc. */
}


/* ---------- TOKENS ---------- */
%token <ival> INT
%token <sval> ID COLOR_HEX TIME_LIT
%token T_STRIP T_IF T_ELSE T_WHILE T_FOR T_LOOP T_FOREVER
%token T_SET T_COLOR T_WAIT T_ROTATE T_DIR T_FADE
%token T_HSV T_LEFT T_RIGHT
%token EQ NEQ LE GE AND OR DOTDOT
%token NEWLINE

/* ---------- PRECEDÊNCIA ---------- */
%left OR
%left AND
%left EQ NEQ
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right '!'        /* unário */
%right UMINUS

%start program
%%

program
    : /* vazio */
    | program statement
    ;

statement
    : T_STRIP INT NEWLINE
    | assignment NEWLINE
    | if_stmt
    | while_stmt
    | for_stmt
    | loop_forever
    | command NEWLINE
    | NEWLINE                 /* linha em branco */
    ;

/* ---------- blocos ---------- */
block
    : '{' statements '}'          /* NEWLINE opcional vira blank‑stmt */
    ;

statements
    : /* vazio */
    | statements statement
    ;

/* ---------- estruturas de controle ---------- */
assignment
    : ID '=' expression
    ;

if_stmt
    : T_IF '(' bool_expr ')' block
    | T_IF '(' bool_expr ')' block T_ELSE block
    ;

while_stmt
    : T_WHILE '(' bool_expr ')' block
    ;

for_stmt
    : T_FOR ID '=' expression DOTDOT expression block
    ;

loop_forever
    : T_LOOP T_FOREVER block
    ;

/* ---------- comandos LED ---------- */
command
    : T_SET expression T_COLOR color_expr
    | T_WAIT TIME_LIT
    | T_ROTATE expression T_DIR direction
    | T_FADE expression
    ;

direction
    : T_LEFT
    | T_RIGHT
    ;

/* ---------- expressões ---------- */
expression
    : expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '%' expression
    | '-' expression   %prec UMINUS
    | '!' expression   %prec '!'
    | INT
    | ID
    | '(' expression ')'
    | color_expr
    ;

bool_expr
    : bool_expr OR rel_expr
    | rel_expr
    ;

rel_expr
    : rel_expr AND eq_expr
    | eq_expr
    ;

eq_expr
    : expression
    | eq_expr EQ  expression
    | eq_expr NEQ expression
    | eq_expr '<' expression
    | eq_expr '>' expression
    | eq_expr LE  expression
    | eq_expr GE  expression
    ;

/* ---------- literais de cor ---------- */
color_expr
    : COLOR_HEX
    | T_HSV '(' expression ',' expression ',' expression ')'
    ;
%%  /* ---- fim da gramática ---- */

void yyerror(const char *s) { fprintf(stderr,"Erro sintático: %s\n", s); }

/* ---- protótipos exportados pelo Flex ---- */
extern void yyrestart ( FILE * );
extern FILE *yyin;

int main(int argc, char **argv)
{
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror("Erro abrindo arquivo");
            return 1;
        }
        yyrestart(f);          /* faz o scanner ler desse arquivo */
    }
    if (yyparse() == 0)
        puts("Programa válido.");
    else
        puts("Programa inválido.");
    return 0;
}