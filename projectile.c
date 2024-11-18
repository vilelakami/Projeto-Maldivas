#include "projectile.h"
#include "constants.h" // Para SCREEN_WIDTH e SCREEN_HEIGHT
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>

void init_projectile(Projectile* proj) {
    // Carrega o sprite do projetil
    proj->sprite = al_load_bitmap("assets/projetil.png");
    if (!proj->sprite) {
        fprintf(stderr, "Erro ao carregar o sprite do projetil.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa as propriedades do projetil
    proj->escala = 4.0f;
    proj->largura_frame = 14;
    proj->altura_frame = 32;
    proj->x = 0;
    proj->y = 0;
    proj->velocidade_y = 150.0f;
    proj->frame_atual = 0;
    proj->contador_animacao = 0;
    proj->velocidade_animacao = 10;
    proj->active = false;
}

void update_projectile(Projectile* proj, float delta_time) {
    if (!proj->active) return;

    // Atualiza a posição com base no delta_time
    proj->y += proj->velocidade_y * delta_time;

    // Atualiza a animação
    proj->contador_animacao++;
    if (proj->contador_animacao >= proj->velocidade_animacao) {
        proj->contador_animacao = 0;
        proj->frame_atual = (proj->frame_atual + 1) % 4; // 4 frames (0 a 3)
    }
}

void draw_projectile(const Projectile* proj) {
    if (!proj->active) return;

    if (!proj->sprite) {
        fprintf(stderr, "Erro: proj->sprite é NULL.\n");
        return; // Evita tentar desenhar um bitmap nulo
    }

    // Define o espaçamento entre os frames
    const int espacamento_frame = 5; // 4 pixels de distância entre os frames

    // Calcula a posição X do frame atual no sprite sheet
    int frame_x = proj->frame_atual * (proj->largura_frame + espacamento_frame);
    int frame_y = 0;

    // Verificar se os frames estão dentro dos limites do bitmap
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

    // Calcula o centro do frame para a rotação
    float sx = proj->largura_frame / 2.0f;
    float sy = proj->altura_frame / 2.0f;

    // Calcula a posição de destino (centro) no display
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

void destroy_projectile(Projectile* proj) {
    if (proj->sprite) {
        al_destroy_bitmap(proj->sprite);
        proj->sprite = NULL;
    }
}
