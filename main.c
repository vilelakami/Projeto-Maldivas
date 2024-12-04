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
#include "interacoes.h"
#include "npc.h"
#include "dialogo.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#define NUM_OBSTACLES 9
#define MAX_PROXIMITY_ZONES 2

float time_since_last_projectile = 0.0f;
Rect obstacles[NUM_OBSTACLES];
Rect proximity_zones[MAX_PROXIMITY_ZONES];

void init_obstacles(Rect* obstacles) {
    // Obstáculo 1 - Combinação do Obstáculo 1 e Obstáculo 5 originais
    obstacles[0].x1 = 0;
    obstacles[0].y1 = 0;
    obstacles[0].x2 = 350; // x2 do antigo Obstáculo 5
    obstacles[0].y2 = 320;

    // Obstáculo 2 (antigo Obstáculo 2) - Interação
    obstacles[1].x1 = 180;
    obstacles[1].y1 = 380;
    obstacles[1].x2 = 260;
    obstacles[1].y2 = 485;

    // Obstáculo 3 (antigo Obstáculo 3) - Interação
    obstacles[2].x1 = 820;
    obstacles[2].y1 = 380;
    obstacles[2].x2 = 900;
    obstacles[2].y2 = 485;

    // Obstáculo 4 (antigo Obstáculo 4)
    obstacles[3].x1 = 820;
    obstacles[3].y1 = 0;
    obstacles[3].x2 = SCREEN_WIDTH;
    obstacles[3].y2 = 320;

    // Obstáculo 5 - Combinação do Obstáculo 6 e Obstáculo 7 originais
    obstacles[4].x1 = 350; // x1 do antigo Obstáculo 6
    obstacles[4].y1 = 0;
    obstacles[4].x2 = 480; // x2 do antigo Obstáculo 7
    obstacles[4].y2 = 480; // y2 do antigo Obstáculo 7

    // Obstáculo 6 (antigo Obstáculo 8)
    obstacles[5].x1 = 575;
    obstacles[5].y1 = 0;
    obstacles[5].x2 = 670;
    obstacles[5].y2 = 480;

    // Obstáculo 7 - Ajuste para não sobrepor o obstáculo 6
    obstacles[6].x1 = 670; // Ajustado de 600 para 670
    obstacles[6].y1 = 0;
    obstacles[6].x2 = 810;
    obstacles[6].y2 = 250;

    // Obstáculo 8 (antigo Obstáculo 11)
    obstacles[7].x1 = 0;
    obstacles[7].y1 = SCREEN_HEIGHT - 50;
    obstacles[7].x2 = 300;
    obstacles[7].y2 = SCREEN_HEIGHT;

    // Obstáculo 9 (antigo Obstáculo 12)
    obstacles[8].x1 = SCREEN_WIDTH - 300;
    obstacles[8].y1 = SCREEN_HEIGHT - 50;
    obstacles[8].x2 = SCREEN_WIDTH;
    obstacles[8].y2 = SCREEN_HEIGHT;
}

void init_proximity_zones(Rect* proximity_zones, Rect* obstacles) {
    // Zona de proximidade para o obstáculo 2 (interação)
    proximity_zones[0].x1 = obstacles[1].x1 - 50;
    proximity_zones[0].y1 = obstacles[1].y1 - 50;
    proximity_zones[0].x2 = obstacles[1].x2 + 50;
    proximity_zones[0].y2 = obstacles[1].y2 + 50;

    // Zona de proximidade para o obstáculo 3 (interação)
    proximity_zones[1].x1 = obstacles[2].x1 - 50;
    proximity_zones[1].y1 = obstacles[2].y1 - 50;
    proximity_zones[1].x2 = obstacles[2].x2 + 50;
    proximity_zones[1].y2 = obstacles[2].y2 + 50;
}

