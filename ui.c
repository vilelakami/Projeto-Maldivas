#include "ui.h"
#include "player.h"
#include <allegro5/allegro_primitives.h>

void draw_life_bar(Player* player) {
    int x = 50;
    int y = 50;
    int largura_max = 200;
    int altura = 20;

    float vida_ratio = (float)player->vida_atual / player->vida_maxima;
    if (vida_ratio < 0) vida_ratio = 0;
    int largura_atual = (int)(largura_max * vida_ratio);

    al_draw_filled_rectangle(x, y, x + largura_max, y + altura, al_map_rgb(100, 100, 100));
    al_draw_filled_rectangle(x, y, x + largura_atual, y + altura, al_map_rgb(0, 255, 0));
    al_draw_rectangle(x, y, x + largura_max, y + altura, al_map_rgb(255, 255, 255), 2);
}

bool is_point_inside_rect(int x, int y, Rect rect) {
    return (x >= rect.x1 && x <= rect.x2 && y >= rect.y1 && y <= rect.y2);
}

bool init_ui() {
    return true;
}

void destroy_ui() {
}
