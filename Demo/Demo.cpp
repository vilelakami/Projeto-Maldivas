#include <stdio.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

int main()
{
    ALLEGRO_DISPLAY* janelaprin = NULL;
    ALLEGRO_BITMAP* teladefundo = NULL;

    // Inicializa a biblioteca Allegro
    if (!al_init()) {
        fprintf(stderr, "ERRO AO INICIALIZAR A ALLEGRO!\n");
        return -1;
    }

    // Inicializa o módulo de imagem
    if (!al_init_image_addon()) {
        fprintf(stderr, "ERRO AO INICIALIZAR O MODULO DE IMAGEM!\n");
        return -1;
    }

    // Cria a janela
    janelaprin = al_create_display(720, 400);
    if (!janelaprin) {
        fprintf(stderr, "Erro ao criar a janela!\n");
        return -1;
    }

    // Carrega a imagem
    teladefundo = al_load_bitmap("seila.png");
    if (!teladefundo) {
        fprintf(stderr, "Erro ao carregar a imagem!\n");
        al_destroy_display(janelaprin);
        return -1;
    }

    // Limpa a tela com a cor branca
    al_clear_to_color(al_map_rgb(255, 255, 255));

    // Desenha a imagem na tela
    al_draw_bitmap(teladefundo, 0, 0, 0);

    // Atualiza a tela para mostrar a imagem
    al_flip_display();

    // Deixa a tela visível por 10 segundos
    al_rest(10.0);

    // Destroi a imagem
    al_destroy_bitmap(teladefundo);

    // Destroi a janela
    al_destroy_display(janelaprin);

    return 0;
}
