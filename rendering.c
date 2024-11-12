// rendering.c
#include "rendering.h"
#include "constants.h"


static bool button_pressed = false;

void render_game(GameState estado, Resources* res, Player* player, Projectile* proj,
    Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y, Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button) {
    if (estado == MENU) {
        // Desenha a imagem do menu ou limpa a tela
        if (res->menu_image) {
            al_draw_bitmap(res->menu_image, 0, 0, 0);
        }
        else {
            al_clear_to_color(al_map_rgb(0, 0, 0)); 
        }

        // Bot�o "Start": Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_start = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= start_button.x1 && mouse_x <= start_button.x2 &&
            mouse_y >= start_button.y1 && mouse_y <= start_button.y2) {
            cor_start = al_map_rgb(150, 150, 150); // Cor quando o mouse est� sobre o bot�o
        }

        // Desenha o bot�o "Start"
        al_draw_filled_rectangle(
            start_button.x1, start_button.y1,
            start_button.x2, start_button.y2,
            cor_start
        );
        al_draw_rectangle(
            start_button.x1, start_button.y1,
            start_button.x2, start_button.y2,
            al_map_rgb(255, 255, 255), 2
        );

        // Desenha o texto "Start" no bot�o
        if (res->font) {
            const char* texto_start = "Start";
            int largura_texto = al_get_text_width(res->font, texto_start);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (start_button.x1 + start_button.x2 - largura_texto) / 2,
                (start_button.y1 + start_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_start);
        }
        //-------------------------------------------------------------Cr�ditos---------------------------------------------------------

        // Bot�o "Creditos": Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_credits = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= credits_button.x1 && mouse_x <= credits_button.x2 &&
            mouse_y >= credits_button.y1 && mouse_y <= credits_button.y2) {
            cor_credits = al_map_rgb(150, 150, 150); // Cor quando o mouse est� sobre o bot�o
        }
        // Desenha o bot�o "Creditos"
        al_draw_filled_rectangle(
            credits_button.x1, credits_button.y1,
            credits_button.x2, credits_button.y2,
            cor_credits
        );
        al_draw_rectangle(
            credits_button.x1, credits_button.y1,
            credits_button.x2, credits_button.y2,
            al_map_rgb(255, 255, 255), 2
        );
        // Desenha o texto "Creditos" no bot�o
        if (res->font) {
            const char* texto_credits = "Creditos";
            int largura_texto = al_get_text_width(res->font, texto_credits);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (credits_button.x1 + credits_button.x2 - largura_texto) / 2,
                (credits_button.y1 + credits_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_credits);
        }
        //-------------------------------------------------------------Instru��es---------------------------------------------------------

        // Bot�o "Instru��es": Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_instructs = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= Instructs_button.x1 && mouse_x <= Instructs_button.x2 &&
            mouse_y >= Instructs_button.y1 && mouse_y <= Instructs_button.y2) {
            cor_instructs = al_map_rgb(150, 150, 150); // Cor quando o mouse est� sobre o bot�o
        }
        // Desenha o bot�o "Instru��es"
        al_draw_filled_rectangle(
            Instructs_button.x1, Instructs_button.y1,
            Instructs_button.x2, Instructs_button.y2,
            cor_instructs
        );
        al_draw_rectangle(
            Instructs_button.x1, Instructs_button.y1,
            Instructs_button.x2, Instructs_button.y2,
            al_map_rgb(255, 255, 255), 2
        );

        // Desenha o texto "Instru��es" no bot�o
        if (res->font) {
            const char* texto_intructions = "Instrucoes";
            int largura_texto = al_get_text_width(res->font, texto_intructions);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (Instructs_button.x1 + Instructs_button.x2 - largura_texto) / 2,
                (Instructs_button.y1 + Instructs_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_intructions);
        }

        // Verifique se o bot�o "Creditos" ou "Instru��es" foi clicado
        if (mouse_x >= credits_button.x1 && mouse_x <= credits_button.x2 &&
            mouse_y >= credits_button.y1 && mouse_y <= credits_button.y2) {
            // Exibe a imagem de cr�ditos
            if (res->creditos) {
                al_draw_bitmap(res->creditos, 0, 0, 0); // Desenha a imagem de cr�ditos
                button_pressed = true;
            }
        }

            if (mouse_x >= Instructs_button.x1 && mouse_x <= Instructs_button.x2 &&
            mouse_y >= Instructs_button.y1 && mouse_y <= Instructs_button.y2) {
            // Exibe a imagem das instru��es
            if (res->instructs) {
                al_draw_bitmap(res->instructs, 0, 0, 0); // Desenha a imagem das instru��es
                button_pressed = true;
            }
        }

        // Finalize o desenho
        al_flip_display();  // Atualiza a tela
    }
    
    //-------------------------------------------------------------Prologo---------------------------------------------------------


    else if (estado == PROLOGO) {
        al_clear_to_color(COR_FUNDO);
        al_draw_bitmap(res->bg_prologo, 0, 0, 0);

        // Bot�o "Prologo": Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_prologo = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= prologo_button.x1 && mouse_x <= prologo_button.x2 &&
            mouse_y >= prologo_button.y1 && mouse_y <= prologo_button.y2) {
            cor_prologo = al_map_rgb(150, 150, 150); // Cor quando o mouse est� sobre o bot�o
        }

        // Desenha o bot�o "Prologo"
        al_draw_filled_rectangle(
            prologo_button.x1, prologo_button.y1,
            prologo_button.x2, prologo_button.y2,
            cor_prologo
        );
        al_draw_rectangle(
            prologo_button.x1, prologo_button.y1,
            prologo_button.x2, prologo_button.y2,
            al_map_rgb(255, 255, 255), 2
        );

        // Desenha o texto "Prologo" no bot�o
        if (res->font) {
            if (res->font) {
                const char* texto_prologo = "Continua";

                // Calcular a largura e altura do texto
                int largura_texto = al_get_text_width(res->font, texto_prologo);
                int altura_texto = al_get_font_line_height(res->font);

                // Coordenadas fixas para o bot�o
                int x1 = 907;
                int y1 = 615;
                int x2 = 1049;
                int y2 = 657;

                // Calcular a posi��o X para centralizar o texto
                float pos_x = (x1 + x2 - largura_texto) / 2;

                // Calcular a posi��o Y para centralizar o texto
                float pos_y = (y1 + y2 - altura_texto) / 2;

                // Desenhar o texto na tela
                al_draw_text(res->font, al_map_rgb(255, 255, 255), pos_x, pos_y, ALLEGRO_ALIGN_LEFT, texto_prologo);
            }

        }

        al_flip_display();

    }
    //---------------------------------------------------Fase 1---------------------------------------
    else if (estado == FASE_1) {
        al_clear_to_color(COR_FUNDO);
        al_draw_bitmap(res->BG_1, 0, 0, 0);
        // Desenha o proj�til
        draw_projectile(proj);

        // Desenha o jogador
        draw_player(player);

        // Desenha a barra de vida
        draw_life_bar(player);

        al_flip_display();
    }
    else if (estado == GAME_OVER) {
        // Desenha a tela de Game Over
        al_clear_to_color(COR_GAME_OVER); // Fundo preto

        if (res->font) {
            // Desenha "GAME OVER" no centro superior
            const char* texto_game_over = "GAME OVER";
            int largura_texto = al_get_text_width(res->font, texto_game_over);
            al_draw_text(res->font, al_map_rgb(255, 0, 0), (SCREEN_WIDTH - largura_texto) / 2, 200, ALLEGRO_ALIGN_LEFT, texto_game_over);
        }

        // Bot�o Continuar: Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_continuar = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= continuar_botao.x1 && mouse_x <= continuar_botao.x2 &&
            mouse_y >= continuar_botao.y1 && mouse_y <= continuar_botao.y2) {
            cor_continuar = al_map_rgb(150, 150, 150); // Cor hover
        }

        // Bot�o Sair: Verifica se o mouse est� sobre o bot�o
        ALLEGRO_COLOR cor_sair = al_map_rgb(100, 100, 100); // Cor padr�o
        if (mouse_x >= sair_botao.x1 && mouse_x <= sair_botao.x2 &&
            mouse_y >= sair_botao.y1 && mouse_y <= sair_botao.y2) {
            cor_sair = al_map_rgb(150, 150, 150); // Cor hover
        }

        // Bot�o Continuar
        al_draw_filled_rectangle(
            continuar_botao.x1, continuar_botao.y1,
            continuar_botao.x2, continuar_botao.y2,
            cor_continuar // Cor ajustada
        );
        al_draw_rectangle(
            continuar_botao.x1, continuar_botao.y1,
            continuar_botao.x2, continuar_botao.y2,
            al_map_rgb(255, 255, 255), 2 // Borda branca
        );

        if (res->font) {
            const char* texto_continuar = "Continuar";
            int largura_botao = al_get_text_width(res->font, texto_continuar);
            int altura_botao = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (continuar_botao.x1 + continuar_botao.x2 - largura_botao) / 2,
                (continuar_botao.y1 + continuar_botao.y2 - altura_botao) / 2,
                ALLEGRO_ALIGN_LEFT, texto_continuar);
        }

        // Bot�o Sair
        al_draw_filled_rectangle(
            sair_botao.x1, sair_botao.y1,
            sair_botao.x2, sair_botao.y2,
            cor_sair // Cor ajustada
        );
        al_draw_rectangle(
            sair_botao.x1, sair_botao.y1,
            sair_botao.x2, sair_botao.y2,
            al_map_rgb(255, 255, 255), 2 // Borda branca
        );

        if (res->font) {
            const char* texto_sair = "Sair";
            int largura_botao = al_get_text_width(res->font, texto_sair);
            int altura_botao = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (sair_botao.x1 + sair_botao.x2 - largura_botao) / 2,
                (sair_botao.y1 + sair_botao.y2 - altura_botao) / 2,
                ALLEGRO_ALIGN_LEFT, texto_sair);
        }

        al_flip_display();
    }
    else {
        // Caso nenhum dos estados anteriores seja correspondido, limpa a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();
    }
}
