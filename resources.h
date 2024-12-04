// resources.h
#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


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
    ALLEGRO_BITMAP* INTRO;
    ALLEGRO_SAMPLE* som_trilha_sonora;
    ALLEGRO_SAMPLE_INSTANCE* inst_trilha;
    ALLEGRO_SAMPLE* som_hit;
    ALLEGRO_SAMPLE* som_gameOver;


} Resources;

// Função para carregar todos os recursos
bool load_resources(Resources* res);

// Função para liberar todos os recursos
void destroy_resources(Resources* res);

#endif // RESOURCES_H