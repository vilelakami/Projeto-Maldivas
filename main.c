#include <stdio.h>
//incluindo biblioteca principal
#include "allegro5/allegro5.h"
//incluindo biblioteca do teclado
#include "allegro5/keyboard.h"
//incluindo biblioteca pra desenhar coisas
#include "allegro5/allegro_primitives.h"
//biblioteca de imagem;
#include "allegro5/allegro_image.h"

int main()
{



    //aqui eu inicializo o programa
    //se der algum erro e não inicializar o programa ele me rettorna -1
    if (!al_init()) {
        fprintf(stderr, "ERRO AO INICIAR");
        return -1;
    }
    //inicia biblioteca de imagem
    al_init_image_addon();

    //aqui inicializo o keyboard
    //se não instalar o teclado me retorna -1
    if (!al_install_keyboard()) {
        fprintf(stderr, "ERRO ao Instalar teclado");
        return -1;
    }

    //inicializo o primitives
    //se der erro ele me retorna -1
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "ERRO ao criar quadrado");
        return -1;
    }
    //load icon da janela
    ALLEGRO_BITMAP* icon = al_load_bitmap("icon.bmp");
    //load sprite personagem principal
    ALLEGRO_BITMAP* protagonista = al_load_bitmap("cientista.png");

    //criando um ponteiro pra criar um display
    ALLEGRO_DISPLAY* tela_inicial;
    //crio o display
    tela_inicial = al_create_display(1280, 720);

    //nome da janela
   al_set_window_title(tela_inicial, "Chernobyl Game");
   //funcao que coloca icone na janel
   al_set_display_icon(tela_inicial, icon);
   

    //verifica se a tela inicial foi criada, se não retorna erro e -1
    if (!tela_inicial) {
        fprintf(stderr, "erro ao criar display");
        return -1;
    }

    //deixo o display em branco
    ALLEGRO_COLOR cor_fundo = al_map_rgb(255, 255, 255);
    //deixando o circulo preto
    ALLEGRO_COLOR cor_circle = al_map_rgb(0, 0, 0);

    //pintando o circulo
    al_clear_to_color(cor_circle);

    //criando uma fila de eventos pra usar o botão ESC
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();

    //criando movimentação do sprite
    float frame = 0.f;
    int pos_x = 0;
    int pos_y = 0;
    //qual imagem ele desenha 
    int frame_atual_y = 00;

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

    

    //declarando uma variavel booleana como falsa
    bool sair = false;

    //enquanto a tecla ESC nao for clicada:
    while (!sair) {

        //crio o evento e espero que alguem clique em esc
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

       //frames
        frame += 0.3f;
        if (frame > 3) {
            frame -= 3;
        }

        //verifica se foi clicada alguma tecla
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

            //verifica se a tecla é a tecla ESC
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                sair = true;
            //verifica se a tecla é a right, add 10 no x
            else if (evento.keyboard.keycode == ALLEGRO_KEY_D)
                x = x + 10.0;

            //verifica se a tecla é o left, add -10 no x
            else if (evento.keyboard.keycode == ALLEGRO_KEY_A)
                x = x - 10.0;

            //verifica se é a tecla UP, add -10 no Y
            else if (evento.keyboard.keycode == ALLEGRO_KEY_W)
                y = y - 10.0;

            //verifica se é a tecla DOWN, add +10 no Y
            else if (evento.keyboard.keycode == ALLEGRO_KEY_S)
                y = y + 10.0;
        }

        //preencho de branco apenas o DISPLAY
        al_clear_to_color(cor_fundo);

        //desenha o circulo por cima do display
        al_draw_filled_circle(x, y, raio, cor_circle);
        //desenhando o sprite do personagem - next frame 240
        al_draw_bitmap_region(protagonista, 0, frame_atual_y, 40 * frame, 40, pos_x, pos_y, 0);
        

        //atualizando display
        al_flip_display();

    }
    //destruindo o sprite
    al_destroy_bitmap(protagonista);
    //destruindo eventos
    al_destroy_event_queue(fila_eventos);
    //destruindo display
    al_destroy_display(tela_inicial);

    return 0;
}

