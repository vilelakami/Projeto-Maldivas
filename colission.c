#include "collision.h"
#include "player.h"
#include <stdio.h>

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
void  verificar_colisaop(Player* player) {
    //verificando colisoes

    if (player->x + player->largura_frame < 260 &&
        player->y + player->altura_frame < 320 &&
        player->x + player->largura_frame > 0 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 190;
        player->y = 290;
        fprintf(stdout, "colidiu com a central do canto esquerdo superior\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 260 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 180 &&
        player->y + player->altura_frame > 380) {

        player->velocidade = 0;
        player->x = 260;
        player->y = 380;
        fprintf(stdout, "colidiu com a ilha no meio esquerdo\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 900 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 820 &&
        player->y + player->altura_frame > 380) {

        player->velocidade = 0;
        player->x = 760;
        player->y = 380;
        fprintf(stdout, "colidiu com a ilha no meio direito\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 1260 &&
        player->y + player->altura_frame < 320 &&
        player->x + player->largura_frame > 820 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 820;
        player->y = 320;
        fprintf(stdout, "colidiu com a parede superior direita\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 350 &&
        player->y + player->altura_frame < 320 &&
        player->x + player->largura_frame > 260 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 300;
        player->y = 280;
        fprintf(stdout, "colidiu com a central superior esquerda\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 430 &&
        player->y + player->altura_frame < 250 &&
        player->x + player->largura_frame > 350 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 360;
        player->y = 280;
        fprintf(stdout, "colidiu com a 2º central superior esquerda\n");
    }
    else {
        player->velocidade = 200.0f;
    };


    if (player->x + player->largura_frame < 480 &&
        player->y + player->altura_frame < 480 &&
        player->x + player->largura_frame > 400 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 350;
        player->y = 300;
        fprintf(stdout, "colidiu com o triangulo esquerdo\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 670 &&
        player->y + player->altura_frame < 480 &&
        player->x + player->largura_frame > 575 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 665;
        player->y = 300;
        fprintf(stdout, "colidiu com o triangulo direito\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 810 &&
        player->y + player->altura_frame < 250 &&
        player->x + player->largura_frame > 730 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 675;
        player->y = 300;
        fprintf(stdout, "colidiu com a 2° central superior direita\n");
    }
    else {
        player->velocidade = 200.0f;
    };

    if (player->x + player->largura_frame < 730 &&
        player->y + player->altura_frame < 200 &&
        player->x + player->largura_frame > 600 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 0;
        player->x = 675;
        player->y = 300;
        fprintf(stdout, "colidiu com a 2° central superior direita\n");
    }
    else {
        player->velocidade = 200.0f;
    };




   
}