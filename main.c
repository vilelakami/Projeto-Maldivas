#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_mouse.h"

// Definindo as dimens�es da tela
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 400
#define FPS 60

// Enum para estados do jogo
typedef enum {
    MENU,
    PROLOGO,
    FASE_1,
    FASE_2,
    FASE_3,
    FINAL1
} GameState;

// Fun��o para inicializar as imagens/fontes etc
bool init_resources(ALLEGRO_BITMAP** fundofase1, ALLEGRO_BITMAP** fundofase2,
    ALLEGRO_BITMAP** fundofase3, ALLEGRO_BITMAP** prologo,
    ALLEGRO_BITMAP** fundomenu, ALLEGRO_BITMAP** play,
    ALLEGRO_BITMAP** howtoplay, ALLEGRO_FONT** fontes,
    ALLEGRO_FONT** fontenome, ALLEGRO_FONT** fontecontorno) {
    *fundofase1 = al_load_bitmap("lab1.PNG");
    *fundofase2 = al_load_bitmap("lab2.PNG");
    *fundofase3 = al_load_bitmap("lab3.PNG");
    *prologo = al_load_bitmap("prologo.PNG");
    *fundomenu = al_load_bitmap("menu.PNG");
    *play = al_load_bitmap("play.PNG");
    *howtoplay = al_load_bitmap("howtoplay.PNG");
    *fontes = al_load_ttf_font("SpicyRice-Regular.ttf", 24, 0);
    *fontenome = al_load_ttf_font("SpicyRice-Regular.ttf", 40, 0);
    *fontecontorno = al_load_ttf_font("SpicyRice-Regular.ttf", 43, 0);

    return (*fundofase1 && *fundofase2 && *fundofase3 &&
        *prologo && *fundomenu && *play && *howtoplay &&
        *fontes && *fontenome && *fontecontorno);
}

int main() {
    // Inicializa��o do Allegro
    if (!al_init()) {
        fprintf(stderr, "Erro ao inicializar o Allegro.\n");
        return -1;
    }

    //instala o teclado, mouse, addons
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // Cria��o da janela
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        fprintf(stderr, "Erro ao criar o display.\n");
        return -1;
    }

    // imagens e fontes
    ALLEGRO_BITMAP* fundofase1, * fundofase2, * fundofase3, * prologo, * fundomenu;
    ALLEGRO_BITMAP* play, * howtoplay;
    ALLEGRO_FONT* fontes, * fontenome, * fontecontorno;

    // carregando imagens
    if (!init_resources(&fundofase1, &fundofase2, &fundofase3, &prologo,
        &fundomenu, &play, &howtoplay, &fontes,
        &fontenome, &fontecontorno)) {
        al_destroy_display(display);
        return -1;
    }

    // Configura��o do evento
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // inicializando a primeira tela e a variavel booleana pro loop
    GameState estado_jogo = MENU;
    bool sair = false;

    // Loop principal do jogo
    while (!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(queue, &evento);

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            sair = true;
        }

        // Menu
        if (estado_jogo == MENU) {
            al_draw_scaled_bitmap(fundomenu, 0, 0,
                al_get_bitmap_width(fundomenu),
                al_get_bitmap_height(fundomenu),
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
            al_draw_text(fontecontorno, al_map_rgb(0, 0, 0), SCREEN_WIDTH / 2, 20, ALLEGRO_ALIGN_CENTRE, "CHERNOBYL GAME");
            al_draw_scaled_bitmap(play, 0, 0, al_get_bitmap_width(play), al_get_bitmap_height(play), 280, 120, 150, 75, 0);
            al_draw_scaled_bitmap(howtoplay, 0, 0, al_get_bitmap_width(howtoplay), al_get_bitmap_height(howtoplay), 280, 200, 150, 75, 0);
            al_flip_display();

            //n ta funcionando (mouse)
            if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && evento.mouse.button == 1) {
                if (evento.mouse.x >= 280 && evento.mouse.x <= 430 &&
                    evento.mouse.y >= 120 && evento.mouse.y <= 195) {
                    estado_jogo = PROLOGO;
                }
                else if (evento.mouse.x >= 280 && evento.mouse.x <= 430 &&
                    evento.mouse.y >= 200 && evento.mouse.y <= 275) {
                    // n ta funcionando
                }
            }
        }
        // Prologo
        else if (estado_jogo == PROLOGO) {
            al_draw_scaled_bitmap(prologo, 0, 0,
                al_get_bitmap_width(prologo),
                al_get_bitmap_height(prologo),
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
            al_flip_display();

            if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                estado_jogo = FASE_1;
            }
        }
        // Fases do jogo (usei esse comando da internet pra ficar mais renderizado
        else if (estado_jogo == FASE_1 || estado_jogo == FASE_2 || estado_jogo == FASE_3) {
            ALLEGRO_BITMAP* fundo_atual = (estado_jogo == FASE_1) ? fundofase1 : (estado_jogo == FASE_2) ? fundofase2 : fundofase3;

            //desenhando fundo atual
            al_draw_scaled_bitmap(fundo_atual, 0, 0,
                al_get_bitmap_width(fundo_atual),
                al_get_bitmap_height(fundo_atual),
                0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
            al_flip_display();

            //desenhando a tela atual em cada fase
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
                if (evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (estado_jogo == FASE_1) estado_jogo = FASE_2;
                    else if (estado_jogo == FASE_2) estado_jogo = FASE_3;
                    else if (estado_jogo == FASE_3) estado_jogo = FINAL1;
                }
            }
        }
        // Tela final // n fiz ainda
        else if (estado_jogo == FINAL1) {
            al_clear_to_color(al_map_rgb(0, 120, 255));
            al_flip_display();
        }
    }

    // destroindo tudo
    al_destroy_bitmap(fundofase1);
    al_destroy_bitmap(fundofase2);
    al_destroy_bitmap(fundofase3);
    al_destroy_bitmap(prologo);
    al_destroy_bitmap(fundomenu);
    al_destroy_bitmap(play);
    al_destroy_bitmap(howtoplay);
    al_destroy_font(fontes);
    al_destroy_font(fontenome);
    al_destroy_font(fontecontorno);
    al_destroy_event_queue(queue);
    al_destroy_display(display);

    return 0;
}
