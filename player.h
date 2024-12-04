#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "rect.h"
#include "interacoes.h"

typedef enum {
    DIRECAO_CIMA = 7,
    DIRECAO_BAIXO = 4,
    DIRECAO_ESQUERDA = 5,
    DIRECAO_DIREITA = 6
} Direcao;

typedef struct {
    ALLEGRO_BITMAP* sprite;
    float x, y;
    float escala;
    int largura_frame, altura_frame;
    float velocidade;
    Direcao direcao;
    int frame_atual;
    int contador_animacao;
    int velocidade_animacao;
    int vida_maxima;
    int vida_atual;
    bool invencivel;
    float tempo_invencibilidade;
    bool perto_do_obstaculo_2;
    bool perto_do_obstaculo_3;
} Player;

void init_player(Player* player);
void update_player(Player* player, const bool* teclas, float delta_time, Rect* obstacles, int num_obstacles, Interacoes* interacoes, Rect* proximity_zones);
void draw_player(Player* player);
void destroy_player(Player* player);

#endif // PLAYER_H
