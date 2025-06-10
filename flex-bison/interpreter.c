#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcmp
#include <unistd.h> // Para usleep (pausa em microsegundos)
#include <math.h> // Conversao hsv to rgb

#include "interpreter.h"
#include "simulator.h"
#include "lights.tab.h"

// --- Funções Auxiliares (protótipos) ---
void symbol_set(InterpreterState* state, char* name, Value value);
Value symbol_get(InterpreterState* state, char* name);
void free_symbol_table(Symbol* table);
ColorRGB hsv_to_rgb(float h, float s, float v);


// --- Função Principal ---
void interpret(NodeList* ast_root) {
    // 1. Inicializa o estado do interpretador
    InterpreterState state;
    state.strip_leds = NULL;
    state.strip_size = 0;
    state.symbol_table = NULL;
    state.is_running = 1;

    printf("\n--- Iniciando Interpretador ---\n");

    // 2. Percorre a lista de statements da AST
    NodeList* current = ast_root;
    while (current != NULL) {
        if (current->node) {
            execute_statement(&state, current->node);
        }
        current = current->next;
    }

    printf("--- Fim da Interpretação ---\n");

    // 3. Libera memória alocada
    free(state.strip_leds);
    free_symbol_table(state.symbol_table);
}


// --- Executor de Statements ---
void execute_statement(InterpreterState* state, AstNode* node) {
    if (!state->is_running || !node) return;

    switch (node->type) {
        case NODE_TYPE_STRIP_DECL: {
            StripDeclNode* decl = (StripDeclNode*)node;
            if (state->strip_leds) free(state->strip_leds); // Libera fita antiga, se houver
            state->strip_size = decl->led_count;
            state->strip_leds = (ColorRGB*)calloc(state->strip_size, sizeof(ColorRGB));
            printf("Interpretador: Fita de LED inicializada com %d LEDs.\n", state->strip_size);
            break;
        }

        case NODE_TYPE_SET_CMD: {
            if (state->strip_size == 0) {
                fprintf(stderr, "Erro de Execução: Fita de LED não inicializada. Use 'strip [tamanho]' primeiro.\n");
                state->is_running = 0; 
                break;
            }
            
            SetCmdNode* set_cmd = (SetCmdNode*)node;
            Value index_val = evaluate_expression(state, set_cmd->index_expr);
            Value color_val = evaluate_expression(state, set_cmd->color_expr);

            if (index_val.type == VAL_INT && color_val.type == VAL_COLOR) {
                int index = index_val.as.int_val;
                if (index >= 0 && index < state->strip_size) {
                    state->strip_leds[index] = color_val.as.color_val;
                }
                //printf("Interpretador: Setando LED %d ...\n", index);
            } else {
                // ADICIONE ESTE BLOCO ELSE
                //printf("DEBUG: Falha na condição do SET_CMD. Tipo do índice: %d, Tipo da cor: %d\n", index_val.type, color_val.type);
            }
            break;
        }

        case NODE_TYPE_ASSIGNMENT: {
            AssignmentNode* assign_node = (AssignmentNode*)node;
            Value expr_val = evaluate_expression(state, assign_node->expression);
            symbol_set(state, assign_node->identifier, expr_val);
            break;
        }

        case NODE_TYPE_IF_STMT: {
            IfStmtNode* if_node = (IfStmtNode*)node;
            Value cond_val = evaluate_expression(state, if_node->condition);

            // Se a condição for verdadeira (qualquer valor inteiro diferente de 0)
            if (cond_val.type == VAL_BOOL && cond_val.as.bool_val != 0) {
                // Executa o bloco 'if'
                NodeList* body = if_node->if_block;
                while (body != NULL) {
                    execute_statement(state, body->node);
                    body = body->next;
                }
            } else if (if_node->else_block) { // Senão, se houver um bloco 'else'
                // Executa o bloco 'else'
                NodeList* body = if_node->else_block;
                while (body != NULL) {
                    execute_statement(state, body->node);
                    body = body->next;
                }
            }
            break;
        }

        case NODE_TYPE_FOR_STMT: {
            //printf("DEBUG: Entrando no FOR_STMT.\n");
            ForStmtNode* for_node = (ForStmtNode*)node;
            Value start_val = evaluate_expression(state, for_node->start_expr);
            Value end_val = evaluate_expression(state, for_node->end_expr);

            if (start_val.type == VAL_INT && end_val.type == VAL_INT) {
                for (int i = start_val.as.int_val; i <= end_val.as.int_val; i++) {
                    //printf("DEBUG: Loop for, i = %d\n", i);
                    // Define/atualiza a variável de loop na tabela de símbolos
                    Value loop_var_val;
                    loop_var_val.type = VAL_INT;
                    loop_var_val.as.int_val = i;
                    symbol_set(state, for_node->identifier, loop_var_val);

                    // Executa o corpo do loop
                    NodeList* body = for_node->block;
                    while (body != NULL) {
                        execute_statement(state, body->node);
                        body = body->next;
                    }
                }
                simulator_draw_strip(state);
            }
            break;
        }
        
        case NODE_TYPE_LOOP_FOREVER: {
            LoopForeverNode* loop_node = (LoopForeverNode*)node;
            // Remova o printf de "Entrando em loop infinito" para não poluir a tela

            while (state->is_running) {
                NodeList* body = loop_node->block;
                while (body != NULL) {
                    execute_statement(state, body->node);
                    body = body->next;
                }
                // Após executar todos os comandos do bloco (rotate, wait),
                // redesenha a fita com as novas cores.
                simulator_draw_strip(state); // <-- ADICIONE AQUI
            }
            break;
        }
        
        case NODE_TYPE_WAIT_CMD: {
            WaitCmdNode* wait_node = (WaitCmdNode*)node;
            // usleep espera em microsegundos, então convertemos de ms
            usleep(wait_node->value_ms * 1000); 
            // TESTE: Imprime a ação para vermos o que está acontecendo
            //printf("Interpretador: Aguardando por %d ms.\n", wait_node->value_ms);
            break;
        }
        
        case NODE_TYPE_ROTATE_CMD: {
            RotateCmdNode* rot_node = (RotateCmdNode*)node;
            Value steps_val = evaluate_expression(state, rot_node->steps_expr);
            if (steps_val.type != VAL_INT || state->strip_size == 0) break;

            int steps = steps_val.as.int_val % state->strip_size;
            if (steps == 0) break;

            // Cria um buffer temporário para a rotação
            ColorRGB* temp_strip = (ColorRGB*)malloc(state->strip_size * sizeof(ColorRGB));
            memcpy(temp_strip, state->strip_leds, state->strip_size * sizeof(ColorRGB));

            for (int i = 0; i < state->strip_size; i++) {
                int source_index;
                if (rot_node->direction == DIR_RIGHT) {
                    source_index = (i - steps + state->strip_size) % state->strip_size;
                } else { // DIR_LEFT
                    source_index = (i + steps) % state->strip_size;
                }
                state->strip_leds[i] = temp_strip[source_index];
            }
            free(temp_strip);
            break;
        }

        default:
            fprintf(stderr, "Erro de interpretação: Statement de tipo %d não implementado.\n", node->type);
            break;
    }
}


