#include <stdio.h>
#include "interpreter.h"

extern FILE* yyin;
extern int yyparse(void);
extern void yyrestart(FILE*);
extern NodeList* ast_root;

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            perror("Erro abrindo arquivo");
            return 1;
        }
        yyrestart(f);
    }

    if (yyparse() == 0) {
        printf("Programa válido. Análise sintática concluída.\n");
        if (ast_root) {
            interpret(ast_root);
        } else {
            puts("Programa vazio, AST não gerada.");
        }
    } else {
        puts("Programa inválido.");
    }

    return 0;
}