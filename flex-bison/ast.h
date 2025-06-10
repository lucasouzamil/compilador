#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

// Forward declaration para permitir ponteiros recursivos
typedef struct AstNode AstNode;

// -----------------------------------------------------------
// 1. TIPOS DE NÓS E ENUMS AUXILIARES
// -----------------------------------------------------------

// Enum para identificar o tipo de cada nó na árvore.
// Essencial para o interpretador saber como processar cada nó.
typedef enum {
    // Nós de Declaração e Estrutura
    NODE_TYPE_PROGRAM,
    NODE_TYPE_STRIP_DECL,

    // Nós de Comando
    NODE_TYPE_SET_CMD,
    NODE_TYPE_WAIT_CMD,
    NODE_TYPE_ROTATE_CMD,
    NODE_TYPE_FADE_CMD,

    // Nós de Controle de Fluxo
    NODE_TYPE_ASSIGNMENT,
    NODE_TYPE_IF_STMT,
    NODE_TYPE_WHILE_STMT,
    NODE_TYPE_FOR_STMT,
    NODE_TYPE_LOOP_FOREVER,

    // Nós de Expressão
    NODE_TYPE_BINARY_OP,
    NODE_TYPE_UNARY_OP,
    NODE_TYPE_INTEGER,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_COLOR_HEX,
    NODE_TYPE_COLOR_HSV,

} NodeType;

// Enum para direções do comando 'rotate'
typedef enum {
    DIR_LEFT,
    DIR_RIGHT
} DirectionType;


// -----------------------------------------------------------
// 2. ESTRUTURA BASE E LISTA DE NÓS
// -----------------------------------------------------------

// Estrutura para uma lista de nós (usada em blocos de código `{...}`)
typedef struct NodeList {
    AstNode *node;          // O nó atual na lista
    struct NodeList *next;  // Ponteiro para o próximo elemento da lista
} NodeList;

// Estrutura base que todos os nós da AST compartilharão.
// O campo 'type' é usado para fazer o "cast" para a struct específica.
struct AstNode {
    NodeType type;
};


// -----------------------------------------------------------
// 3. NÓS DE DECLARAÇÃO E CONTROLE DE FLUXO
// -----------------------------------------------------------

// Nó para a declaração `strip <INTEGER>`
typedef struct {
    NodeType type;      // NODE_TYPE_STRIP_DECL
    int led_count;      // Quantidade de LEDs
} StripDeclNode;

// Nó para atribuições `identificador = expressao`
typedef struct {
    NodeType type;      // NODE_TYPE_ASSIGNMENT
    char* identifier;   // Nome da variável
    AstNode* expression; // Ponteiro para a expressão à direita
} AssignmentNode;

// Nó para a estrutura `if (cond) { ... } else { ... }`
typedef struct {
    NodeType type;          // NODE_TYPE_IF_STMT
    AstNode* condition;     // Expressão booleana da condição
    NodeList* if_block;     // Lista de statements do bloco 'if'
    NodeList* else_block;   // Lista de statements do bloco 'else' (pode ser NULL)
} IfStmtNode;

// Nó para a estrutura `while (cond) { ... }`
typedef struct {
    NodeType type;          // NODE_TYPE_WHILE_STMT
    AstNode* condition;     // Expressão booleana da condição
    NodeList* block;        // Lista de statements do loop
} WhileStmtNode;

// Nó para a estrutura `for i = start..end { ... }`
typedef struct {
    NodeType type;          // NODE_TYPE_FOR_STMT
    char* identifier;       // Nome da variável do loop (ex: "i")
    AstNode* start_expr;    // Expressão do valor inicial
    AstNode* end_expr;      // Expressão do valor final
    NodeList* block;        // Lista de statements do corpo do loop
} ForStmtNode;

// Nó para a estrutura `loop forever { ... }`
typedef struct {
    NodeType type;      // NODE_TYPE_LOOP_FOREVER
    NodeList* block;    // Lista de statements do loop infinito
} LoopForeverNode;


// -----------------------------------------------------------
// 4. NÓS DE COMANDOS DEDICADOS
// -----------------------------------------------------------

// Nó para o comando `set <expr> color <color_expr>`
typedef struct {
    NodeType type;          // NODE_TYPE_SET_CMD
    AstNode* index_expr;    // Expressão que define o(s) LED(s)
    AstNode* color_expr;    // Expressão que define a cor
} SetCmdNode;

// Nó para o comando `wait <TIME_LITERAL>`
typedef struct {
    NodeType type;      // NODE_TYPE_WAIT_CMD
    int value_ms;       // Valor do tempo sempre em milissegundos
} WaitCmdNode;

// Nó para o comando `rotate <expr> dir <direction>`
typedef struct {
    NodeType type;          // NODE_TYPE_ROTATE_CMD
    AstNode* steps_expr;    // Expressão que define quantos passos rotacionar
    DirectionType direction; // Direção da rotação (LEFT ou RIGHT)
} RotateCmdNode;

// Nó para o comando `fade <expr>`
typedef struct {
    NodeType type;          // NODE_TYPE_FADE_CMD
    AstNode* amount_expr;   // Expressão que define a intensidade do fade
} FadeCmdNode;


// -----------------------------------------------------------
// 5. NÓS DE EXPRESSÃO
// -----------------------------------------------------------

// Nó para operações binárias (ex: a + b, x > 5, p && q)
typedef struct {
    NodeType type;      // NODE_TYPE_BINARY_OP
    int op;             // O operador (ex: '+', EQ, AND). Vem dos tokens do Bison.
    AstNode* left;      // Expressão da esquerda
    AstNode* right;     // Expressão da direita
} BinaryOpNode;

// Nó para operações unárias (ex: -5, !flag)
typedef struct {
    NodeType type;      // NODE_TYPE_UNARY_OP
    int op;             // O operador (ex: '-', '!')
    AstNode* operand;   // A expressão a ser operada
} UnaryOpNode;

// Nós "folha" da árvore (não possuem filhos)
typedef struct {
    NodeType type;      // NODE_TYPE_INTEGER
    int value;
} IntegerNode;

typedef struct {
    NodeType type;      // NODE_TYPE_IDENTIFIER
    char* name;
} IdentifierNode;

typedef struct {
    NodeType type;      // NODE_TYPE_COLOR_HEX
    char* hex_code;     // String no formato "#RRGGBB"
} ColorHexNode;

// Nó para a função de cor `hsv(h, s, v)`
typedef struct {
    NodeType type;      // NODE_TYPE_COLOR_HSV
    AstNode* h_expr;    // Expressão para Hue
    AstNode* s_expr;    // Expressão para Saturation
    AstNode* v_expr;    // Expressão para Value
} HsvColorNode;


// -----------------------------------------------------------
// 6. FUNÇÕES CONSTRUTORAS (PROTÓTIPOS)
// -----------------------------------------------------------
// É uma boa prática criar funções para alocar e inicializar cada
// tipo de nó, para manter o arquivo do Bison (`.y`) mais limpo.

AstNode* create_binary_op(int op, AstNode* left, AstNode* right);
AstNode* create_set_command(AstNode* index, AstNode* color);
// ... protótipos para todas as outras estruturas.

#endif // AST_H