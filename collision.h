// collision.h
#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

// Função para verificar colisão retangular
bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2);

#endif
