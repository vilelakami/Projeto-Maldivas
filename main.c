    #include <stdio.h>
    //incluindo biblioteca principal
    #include "allegro5/allegro5.h"
    //incluindo biblioteca do teclado
    #include "allegro5/keyboard.h"
    //incluindo biblioteca pra desenhar coisas
    #include "allegro5/allegro_primitives.h"
    //incluindo biblioteca de imagem
    #include "allegro5/allegro_image.h"
    // incluindo biblioteca de fontes
    #include "allegro5/allegro_ttf.h"
    // incluindo biblioteca de fontes
    #include "allegro5/allegro_font.h"
    // incluindo biblioteca do mouse
    #include "allegro5/mouse.h"

    //criando struct e enumerando telas
    typedef enum {
        PROLOGO,
        FASE_1,
        FASE_2,
        FASE_3,
        FASE_4,
        FINAL1
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

        //inicializo ttf addon
        if (!al_init_ttf_addon() || !al_init_font_addon()) {
            fprintf(stderr, "ERRO ao criar fontes");
            return -1;
        }

        //instalando MOUSE
        if (!al_install_mouse()) {
            fprintf(stderr, "ERRO ao instalar bibliteca do mousq");
            return -1;
        }

        //criando um ponteiro pra criar um display
        ALLEGRO_DISPLAY* tela_inicial;
        //criando um ponteiro pra imagem de fundo 
        ALLEGRO_BITMAP* fundofase1;

        ALLEGRO_BITMAP* fundofase2;

        ALLEGRO_BITMAP* fundofase3;

        ALLEGRO_BITMAP* fundomenu;

        //criando ponteiros pros botoes
        ALLEGRO_BITMAP* play;

        ALLEGRO_BITMAP* howtoplay;

        //ALLEGRO_BITMAP* fundofinal;

        //ALLEGRO_BITMAP* fundofase4;

        //ponteiro pra fonte que eu usei
        ALLEGRO_FONT* fontes,* fontenome, *fontecontorno;

        //crio o display
        tela_inicial = al_create_display(800, 600 );
       
        //carrego as imagems dos backgrounds
        fundofase1 = al_load_bitmap("backgrounds/BG-1.PNG");

        fundofase2 = al_load_bitmap("backgrounds/BG-2.PNG");

        fundofase3 = al_load_bitmap("fundoTres.PNG");

        fundomenu = al_load_bitmap("backgrounds/menu.PNG");

        //carregando sprites
        play = al_load_bitmap("play.PNG");
        howtoplay = al_load_bitmap("howtoplay.PNG");

        // carregando fontes
        fontes = al_load_ttf_font("SpicyRice-Regular.ttf", 24, 0);
        fontenome = al_load_ttf_font("SpicyRice-Regular.ttf", 40, 0);
        fontecontorno = al_load_ttf_font("SpicyRice-Regular.ttf", 43, 0);

      
        //verifica se a tela inicial foi criada, se não retorna erro e -1
        if (!tela_inicial) {
            fprintf(stderr, "erro ao criar display");
            return -1;
        }
        //verifico se o fundo foi carregado, se não ele me retorna -1
        if (!fundofase1 || !fundofase2 || !fundofase3 || !fundomenu || !play || !howtoplay) {
            fprintf(stderr, "erro ao criar fundo");
            return -1;
        }
        //verificando se as fontes foram criadas
        if (!fontes || !fontenome || !fontecontorno) {
            fprintf(stderr, "erro ao criar fontes");
        }
        //deixo o display em branco
        ALLEGRO_COLOR cor_fundo = al_map_rgb(255, 255, 255);


        //colorindo o menu
        ALLEGRO_COLOR cor_nome = al_map_rgb(255, 255, 0);
        ALLEGRO_COLOR cor_contorno = al_map_rgb(0, 0, 0);

        
        //preencho de branco apenas o DISPLAY
        al_clear_to_color(cor_fundo);

        //criando uma fila de eventos pra usar o botão ESC
        ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();

        //se ele nao criar o evento, destrói o display
        if (!fila_eventos) {
            fprintf(stderr, "erro ao criar eventos");
            al_destroy_display(tela_inicial);
            return -1;
        }

        //registrando o evento e o teclado e o mouse
        al_register_event_source(fila_eventos, al_get_keyboard_event_source());
        //al_register_event_source(fila_eventos, al_get_mouse_event_source());

        //declarando as variaveis do circulo
        float x = 360;
        float y = 200;
        float raio = 20;

        //declaro fases e dou o nome de tela atual do jogo, a primeira tela sempre será o PROLOGO
        Fases tela_do_jogo = PROLOGO;

        //declarando uma variavel booleana como falsa
        bool sair = false;

        //desenhando fundo do MENU
        al_draw_scaled_bitmap(fundomenu,
            0, 0,
            al_get_bitmap_width(fundomenu), al_get_bitmap_height(fundomenu),
            0, 0,
            800, 600,
            0);


         //título
//al_draw_text(fontecontorno, cor_contorno, 180, 20, ALLEGRO_ALIGN_CENTRE, "CHERNOBYL GAME");
      //   al_draw_text(fontenome, cor_nome, 180, 20, ALLEGRO_ALIGN_CENTRE, "CHERNOBYL GAME");

         //botao play
         al_draw_scaled_bitmap(play,
             0, 0,
             al_get_bitmap_width(play), al_get_bitmap_height(play),
             325, 300,
             150, 75,
             0);

         //botao how to play
        /* al_draw_scaled_bitmap(howtoplay,
             0, 0,
             al_get_bitmap_width(howtoplay), al_get_bitmap_height(howtoplay),
             280, 200,
             150, 75,
             0);
             */

         al_flip_display();

        //enquanto a tecla ESC nao for clicada:
        while (!sair) {
            
            //crio o evento e espero que alguem clique em esc
            ALLEGRO_EVENT tecla;
            al_wait_for_event(fila_eventos, &tecla);

            /*
            //verifico se o mouse foi clicado
            if (tecla.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                //verificando se foi a tecla do lado esquerdo (eu acho kkk)
                if (tecla.mouse.button == 1) {
                    // NAO ESTOU CONSEGUINDO FAZER ELE VERIFICAR O PLAY
                    if (tecla.mouse.x >= 280 && tecla.mouse.x <= 430 &&
                        tecla.mouse.y >= 120 && tecla.mouse.y <= 195) {
                        tela_do_jogo = FASE_1; 
                    }
                    // NEM ESSE
                    else if (tecla.mouse.x >= 280 && tecla.mouse.x <= 430 &&
                        tecla.mouse.y >= 200 && tecla.mouse.y <= 275) {
                        tela_do_jogo = PROLOGO; 
                    }
                }
            }   
            */

            //verifica se foi clicada alguma tecla
            if (tecla.type == ALLEGRO_EVENT_KEY_DOWN) {

                //verifica se a tecla é a tecla ESC
                if (tecla.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                    sair = true;
               
                //verifica se enter foi clicado
                else if (tecla.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    //verifica se a tela atual é menu, se for e o enter for clicado, ele vai pra próx tela, fase 1
                    if (tela_do_jogo == PROLOGO)
                        tela_do_jogo = FASE_1;

                    //mesma coisa, mas agr verifica se está na tela fase 1
                    else if (tela_do_jogo == FASE_1)
                        tela_do_jogo = FASE_2;

                    //mesma coisa mas verifica se a tela atual é a fase 3
                    else if (tela_do_jogo == FASE_2)
                        tela_do_jogo = FASE_3;

                    //mesma coisa mas verifica se a tela atual é a fase 4
                    else if (tela_do_jogo == FASE_3)
                        tela_do_jogo = FASE_4;

                }

            }

            //preencho de branco apenas o DISPLAY
            al_clear_to_color(cor_fundo);

            //verificando quais foram as telas escolhidas para desenhar o fundo
            switch (tela_do_jogo) {
            case PROLOGO:
                al_clear_to_color(al_map_rgb(0, 0, 255));
                break;

            case FASE_1: 
                al_draw_scaled_bitmap(fundofase1,
                    0, 0,
                    al_get_bitmap_width(fundofase1), al_get_bitmap_height(fundofase1), 
                    0, 0,
                    800, 600, 
                    0);

                //verifica se a tecla é a right, add 10 no x
                if (tecla.keyboard.keycode == ALLEGRO_KEY_D) {
                //verificando se o circulo encosta na borda, pra ele não sair da    tela
                if (x + raio < 650)
                    x = x + 10.0;
            }

                //verifica se a tecla é o left, add -10 no x
                else if (tecla.keyboard.keycode == ALLEGRO_KEY_A) {
                    if (x - raio > 40)
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
                break;

            case FASE_2:
                al_draw_scaled_bitmap(fundofase2,
                    0, 0,
                    al_get_bitmap_width(fundofase2), al_get_bitmap_height(fundofase2),
                    0, 0,
                    800, 600,
                    0);
                break;

            case FASE_3:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(fundofase3,
                    0, 0,
                    al_get_bitmap_width(fundofase3), al_get_bitmap_height(fundofase3),
                    0, 0,
                    800, 600,
                    0);
                break;

            case FASE_4:
                al_clear_to_color(al_map_rgb(0, 120, 255));
                break;

            case FINAL1:
                al_clear_to_color(al_map_rgb(0, 120, 255));
                break;
            }

            //desenha o circulo por cima do display
           

            //atualizando display
            al_flip_display();

        }

        //destruindo eventos
        al_destroy_event_queue(fila_eventos);

        //destruindo display
        al_destroy_display(tela_inicial);

        //destruindo fundos
        al_destroy_bitmap(fundofase1);
        al_destroy_bitmap(fundofase2);
        al_destroy_bitmap(fundofase3);
        al_destroy_bitmap(fundomenu);
        al_destroy_bitmap(play);
        al_destroy_bitmap(howtoplay);
        al_destroy_font(fontes);
        al_destroy_font(fontenome);
        al_destroy_font(fontecontorno);

        return 0;
    }
    
