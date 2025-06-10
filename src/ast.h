#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

typedef struct AstNode AstNode;

typedef enum {
    NODE_TYPE_PROGRAM,
    NODE_TYPE_STRIP_DECL,
    NODE_TYPE_SET_CMD,
    NODE_TYPE_WAIT_CMD,
    NODE_TYPE_ROTATE_CMD,
    NODE_TYPE_FADE_CMD,
    NODE_TYPE_ASSIGNMENT,
    NODE_TYPE_IF_STMT,
    NODE_TYPE_WHILE_STMT,
    NODE_TYPE_FOR_STMT,
    NODE_TYPE_LOOP_FOREVER,
    NODE_TYPE_BINARY_OP,
    NODE_TYPE_UNARY_OP,
    NODE_TYPE_INTEGER,
    NODE_TYPE_IDENTIFIER,
    NODE_TYPE_COLOR_HEX,
    NODE_TYPE_COLOR_HSV,
} NodeType;

typedef enum {
    DIR_LEFT,
    DIR_RIGHT
} DirectionType;

typedef struct NodeList {
    AstNode *node;
    struct NodeList *next;
} NodeList;

struct AstNode {
    NodeType type;
};

typedef struct {
    NodeType type;
    int led_count;
} StripDeclNode;

typedef struct {
    NodeType type;
    char* identifier;
    AstNode* expression;
} AssignmentNode;

typedef struct {
    NodeType type;

    AstNode* condition;
    NodeList* if_block;
    NodeList* else_block; // Pode ser NULL
} IfStmtNode;

typedef struct {
    NodeType type;
    AstNode* condition;
    NodeList* block;
} WhileStmtNode;

typedef struct {
    NodeType type;
    char* identifier;
    AstNode* start_expr;
    AstNode* end_expr;
    NodeList* block;
} ForStmtNode;

typedef struct {
    NodeType type;
    NodeList* block;
} LoopForeverNode;

typedef struct {
    NodeType type;
    AstNode* index_expr;
    AstNode* color_expr;
} SetCmdNode;

typedef struct {
    NodeType type;
    int value_ms;
} WaitCmdNode;

typedef struct {
    NodeType type;
    AstNode* steps_expr;
    DirectionType direction;
} RotateCmdNode;

typedef struct {
    NodeType type;
    AstNode* amount_expr;
} FadeCmdNode;

typedef struct {
    NodeType type;
    int op; // Token do operador, ex: '+'
    AstNode* left;
    AstNode* right;
} BinaryOpNode;

typedef struct {
    NodeType type;
    int op;
    AstNode* operand;
} UnaryOpNode;

typedef struct {
    NodeType type;
    int value;
} IntegerNode;

typedef struct {
    NodeType type;
    char* name;
} IdentifierNode;

typedef struct {
    NodeType type;
    char* hex_code;
} ColorHexNode;

typedef struct {
    NodeType type;
    AstNode* h_expr;
    AstNode* s_expr;
    AstNode* v_expr;
} HsvColorNode;

/* portotipos das funcoes construtoras da AST */
AstNode* create_binary_op(int op, AstNode* left, AstNode* right);
AstNode* create_set_command(AstNode* index, AstNode* color);

#endif 