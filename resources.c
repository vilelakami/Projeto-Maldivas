#include "resources.h"
#include <stdio.h>

bool load_resources(Resources* res) {
    // Carrega o ícone
    res->icon = al_load_bitmap("icon.bmp");
    if (!res->icon) {
        fprintf(stderr, "Erro ao carregar o ícone.\n");
        return false;
    }

    // Carrega a imagem do menu
    res->menu_image = al_load_bitmap("assets/menu_1.png");
    if (!res->menu_image) {
        fprintf(stderr, "Erro ao carregar a imagem do menu.\n");
        return false;
    }

    // Carrega a imagem de background da fase 1
    res->BG_1 = al_load_bitmap("assets/BG-1.png");
    if (!res->BG_1) {
        fprintf(stderr, "Erro ao carregar o background da fase 1.\n");
        return false;
    }

    // Carrega a fonte embutida do Allegro
    res->font = al_create_builtin_font();
    if (!res->font) {
        fprintf(stderr, "Erro ao criar a fonte embutida.\n");
        return false;
    }

    // Carrega outros recursos...
    res->bg_prologo = al_load_bitmap("assets/fundoUm.png");
    if (!res->bg_prologo) {
        fprintf(stderr, "Erro ao carregar o prólogo.\n");
        return false;
    }

    res->bg_prologo2 = al_load_bitmap("assets/fundoDoiss.png");
    if (!res->bg_prologo2) {
        fprintf(stderr, "Erro ao carregar o prólogo 2.\n");
        return false;
    }

    res->bg_prologo3 = al_load_bitmap("assets/fundoTres.png");
    if (!res->bg_prologo3) {
        fprintf(stderr, "Erro ao carregar o prólogo 3.\n");
        return false;
    }

    res->bg_prologo4 = al_load_bitmap("assets/fundoQuatro.png");
    if (!res->bg_prologo4) {
        fprintf(stderr, "Erro ao carregar o prólogo 4.\n");
        return false;
    }

    res->creditos = al_load_bitmap("assets/Creditos.png");
    if (!res->creditos) {
        fprintf(stderr, "Erro ao carregar os créditos.\n");
        return false;
    }

    res->instructs = al_load_bitmap("assets/Instrucoes.png");
    if (!res->instructs) {
        fprintf(stderr, "Erro ao carregar as instruções.\n");
        return false;
    }

    res->INTRO = al_load_bitmap("assets/bg_prologo.png");
    if (!res->INTRO) {
        fprintf(stderr, "Erro ao carregar o fundo INTRO.\n");
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
    if (res->BG_1) {
        al_destroy_bitmap(res->BG_1);
        res->BG_1 = NULL;
    }
    if (res->font) {
        al_destroy_font(res->font);
        res->font = NULL;
    }
    if (res->bg_prologo) {
        al_destroy_bitmap(res->bg_prologo);
        res->bg_prologo = NULL;
    }
    if (res->bg_prologo2) {
        al_destroy_bitmap(res->bg_prologo2);
        res->bg_prologo2 = NULL;
    }
    if (res->bg_prologo3) {
        al_destroy_bitmap(res->bg_prologo3);
        res->bg_prologo3 = NULL;
    }
    if (res->bg_prologo4) {
        al_destroy_bitmap(res->bg_prologo4);
        res->bg_prologo4 = NULL;
    }
    if (res->creditos) {
        al_destroy_bitmap(res->creditos);
        res->creditos = NULL;
    }
    if (res->instructs) {
        al_destroy_bitmap(res->instructs);
        res->instructs = NULL;
    }
    if (res->INTRO) {
        al_destroy_bitmap(res->INTRO);
        res->INTRO = NULL;
    }
}