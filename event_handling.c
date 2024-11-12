// event_handling.c
#include "event_handling.h"
#include <stdio.h>

void init_game_input(GameInput* input) {
    input->sair = false;
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        input->teclas[i] = false;
    }
    input->mouse_x = 0;
    input->mouse_y = 0;
}

void handle_event(ALLEGRO_EVENT evento, GameInput* input, GameState* estado, Player* player, Projectile* proj,
    Rect continuar_botao, Rect sair_botao, Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button) {
    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES ||
        evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
        evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        input->mouse_x = evento.mouse.x;
        input->mouse_y = evento.mouse.y;
    }

    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        printf("Clique detectado em (%d, %d) no estado %d\n", input->mouse_x, input->mouse_y, *estado);

        if (*estado == MENU) {
            // Verifica se o clique est� no bot�o "Start"
            if (input->mouse_x >= start_button.x1 && input->mouse_x <= start_button.x2 &&
                input->mouse_y >= start_button.y1 && input->mouse_y <= start_button.y2) {
                // Muda o estado para Prologo
                *estado = PROLOGO;
                printf("Estado mudou para prologo\n");
            }

            if (input->mouse_x >= credits_button.x1 && input->mouse_x <= credits_button.x2 &&
                input->mouse_y >= credits_button.y1 && input->mouse_y <= credits_button.y2) {
                // Muda o estado para Prologo
                *estado = CREDITOS;
                printf("Estado mudou para os cr�ditos\n");
            }

            if (input->mouse_x >= Instructs_button.x1 && input->mouse_x <= Instructs_button.x2 &&
                input->mouse_y >= Instructs_button.y1 && input->mouse_y <= Instructs_button.y2) {
                // Muda o estado para Prologo
                *estado = INSTRU��ES;
                printf("Estado mudou para as instru��es\n");
            }

        }

        else if (*estado == PROLOGO) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {
                // Muda o estado para FASE_1 quando o bot�o "Avan�ar Prologo" for clicado
                *estado = FASE_1;
                printf("Estado mudou para FASE 1\n");
            }
        }
        else if (*estado == GAME_OVER) {
            // Verifica se o clique est� no bot�o "Continuar"
            if (input->mouse_x >= continuar_botao.x1 && input->mouse_x <= continuar_botao.x2 &&
                input->mouse_y >= continuar_botao.y1 && input->mouse_y <= continuar_botao.y2) {
                // Reinicia o jogador e o proj�til
                destroy_player(player);
                init_player(player);
                destroy_projectile(proj);
                init_projectile(proj);

                // Muda o estado para FASE_1
                *estado = FASE_1;
                printf("Reiniciando o jogo...\n");
            }// Verifica se o clique est� no bot�o "Sair"
                else if (input->mouse_x >= sair_botao.x1 && input->mouse_x <= sair_botao.x2 &&
                input->mouse_y >= sair_botao.y1 && input->mouse_y <= sair_botao.y2) {
                input->sair = true;
                printf("Saindo do jogo...\n");
            }
        }
    }
    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        input->teclas[evento.keyboard.keycode] = true;

        if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            input->sair = true;
        }
    }
    else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
        input->teclas[evento.keyboard.keycode] = false;
    }
    else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        input->sair = true;
    }
}
