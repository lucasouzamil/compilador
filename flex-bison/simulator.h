#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "interpreter.h" // Precisamos do InterpreterState

/**
 * @brief Desenha o estado atual da fita de LED no terminal.
 * * @param state O estado do interpretador, contendo a fita de LEDs e seu tamanho.
 */
void simulator_draw_strip(InterpreterState* state);

#endif // SIMULATOR_H