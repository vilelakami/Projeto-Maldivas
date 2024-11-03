// projectile.c
#include "projectile.h"
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

// Inicializa as propriedades do projetil
void init_projectile(Projectile* proj) {
    // Carrega o sprite do projetil
    proj->sprite = al_load_bitmap("assets/projetil.png");
    if (!proj->sprite) {
        fprintf(stderr, "Erro ao carregar o sprite do projetil.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa as propriedades do projetil
    proj->escala = 2.0f;
    proj->largura_frame = 14;
    proj->altura_frame = 32;
    proj->x = (1280 / 2) - (proj->largura_frame * proj->escala) / 2;
    proj->y = -proj->altura_frame * proj->escala;
    proj->velocidade_y = 350.0f;
    proj->frame_atual = 0;
    proj->contador_animacao = 0;
    proj->velocidade_animacao = 10;
}

// Atualiza a posi��o do projetil e a anima��o
void update_projectile(Projectile* proj, float delta_time) {
    // Atualiza a posi��o com base no delta_time
    proj->y += proj->velocidade_y * delta_time;

    // Reinicia o projetil quando sai da tela
    if (proj->y > 700) {
        proj->y = -proj->altura_frame * proj->escala;
        proj->x = (1280 / 2) - (proj->largura_frame * proj->escala) / 2; // Centraliza horizontalmente
    }

    // Atualiza a anima��o
    proj->contador_animacao++;
    if (proj->contador_animacao >= proj->velocidade_animacao) {
        proj->contador_animacao = 0;
        proj->frame_atual = (proj->frame_atual + 1) % 4; // 4 frames (0 a 3)
    }
}

// Desenha o projetil na tela rotacionado 180 graus
void draw_projectile(const Projectile* proj) {
    if (!proj->sprite) {
        fprintf(stderr, "Erro: proj->sprite � NULL.\n");
        return; // Evita tentar desenhar um bitmap nulo
    }

    // Define o espa�amento entre os frames
    const int espacamento_frame = 5; // 4 pixels de dist�ncia entre os frames

    // Calcula a posi��o X do frame atual no sprite sheet
    int frame_x = proj->frame_atual * (proj->largura_frame + espacamento_frame);
    int frame_y = 0;

    // Verificar se os frames est�o dentro dos limites do bitmap
    int bitmap_width = al_get_bitmap_width(proj->sprite);
    int bitmap_height = al_get_bitmap_height(proj->sprite);

    if (frame_x + proj->largura_frame > bitmap_width || frame_y + proj->altura_frame > bitmap_height) {
        fprintf(stderr, "Erro: Frame fora dos limites do bitmap.\n");
        return;
    }

    // Cria um sub-bitmap para o frame atual
    ALLEGRO_BITMAP* frame_bitmap = al_create_sub_bitmap(proj->sprite, frame_x, frame_y, proj->largura_frame, proj->altura_frame);
    if (!frame_bitmap) {
        fprintf(stderr, "Erro ao criar o sub-bitmap do frame.\n");
        return;
    }

    // Calcula o centro do frame para a rota��o
    float sx = proj->largura_frame / 2.0f;
    float sy = proj->altura_frame / 2.0f;

    // Calcula a posi��o de destino (centro) no display
    float dx = proj->x + (proj->largura_frame * proj->escala) / 2.0f;
    float dy = proj->y + (proj->altura_frame * proj->escala) / 2.0f;

    // Rotaciona 180 graus (ALLEGRO_PI radianos)
    float angle = ALLEGRO_PI;

    // Desenha o bitmap rotacionado
    al_draw_scaled_rotated_bitmap(
        frame_bitmap,
        sx, sy,
        dx, dy,
        proj->escala, proj->escala,
        angle,
        0
    );

    // Libera o sub-bitmap
    al_destroy_bitmap(frame_bitmap);
}

// Libera os recursos do projetil
void destroy_projectile(Projectile* proj) {
    if (proj->sprite) {
        al_destroy_bitmap(proj->sprite);
        proj->sprite = NULL;
    }
}
