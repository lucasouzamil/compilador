#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h" // Precisamos das definições da AST

// Estrutura simples para representar uma cor RGB
typedef struct {
    unsigned char r, g, b;
} ColorRGB;

// Estrutura para um valor genérico (pode ser inteiro, booleano, cor, etc.)
// Usaremos uma "tagged union" para isso.
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

// Estrutura para a Tabela de Símbolos (para guardar variáveis como 'i' do for)
// Implementação simples como lista ligada.
typedef struct Symbol {
    char* name;
    Value value;
    struct Symbol* next;
} Symbol;

// O estado completo do nosso interpretador ("A VM")
typedef struct {
    ColorRGB* strip_leds;   // Array dinâmico para as cores da fita
    int strip_size;         // Tamanho da fita
    Symbol* symbol_table;   // Ponteiro para o início da tabela de símbolos
    int is_running;         // Flag para controlar loops infinitos
} InterpreterState;


// --- Protótipos das Funções Principais ---

// Função principal que inicia a interpretação
void interpret(NodeList* ast_root);

// Funções que caminham pela árvore
void execute_statement(InterpreterState* state, AstNode* node);
Value evaluate_expression(InterpreterState* state, AstNode* node);

#endif // INTERPRETER_H