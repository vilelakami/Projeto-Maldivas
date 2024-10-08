
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
    #include "allegro5/allegro_font.h"

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


    //criando struct e enumerando telas
    typedef enum {
        PROLOGO,
        FASE_1,
        FASE_2,
        FASE_3,
        FASE_4,
        GAMEOVER,
        FINAL1
    }Fases;


    

        //aqui inicializo o keyboard
        //se não instalar o teclado me retorna -1
        if (!al_install_keyboard()) {
            fprintf(stderr, "ERRO ao Instalar teclado");
            return -1;
        }
=======
    
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

        //criando um ponteiro pra criar um display
        ALLEGRO_DISPLAY* tela_inicial;
        //criando um ponteiro pra imagem de fundo 
        ALLEGRO_BITMAP* fundofase1;


        ALLEGRO_BITMAP* fundofase2;
=======
    //criando movimentação do sprite
    float frame = 0.f;
    int pos_x = 0;
    int pos_y = 0;
    //qual imagem ele desenha 
    int frame_atual_y = 00;


        ALLEGRO_BITMAP* fundofase3;

        ALLEGRO_BITMAP* fundomenu;

        ALLEGRO_BITMAP* fundoGO;

        ALLEGRO_BITMAP* fundofinal;

        ALLEGRO_BITMAP* fundofase4;

<<<<<<< HEAD
        //ALLEGRO_BITMAP* fundofase4;


        //ponteiro pra fonte que eu usei
        ALLEGRO_FONT* fontes,* fontenome, *fontecontorno;
=======
    

    //declarando uma variavel booleana como falsa
    bool sair = false;

=======
        ALLEGRO_FONT* fontes;
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)

        //crio o display
        tela_inicial = al_create_display(720, 400);
       
        //carrego as imagems dos backgrounds
        fundofase1 = al_load_bitmap("fundoUm.PNG");

        fundofase2 = al_load_bitmap("fundoDoiss.PNG");

<<<<<<< HEAD

        fundofase3 = al_load_bitmap("fundoTres.PNG");
=======
       //frames
        frame += 0.3f;
        if (frame > 3) {
            frame -= 3;
        }

        //verifica se foi clicada alguma tecla
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

=======
        fundofase3 = al_load_bitmap("fundoTres.P    NG");
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)

        fundomenu = al_load_bitmap("menu.PNG");

        fontes = al_load_ttf_font("SpicyRice.ofl", 12, 0);

      
        //verifica se a tela inicial foi criada, se não retorna erro e -1
        if (!tela_inicial) {
            fprintf(stderr, "erro ao criar display");
            return -1;
        }
<<<<<<< HEAD
        //verifico se o fundo foi carregado, se não ele me retorna -1
        if (!fundofase1 || !fundofase2 || !fundofase3 || !fundomenu || !play || !howtoplay) {
=======
        //verifico se o fundo foi carregado, se n�o ele me retorna -1
        if (!fundofase1 || !fundofase2 || !fundofase3 || !fundoGO || !fundofinal || !fundofase4) {
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
            fprintf(stderr, "erro ao criar fundo");
            return -1;
        }
        if (!fontes) {
            fprintf(stderr, "erro ao criar fontes");
        }
        //deixo o display em brancoA
        ALLEGRO_COLOR cor_fundo = al_map_rgb(255, 255, 255);
        //deixando o circulo preto
        ALLEGRO_COLOR cor_circle = al_map_rgb(0, 0, 0);
        ALLEGRO_COLOR cor_rect = al_map_rgb(255, 255, 0);
        ALLEGRO_COLOR cor_startgame = al_map_rgb(0, 0, 0);
        

        //preencho de branco apenas o DISPLAY
        al_clear_to_color(cor_fundo);

<<<<<<< HEAD

        //pintando o circulo
        al_clear_to_color(cor_circle);
=======
        //desenha o circulo por cima do display
        al_draw_filled_circle(x, y, raio, cor_circle);
        //desenhando o sprite do personagem - next frame 240
        al_draw_bitmap_region(protagonista, 0, frame_atual_y, 40 * frame, 40, pos_x, pos_y, 0);
=======
        
        //pintando o circulo
        al_clear_to_color(cor_circle);
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
        


        //criando uma fila de eventos pra usar o botão ESC
        ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();


<<<<<<< HEAD
        //se ele nao criar o evento, destrói o display
=======
        //se ele nao criar o evento, destr�i o display
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
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

        //declaro fases e dou o nome de tela atual do jogo, a primeira tela sempre será o PROLOGO
        Fases tela_do_jogo = PROLOGO;

        //declarando uma variavel booleana como falsa
        bool sair = false;

        al_draw_scaled_bitmap(fundomenu,
            0, 0,
            al_get_bitmap_width(fundomenu), al_get_bitmap_height(fundomenu),
            0, 0,
            720, 400,
            0);

<<<<<<< HEAD

         //título
         al_draw_text(fontecontorno, cor_contorno, 180, 20, ALLEGRO_ALIGN_CENTRE, "CHERNOBYL GAME");
         al_draw_text(fontenome, cor_nome, 180, 20, ALLEGRO_ALIGN_CENTRE, "CHERNOBYL GAME");

         //botao play
         al_draw_scaled_bitmap(play,
             0, 0,
             al_get_bitmap_width(play), al_get_bitmap_height(play),
             280, 120,
             150, 75,
             0);

         //botao how to play
         al_draw_scaled_bitmap(howtoplay,
             0, 0,
             al_get_bitmap_width(howtoplay), al_get_bitmap_height(howtoplay),
             280, 200,
             150, 75,
             0);
=======
    }
    //destruindo o sprite
    al_destroy_bitmap(protagonista);
    //destruindo eventos
    al_destroy_event_queue(fila_eventos);
    //destruindo display
    al_destroy_display(tela_inicial);



         al_flip_display();

