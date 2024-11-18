// collision.h
#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "player.h"


typedef struct {
    int x1, y1, x2, y2;
} Retangulos;

bool colisaoPersonagem(Player* player, Retangulos* retangulo);

// Fun��o para verificar colis�o retangular
bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2);

#endif
