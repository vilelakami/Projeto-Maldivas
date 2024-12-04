// resources.h
#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

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
    ALLEGRO_BITMAP* INTRO; // Adicionado
} Resources;

// Funções existentes
bool load_resources(Resources* res);
void destroy_resources(Resources* res);

#endif // RESOURCES_H
