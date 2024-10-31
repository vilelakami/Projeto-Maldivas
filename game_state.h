// game_state.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    MENU,
    PROLOGO,
    FASE_1,
    //FASE_2,
    //FASE_3,
    GAME_OVER,
    PLAYING
} GameState;

// Declaração da função atualizar_estado
void atualizar_estado(GameState* estado);

#endif // GAME_STATE_H
