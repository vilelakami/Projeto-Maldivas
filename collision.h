#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "rect.h"

// Fun��o para verificar colis�o retangular
bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2);

// Fun��o para verificar colis�o entre dois Ret�ngulos
bool verifica_colisao_rect(Rect a, Rect b);

#endif
