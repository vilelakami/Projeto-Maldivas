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
    ALLEGRO_BITMAP* protagonista = al_load_bitmap("scientist.png");
    //load bg 
    ALLEGRO_BITMAP* bg = al_load_bitmap("BG-1.png");

    //criando um ponteiro pra criar um display
    ALLEGRO_DISPLAY* tela_inicial;
    //crio o display
    tela_inicial = al_create_display(800, 600);

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
   // al_clear_to_color(cor_circle);

    //criando uma fila de eventos pra usar o botão ESC
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();

    //criando movimentação do sprite
    float frame = 0.f;
    int pos_x = 80;
    int pos_y = 320;
    //qual imagem ele desenha 
    int frame_atual_y = 0;

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
            //verifica se a tecla é a right, add 20 no x
            else if (evento.keyboard.keycode == ALLEGRO_KEY_D) {

                pos_x += 20;
                frame_atual_y = 104;
            }
            //verifica se a tecla é o left, add -20 no x
            else if (evento.keyboard.keycode == ALLEGRO_KEY_A) {
                pos_x -= 20;
                frame_atual_y = 52;
            }
            //verifica se é a tecla UP, add -20 no Y
            else if (evento.keyboard.keycode == ALLEGRO_KEY_W) {
                pos_y -= 20;
                frame_atual_y = 156;
            }
            //verifica se é a tecla DOWN, add +20 no Y
            else if (evento.keyboard.keycode == ALLEGRO_KEY_S) {
                pos_y += 20;
                frame_atual_y = 0;
            }
        }

        //preencho de branco apenas o DISPLAY
        al_clear_to_color(cor_fundo);

        //desenha o bg 
        al_draw_bitmap(bg, 0, 0, 0);

        //desenhando o sprite do personagem - next frame 240
        al_draw_bitmap_region(protagonista, 34 * (int)frame, frame_atual_y, 34 , 52, pos_x, pos_y, 0);
        
        

        //atualizando display
        al_flip_display();

    }
    //destruindo bg
    al_destroy_bitmap(bg);
    //destruindo o sprite
    al_destroy_bitmap(protagonista);
    //destruindo eventos
    al_destroy_event_queue(fila_eventos);
    //destruindo display
    al_destroy_display(tela_inicial);

    return 0;
}

