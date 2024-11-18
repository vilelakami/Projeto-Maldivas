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

        // Intervalo para cria��o de proj�teis
        const float projectile_spawn_interval = 0.5f; // Intervalo de 0,5 segundos

        // Verifica se � hora de criar um novo proj�til
        if (*time_since_last_projectile >= projectile_spawn_interval) {

            // Encontra um proj�til inativo para reutilizar
            for (int i = 0; i < num_projectiles; ++i) {
                if (!projectiles[i].active) {

                    // Ativa e inicializa o proj�til
                    projectiles[i].active = true;
                    projectiles[i].x = rand() % (SCREEN_WIDTH - (int)(projectiles[i].largura_frame * projectiles[i].escala));
                    projectiles[i].y = -projectiles[i].altura_frame * projectiles[i].escala;
                    break; // Sai do loop ap�s ativar um proj�til
                }
            }
            *time_since_last_projectile = 0.0f; // Reseta o temporizador
        }

        // Calcula as dimens�es do jogador para colis�o
        float player_largura = player->largura_frame * player->escala;
        float player_altura = player->altura_frame * player->escala;

        // Atualiza e verifica colis�es para cada proj�til ativo
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

                        // Desativa o proj�til
                        projectiles[i].active = false;

                        printf("Voc� foi atingido! Vida atual: %d\n", player->vida_atual);
                    }
                }

                // Desativa o proj�til se sair da tela
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
