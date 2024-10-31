// ui.c
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

// Desenha a barra de vida
void draw_life_bar(Player* player) {
    // Define a posição e tamanho da barra de vida
    int x = 50;
    int y = 50;
    int largura_max = 200;
    int altura = 20;

    // Calcula a largura atual da barra de vida
    float vida_ratio = (float)player->vida_atual / player->vida_maxima;
    if (vida_ratio < 0) vida_ratio = 0;
    int largura_atual = (int)(largura_max * vida_ratio);

    // Desenha o fundo da barra (cinza)
    al_draw_filled_rectangle(x, y, x + largura_max, y + altura, al_map_rgb(100, 100, 100));

    // Desenha a vida atual (verde)
    al_draw_filled_rectangle(x, y, x + largura_atual, y + altura, al_map_rgb(0, 255, 0));

    // Desenha a borda branca
    al_draw_rectangle(x, y, x + largura_max, y + altura, al_map_rgb(255, 255, 255), 2);
}

// Verifica se um ponto está dentro de um retângulo
bool is_point_inside_rect(int x, int y, Rect rect) {
    return (x >= rect.x1 && x <= rect.x2 && y >= rect.y1 && y <= rect.y2);
}

// Inicializa o módulo de UI
bool init_ui() {
    return true;
}

// Finaliza o módulo de UI
void destroy_ui() {
}
