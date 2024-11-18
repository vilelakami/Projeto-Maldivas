#include "collision.h"

bool colisaoPersonagem(Player* player, Retangulos* retangulo)
{
    return false;
}

bool verifica_colisao(float x1, float y1, float largura1, float altura1,
    float x2, float y2, float largura2, float altura2) {
    return x1 < x2 + largura2 &&
        x1 + largura1 > x2 &&
        y1 < y2 + altura2 &&
        y1 + altura1 > y2;
}

bool verificar_colisaop(Player* player, Retangulos* retangulo) {
    //verificando colisoes
    if (player->x + player->largura_frame > retangulo->x1 && player->x < retangulo->x2) {
        if (player->x + player->largura_frame > retangulo->x1 && player->x < retangulo->x1) {
            player->x = player->x;
        }
        else if (player->x < retangulo->x2 && player->x + player->largura_frame > retangulo->x2) {
            player->x = player->x;
        }
    }

    if (player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y2) {
        if (player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y1) {
            player->y = player->y;
        }
        else if (player->y < retangulo->y2 && player->y + player->altura_frame > retangulo->y2) {
            player->y = player->y;
        }
    }

    return player->x + player->largura_frame > retangulo->x1 && player->x < retangulo->x2 &&
        player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y2;
}

