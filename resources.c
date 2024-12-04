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

    // Carrega a imagem do menu
    res->menu_image = al_load_bitmap("assets/menu_1.png");
    if (!res->menu_image) {
        fprintf(stderr, "Erro ao carregar a imagem do menu.\n");
        return false;
    }
    // Carrega o a imagem  background da fase 1
    res->BG_1 = al_load_bitmap("assets/BG-1.png");
    if (!res->BG_1) {
        fprintf(stderr, "Erro ao carregar o background fase 1.\n");
        return false;
    }

    // Cria a fonte incorporada do Allegro
    res->font = al_create_builtin_font();
    if (!res->font) {
        fprintf(stderr, "Erro ao criar a fonte incorporada.\n");
        return false;
    }

    res->bg_prologo = al_load_bitmap("assets/fundoUm.png");
    if (!res->bg_prologo) {
        fprintf(stderr, "Erro ao carregar o prologo.\n");
        return false;
    }

    res->bg_prologo2 = al_load_bitmap("assets/fundoDoiss.png");
    if (!res->bg_prologo2) {
        fprintf(stderr, "Erro ao carregar o prologo 2.\n");
        return false;
    }

    res->bg_prologo3 = al_load_bitmap("assets/fundoTres.png");
    if (!res->bg_prologo3) {
        fprintf(stderr, "Erro ao carregar o prologo 3.\n");
        return false;
    }

    res->bg_prologo4 = al_load_bitmap("assets/fundoQuatro.png");
    if (!res->bg_prologo4) {
        fprintf(stderr, "Erro ao carregar o prologo 4.\n");
        return false;
    }
    res->INTRO = al_load_bitmap("assets/bg_prologo.png");
    if (!res->INTRO) {
        fprintf(stderr, "Erro ao carregar a bg INTRO. \n");
        return false;
    }


    res->creditos = al_load_bitmap("assets/Creditos.png");
    if (!res->creditos) {
        fprintf(stderr, "Erro ao carregar o créditos.\n");
        return false;
    }

    res->instructs = al_load_bitmap("assets/Instrucoes.png");
    if (!res->instructs) {
        fprintf(stderr, "Erro ao carregar o Instruções.\n");
        return false;
    }

    res->som_trilha_sonora = al_load_sample("assets/sons/trilhaSonora.wav");
    if (!res->som_trilha_sonora) {
        fprintf(stderr, "Erro ao carregar a trilha sonora.\n");
        return -1;
    }

    res->inst_trilha = al_create_sample_instance(res->som_trilha_sonora);
    if (!res->inst_trilha) {
        fprintf(stderr, "Erro ao carregar a instancia trilha sonora.\n");
        return -1;
    }

    res->som_hit = al_load_sample("assets/Sons/PlayerDie.wav");
    if (!res->som_hit) {
        fprintf(stderr, "Erro ao carregar o som de hit.\n");
        return false;
    }

    res->som_gameOver = al_load_sample("assets/Sons/gameOverSound.wav", 0.3);
    if (!res->som_gameOver) {
        fprintf(stderr, "Erro ao carregar o som game over.\n");
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
    if (res->INTRO) {
        al_destroy_bitmap(res->INTRO);
        res->INTRO = NULL;
    }
    if (res->creditos) {
        al_destroy_bitmap(res->creditos);
        res->creditos = NULL;
    }
    if (res->instructs) {
        al_destroy_bitmap(res->instructs);
        res->instructs = NULL;
    }
    if (res->som_trilha_sonora) {
        al_destroy_sample(res->som_trilha_sonora);
        res->som_trilha_sonora = NULL;
    }
    if (res->inst_trilha) {
        al_destroy_sample(res->inst_trilha);
        res->inst_trilha = NULL;
    }
    if (res->som_hit) {
        al_destroy_sample(res->som_hit);
        res->som_hit = NULL;
    }
    if (res->som_gameOver) {
        al_destroy_sample(res->som_gameOver);
        res->som_gameOver = NULL;
    }

}