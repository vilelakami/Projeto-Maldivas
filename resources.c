// resources.c
#include "resources.h"
#include <stdio.h>

bool load_resources(Resources* res) {
    // Carrega o �cone
    res->icon = al_load_bitmap("icon.bmp");
    if (!res->icon) {
        fprintf(stderr, "Erro ao carregar o �cone.\n");
        return false;
    }

    // Carrega a imagem do menu
    res->menu_image = al_load_bitmap("assets/menu.png");
    if (!res->menu_image) {
        fprintf(stderr, "Erro ao carregar a imagem do menu.\n");
        return false;
    }

    // Cria a fonte incorporada do Allegro
    res->font = al_create_builtin_font();
    if (!res->font) {
        fprintf(stderr, "Erro ao criar a fonte incorporada.\n");
        return false;
    }

    printf("Recursos carregados com sucesso.\n");
    return true;
}

void destroy_resources(Resources* res) {
    if (res->icon) {
        al_destroy_bitmap(res->icon);
        res->icon = NULL;
    }
    if (res->menu_image) {
        al_destroy_bitmap(res->menu_image);
        res->menu_image = NULL;
    }
    if (res->font) {
        al_destroy_font(res->font);
        res->font = NULL;
    }
}
