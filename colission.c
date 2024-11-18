#include "collision.h"
#include "stdio.h"

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


void  verificar_colisaop(Player* player) {
    //verificando colisoes


    if (player->x + player->largura_frame < 260 &&
        player->y + player->altura_frame < 320 &&
        player->x + player->largura_frame > 0 &&
        player->y + player->altura_frame > 0) {

        player->velocidade = 3;
        player->x++;
        player->y++;
        fprintf(stdout, "colidiu em parede superior esquerda\n");

    }
    else{ player->velocidade = 200.0f;
};

    if (player->x + player->largura_frame < 100 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 0 &&
        player->y + player->altura_frame > 340) {

        player->x++;
        player->y++;
        player->velocidade = 1;
        fprintf(stdout, "colidiu no painel esquerdo\n");

    };
    if (player->x + player->largura_frame < 260 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 180 &&
        player->y + player->altura_frame > 380) {

        player->velocidade = 1;
        player->x++;
        player->y++;
        fprintf(stdout, "colidiu no terminal esquerdo\n");

    };
    if (player->x + player->largura_frame < 900 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 820 &&
        player->y + player->altura_frame > 380) {

        player->velocidade = 1;
        player->x--;
        player->y++;
        fprintf(stdout, "colidiu no terminal direito\n");

    };
    if (player->x + player->largura_frame < 1260 &&
        player->y + player->altura_frame < 485 &&
        player->x + player->largura_frame > 980 &&
        player->y + player->altura_frame > 310) {

        player->x--;
        player->y++;
        
        player->velocidade = 1;
        fprintf(stdout, "colidiu no painel direito \n");

    };
    if (player->x + player->largura_frame < 1260 &&
        player->y + player->altura_frame < 320 &&
        player->x + player->largura_frame > 820 &&
        player->y + player->altura_frame > 0) {

        player->x--;
        player->y++;
        player->velocidade = 1;
        fprintf(stdout, "colidiu parede suerior direita\n");

    };
    if (player->x + player->largura_frame < 580 &&
        player->y + player->altura_frame < 385 &&
        player->x + player->largura_frame > 500 &&
        player->y + player->altura_frame > 210) {

        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };

    if (player->x + player->largura_frame > 400 &&
        player->y + player->altura_frame > 0 &&
        player->x + player->largura_frame < 650 &&
        player->y + player->altura_frame < 160) {

        player->velocidade = 1;        
        player->y++;

        fprintf(stdout, "colidiu em parede superior direita\n");

    }; 

    if (player->x + player->largura_frame < 660 &&
        player->y + player->altura_frame < 370 &&
        player->x + player->largura_frame > 580 &&
        player->y + player->altura_frame > 320) {

        player->x--;
        player->y--;
        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };

    if (player->x + player->largura_frame < 420 &&
        player->y + player->altura_frame < 370 &&
        player->x + player->largura_frame > 500 &&
        player->y + player->altura_frame > 320) {

        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };

    if (player->x + player->largura_frame < 470 &&
        player->y + player->altura_frame < 508 &&
        player->x + player->largura_frame > 444 &&
        player->y + player->altura_frame > 433) {

        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };

    if (player->x + player->largura_frame < 982 &&
        player->y + player->altura_frame < 692 &&
        player->x + player->largura_frame > 821 &&
        player->y + player->altura_frame > 654) {

        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };

    if (player->x + player->largura_frame < 260 &&
        player->y + player->altura_frame < 680 &&
        player->x + player->largura_frame > 90 &&
        player->y + player->altura_frame > 650) {

        player->velocidade = 1;
        fprintf(stdout, "colidiu\n");

    };
 }   /*
    void verifica_colisaop(Player* player, Retangulos * retangulo)
    
    if (player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y2) {
        if (player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y1) {
            player->y = player->y;
        }
        else if (player->y < retangulo->y2 && player->y + player->altura_frame > retangulo->y2) {
            player->y = player->y;
            fprintf(stdout, "teste\n");
        }
    }

    return player->x + player->largura_frame > retangulo->x1 && player->x < retangulo->x2 &&
        player->y + player->altura_frame > retangulo->y1 && player->y < retangulo->y2;
}
*/

