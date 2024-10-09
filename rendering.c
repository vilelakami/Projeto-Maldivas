// rendering.c
#include "rendering.h"
#include "constants.h" // Inclus�o necess�ria para COR_FUNDO e COR_GAME_OVER

void render_game(GameState estado, Resources* res, Player* player, Projectile* proj, Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y) {
    if (estado == PLAYING) {
        al_clear_to_color(COR_FUNDO);

        // Desenha o projetil
        draw_projectile(proj);

        // Desenha o jogador
        draw_player(player);

        // Desenha ret�ngulos de colis�o para depura��o (opcional)
        float player_largura = player->largura_frame * player->escala;
        float player_altura = player->altura_frame * player->escala;
        float proj_largura = proj->largura_frame * proj->escala;
        float proj_altura = proj->altura_frame * proj->escala;

        al_draw_rectangle(
            player->x, player->y,
            player->x + player_largura, player->y + player_altura,
            al_map_rgb(0, 0, 255), 2 // Azul para o jogador
        );

        al_draw_rectangle(
            proj->x, proj->y,
            proj->x + proj_largura, proj->y + proj_altura,
            al_map_rgb(255, 0, 0), 2 // Vermelho para o projetil
        );

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

        // Desenha os bot�es "Continuar" e "Sair" com cores ajustadas
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
}
