// resources.c
#include "resources.h"
#include <stdio.h>

bool load_resources(Resources* res) {
    // Carrega o ícone
    res->icon = al_load_bitmap("icon.bmp");
    if (!res->icon) {
        fprintf(stderr, "Erro ao carregar o ícone.\n");
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
    if (res->font) {
        al_destroy_font(res->font);
        res->font = NULL;
    }
    // Libere outros recursos aqui se necessário
}
