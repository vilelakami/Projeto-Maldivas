// ui.h
#ifndef UI_H
#define UI_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"

// Inicializa o m�dulo de UI
bool init_ui();

// Desenha a barra de vida
void draw_life_bar(Player* player);

// Verifica se um ponto est� dentro de um ret�ngulo
bool is_point_inside_rect(int x, int y, Rect rect);

// Finaliza o m�dulo de UI
void destroy_ui();

#endif // UI_H
