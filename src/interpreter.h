#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"

typedef struct {
    unsigned char r, g, b;
} ColorRGB;

typedef enum {
    VAL_INT,
    VAL_COLOR,
    VAL_BOOL
} ValueType;

typedef struct {
    ValueType type;
    union {
        int int_val;
        ColorRGB color_val;
        int bool_val;
    } as;
} Value;

typedef struct Symbol {
    char* name;
    Value value;
    struct Symbol* next;
} Symbol;

typedef struct {
    ColorRGB* strip_leds;   
    int strip_size;         
    Symbol* symbol_table;   
    int is_running;      
} InterpreterState;

// funcao principal que inicia a interpretacao
void interpret(NodeList* ast_root);

// funcoes que caminham pela arvore
void execute_statement(InterpreterState* state, AstNode* node);
Value evaluate_expression(InterpreterState* state, AstNode* node);

#endif