int main() {
    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar o Allegro.\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "Erro ao inicializar o addon de primitivas.\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "Erro ao inicializar o addon de imagem.\n");
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

    srand(time(NULL));

    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Erro ao criar o display.\n");
        return -1;
    }

    al_set_window_title(display, "Chernobyl Game");

    Resources res;
    if (!load_resources(&res)) {
        al_destroy_display(display);
        return -1;
    }

    if (res.icon) {
        al_set_display_icon(display, res.icon);
    }

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

    Player player;
    init_player(&player);

    Projectile projectiles[MAX_PROJECTILES];
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        init_projectile(&projectiles[i]);
        projectiles[i].active = false;
    }

    GameInput input;
    init_game_input(&input);

    Rect continuar_botao = { BOTAO_CONTINUAR_X1, BOTAO_CONTINUAR_Y1, BOTAO_CONTINUAR_X2, BOTAO_CONTINUAR_Y2 };
    Rect sair_botao = { BOTAO_SAIR_X1, BOTAO_SAIR_Y1, BOTAO_SAIR_X2, BOTAO_SAIR_Y2 };

    Rect start_button = {
        SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 - 75,
        SCREEN_WIDTH / 2 + 100,
        SCREEN_HEIGHT / 2 - 25
    };

    Rect credits_button = {
        SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2,
        SCREEN_WIDTH / 2 + 100,
        SCREEN_HEIGHT / 2 + 50
    };

    Rect Instructs_button = {
        SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 + 75,
        SCREEN_WIDTH / 2 + 100,
        SCREEN_HEIGHT / 2 + 125
    };

    Rect prologo_button = {
        SCREEN_WIDTH - 150,
        20,
        SCREEN_WIDTH - 50,
        70
    };

    Rect botao_sair_vitoria = {
    SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 50,
    SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100
    };

    Rect botao_menu_vitoria = {
        SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50,
        SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2 + 100
    };


    init_obstacles(obstacles);
    init_proximity_zones(proximity_zones, obstacles);
    int num_obstacles = NUM_OBSTACLES;

    double tempo_anterior = al_get_time();
    time_since_last_projectile = 0.0f;

    GameState estado = MENU;

    NPC_DIRETOR npc_chefe;
    init_npc_chefe(&npc_chefe);

    NPC_ENGENHEIRO npc_engenheiro;
    init_npc_engenheiro(&npc_engenheiro);

    DialogueManager dialogue_manager;
    init_dialogue_manager(&dialogue_manager);

    Interacoes interacoes;
    init_interacoes(&interacoes);

    while (!input.sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(queue, &evento);

        if (evento.type == ALLEGRO_EVENT_TIMER) {
            double tempo_atual = al_get_time();
            float delta_time = (float)(tempo_atual - tempo_anterior);
            tempo_anterior = tempo_atual;

            update_game(&estado, &player, projectiles, MAX_PROJECTILES, input.teclas, delta_time, &time_since_last_projectile, obstacles, &num_obstacles, &interacoes, proximity_zones);

            render_game(estado, &res, &player, projectiles, MAX_PROJECTILES,
                continuar_botao, sair_botao, input.mouse_x, input.mouse_y,
                start_button, prologo_button, credits_button, Instructs_button,
                obstacles, num_obstacles, &interacoes,
                botao_sair_vitoria, botao_menu_vitoria,
                &npc_chefe, &npc_engenheiro, &dialogue_manager);

        }
        else {
            handle_event(evento, &input, &estado, &player, projectiles, MAX_PROJECTILES,
                continuar_botao, sair_botao, start_button, prologo_button, credits_button, Instructs_button, &interacoes,
                botao_sair_vitoria, botao_menu_vitoria, &dialogue_manager);

        }
    }

    destroy_player(&player);
    for (int i = 0; i < MAX_PROJECTILES; ++i) {
        destroy_projectile(&projectiles[i]);
    }
    destroy_resources(&res);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    destroy_npc_chefe(&npc_chefe);
    destroy_npc_engenheiro(&npc_engenheiro);

    return 0;
}
