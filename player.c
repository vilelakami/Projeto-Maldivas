#include "player.h"
#include "collision.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

void init_player(Player* player) {
    // Carrega o sprite do jogador
    player->sprite = al_load_bitmap("assets/cientista.png");
    if (!player->sprite) {
        fprintf(stderr, "Erro ao carregar o sprite do jogador.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa as propriedades do jogador
    player->escala = 2.0f;
    player->largura_frame = 40;
    player->altura_frame = 40;

    player->x = (1080 / 2) - (player->largura_frame * player->escala) / 2;
    player->y = (700 / 2) - (player->altura_frame * player->escala) / 2;
    player->velocidade = 200.0f;
    player->direcao = DIRECAO_BAIXO;
    player->frame_atual = 0;
    player->contador_animacao = 0;
    player->velocidade_animacao = 10;
    player->vida_maxima = 20;
    player->vida_atual = player->vida_maxima;
    player->invencivel = false;
    player->tempo_invencibilidade = 0.0f;
}

void update_player(Player* player, const bool* teclas, float delta_time, Rect* obstacles, int num_obstacles) {
    bool movendo = false;

    float dx = 0.0f;
    float dy = 0.0f;

    // Movimentação baseada em delta_time
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

    // Movimento no eixo X
    if (dx != 0.0f) {
        float new_x = player->x + dx;

        // Prevenir que o jogador saia da tela
        if (new_x < 0) new_x = 0;
        if (new_x + (player->largura_frame * player->escala) > 1080)
            new_x = 1080 - (player->largura_frame * player->escala);

        // Cria o retângulo do jogador na nova posição X
        Rect player_rect_x = {
            (int)new_x,
            (int)player->y,
            (int)(new_x + player->largura_frame * player->escala),
            (int)(player->y + player->altura_frame * player->escala)
        };

        // Verifica colisão com obstáculos
        bool collision_x = false;
        for (int i = 0; i < num_obstacles; ++i) {
            if (verifica_colisao_rect(player_rect_x, obstacles[i])) {
                collision_x = true;
                break;
            }
        }

        // Se não houver colisão, atualiza a posição X
        if (!collision_x) {
            player->x = new_x;
        }
    }

    // Movimento no eixo Y
    if (dy != 0.0f) {
        float new_y = player->y + dy;

        // Prevenir que o jogador saia da tela
        if (new_y < 0) new_y = 0;
        if (new_y + (player->altura_frame * player->escala) > 700)
            new_y = 700 - (player->altura_frame * player->escala);

        // Cria o retângulo do jogador na nova posição Y
        Rect player_rect_y = {
            (int)player->x,
            (int)new_y,
            (int)(player->x + player->largura_frame * player->escala),
            (int)(new_y + player->altura_frame * player->escala)
        };

        // Verifica colisão com obstáculos
        bool collision_y = false;
        for (int i = 0; i < num_obstacles; ++i) {
            if (verifica_colisao_rect(player_rect_y, obstacles[i])) {
                collision_y = true;
                break;
            }
        }

        // Se não houver colisão, atualiza a posição Y
        if (!collision_y) {
            player->y = new_y;
        }
    }

    verificar_colisaop(player);
    // Prevenir que o jogador saia da tela
    if (player->x < 0) player->x = 0;
    if (player->y < 0) player->y = 0;
    if (player->x + (player->largura_frame * player->escala) > 1080)
        player->x = 1080 - (player->largura_frame * player->escala);
    if (player->y + (player->altura_frame * player->escala) > 700)
        player->y = 700 - (player->altura_frame * player->escala);

    // Atualiza a animação
    if (movendo) {
        player->contador_animacao++;
        if (player->contador_animacao >= player->velocidade_animacao) {
            player->contador_animacao = 0;
            player->frame_atual = (player->frame_atual + 1) % 4; // 4 frames (0 a 3)
        }
    }
    else {
        player->frame_atual = 0;
        player->contador_animacao = 0;
    }

    // Atualiza o temporizador de invencibilidade
    if (player->invencivel) {
        player->tempo_invencibilidade -= delta_time;
        if (player->tempo_invencibilidade <= 0.0f) {
            player->invencivel = false;
            player->tempo_invencibilidade = 0.0f;
        }
    }
}

void draw_player(Player* player) {
    // Se o jogador estiver invencível, faça o sprite piscar
    bool desenhar = true;
    if (player->invencivel) {
        // Pisca a cada 0.1 segundos
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
