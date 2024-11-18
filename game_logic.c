#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void update_game(GameState* estado, Player* player, Projectile* projectiles, int num_projectiles, const bool* teclas, float delta_time, float* time_since_last_projectile) {
    if (*estado == FASE_1) {
        // Atualiza o jogador
        update_player(player, teclas, delta_time);

        // Atualiza o temporizador
        *time_since_last_projectile += delta_time;

        // Intervalo para criação de projéteis
        const float projectile_spawn_interval = 0.5f; // Intervalo de 0,5 segundos

        // Verifica se é hora de criar um novo projétil
        if (*time_since_last_projectile >= projectile_spawn_interval) {

            // Encontra um projétil inativo para reutilizar
            for (int i = 0; i < num_projectiles; ++i) {
                if (!projectiles[i].active) {

                    // Ativa e inicializa o projétil
                    projectiles[i].active = true;
                    projectiles[i].x = rand() % (SCREEN_WIDTH - (int)(projectiles[i].largura_frame * projectiles[i].escala));
                    projectiles[i].y = -projectiles[i].altura_frame * projectiles[i].escala;
                    break; // Sai do loop após ativar um projétil
                }
            }
            *time_since_last_projectile = 0.0f; // Reseta o temporizador
        }

        // Calcula as dimensões do jogador para colisão
        float player_largura = player->largura_frame * player->escala;
        float player_altura = player->altura_frame * player->escala;

        // Atualiza e verifica colisões para cada projétil ativo
        for (int i = 0; i < num_projectiles; ++i) {
            if (projectiles[i].active) {
                update_projectile(&projectiles[i], delta_time);

                float proj_largura = projectiles[i].largura_frame * projectiles[i].escala;
                float proj_altura = projectiles[i].altura_frame * projectiles[i].escala;

                if (verifica_colisao(player->x, player->y, player_largura, player_altura,
                    projectiles[i].x, projectiles[i].y, proj_largura, proj_altura)) {
                    if (!player->invencivel) {
                        // Reduz a vida do jogador
                        player->vida_atual -= 10;
                        if (player->vida_atual < 0) player->vida_atual = 0;

                        // Ativa a invencibilidade por 2 segundos
                        player->invencivel = true;
                        player->tempo_invencibilidade = 2.0f;

                        // Desativa o projétil
                        projectiles[i].active = false;

                        printf("Você foi atingido! Vida atual: %d\n", player->vida_atual);
                    }
                }

                // Desativa o projétil se sair da tela
                if (projectiles[i].y > SCREEN_HEIGHT) {
                    projectiles[i].active = false;
                }
            }
        }

        // Verifica se o jogador morreu
        if (player->vida_atual <= 0) {
            *estado = GAME_OVER;
            printf("Jogador morreu!\n");
        }
    }
}