=======
        al_draw_filled_rectangle(100, 100, 100, 100, cor_rect);
        al_draw_text(fontes, cor_startgame, 360, 165, ALLEGRO_ALIGN_CENTRE, "START GAME");
        
        al_flip_display();
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
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
               
                //verifica se enter foi clicado
                else if (tecla.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    //verifica se a tela atual é menu, se for e o enter for clicado, ele vai pra próx tela, fase 1
                    if (tela_do_jogo == PROLOGO)
                        tela_do_jogo = FASE_1;
<<<<<<< HEAD

                    //mesma coisa, mas agr verifica se está na tela fase 1
=======
                    //mesma coisa, mas agr verifica se est� na tela fase 1
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
                    else if (tela_do_jogo == FASE_1)
                        tela_do_jogo = FASE_2;

                    //mesma coisa mas verifica se a tela atual é a fase 3
                    else if (tela_do_jogo == FASE_2)
                        tela_do_jogo = FASE_3;

<<<<<<< HEAD
                    //mesma coisa mas verifica se a tela atual é a fase 4
=======
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
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
                    720, 400, 
<<<<<<< HEAD
                    0);

                //verifica se a tecla é a right, add 10 no x
                if (tecla.keyboard.keycode == ALLEGRO_KEY_D) {
                //verificando se o circulo encosta na borda, pra ele não sair da    tela
=======
                    0); 
                //verifica se a tecla � a right, add 10 no x
             if (tecla.keyboard.keycode == ALLEGRO_KEY_D) {
                //verificando se o circulo encosta na borda, pra ele n�o sair da    tela
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
                if (x + raio < 650)
                    x = x + 10.0;
            }

<<<<<<< HEAD
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
=======
            //verifica se a tecla � o left, add -10 no x
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_A) {
                if (x - raio > 40)
                    x = x - 10.0;
            }

            //verifica se � a tecla UP, add -10 no Y
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_W) {
                if (y - raio > 0)
                    y = y - 10.0;
            }
            //verifica se � a tecla DOWN, add +10 no Y
            else if (tecla.keyboard.keycode == ALLEGRO_KEY_S) {
                if (y + raio < 400)
                    y = y + 10.0;
            }
>>>>>>> parent of 98744c1 (tela de menu, backgrounds)
                break;
            case FASE_2:
                al_draw_scaled_bitmap(fundofase2,
                    0, 0,
                    al_get_bitmap_width(fundofase2), al_get_bitmap_height(fundofase2),
                    0, 0,
                    720, 400,
                    0);
                break;
            case FASE_3:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_scaled_bitmap(fundofase3,
                    0, 0,
                    al_get_bitmap_width(fundofase3), al_get_bitmap_height(fundofase3),
                    0, 0,
                    720, 400,
                    0);
                break;
            case FASE_4:
                al_clear_to_color(al_map_rgb(0, 120, 255));
                break;
            case GAMEOVER:
                break;
            case FINAL1:
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

        al_destroy_bitmap(fundofase2);
        return 0;
    }
