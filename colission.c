#include "collision.h"

bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2) {
    return x1 < x2 + largura2 &&
        x1 + largura1 > x2 &&
        y1 < y2 + altura2 &&
        y1 + altura1 > y2;
}

bool verifica_colisao_rect(Rect a, Rect b) {
    return a.x1 < b.x2 &&
        a.x2 > b.x1 &&
        a.y1 < b.y2 &&
        a.y2 > b.y1;
}