// --- Avaliador de Expressões ---
Value evaluate_expression(InterpreterState* state, AstNode* node) {
    Value result;
    result.type = VAL_INT; // Valor padrão
    result.as.int_val = 0;

    if (!node) return result;

    switch (node->type) {
        case NODE_TYPE_INTEGER: {
            result.type = VAL_INT;
            result.as.int_val = ((IntegerNode*)node)->value;
            break;
        }

        // REMOVA ESTE BLOCO INTEIRO DE DENTRO DE execute_statement
        case NODE_TYPE_UNARY_OP: {
            UnaryOpNode* un_op = (UnaryOpNode*)node;
            Value operand_val = evaluate_expression(state, un_op->operand);

            // Se for negação numérica (ex: -1)
            if (un_op->op == '-' && operand_val.type == VAL_INT) {
                result.type = VAL_INT;
                result.as.int_val = -operand_val.as.int_val;
            } 
            // Se for negação lógica (ex: !verdadeiro)
            else if (un_op->op == '!' && operand_val.type == VAL_BOOL) {
                result.type = VAL_BOOL;
                result.as.bool_val = !operand_val.as.bool_val;
            }
            break;
        }
                
        case NODE_TYPE_IDENTIFIER: {
            return symbol_get(state, ((IdentifierNode*)node)->name);
        }

        case NODE_TYPE_COLOR_HEX: {
            ColorHexNode* color_node = (ColorHexNode*)node;
            result.type = VAL_COLOR;
            long hex_val = strtol(color_node->hex_code + 1, NULL, 16);
            result.as.color_val.r = (hex_val >> 16) & 0xFF;
            result.as.color_val.g = (hex_val >> 8) & 0xFF;
            result.as.color_val.b = hex_val & 0xFF;
            break;
        }
        
        case NODE_TYPE_COLOR_HSV: {
            HsvColorNode* hsv_node = (HsvColorNode*)node;
            Value h_val = evaluate_expression(state, hsv_node->h_expr);
            Value s_val = evaluate_expression(state, hsv_node->s_expr);
            Value v_val = evaluate_expression(state, hsv_node->v_expr);

            result.type = VAL_COLOR;
            if (h_val.type == VAL_INT && s_val.type == VAL_INT && v_val.type == VAL_INT) {
                // Normaliza os valores para o algoritmo (H: 0-360, S/V: 0-1)
                result.as.color_val = hsv_to_rgb((float)h_val.as.int_val, (float)s_val.as.int_val, (float)v_val.as.int_val);
            } else {
                result.as.color_val = (ColorRGB){0,0,0}; // Preto em caso de erro
            }
            break;
        }

        case NODE_TYPE_BINARY_OP: {
            BinaryOpNode* bin_op = (BinaryOpNode*)node;
            Value left = evaluate_expression(state, bin_op->left);
            Value right = evaluate_expression(state, bin_op->right);

            if (left.type == VAL_INT && right.type == VAL_INT) {
                // Operações que retornam um booleano (verdadeiro/falso)
                if (bin_op->op == EQ || bin_op->op == NEQ || bin_op->op == '<' || bin_op->op == '>' || bin_op->op == LE || bin_op->op == GE) {
                    result.type = VAL_BOOL;
                    switch(bin_op->op) {
                        case EQ:  result.as.bool_val = (left.as.int_val == right.as.int_val); break;
                        case NEQ: result.as.bool_val = (left.as.int_val != right.as.int_val); break;
                        case '<': result.as.bool_val = (left.as.int_val < right.as.int_val); break;
                        case '>': result.as.bool_val = (left.as.int_val > right.as.int_val); break;
                        case LE:  result.as.bool_val = (left.as.int_val <= right.as.int_val); break;
                        case GE:  result.as.bool_val = (left.as.int_val >= right.as.int_val); break;
                    }
                } else { // Operações aritméticas que retornam um inteiro
                    result.type = VAL_INT;
                    switch(bin_op->op) {
                        case '+': result.as.int_val = left.as.int_val + right.as.int_val; break;
                        case '-': result.as.int_val = left.as.int_val - right.as.int_val; break;
                        case '*': result.as.int_val = left.as.int_val * right.as.int_val; break;
                        case '/': result.as.int_val = left.as.int_val / right.as.int_val; break;
                        case '%': result.as.int_val = left.as.int_val % right.as.int_val; break;
                    }
                }
            }
            break;
        }
        
        default:
            fprintf(stderr, "Erro de avaliação: Expressão de tipo %d não implementada.\n", node->type);
            break;
    }
    return result;
}

