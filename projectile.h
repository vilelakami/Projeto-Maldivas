#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <allegro5/allegro5.h>
#include <stdbool.h>

// Estrutura que representa o projetil
typedef struct {
    float x, y;
    float velocidade_y;
    float escala;
    int largura_frame;
    int altura_frame;
    ALLEGRO_BITMAP* sprite;
    int frame_atual;
    int contador_animacao;
    int velocidade_animacao;
    bool active;
} Projectile;

// Funções de gerenciamento do projetil
void init_projectile(Projectile* proj);
void update_projectile(Projectile* proj, float delta_time);
void draw_projectile(const Projectile* proj);
void destroy_projectile(Projectile* proj);

#endif // PROJECTILE_H
