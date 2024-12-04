#include "event_handling.h"
#include "game_state.h"
#include "constants.h"
#include "interacoes.h"
#include "player.h"
#include "projectile.h"
#include "ui.h"
#include <allegro5/allegro.h>

void init_game_input(GameInput* input) {
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
        input->teclas[i] = false;
    }
    input->mouse_x = 0;
    input->mouse_y = 0;
    input->sair = false;
}

void handle_event(ALLEGRO_EVENT evento, GameInput* input, GameState* estado, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button, Interacoes* interacoes, Rect botao_sair_vitoria, Rect botao_menu_vitoria) {

    if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        input->sair = true;
    }
    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        input->teclas[evento.keyboard.keycode] = true;

        if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            input->sair = true;
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_F) {
            if (player->perto_do_obstaculo_2 && !interacoes->interagiu_obstaculo_2) {
                interacoes->interagiu_obstaculo_2 = true;
                interacoes->contador_interacoes++;
                printf("Interagiu com o obstáculo 2.\n");
            }

            if (player->perto_do_obstaculo_3 && !interacoes->interagiu_obstaculo_3) {
                interacoes->interagiu_obstaculo_3 = true;
                interacoes->contador_interacoes++;
                printf("Interagiu com o obstáculo 3.\n");
            }
        }
    }
    else if (evento.type == ALLEGRO_EVENT_KEY_UP) {
        input->teclas[evento.keyboard.keycode] = false;
    }
    else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) {
        input->mouse_x = evento.mouse.x;
        input->mouse_y = evento.mouse.y;
    }
    else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (*estado == MENU) {
            if (input->mouse_x >= start_button.x1 && input->mouse_x <= start_button.x2 &&
                input->mouse_y >= start_button.y1 && input->mouse_y <= start_button.y2) {
                reset_game(player, projectiles, num_projectiles, interacoes);
                *estado = PROLOGO;
            }
            else if (input->mouse_x >= credits_button.x1 && input->mouse_x <= credits_button.x2 &&
                input->mouse_y >= credits_button.y1 && input->mouse_y <= credits_button.y2) {
                *estado = CREDITOS;
            }
            else if (input->mouse_x >= Instructs_button.x1 && input->mouse_x <= Instructs_button.x2 &&
                input->mouse_y >= Instructs_button.y1 && input->mouse_y <= Instructs_button.y2) {
                *estado = INSTRUÇÕES;
            }
        }
        else if (*estado == PROLOGO || *estado == PROLOGO2 || *estado == PROLOGO3 || *estado == PROLOGO4) {
            if (input->mouse_x >= prologo_button.x1 && input->mouse_x <= prologo_button.x2 &&
                input->mouse_y >= prologo_button.y1 && input->mouse_y <= prologo_button.y2) {
                // Avança para a próxima tela do prólogo ou inicia o jogo
                if (*estado == PROLOGO) {
                    *estado = PROLOGO2;
                }
                else if (*estado == PROLOGO2) {
                    *estado = PROLOGO3;
                }
                else if (*estado == PROLOGO3) {
                    *estado = PROLOGO4;
                }
                else if (*estado == PROLOGO4) {
                    *estado = FASE_1;
                }
            }
        }
        else if (*estado == GAME_OVER) {
            if (input->mouse_x >= continuar_botao.x1 && input->mouse_x <= continuar_botao.x2 &&
                input->mouse_y >= continuar_botao.y1 && input->mouse_y <= continuar_botao.y2) {
                // Reiniciar o jogo
                destroy_player(player);
                init_player(player);

                for (int i = 0; i < num_projectiles; ++i) {
                    destroy_projectile(&projectiles[i]);
                    init_projectile(&projectiles[i]);
                    projectiles[i].active = false;
                }

                extern float time_since_last_projectile;
                time_since_last_projectile = 0.0f;

                init_interacoes(interacoes);

                *estado = FASE_1;
            }
            else if (input->mouse_x >= sair_botao.x1 && input->mouse_x <= sair_botao.x2 &&
                input->mouse_y >= sair_botao.y1 && input->mouse_y <= sair_botao.y2) {
                // Sair do jogo
                input->sair = true;
            }
        }
        else if (*estado == VITORIA) {
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (input->mouse_x >= botao_sair_vitoria.x1 && input->mouse_x <= botao_sair_vitoria.x2 &&
                    input->mouse_y >= botao_sair_vitoria.y1 && input->mouse_y <= botao_sair_vitoria.y2) {
                    // Sair do jogo
                    input->sair = true;
                }
                else if (input->mouse_x >= botao_menu_vitoria.x1 && input->mouse_x <= botao_menu_vitoria.x2 &&
                    input->mouse_y >= botao_menu_vitoria.y1 && input->mouse_y <= botao_menu_vitoria.y2) {
                    reset_game(player, projectiles, num_projectiles, interacoes);
                    *estado = MENU;
                }
            }
        }

        else if (*estado == CREDITOS || *estado == INSTRUÇÕES) {
            // Voltar ao menu ao clicar em qualquer lugar
            *estado = MENU;
        }
    }
}
