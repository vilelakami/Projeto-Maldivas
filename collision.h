#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "rect.h"
#include "player.h"

// Função para verificar colisão retangular baseada em coordenadas e dimensões
bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2);

// Função para verificar colisão entre dois retângulos definidos pela estrutura Rect
bool verifica_colisao_rect(Rect a, Rect b);

#endif // COLLISION_H
