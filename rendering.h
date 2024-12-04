#ifndef RENDERING_H
#define RENDERING_H

#include "game_state.h"
#include "resources.h"
#include "player.h"
#include "projectile.h"
#include "rect.h"
#include "interacoes.h"
#include "npc.h"
#include "dialogo.h"

void render_game(GameState estado, Resources* res, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y,
    Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button,
    Rect* obstacles, int num_obstacles, Interacoes* interacoes,
    Rect botao_sair_vitoria, Rect botao_menu_vitoria,
    NPC_DIRETOR* npc_chefe, NPC_ENGENHEIRO* npc_engenheiro, DialogueManager* dialogue_manager);

#endif // RENDERING_H
