#include <stdio.h>
//incluindo biblioteca principal
#include "allegro5/allegro5.h"
//incluindo biblioteca do teclado
#include "allegro5/keyboard.h"
//incluindo biblioteca pra desenhar coisas
#include "allegro5/allegro_primitives.h"
//incluindo biblioteca de imagem
#include "allegro5/allegro_image.h"

//criando struct e enumerando telas
typedef enum {
    MENU,
    FASE_1,
    FASE_2,
    FASE_3
}Fases;

int main()
{
    //aqui eu inicializo o programa
    //se der algum erro e não inicializar o programa ele me rettorna -1
    if (!al_init()) {
        fprintf(stderr, "ERRO AO INICIAR");
        return -1;
    }

    //aqui inicializo o keyboard
    //se não instalar o teclado me retorna -1
    if (!al_install_keyboard()) {
        fprintf(stderr, "ERRO ao Instalar teclado");
        return -1;
    }

    //inicializo o primitives
    //se der erro ele me retorna -1
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "ERRO ao criar circulo  ");
        return -1;
    }
    //inicializo o image addon
    //se der erro ele me retorna -1
    if (!al_init_image_addon()) {
        fprintf(stderr, "ERRO ao criar imagem");
        return -1;
    }
    //criando um ponteiro pra criar um display
    ALLEGRO_DISPLAY* tela_inicial;
    //criando um ponteiro pra imagem de fundo da fase 1
    ALLEGRO_BITMAP* fundofase1;

    //crio o display
    tela_inicial = al_create_display(720, 400);
    //carrego a imagem
    fundofase1 = al_load_bitmap("fase1.bmp");


    //verifica se a tela inicial foi criada, se não retorna erro e -1
    if (!tela_inicial) {
        fprintf(stderr, "erro ao criar display");
        return -1;
    }
    //verifico se o fundo foi carregado, se não ele me retorna -1
    if (!fundofase1) {
        fprintf(stderr, "erro ao criar fundo da fase 1");
        return -1;
    }
    //deixo o display em branco
    ALLEGRO_COLOR cor_fundo = al_map_rgb(255, 255, 255);
    //deixando o circulo preto
    ALLEGRO_COLOR cor_circle = al_map_rgb(0, 0, 0);


    //preencho de branco apenas o DISPLAY
    al_clear_to_color(cor_fundo);
    //pintando o circulo
    al_clear_to_color(cor_circle);

    //criando uma fila de eventos pra usar o botão ESC
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();


    //se ele nao criar o evento, destrói o display
    if (!fila_eventos) {
        fprintf(stderr, "erro ao criar eventos");
        al_destroy_display(tela_inicial);
        return -1;
    }

    //registrando o evento e o teclado
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    //declarando as variaveis do circulo
    float x = 360;
    float y = 200;
    float raio = 20;

    //declaro fases e dou o nome de tela atual do jogo, a primeira tela sempre será o MENU
    Fases tela_do_jogo = MENU;

    //declarando uma variavel booleana como falsa
    bool sair = false;

    //enquanto a tecla ESC nao for clicada:
    while (!sair) {

        //crio o evento e espero que alguem clique em esc
        ALLEGRO_EVENT tecla;
        al_wait_for_event(fila_eventos, &tecla);

        //verifica se foi clicada alguma tecla
        if (tecla.type == ALLEGRO_EVENT_KEY_DOWN) {

            //verifica se a tecla é a tecla ESC
            if (tecla.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                sair = true;
            //verifica se a tecla é a right, add 10 no x
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_D) {
                //verificando se o circulo encosta na borda, pra ele não sair da tela
                if (x + raio < 720)
                    x = x + 10.0;
            }

            //verifica se a tecla é o left, add -10 no x
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_A) {
                if (x - raio > 0)
                    x = x - 10.0;
            }

            //verifica se é a tecla UP, add -10 no Y
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_W) {
                if (y - raio > 0)
                    y = y - 10.0;
            }
            //verifica se é a tecla DOWN, add +10 no Y
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_S) {
                if (y + raio < 400)
                    y = y + 10.0;
            }
            //verifica se enter foi clicado
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                //verifica se a tela atual é menu, se for e o enter for clicado, ele vai pra próx tela, fase 1
                if (tela_do_jogo == MENU)
                    tela_do_jogo = FASE_1;
                //mesma coisa, mas agr verifica se está na tela fase 1
                else if (tela_do_jogo == FASE_1)
                    tela_do_jogo = FASE_2;

                //mesma coisa mas verifica se a tela atual é a fase 3
                else if (tela_do_jogo == FASE_2)
                    tela_do_jogo = FASE_3;
            }

        }

        //preencho de branco apenas o DISPLAY
        al_clear_to_color(cor_fundo);

        //verificando quais foram as telas escolhidas para desenhar o fundo
        switch (tela_do_jogo) {
        case MENU:
            al_clear_to_color(al_map_rgb(0, 0, 255));
            break;
        case FASE_1:
            al_draw_bitmap(fundofase1, 0, 0, 0);
            break;
        case FASE_2:
            al_clear_to_color(al_map_rgb(255, 0, 0));
            break;
        case FASE_3:
            al_clear_to_color(al_map_rgb(255, 120, 255));
            break;
        }

        //desenha o circulo por cima do display
        al_draw_filled_circle(x, y, raio, cor_circle);

        //atualizando display
        al_flip_display();

    }

    //destruindo eventos
    al_destroy_event_queue(fila_eventos);
    //destruindo display
    al_destroy_display(tela_inicial);
    //destruindo fundos
    al_destroy_bitmap(fundofase1);
    return 0;
}
