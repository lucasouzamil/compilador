#include <stdio.h>
#include "simulator.h"

void simulator_draw_strip(InterpreterState* state) {
    if (!state || !state->strip_leds || state->strip_size == 0) {
        return;
    }

    // 1. Move o cursor para o início da linha atual.
    // Isso permite que o próximo print sobrescreva a linha, criando a animação.
    printf("\r");

    // 2. Itera por cada LED na fita virtual.
    for (int i = 0; i < state->strip_size; i++) {
        ColorRGB color = state->strip_leds[i];

        // 3. Define a cor de fundo do caractere usando um código de escape ANSI.
        // \x1b[48;2;R;G;Bm define a cor de fundo (background).
        printf("\x1b[48;2;%d;%d;%dm", color.r, color.g, color.b);
        
        // 4. Imprime um espaço em branco, que será colorido pelo código acima,
        // simulando um bloco de LED.
        printf(" "); 
    }

    // 5. Reseta todas as formatações de cor para o padrão do terminal.
    printf("\x1b[0m");

    // 6. Força a "descarga" do buffer de saída para a tela.
    // Essencial para que a animação funcione corretamente sem esperar por uma nova linha.
    fflush(stdout);
}