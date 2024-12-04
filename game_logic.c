#include "game_logic.h"
#include "constants.h"
#include "collision.h"
#include <stdio.h>
#include <stdlib.h>

void update_game(GameState* estado, Player* player, Projectile* projectiles, int num_projectiles, const bool* teclas, float delta_time, float* time_since_last_projectile, Rect* obstacles, int* num_obstacles, Interacoes* interacoes, Rect* proximity_zones) {
    if (*estado == FASE_1) {
        update_player(player, teclas, delta_time, obstacles, *num_obstacles, interacoes, proximity_zones);

        *time_since_last_projectile += delta_time;
        const float projectile_spawn_interval = 0.5f;

        if (*time_since_last_projectile >= projectile_spawn_interval) {
            for (int i = 0; i < num_projectiles; ++i) {
                if (!projectiles[i].active) {
                    projectiles[i].active = true;
                    projectiles[i].x = rand() % (SCREEN_WIDTH - (int)(projectiles[i].largura_frame * projectiles[i].escala));
                    projectiles[i].y = -projectiles[i].altura_frame * projectiles[i].escala;
                    break;
                }
            }
            *time_since_last_projectile = 0.0f;
        }

        float player_largura = player->largura_frame * player->escala;
        float player_altura = player->altura_frame * player->escala;

        for (int i = 0; i < num_projectiles; ++i) {
            if (projectiles[i].active) {
                update_projectile(&projectiles[i], delta_time);

                float proj_largura = projectiles[i].largura_frame * projectiles[i].escala;
                float proj_altura = projectiles[i].altura_frame * projectiles[i].escala;

                if (verifica_colisao(player->x, player->y, player_largura, player_altura,
                    projectiles[i].x, projectiles[i].y, proj_largura, proj_altura)) {
                    if (!player->invencivel) {
                        player->vida_atual -= 10;
                        if (player->vida_atual < 0) player->vida_atual = 0;

                        player->invencivel = true;
                        player->tempo_invencibilidade = 2.0f;

                        projectiles[i].active = false;
                    }
                }

                if (projectiles[i].y > SCREEN_HEIGHT) {
                    projectiles[i].active = false;
                }
            }
        }

        if (player->vida_atual <= 0) {
            *estado = GAME_OVER;
        }

        if (interacoes->contador_interacoes >= 2) {
            *num_obstacles = 9;
        }

        if (player->y + player->altura_frame * player->escala >= SCREEN_HEIGHT - 10) {
            if (interacoes->contador_interacoes >= 2) {
                *estado = VITORIA;
                printf("Jogador venceu o jogo!\n");
            }
            else {
                player->y = SCREEN_HEIGHT - 10 - player->altura_frame * player->escala;
            }
        }
    }
}
