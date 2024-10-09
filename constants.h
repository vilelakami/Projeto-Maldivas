// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <allegro5/allegro5.h>

// Definições das constantes da tela
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define FPS 60

// Posições e dimensões dos botões na tela de Game Over
#define BOTAO_CONTINUAR_X1 540
#define BOTAO_CONTINUAR_Y1 400
#define BOTAO_CONTINUAR_X2 740
#define BOTAO_CONTINUAR_Y2 450

#define BOTAO_SAIR_X1 540
#define BOTAO_SAIR_Y1 500
#define BOTAO_SAIR_X2 740
#define BOTAO_SAIR_Y2 550

// Cores
#define COR_FUNDO al_map_rgb(255, 255, 255)
#define COR_GAME_OVER al_map_rgb(0, 0, 0)

#endif // CONSTANTS_H
