// game_logic.c
#include "game_logic.h"
#include <stdio.h>  // Para printf

void update_game(GameState* estado, Player* player, Projectile* proj, const bool* teclas, float delta_time) {
    // Atualiza a l�gica do jogo apenas se estiver em uma das fases do jogo
    if (*estado == FASE_1) {
        // Atualiza o jogador
        update_player(player, teclas, delta_time);

        // Atualiza o proj�til
        update_projectile(proj, delta_time);

        // Calcula as dimens�es para colis�o
        float player_largura = player->largura_frame * player->escala;
        float player_altura = player->altura_frame * player->escala;
        float proj_largura = proj->largura_frame * proj->escala;
        float proj_altura = proj->altura_frame * proj->escala;

        // Verifica colis�o
        if (verifica_colisao(player->x, player->y, player_largura, player_altura,
            proj->x, proj->y, proj_largura, proj_altura)) {
            if (!player->invencivel) {
                // Reduz a vida do jogador
                player->vida_atual -= 10;
                if (player->vida_atual < 0) player->vida_atual = 0;

                // Ativa a invencibilidade por 2 segundos
                player->invencivel = true;
                player->tempo_invencibilidade = 2.0f;

                // Reinicia o proj�til
                init_projectile(proj);

                printf("Colisao detectada! Vida atual: %d\n", player->vida_atual);
            }
        }

        // Verifica se o jogador morreu
        if (player->vida_atual <= 0) {
            *estado = GAME_OVER;
            printf("Jogador morreu!\n");
        }
    }
}
