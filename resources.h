// resources.h
#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// Estrutura para armazenar todos os recursos do jogo
typedef struct {
    ALLEGRO_BITMAP* icon;
    ALLEGRO_FONT* font;
    // Adicione outros recursos aqui se necessário
} Resources;

// Função para carregar todos os recursos
bool load_resources(Resources* res);

// Função para liberar todos os recursos
void destroy_resources(Resources* res);

#endif // RESOURCES_H
