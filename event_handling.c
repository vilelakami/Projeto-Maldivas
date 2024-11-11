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
    Rect continuar_botao, Rect sair_botao, Rect start_button, Rect avancar_botao) {

    // Atualiza a posição do mouse
    if (evento.type == ALLEGRO_EVENT_MOUSE_AXES ||
        evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
        evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
        input->mouse_x = evento.mouse.x;
        input->mouse_y = evento.mouse.y;
    }

    if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        printf("Clique detectado em (%d, %d) no estado %d\n", input->mouse_x, input->mouse_y, *estado);

        // Lida com eventos de clique nos botões
        if (*estado == MENU) {
            // Verifica se o clique está no botão "Start"
            if (input->mouse_x >= start_button.x1 && input->mouse_x <= start_button.x2 &&
                input->mouse_y >= start_button.y1 && input->mouse_y <= start_button.y2) {
                *estado = INTRODUCAO;  // Muda para o estado INTRODUCAO
                printf("Estado mudou para introdução\n");
            }
        }
        else if (*estado == INTRODUCAO) {
            // Verifica se o clique foi dentro da área do botão de avançar
            if (evento.mouse.x >= avancar_botao.x1 && evento.mouse.x <= avancar_botao.x2 &&
                evento.mouse.y >= avancar_botao.y1 && evento.mouse.y <= avancar_botao.y2) {
                *estado = FASE_1;
                printf("Estado mudou para FASE_1 após clique na introdução.\n");
            }
        }


        else if (*estado == GAME_OVER) {
            // Lida com o botão "Continuar"
            if (input->mouse_x >= continuar_botao.x1 && input->mouse_x <= continuar_botao.x2 &&
                input->mouse_y >= continuar_botao.y1 && input->mouse_y <= continuar_botao.y2) {
                destroy_player(player);
                init_player(player);
                destroy_projectile(proj);
                init_projectile(proj);
                *estado = FASE_1;
                printf("Reiniciando o jogo...\n");
            }
            // Lida com o botão "Sair"
            else if (input->mouse_x >= sair_botao.x1 && input->mouse_x <= sair_botao.x2 &&
                input->mouse_y >= sair_botao.y1 && input->mouse_y <= sair_botao.y2) {
                input->sair = true;
                printf("Saindo do jogo...\n");
            }
        }
    }
    // Agora, fora do bloco de clique, tratamos o evento de tecla
    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        input->teclas[evento.keyboard.keycode] = true;

       
      
        // Se pressionar ESC, sair do jogo
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
