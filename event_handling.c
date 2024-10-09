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
    input->estado = PLAYING;
}

void handle_event(ALLEGRO_EVENT evento, GameInput* input, Player* player, Projectile* proj, Rect continuar_botao, Rect sair_botao) {
    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        input->mouse_x = evento.mouse.x;
        input->mouse_y = evento.mouse.y;

        if (input->estado == GAME_OVER) {
            // Verifica se o clique está no botão "Continuar"
            if (input->mouse_x >= continuar_botao.x1 && input->mouse_x <= continuar_botao.x2 &&
                input->mouse_y >= continuar_botao.y1 && input->mouse_y <= continuar_botao.y2) {
                // Reinicia o jogador
                destroy_player(player);
                init_player(player);

                // Reinicia o projetil
                destroy_projectile(proj);
                init_projectile(proj);

                // Muda o estado para PLAYING
                input->estado = PLAYING;
                printf("Reiniciando o jogo...\n");
            }

            // Verifica se o clique está no botão "Sair"
            if (input->mouse_x >= sair_botao.x1 && input->mouse_x <= sair_botao.x2 &&
                input->mouse_y >= sair_botao.y1 && input->mouse_y <= sair_botao.y2) {
                // Sair do jogo
                input->sair = true;
                printf("Saindo do jogo...\n");
            }
        }
    }
    else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES ||
        evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        // Atualiza a posição do mouse para efeitos de hover
        input->mouse_x = evento.mouse.x;
        input->mouse_y = evento.mouse.y;
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
