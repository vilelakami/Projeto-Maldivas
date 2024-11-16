#include "event_handling.h"
#include <stdio.h>

// Variável global para o temporizador dos projéteis
extern float time_since_last_projectile;

void init_game_input(GameInput* input) {
    input->sair = false;
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        input->teclas[i] = false;
    }
    input->mouse_x = 0;
    input->mouse_y = 0;
}

void handle_event(ALLEGRO_EVENT evento, GameInput* input, GameState* estado, Player* player, Projectile* projectiles, int num_projectiles,
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

            // Verifica se o clique está no botão "Start"
            if (input->mouse_x >= start_button.x1 && input->mouse_x <= start_button.x2 &&
                input->mouse_y >= start_button.y1 && input->mouse_y <= start_button.y2) {

                // Muda o estado para Prologo
                *estado = PROLOGO;
                printf("Estado mudou para prologo\n");
            }

            // Verifica se o clique está no botão "Creditos"
            else if (input->mouse_x >= credits_button.x1 && input->mouse_x <= credits_button.x2 &&
                input->mouse_y >= credits_button.y1 && input->mouse_y <= credits_button.y2) {

                // Muda o estado para Créditos
                *estado = CREDITOS;
                printf("Estado mudou para os créditos\n");
            }

            // Verifica se o clique está no botão "Instruções"
            else if (input->mouse_x >= Instructs_button.x1 && input->mouse_x <= Instructs_button.x2 &&
                input->mouse_y >= Instructs_button.y1 && input->mouse_y <= Instructs_button.y2) {

                // Muda o estado para Instruções
                *estado = INSTRUÇÕES;
                printf("Estado mudou para as instruções\n");
            }
        }
        else if (*estado == PROLOGO) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {

                // Muda o estado para Prologo 2 quando o botão "Continua" for clicado
                *estado = PROLOGO2;
                printf("Estado mudou para Prologo 2\n");
            }
        }
        else if (*estado == PROLOGO2) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {

                // Muda o estado para Prologo 3 quando o botão "Continua" for clicado
                *estado = PROLOGO3;
                printf("Estado mudou para Prologo 3\n");
            }
        }
        else if (*estado == PROLOGO3) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {

                // Muda o estado para Prologo 4 quando o botão "Continua" for clicado
                *estado = PROLOGO4;
                printf("Estado mudou para Prologo 4\n");
            }
        }
        else if (*estado == PROLOGO4) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {

                // Muda o estado para Menu quando o botão "Continua" for clicado
                *estado = FASE_1;
                printf("Estado mudou para Fase 1\n");
            }
        }
        else if (*estado == GAME_OVER) {

            // Verifica se o clique está no botão "Continuar"
            if (input->mouse_x >= continuar_botao.x1 && input->mouse_x <= continuar_botao.x2 &&
                input->mouse_y >= continuar_botao.y1 && input->mouse_y <= continuar_botao.y2) {

                // Reinicia o jogador e os projéteis
                destroy_player(player);
                init_player(player);

                for (int i = 0; i < num_projectiles; ++i) {
                    destroy_projectile(&projectiles[i]);
                    init_projectile(&projectiles[i]);
                    projectiles[i].active = false;
                }

                // Reseta o temporizador de criação dos projéteis
                time_since_last_projectile = 0.0f;

                // Muda o estado para FASE_1
                *estado = FASE_1;
                printf("Reiniciando o jogo...\n");
            }

            // Verifica se o clique está no botão "Sair"
            else if (input->mouse_x >= sair_botao.x1 && input->mouse_x <= sair_botao.x2 &&
                input->mouse_y >= sair_botao.y1 && input->mouse_y <= sair_botao.y2) {
                input->sair = true;
                printf("Saindo do jogo...\n");
            }
        }

        else if (*estado == CREDITOS || *estado == INSTRUÇÕES) {
            // Se clicar em qualquer lugar na tela de créditos ou instruções, volta para o menu
            *estado = MENU;
            printf("Voltando para o menu principal\n");
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