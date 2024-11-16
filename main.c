#include "constants.h"
#include "resources.h"
#include "event_handling.h"
#include "game_logic.h"
#include "rendering.h"
#include "player.h"
#include "projectile.h"
#include "collision.h"
#include "ui.h"
#include "game_state.h"
#include "rect.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdlib.h>
#include <time.h>

// Variável global para o temporizador dos projéteis
float time_since_last_projectile = 0.0f;

int main() {
    // Inicialização do Allegro e addons
    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar o Allegro.\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro ao inicializar o addon de imagem.\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erro ao inicializar o addon de primitivas.\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "Erro ao instalar o teclado.\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "Erro ao instalar o mouse.\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "Erro ao inicializar o addon de fontes.\n");
        return -1;
    }

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Criação da janela
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Erro ao criar o display.\n");
        return -1;
    }

    al_set_window_title(display, "Chernobyl Game");

    // Carrega recursos
    Resources res;
    if (!load_resources(&res)) {
        al_destroy_display(display);
        return -1;
    }

    // Define o ícone do display
    if (res.icon) {
        al_set_display_icon(display, res.icon);
    }

    // Cria a fila de eventos
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (!queue) {
        fprintf(stderr, "Erro ao criar a fila de eventos.\n");
        destroy_resources(&res);
        al_destroy_display(display);
        return -1;
    }
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());

    // Cria o temporizador para FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "Erro ao criar o temporizador.\n");
        al_destroy_event_queue(queue);
        destroy_resources(&res);
        al_destroy_display(display);
        return -1;
    }
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    // Inicializa o jogador
    Player player;
    init_player(&player);

    // Inicializa os projéteis
    Projectile projectiles[MAX_PROJECTILES];
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        init_projectile(&projectiles[i]);
        projectiles[i].active = false; // Define todos os projéteis como inativos
    }

    // Inicializa os inputs do jogo
    GameInput input;
    init_game_input(&input);

    // Define retângulos para os botões
    Rect continuar_botao = { BOTAO_CONTINUAR_X1, BOTAO_CONTINUAR_Y1, BOTAO_CONTINUAR_X2, BOTAO_CONTINUAR_Y2 };
    Rect sair_botao = { BOTAO_SAIR_X1, BOTAO_SAIR_Y1, BOTAO_SAIR_X2, BOTAO_SAIR_Y2 };

    // Definir o botão "Start"
    Rect start_button = {
        SCREEN_WIDTH / 2 - 100, // x1
        SCREEN_HEIGHT / 2 - 25, // y1
        SCREEN_WIDTH / 2 + 100, // x2
        SCREEN_HEIGHT / 2 + 25  // y2
    };

    Rect credits_button = {
         SCREEN_WIDTH / 2 - 100, // x1
         SCREEN_HEIGHT / 2 + 35, // y1
         SCREEN_WIDTH / 2 + 100, // x2
         SCREEN_HEIGHT / 2 + 85  // y2
    };

    Rect Instructs_button = {
         SCREEN_WIDTH / 2 - 100, // x1
         SCREEN_HEIGHT / 2 + 95, // y1
         SCREEN_WIDTH / 2 + 100, // x2
         SCREEN_HEIGHT / 2 + 145  // y2
    };

    Rect prologo_button = { 907, 75, 1049, 112 };

    // Variáveis para rastrear o delta_time
    double tempo_anterior = al_get_time();
    time_since_last_projectile = 0.0f; // Inicializa o temporizador

    // Inicializando o estado atual
    GameState estado = MENU;

    // Loop principal do jogo
    while (!input.sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(queue, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            // Calcula o delta_time
            double tempo_atual = al_get_time();
            float delta_time = (float)(tempo_atual - tempo_anterior);
            tempo_anterior = tempo_atual;

            // Atualiza a lógica do jogo
            update_game(&estado, &player, projectiles, MAX_PROJECTILES, input.teclas, delta_time, &time_since_last_projectile);

            // Renderiza o jogo
            render_game(estado, &res, &player, projectiles, MAX_PROJECTILES,
                continuar_botao, sair_botao, input.mouse_x, input.mouse_y,
                start_button, prologo_button, credits_button, Instructs_button);
        }
        else {
            // Lida com os eventos
            handle_event(evento, &input, &estado, &player, projectiles, MAX_PROJECTILES,
                continuar_botao, sair_botao, start_button, prologo_button, credits_button, Instructs_button);
        }
    }

    // Finaliza recursos
    destroy_player(&player);
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        destroy_projectile(&projectiles[i]);
    }
    destroy_resources(&res);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}
