#ifndef RENDERING_H
#define RENDERING_H

#include "constants.h"  // Incluído para acessar SCREEN_WIDTH e outras constantes
#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"
#include "ui.h"
#include "resources.h"

// Função para renderizar o estado atual do jogo
void render_game(GameState estado, Resources* res, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y,
    Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button);

#endif // RENDERING_H
