// rendering.h
#ifndef RENDERING_H
#define RENDERING_H

#include "constants.h"  // Inclu�do para acessar SCREEN_WIDTH e outras constantes
#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"
#include "ui.h"
#include "resources.h"

// Fun��o para renderizar o estado atual do jogo
void render_game(GameState estado, Resources* res, Player* player, Projectile* proj, Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y);

#endif // RENDERING_H
