#include "rendering.h"
#include "constants.h"
#include "resources.h"
#include "player.h"
#include "projectile.h"
#include "ui.h"
#include "interacoes.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "npc.h"

void render_game(GameState estado, Resources* res, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y,
    Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button,
    Rect* obstacles, int num_obstacles, Interacoes* interacoes,
    Rect botao_sair_vitoria, Rect botao_menu_vitoria,
    NPC_DIRETOR* npc_chefe, NPC_ENGENHEIRO* npc_engenheiro,
    DialogueManager* dialogue_manager) {

    if (estado == MENU) {
        if (res->menu_image) {
            al_draw_bitmap(res->menu_image, 0, 0, 0);
        }
        else {
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

        // Desenha o botão "Start"
        ALLEGRO_COLOR cor_start = al_map_rgb(100, 100, 100);
        if (mouse_x >= start_button.x1 && mouse_x <= start_button.x2 &&
            mouse_y >= start_button.y1 && mouse_y <= start_button.y2) {
            cor_start = al_map_rgb(150, 150, 150);
        }

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

        if (res->font) {
            const char* texto_start = "Comecar";
            int largura_texto = al_get_text_width(res->font, texto_start);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (start_button.x1 + start_button.x2 - largura_texto) / 2,
                (start_button.y1 + start_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_start);
        }

        // Desenha o botão "Credits"
        ALLEGRO_COLOR cor_credits = al_map_rgb(100, 100, 100);
        if (mouse_x >= credits_button.x1 && mouse_x <= credits_button.x2 &&
            mouse_y >= credits_button.y1 && mouse_y <= credits_button.y2) {
            cor_credits = al_map_rgb(150, 150, 150);
        }

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

        if (res->font) {
            const char* texto_credits = "Creditos";
            int largura_texto = al_get_text_width(res->font, texto_credits);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (credits_button.x1 + credits_button.x2 - largura_texto) / 2,
                (credits_button.y1 + credits_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_credits);
        }

        // Desenha o botão "Instruction"
        ALLEGRO_COLOR cor_instructs = al_map_rgb(100, 100, 100);
        if (mouse_x >= Instructs_button.x1 && mouse_x <= Instructs_button.x2 &&
            mouse_y >= Instructs_button.y1 && mouse_y <= Instructs_button.y2) {
            cor_instructs = al_map_rgb(150, 150, 150);
        }

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

        if (res->font) {
            const char* texto_instructions = "Instrucoes";
            int largura_texto = al_get_text_width(res->font, texto_instructions);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (Instructs_button.x1 + Instructs_button.x2 - largura_texto) / 2,
                (Instructs_button.y1 + Instructs_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_instructions);
        }

        al_flip_display();
    }

    else if (estado == INTRO) {
        al_clear_to_color(COR_FUNDO);
        if (res->INTRO) {
            al_draw_bitmap(res->INTRO, 0, 0, 0);
        }

        draw_npc_chefe(npc_chefe);
        draw_npc_engenheiro(npc_engenheiro);
        movimento_eng(npc_engenheiro, npc_chefe);

        if (!dialogue_manager->dialogue_finished) {
            const char* texto = dialogue_manager->dialogues[dialogue_manager->dialogue_index].texto;
            ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
            int x = 100; // Posição X do texto
            int y = 500; // Posição Y do texto
            int largura_caixa = SCREEN_WIDTH - 200;
            int altura_caixa = 100;

            // Desenha uma caixa para o diálogo
            al_draw_filled_rectangle(x - 10, y - 10, x + largura_caixa + 10, y + altura_caixa + 10, al_map_rgb(0, 0, 0));
            al_draw_rectangle(x - 10, y - 10, x + largura_caixa + 10, y + altura_caixa + 10, al_map_rgb(255, 255, 255), 2);

            // Desenha o texto do diálogo
            al_draw_text(res->font, text_color, x, y, 0, texto);
        }

        // Desenhar o botão 'Continuar'
        ALLEGRO_COLOR cor_prologo = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= prologo_button.x1 && mouse_x <= prologo_button.x2 &&
            mouse_y >= prologo_button.y1 && mouse_y <= prologo_button.y2) {
            cor_prologo = al_map_rgb(150, 150, 150); // Cor quando o mouse está sobre o botão
        }

        // Desenha o botão 'Continuar'
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

        // Desenha o texto 'Continuar' no botão
        if (res->font) {
            const char* texto_prologo = "Continuar";
            int largura_texto = al_get_text_width(res->font, texto_prologo);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (prologo_button.x1 + prologo_button.x2 - largura_texto) / 2,
                (prologo_button.y1 + prologo_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_prologo);
        }

        al_flip_display();
    }

    else if (estado == PROLOGO || estado == PROLOGO2 || estado == PROLOGO3 || estado == PROLOGO4) {
        al_clear_to_color(COR_FUNDO);

        ALLEGRO_BITMAP* bg_prologo = NULL;
        switch (estado) {
        case PROLOGO:
            bg_prologo = res->bg_prologo;
            break;
        case PROLOGO2:
            bg_prologo = res->bg_prologo2;
            break;
        case PROLOGO3:
            bg_prologo = res->bg_prologo3;
            break;
        case PROLOGO4:
            bg_prologo = res->bg_prologo4;
            break;
        default:
            break;
        }

        if (bg_prologo) {
            al_draw_bitmap(bg_prologo, 0, 0, 0);
        }

        // Desenha o botão "Continuar"
        ALLEGRO_COLOR cor_prologo = al_map_rgb(100, 100, 100);
        if (mouse_x >= prologo_button.x1 && mouse_x <= prologo_button.x2 &&
            mouse_y >= prologo_button.y1 && mouse_y <= prologo_button.y2) {
            cor_prologo = al_map_rgb(150, 150, 150);
        }

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

        if (res->font) {
            const char* texto_prologo = "Continuar";
            int largura_texto = al_get_text_width(res->font, texto_prologo);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (prologo_button.x1 + prologo_button.x2 - largura_texto) / 2,
                (prologo_button.y1 + prologo_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_prologo);
        }

        al_flip_display();
    }
    else if (estado == FASE_1) {
        al_clear_to_color(COR_FUNDO);
        al_draw_bitmap(res->BG_1, 0, 0, 0);

        // Desenha obstáculos e seus números para depuração
        for (int i = 0; i < num_obstacles; ++i) {
        }

        for (int i = 0; i < num_projectiles; ++i) {
            if (projectiles[i].active) {
                draw_projectile(&projectiles[i]);
            }
        }

        draw_player(player);

        if (player->perto_do_obstaculo_2 && !interacoes->interagiu_obstaculo_2) {
            if (res->font) {
                al_draw_text(res->font, al_map_rgb(255, 255, 255), player->x, player->y - 20, 0, "Aperte F para interagir");
            }
            else {
                printf("Fonte nao carregada.\n");
            }
        }

        if (player->perto_do_obstaculo_3 && !interacoes->interagiu_obstaculo_3) {
            if (res->font) {
                al_draw_text(res->font, al_map_rgb(255, 255, 255), player->x, player->y - 20, 0, "Aperte F para interagir");
            }
            else {
                printf("Fonte nao carregada.\n");
            }
        }

        draw_life_bar(player);

        al_flip_display();
    }
    else if (estado == GAME_OVER) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (res->font) {
            const char* texto_game_over = "GAME OVER";
            int largura_texto = al_get_text_width(res->font, texto_game_over);
            al_draw_text(res->font, al_map_rgb(255, 0, 0),
                (SCREEN_WIDTH - largura_texto) / 2, SCREEN_HEIGHT / 2 - 50, ALLEGRO_ALIGN_LEFT, texto_game_over);
        }
        else {
            printf("Fonte nao carregada.\n");
        }

        // Desenha os botões "Continuar" e "Sair" na tela
        // Desenhar o botão "Continuar"
        ALLEGRO_COLOR cor_continuar = al_map_rgb(100, 100, 100);
        if (mouse_x >= continuar_botao.x1 && mouse_x <= continuar_botao.x2 &&
            mouse_y >= continuar_botao.y1 && mouse_y <= continuar_botao.y2) {
            cor_continuar = al_map_rgb(150, 150, 150);
        }

        al_draw_filled_rectangle(
            continuar_botao.x1, continuar_botao.y1,
            continuar_botao.x2, continuar_botao.y2,
            cor_continuar
        );
        al_draw_rectangle(
            continuar_botao.x1, continuar_botao.y1,
            continuar_botao.x2, continuar_botao.y2,
            al_map_rgb(255, 255, 255), 2
        );

        if (res->font) {
            const char* texto_continuar = "Continuar";
            int largura_texto = al_get_text_width(res->font, texto_continuar);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (continuar_botao.x1 + continuar_botao.x2 - largura_texto) / 2,
                (continuar_botao.y1 + continuar_botao.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_continuar);
        }

        // Desenhar o botão "Sair"
        ALLEGRO_COLOR cor_sair = al_map_rgb(100, 100, 100);
        if (mouse_x >= sair_botao.x1 && mouse_x <= sair_botao.x2 &&
            mouse_y >= sair_botao.y1 && mouse_y <= sair_botao.y2) {
            cor_sair = al_map_rgb(150, 150, 150);
        }

        al_draw_filled_rectangle(
            sair_botao.x1, sair_botao.y1,
            sair_botao.x2, sair_botao.y2,
            cor_sair
        );
        al_draw_rectangle(
            sair_botao.x1, sair_botao.y1,
            sair_botao.x2, sair_botao.y2,
            al_map_rgb(255, 255, 255), 2
        );

        if (res->font) {
            const char* texto_sair = "Sair";
            int largura_texto = al_get_text_width(res->font, texto_sair);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (sair_botao.x1 + sair_botao.x2 - largura_texto) / 2,
                (sair_botao.y1 + sair_botao.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_sair);
        }

        al_flip_display();
        }

    else if (estado == CREDITOS) {
        if (res->creditos) {
            al_draw_bitmap(res->creditos, 0, 0, 0);
        }
        al_flip_display();
    }
    else if (estado == INSTRUÇÕES) {
        if (res->instructs) {
            al_draw_bitmap(res->instructs, 0, 0, 0);
        }
        al_flip_display();
    }
    else if (estado == VITORIA) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (res->font) {
            const char* texto_vitoria = "Voce venceu!";
            int largura_texto = al_get_text_width(res->font, texto_vitoria);
            al_draw_text(res->font, al_map_rgb(0, 255, 0),
                (SCREEN_WIDTH - largura_texto) / 2, SCREEN_HEIGHT / 2 - 50, ALLEGRO_ALIGN_LEFT, texto_vitoria);

            // Desenha o botão "Sair"
            ALLEGRO_COLOR cor_sair_vitoria = al_map_rgb(100, 100, 100);
            if (mouse_x >= botao_sair_vitoria.x1 && mouse_x <= botao_sair_vitoria.x2 &&
                mouse_y >= botao_sair_vitoria.y1 && mouse_y <= botao_sair_vitoria.y2) {
                cor_sair_vitoria = al_map_rgb(150, 150, 150);
            }

            al_draw_filled_rectangle(
                botao_sair_vitoria.x1, botao_sair_vitoria.y1,
                botao_sair_vitoria.x2, botao_sair_vitoria.y2,
                cor_sair_vitoria
            );
            al_draw_rectangle(
                botao_sair_vitoria.x1, botao_sair_vitoria.y1,
                botao_sair_vitoria.x2, botao_sair_vitoria.y2,
                al_map_rgb(255, 255, 255), 2
            );

            const char* texto_sair = "Sair";
            int largura_texto_sair = al_get_text_width(res->font, texto_sair);
            int altura_texto_sair = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (botao_sair_vitoria.x1 + botao_sair_vitoria.x2 - largura_texto_sair) / 2,
                (botao_sair_vitoria.y1 + botao_sair_vitoria.y2 - altura_texto_sair) / 2,
                ALLEGRO_ALIGN_LEFT, texto_sair);

            // Desenha o botão "Menu"
            ALLEGRO_COLOR cor_menu_vitoria = al_map_rgb(100, 100, 100);
            if (mouse_x >= botao_menu_vitoria.x1 && mouse_x <= botao_menu_vitoria.x2 &&
                mouse_y >= botao_menu_vitoria.y1 && mouse_y <= botao_menu_vitoria.y2) {
                cor_menu_vitoria = al_map_rgb(150, 150, 150);
            }

            al_draw_filled_rectangle(
                botao_menu_vitoria.x1, botao_menu_vitoria.y1,
                botao_menu_vitoria.x2, botao_menu_vitoria.y2,
                cor_menu_vitoria
            );
            al_draw_rectangle(
                botao_menu_vitoria.x1, botao_menu_vitoria.y1,
                botao_menu_vitoria.x2, botao_menu_vitoria.y2,
                al_map_rgb(255, 255, 255), 2
            );

            const char* texto_menu = "Menu";
            int largura_texto_menu = al_get_text_width(res->font, texto_menu);
            int altura_texto_menu = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (botao_menu_vitoria.x1 + botao_menu_vitoria.x2 - largura_texto_menu) / 2,
                (botao_menu_vitoria.y1 + botao_menu_vitoria.y2 - altura_texto_menu) / 2,
                ALLEGRO_ALIGN_LEFT, texto_menu);
        }
        else {
            printf("Fonte nao carregada.\n");
        }

        al_flip_display();
        }

    else {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();
    }
}
