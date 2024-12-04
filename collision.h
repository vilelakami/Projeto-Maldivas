#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "rect.h"
#include "player.h"

// Fun��o para verificar colis�o retangular baseada em coordenadas e dimens�es
bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2);

// Fun��o para verificar colis�o entre dois ret�ngulos definidos pela estrutura Rect
bool verifica_colisao_rect(Rect a, Rect b);

#endif // COLLISION_H
