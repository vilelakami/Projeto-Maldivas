// resources.h
#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>


// Estrutura para armazenar todos os recursos do jogo
typedef struct {
    ALLEGRO_BITMAP* BG_1;
    ALLEGRO_BITMAP* icon;
    ALLEGRO_BITMAP* menu_image;
    ALLEGRO_FONT* font;
    ALLEGRO_BITMAP* bg_prologo;
    ALLEGRO_BITMAP* bg_prologo2;
    ALLEGRO_BITMAP* bg_prologo3;
    ALLEGRO_BITMAP* bg_prologo4;
    ALLEGRO_BITMAP* creditos;
    ALLEGRO_BITMAP* instructs;

} Resources;

// Função para carregar todos os recursos
bool load_resources(Resources* res);

// Função para liberar todos os recursos
void destroy_resources(Resources* res);

#endif // RESOURCES_H