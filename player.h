// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include <allegro5/allegro5.h>

// Constantes de direção
#define DIRECAO_BAIXO 4
#define DIRECAO_ESQUERDA 5
#define DIRECAO_DIREITA 6
#define DIRECAO_CIMA 7

// Estrutura do jogador
typedef struct {
    float x, y;
    float velocidade;
    int direcao;
    int frame_atual;
    int contador_animacao;
    int velocidade_animacao;
    float escala;
    int largura_frame;
    int altura_frame;
    int vida_atual;
    int vida_maxima;
    bool invencivel;
    float tempo_invencibilidade;
    ALLEGRO_BITMAP* sprite;
} Player;

// Funções relacionadas ao jogador
void init_player(Player* player);
void update_player(Player* player, const bool* teclas, float delta_time);
void draw_player(Player* player);
void destroy_player(Player* player);

#endif // PLAYER_H
