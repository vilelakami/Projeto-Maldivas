#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "player.h"
#include "projectile.h"
#include "game_state.h"
#include "rect.h"
#include "interacoes.h"

void update_game(GameState* estado, Player* player, Projectile* projectiles, int num_projectiles, const bool* teclas, float delta_time, float* time_since_last_projectile, Rect* obstacles, int* num_obstacles, Interacoes* interacoes, Rect* proximity_zones);

#endif // GAME_LOGIC_H
