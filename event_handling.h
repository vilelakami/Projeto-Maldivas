#ifndef EVENT_HANDLING_H
#define EVENT_HANDLING_H

#include "game_state.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"
#include "interacoes.h"
#include <allegro5/allegro5.h>

// Estrutura para armazenar inputs do jogo
typedef struct {
    bool sair;
    bool teclas[ALLEGRO_KEY_MAX];
    int mouse_x;
    int mouse_y;
} GameInput;

// Função para inicializar os inputs do jogo
void init_game_input(GameInput* input);

// Função para lidar com eventos
void handle_event(ALLEGRO_EVENT evento, GameInput* input, GameState* estado, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button, Interacoes* interacoes,
    Rect botao_sair_vitoria, Rect botao_menu_vitoria);


#endif // EVENT_HANDLING_H