// --- Funções da Tabela de Símbolos ---

void symbol_set(InterpreterState* state, char* name, Value value) {
    Symbol* current = state->symbol_table;
    // Primeiro, verifica se o símbolo já existe para atualizá-lo
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    // Se não existe, cria um novo e adiciona no início da lista
    Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->value = value;
    new_sym->next = state->symbol_table;
    state->symbol_table = new_sym;
}

Value symbol_get(InterpreterState* state, char* name) {
    Symbol* current = state->symbol_table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    // Se não encontrou, retorna 0 por padrão
    fprintf(stderr, "Aviso: Variável '%s' não encontrada. Usando valor 0.\n", name);
    Value default_val;
    default_val.type = VAL_INT;
    default_val.as.int_val = 0;
    return default_val;
}

void free_symbol_table(Symbol* table) {
    while (table != NULL) {
        Symbol* next = table->next;
        free(table->name);
        free(table);
        table = next;
    }
}

// --- Funções de Conversão de Cor ---

// Converte de HSV (Hue, Saturation, Value) para RGB
// h: 0-359, s: 0-1, v: 0-1 (usaremos int para simplificar e converteremos internamente)
ColorRGB hsv_to_rgb(float h, float s, float v) {
    float C = v * s;
    float H_prime = fmod(h / 60.0, 6);
    float X = C * (1 - fabs(fmod(H_prime, 2) - 1));
    float m = v - C;
    
    float r_temp, g_temp, b_temp;

    if (H_prime >= 0 && H_prime < 1) { r_temp = C; g_temp = X; b_temp = 0; }
    else if (H_prime >= 1 && H_prime < 2) { r_temp = X; g_temp = C; b_temp = 0; }
    else if (H_prime >= 2 && H_prime < 3) { r_temp = 0; g_temp = C; b_temp = X; }
    else if (H_prime >= 3 && H_prime < 4) { r_temp = 0; g_temp = X; b_temp = C; }
    else if (H_prime >= 4 && H_prime < 5) { r_temp = X; g_temp = 0; b_temp = C; }
    else { r_temp = C; g_temp = 0; b_temp = X; }

    ColorRGB final_color;
    final_color.r = (unsigned char)((r_temp + m) * 255);
    final_color.g = (unsigned char)((g_temp + m) * 255);
    final_color.b = (unsigned char)((b_temp + m) * 255);

    return final_color;
}