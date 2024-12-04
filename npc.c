#include "npc.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

void init_npc_chefe(NPC_DIRETOR* npc_chefe) {
    // Carrega o sprite do NPC chefe da usina 
    npc_chefe->NPC_CHEFE = al_load_bitmap ("assets/chefe.png");
    if (!npc_chefe->NPC_CHEFE) {
        fprintf(stderr, "Erro ao carregar o sprite do NPC chefe da usina.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa o npc 
    npc_chefe->escala = 2.5f;
    npc_chefe->largura_frame = 34;
    npc_chefe->altura_frame = 52;

    npc_chefe->x = 400;
    npc_chefe->y = 340;
    npc_chefe->velocidade = 200.0f;
    npc_chefe->direcao = DIRECAO_ESQUERDA;
    npc_chefe->frame_atual = 0;
    npc_chefe->contador_animacao = 0;
    npc_chefe->velocidade_animacao = 10;
    npc_chefe->vida_maxima = 20;
    npc_chefe->vida_atual = npc_chefe->vida_maxima;
    npc_chefe->invencivel = false;
    npc_chefe->tempo_invencibilidade = 0.0f;
}

void draw_npc_chefe(NPC_DIRETOR* npc_chefe) {
    
    bool desenhar = true;

    if (desenhar) {
        int frame_x = npc_chefe->frame_atual * npc_chefe->largura_frame;
        int frame_y = npc_chefe->direcao * npc_chefe->altura_frame;

        al_draw_scaled_bitmap(
            
            npc_chefe->NPC_CHEFE,
            frame_x, frame_y,
            npc_chefe->largura_frame, npc_chefe->altura_frame,
            npc_chefe->x, npc_chefe->y,
            npc_chefe->largura_frame * npc_chefe->escala,
            npc_chefe->altura_frame * npc_chefe->escala,
                    0
                );
    }
}

void init_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro) {
    // Carrega o sprite do NPC engenheiro da usina 
    npc_engenheiro->NPC_ENGENHEIRO = al_load_bitmap("assets/engenheiro.png");
    if (!npc_engenheiro->NPC_ENGENHEIRO) {
        fprintf(stderr, "Erro ao carregar o sprite do NPC engenheiro da usina.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa o npc engenheiro da usina
    npc_engenheiro->escala = 2.5f;
    npc_engenheiro->largura_frame = 34;
    npc_engenheiro->altura_frame = 52;

    npc_engenheiro->x = 500;
    npc_engenheiro->y = 740;
    npc_engenheiro->velocidade = 200.0f;
    npc_engenheiro->direcao = DIRECAO_BAIXO;
    npc_engenheiro->frame_atual = 0;
    npc_engenheiro->contador_animacao = 0;
    npc_engenheiro->velocidade_animacao = 10;
    npc_engenheiro->vida_maxima = 20;
    npc_engenheiro->vida_atual = npc_engenheiro->vida_maxima;
    npc_engenheiro->invencivel = false;
    npc_engenheiro->tempo_invencibilidade = 0.0f;
}
//NPC ENGENHEIRO CHEFE
void draw_npc_engenheiro(NPC_ENGENHEIRO*npc_engenheiro) {

    bool desenhar = true;

    if (desenhar) {
        int frame_x = npc_engenheiro->frame_atual * npc_engenheiro->largura_frame;
        int frame_y = npc_engenheiro->direcao * npc_engenheiro->altura_frame;

        al_draw_scaled_bitmap(

            npc_engenheiro->NPC_ENGENHEIRO,
            frame_x, frame_y,
            npc_engenheiro->largura_frame, npc_engenheiro->altura_frame,
            npc_engenheiro->x, npc_engenheiro->y,
            npc_engenheiro->largura_frame * npc_engenheiro->escala,
            npc_engenheiro->altura_frame * npc_engenheiro->escala,
            0
        );
    }
}
//função que anima a cena de dialogo educacional entre os npcs
void movimento_eng(NPC_ENGENHEIRO* npc_engenheiro, NPC_DIRETOR*npc_chefe) {
    bool movendo = true;
    npc_engenheiro->direcao = DIRECAO_CIMA;
    if (movendo) {
        
    npc_engenheiro->y  --;
    // animação
    if (movendo) {
        npc_engenheiro->contador_animacao++;
        if (npc_engenheiro->contador_animacao >= npc_engenheiro->velocidade_animacao) {
            npc_engenheiro->contador_animacao = 0;
            npc_engenheiro->frame_atual = (npc_engenheiro->frame_atual + 1) % 4; 
        }
    }
    else {
        npc_engenheiro->frame_atual = 0;
        npc_engenheiro->contador_animacao = 0;
    }
   
    
  
    }
    if (npc_engenheiro->y <= 340) {
        movendo = false;
        npc_engenheiro->frame_atual = 0;
        npc_engenheiro->y = 340;
        npc_engenheiro->direcao = DIRECAO_ESQUERDA;
        npc_chefe->direcao = DIRECAO_DIREITA;
       
    }

}
//dialogo educacional



    



void destroy_npc_chefe(NPC_DIRETOR* npc_chefe) {
    if (npc_chefe->NPC_CHEFE) {
        al_destroy_bitmap(npc_chefe->NPC_CHEFE);
        npc_chefe->NPC_CHEFE = NULL;
    }
}
void destroy_npc_engenheiro(NPC_ENGENHEIRO* npc_engenheiro) {
    if (npc_engenheiro->NPC_ENGENHEIRO) {
        al_destroy_bitmap(npc_engenheiro->NPC_ENGENHEIRO);
        npc_engenheiro->NPC_ENGENHEIRO = NULL;
    }
}


