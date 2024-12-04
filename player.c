#include "player.h"
#include "collision.h"
#include "constants.h"
#include "interacoes.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init_player(Player* player) {
    player->sprite = al_load_bitmap("assets/cientista.png");
    if (!player->sprite) {
        fprintf(stderr, "Erro ao carregar o sprite do jogador.\n");
        exit(EXIT_FAILURE);
    }

    player->escala = 2.0f;
    player->largura_frame = 40;
    player->altura_frame = 40;

    player->x = 350;
    player->y = 500;

    player->velocidade = 200.0f;
    player->direcao = DIRECAO_BAIXO;
    player->frame_atual = 0;
    player->contador_animacao = 0;
    player->velocidade_animacao = 10;
    player->vida_maxima = 20;
    player->vida_atual = player->vida_maxima;
    player->invencivel = false;
    player->tempo_invencibilidade = 0.0f;
    player->perto_do_obstaculo_2 = false;
    player->perto_do_obstaculo_3 = false;
}

void update_player(Player* player, const bool* teclas, float delta_time, Rect* obstacles, int num_obstacles, Interacoes* interacoes, Rect* proximity_zones) {
    bool movendo = false;

    float dx = 0.0f;
    float dy = 0.0f;

    if (teclas[ALLEGRO_KEY_W]) {
        dy -= player->velocidade * delta_time;
        player->direcao = DIRECAO_CIMA;
        movendo = true;
    }
    if (teclas[ALLEGRO_KEY_S]) {
        dy += player->velocidade * delta_time;
        player->direcao = DIRECAO_BAIXO;
        movendo = true;
    }
    if (teclas[ALLEGRO_KEY_A]) {
        dx -= player->velocidade * delta_time;
        player->direcao = DIRECAO_ESQUERDA;
        movendo = true;
    }
    if (teclas[ALLEGRO_KEY_D]) {
        dx += player->velocidade * delta_time;
        player->direcao = DIRECAO_DIREITA;
        movendo = true;
    }

    if (dx != 0.0f) {
        float new_x = player->x + dx;

        if (new_x < 0) new_x = 0;
        if (new_x + (player->largura_frame * player->escala) > SCREEN_WIDTH)
            new_x = SCREEN_WIDTH - (player->largura_frame * player->escala);

        Rect player_rect_x = {
            (int)new_x,
            (int)player->y,
            (int)(new_x + player->largura_frame * player->escala),
            (int)(player->y + player->altura_frame * player->escala)
        };

        bool collision_x = false;
        for (int i = 0; i < num_obstacles; ++i) {
            if (verifica_colisao_rect(player_rect_x, obstacles[i])) {
                collision_x = true;
                break;
            }
        }

        if (!collision_x) {
            player->x = new_x;
        }
    }

    if (dy != 0.0f) {
        float new_y = player->y + dy;

        if (new_y < 0) new_y = 0;
        if (new_y + (player->altura_frame * player->escala) > SCREEN_HEIGHT)
            new_y = SCREEN_HEIGHT - (player->altura_frame * player->escala);

        Rect player_rect_y = {
            (int)player->x,
            (int)new_y,
            (int)(player->x + player->largura_frame * player->escala),
            (int)(new_y + player->altura_frame * player->escala)
        };

        bool collision_y = false;
        for (int i = 0; i < num_obstacles; ++i) {
            if (verifica_colisao_rect(player_rect_y, obstacles[i])) {
                collision_y = true;
                break;
            }
        }

        if (!collision_y) {
            player->y = new_y;
        }
    }

    if (player->x < 0) player->x = 0;
    if (player->y < 0) player->y = 0;
    if (player->x + (player->largura_frame * player->escala) > SCREEN_WIDTH)
        player->x = SCREEN_WIDTH - (player->largura_frame * player->escala);
    if (player->y + (player->altura_frame * player->escala) > SCREEN_HEIGHT)
        player->y = SCREEN_HEIGHT - (player->altura_frame * player->escala);

    if (movendo) {
        player->contador_animacao++;
        if (player->contador_animacao >= player->velocidade_animacao) {
            player->contador_animacao = 0;
            player->frame_atual = (player->frame_atual + 1) % 4;
        }
    }
    else {
        player->frame_atual = 0;
        player->contador_animacao = 0;
    }

    if (player->invencivel) {
        player->tempo_invencibilidade -= delta_time;
        if (player->tempo_invencibilidade <= 0.0f) {
            player->invencivel = false;
            player->tempo_invencibilidade = 0.0f;
        }
    }

    // Verifica proximidade usando colisão com as zonas de proximidade
    if (!interacoes->interagiu_obstaculo_2) {
        Rect player_rect = {
            (int)player->x,
            (int)player->y,
            (int)(player->x + player->largura_frame * player->escala),
            (int)(player->y + player->altura_frame * player->escala)
        };

        if (verifica_colisao_rect(player_rect, proximity_zones[0])) {
            player->perto_do_obstaculo_2 = true;
        }
        else {
            player->perto_do_obstaculo_2 = false;
        }
    }

    if (!interacoes->interagiu_obstaculo_3) {
        Rect player_rect = {
            (int)player->x,
            (int)player->y,
            (int)(player->x + player->largura_frame * player->escala),
            (int)(player->y + player->altura_frame * player->escala)
        };

        if (verifica_colisao_rect(player_rect, proximity_zones[1])) {
            player->perto_do_obstaculo_3 = true;
        }
        else {
            player->perto_do_obstaculo_3 = false;
        }
    }
}

void draw_player(Player* player) {
    bool desenhar = true;
    if (player->invencivel) {
        int pisca = (int)(player->tempo_invencibilidade * 10) % 2;
        desenhar = pisca == 0;
    }

    if (desenhar) {
        int frame_x = player->frame_atual * player->largura_frame;
        int frame_y = player->direcao * player->altura_frame;

        al_draw_scaled_bitmap(
            player->sprite,
            frame_x, frame_y,
            player->largura_frame, player->altura_frame,
            player->x, player->y,
            player->largura_frame * player->escala,
            player->altura_frame * player->escala,
            0
        );
    }
}

void destroy_player(Player* player) {
    if (player->sprite) {
        al_destroy_bitmap(player->sprite);
        player->sprite = NULL;
    }
}
