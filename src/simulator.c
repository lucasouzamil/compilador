#include <stdio.h>
#include "simulator.h"

void simulator_draw_strip(InterpreterState* state) {
    if (!state || !state->strip_leds || state->strip_size == 0) {
        return;
    }

    printf("\r");

    for (int i = 0; i < state->strip_size; i++) {
        ColorRGB color = state->strip_leds[i];
        printf("\x1b[48;2;%d;%d;%dm", color.r, color.g, color.b);
        printf(" "); 
    }

    printf("\x1b[0m");
    fflush(stdout);
}