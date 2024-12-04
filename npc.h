#ifndef NPC_H
#define NPC_H

#include <stdbool.h>
#include <allegro5/allegro5.h>
#include "dialogo.h" // Inclua o arquivo onde DialogueManager é definido

// Definições de direções
#define DIRECAO_BAIXO 0
#define DIRECAO_ESQUERDA 1
#define DIRECAO_DIREITA 2
#define DIRECAO_CIMA 3

// Definição da estrutura NPC_DIRETOR
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
    ALLEGRO_BITMAP* NPC_CHEFE;
} NPC_DIRETOR;

// Definição da estrutura NPC_ENGENHEIRO
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
    ALLEGRO_BITMAP* NPC_ENGENHEIRO;
} NPC_ENGENHEIRO;

// Declaração das funções para o NPC_DIRETOR
void init_npc_chefe(NPC_DIRETOR* npc_chefe);
void draw_npc_chefe(NPC_DIRETOR* npc_chefe);
void destroy_npc_chefe(NPC_DIRETOR* npc_chefe);

// Declaração das funções para o NPC_ENGENHEIRO
void init_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro);
void draw_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro);
void destroy_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro);

// Função para atualizar o movimento do engenheiro
bool update_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro, NPC_DIRETOR* npc_chefe);

#endif // NPC_H
