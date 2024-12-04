// game_state.c
#include "game_state.h"
#include "player.h"
#include "projectile.h"

// Definição da função atualizar_estado
void atualizar_estado(GameState* estado) {

}

void reset_game(Player* player, Projectile* projectiles, int num_projectiles, Interacoes* interacoes) {
    destroy_player(player);
    init_player(player);

    for (int i = 0; i < num_projectiles; ++i) {
        destroy_projectile(&projectiles[i]);
        init_projectile(&projectiles[i]);
        projectiles[i].active = false;
    }

    extern float time_since_last_projectile;
    time_since_last_projectile = 0.0f;

    init_interacoes(interacoes);
}

