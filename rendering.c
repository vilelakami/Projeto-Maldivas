// rendering.c
#include "rendering.h"
#include "constants.h"
#include "resources.h"
#include <stdio.h>
#include <allegro5/keyboard.h>


al_install_keyboard();
static bool button_pressed = false;
static bool som_GO = false;

void render_game(GameState estado, Resources* res, Player* player, Projectile* projectiles, int num_projectiles,
    Rect continuar_botao, Rect sair_botao, int mouse_x, int mouse_y,
    Rect start_button, Rect prologo_button, Rect credits_button, Rect Instructs_button, Rect* obstacles, int num_obstacles, NPC_DIRETOR* npc_chefe, NPC_ENGENHEIRO* npc_engenheiro) {

    if (estado == MENU) {

        // Desenha a imagem do menu ou limpa a tela
        if (res->menu_image) {
            al_draw_bitmap(res->menu_image, 0, 0, 0);
        }
        else {
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }

        // Botão "Start": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_start = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= start_button.x1 && mouse_x <= start_button.x2 &&
            mouse_y >= start_button.y1 && mouse_y <= start_button.y2) {
            cor_start = al_map_rgb(150, 150, 150); // Cor quando o mouse está sobre o botão
        }

        // Desenha o botão "Start"
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

        // Desenha o texto "Start" no botão
        if (res->font) {
            const char* texto_start = "Start";
            int largura_texto = al_get_text_width(res->font, texto_start);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (start_button.x1 + start_button.x2 - largura_texto) / 2,
                (start_button.y1 + start_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_start);
        }

        // Botão "Credits": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_credits = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= credits_button.x1 && mouse_x <= credits_button.x2 &&
            mouse_y >= credits_button.y1 && mouse_y <= credits_button.y2) {
            cor_credits = al_map_rgb(150, 150, 150); // Cor quando o mouse está sobre o botão
        }

        // Desenha o botão "Credits"
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

        // Desenha o texto "Credits" no botão
        if (res->font) {
            const char* texto_credits = "Credits";
            int largura_texto = al_get_text_width(res->font, texto_credits);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (credits_button.x1 + credits_button.x2 - largura_texto) / 2,
                (credits_button.y1 + credits_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_credits);
        }

        // Botão "Instruction": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_instructs = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= Instructs_button.x1 && mouse_x <= Instructs_button.x2 &&
            mouse_y >= Instructs_button.y1 && mouse_y <= Instructs_button.y2) {
            cor_instructs = al_map_rgb(150, 150, 150); // Cor quando o mouse está sobre o botão
        }

        // Desenha o botão "Instruction"
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

        // Desenha o texto "Instruction" no botão
        if (res->font) {
            const char* texto_instructions = "Instruction";
            int largura_texto = al_get_text_width(res->font, texto_instructions);
            int altura_texto = al_get_font_line_height(res->font);
            al_draw_text(res->font, al_map_rgb(255, 255, 255),
                (Instructs_button.x1 + Instructs_button.x2 - largura_texto) / 2,
                (Instructs_button.y1 + Instructs_button.y2 - altura_texto) / 2,
                ALLEGRO_ALIGN_LEFT, texto_instructions);
        }

        al_flip_display();  // Atualiza a tela
    }
    else if (estado == PROLOGO || estado == PROLOGO2 || estado == PROLOGO3 || estado == PROLOGO4) {
        al_clear_to_color(COR_FUNDO);

        // Seleciona o background apropriado
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

        // Botão "Continuar": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_prologo = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= prologo_button.x1 && mouse_x <= prologo_button.x2 &&
            mouse_y >= prologo_button.y1 && mouse_y <= prologo_button.y2) {
            cor_prologo = al_map_rgb(150, 150, 150); // Cor quando o mouse está sobre o botão
        }

        // Desenha o botão "Continuar"
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

        // Desenha o texto "Continuar" no botão
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
    else if 
        (estado == INTRO) {
            al_clear_to_color(COR_GAME_OVER);
            al_draw_bitmap(res->INTRO, 0, 0, 0);
            draw_npc_chefe(npc_chefe);
            draw_npc_engenheiro(npc_engenheiro);
            movimento_eng(npc_engenheiro, npc_chefe);
           // dialogo( npc_engenheiro);
            int fala = 1;
            if (ALLEGRO_KEY_BACKSPACE) {
                fala + 1;
            }
            if (npc_engenheiro->y <= 340) {
                al_draw_filled_rectangle(360, 500, 690, 620, COR_GAME_OVER);
             
                switch (fala) {
                case  1:
                    al_draw_text(res->font, al_map_rgb(255, 255, 0), 400, 500, 0, "teste1");
                    break;
                case 2:
                    al_draw_text(res->font, al_map_rgb(255, 255, 0), 400, 500, 0, "teste2");
                    break;
                case 3:
                    al_draw_text(res->font, al_map_rgb(255, 255, 0), 400, 500, 0, "teste3");
                    break;
                case 4:
                    al_draw_text(res->font, al_map_rgb(255, 255, 0), 400, 500, 0, "teste4"); 
                    break;
                case 5:
                    al_draw_text(res->font, al_map_rgb(255, 255, 0), 400, 500, 0, "teste5");
                default:
                    break;
                }
                
                
            }
            al_flip_display();

    }
    else if (estado == FASE_1) {
        al_clear_to_color(COR_FUNDO);
        al_draw_bitmap(res->BG_1, 0, 0, 0);

        // Desenha os obstáculos
        for (int i = 0; i < num_obstacles; ++i) {
            al_draw_filled_rectangle(
                obstacles[i].x1, obstacles[i].y1,
                obstacles[i].x2, obstacles[i].y2,
                al_map_rgba(0, 0, 0, 0) // Vermelho semi-transparente
            );
        }

        // Desenha todos os projéteis ativos
        for (int i = 0; i < num_projectiles; ++i) {
            if (projectiles[i].active) {
                draw_projectile(&projectiles[i]);
            }
        }

        // Desenha o jogador
        draw_player(player);

        // Desenha a barra de vida
        draw_life_bar(player);

        al_flip_display();
    }
    else if (estado == GAME_OVER) {
        // Desenha a tela de Game Over
        al_clear_to_color(COR_GAME_OVER); // Fundo preto
        if (res->inst_trilha && al_get_sample_instance_playing(res->inst_trilha)) {
            al_stop_sample_instance(res->inst_trilha);
        }

        // Desenha a tela de Game Over
        al_clear_to_color(COR_GAME_OVER); // Fundo preto

        if (!som_GO) {
            if (res->som_gameOver) {
                al_play_sample(res->som_gameOver, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            }
            som_GO = true;
        }

        // Redefinir o som ao sair do GAME_OVER
        if (estado != GAME_OVER) {
            som_GO = false;
        }


        if (res->font) {
            // Desenha "GAME OVER" no centro superior
            const char* texto_game_over = "GAME OVER";
            int largura_texto = al_get_text_width(res->font, texto_game_over);
            al_draw_text(res->font, al_map_rgb(255, 0, 0),
                (SCREEN_WIDTH - largura_texto) / 2, 200, ALLEGRO_ALIGN_LEFT, texto_game_over);
        }

        // Botão "Continuar": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_continuar = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= continuar_botao.x1 && mouse_x <= continuar_botao.x2 &&
            mouse_y >= continuar_botao.y1 && mouse_y <= continuar_botao.y2) {
            cor_continuar = al_map_rgb(150, 150, 150); // Cor hover
        }

        // Botão "Sair": Verifica se o mouse está sobre o botão
        ALLEGRO_COLOR cor_sair = al_map_rgb(100, 100, 100); // Cor padrão
        if (mouse_x >= sair_botao.x1 && mouse_x <= sair_botao.x2 &&
            mouse_y >= sair_botao.y1 && mouse_y <= sair_botao.y2) {
            cor_sair = al_map_rgb(150, 150, 150); // Cor hover
        }

        // Botão "Continuar"
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

        // Botão "Sair"
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
    else if (estado == CREDITOS) {
        // Desenha a tela de créditos
        if (res->creditos) {
            al_draw_bitmap(res->creditos, 0, 0, 0);
        }
        al_flip_display();
    }
    else if (estado == INSTRUÇÕES) {
        // Desenha a tela de instruções
        if (res->instructs) {
            al_draw_bitmap(res->instructs, 0, 0, 0);
        }
        al_flip_display();
    }
    else {
        // Caso nenhum dos estados anteriores seja correspondido, limpa a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();
    }
}
