// event_handling.h
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
    GameState estado;
} GameInput;

// Inicializa a estrutura de entrada
void init_game_input(GameInput* input);

// Lida com um único evento recebido
void handle_event(ALLEGRO_EVENT evento, GameInput* input, Player* player, Projectile* proj, Rect continuar_botao, Rect sair_botao);

#endif // EVENT_HANDLING_H
