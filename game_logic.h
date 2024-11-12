#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "collision.h"

// Atualiza a lógica do jogo com base no estado atual
void update_game(GameState* estado, Player* player, Projectile* projectiles, int num_projectiles, const bool* teclas, float delta_time, float* time_since_last_projectile);

#endif // GAME_LOGIC_H
