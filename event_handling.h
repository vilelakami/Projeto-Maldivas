#ifndef EVENT_HANDLING_H
#define EVENT_HANDLING_H

#include <allegro5/allegro5.h>
#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"

// Estrutura para armazenar o estado das entradas do jogo
typedef struct {
    bool sair;
    bool teclas[ALLEGRO_KEY_MAX];
    int mouse_x;
    int mouse_y;
} GameInput;

// Inicializa a estrutura de entrada
void init_game_input(GameInput* input);

// Lida com um único evento recebido
void handle_event(ALLEGRO_EVENT evento, GameInput* input, GameState* estado, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button);

#endif // EVENT_HANDLING_H
