#include <stdio.h>
#include "allegro5/allegro5.h"
#include "allegro5/keyboard.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"


// Função que inicializa o jogo
void inicializa_jogo() {
    // Inicializa o Allegro
    if (!al_init()) {
        fprintf(stderr, "ERRO AO INICIAR\n");
        return;
    }

    // Inicializa o teclado
    if (!al_install_keyboard()) {
        fprintf(stderr, "ERRO ao instalar teclado\n");
        return;
    }

    // Inicializa os primitives
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "ERRO ao inicializar primitives\n");
        return;
    }

    // Inicializa o addon de imagens
    if (!al_init_image_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon de imagem\n");
        return;
    }

    // Inicializa o addon de fontes
    if (!al_init_font_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon de fonte\n");
        return;
    }

    // Inicializa o addon TTF
    if (!al_init_ttf_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon TTF\n");
        return;
    }

    // Cria o display
    ALLEGRO_DISPLAY* tela_inicial = al_create_display(720, 400);
    if (!tela_inicial) {
        fprintf(stderr, "ERRO ao criar display\n");
        return;
    }

    // Definição de cores
    ALLEGRO_COLOR cor_fundo = al_map_rgb(0, 0, 0); // Cor de fundo preta
    ALLEGRO_COLOR cor_fala = al_map_rgb(0, 0, 0); // Cor da caixa de fala branca
    ALLEGRO_COLOR cor_borda = al_map_rgb(255, 255, 255); // Cor da borda branca
    ALLEGRO_COLOR cor_botao = al_map_rgb(255, 255, 255); // Cor do botão
    ALLEGRO_COLOR cor_texto_botao = al_map_rgb(0, 0, 0); // Cor do texto do botão

    // Carrega a imagem de fundo
    ALLEGRO_BITMAP* fundo = al_load_bitmap("BG-1.PNG");
    if (!fundo) {
        fprintf(stderr, "ERRO ao carregar a imagem de fundo\n");
        al_destroy_display(tela_inicial);
        return;
    }

    // Cria fila de eventos
    ALLEGRO_EVENT_QUEUE* fila_eventos = al_create_event_queue();
    if (!fila_eventos) {
        fprintf(stderr, "ERRO ao criar fila de eventos\n");
        al_destroy_bitmap(fundo);
        al_destroy_display(tela_inicial);
        return;
    }

    // Registra o teclado na fila de eventos
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());

    // Carrega a fonte "Roboto Light" com tamanho reduzido
    ALLEGRO_FONT* fonte = al_load_ttf_font("Roboto-Light.ttf", 15, 0); // Tamanho da fonte alterado para 18
    if (!fonte) {
        fprintf(stderr, "ERRO ao carregar a fonte 'Roboto Light'\n");
        al_destroy_event_queue(fila_eventos);
        al_destroy_bitmap(fundo);
        al_destroy_display(tela_inicial);
        return;
    }

    const char* introducao[] = {
          "Neste jogo, você assume o papel de Aleksandr Goncharov,",
          "um engenheiro nuclear que luta para manter o reator",
          "em segurança durante o desastre de Chernobyl.",
          "Sua missão é lidar com a destruição e salvar",
          "o que pode ser salvo."
    };

    // Variável para sair do loop
    bool sair = false;

    // Loop principal
    while (!sair) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(fila_eventos, &evento);

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                sair = true;
        }

        // Limpa o display
        al_clear_to_color(cor_fundo);

        // Desenha o fundo escalado para preencher o display
        al_draw_scaled_bitmap(fundo, 0, 0,
            al_get_bitmap_width(fundo),
            al_get_bitmap_height(fundo),
            0, 0, 720, 400,
            0);

        // Desenha a caixa de diálogo
        float x_fala = 120; // Posição x da caixa de fala
        float y_fala = 190; // Posição y da caixa de fala
        float largura_fala = 500; // Largura da caixa de fala
        float altura_fala = 80; // Altura da caixa de fala

        // Desenha o retângulo da fala
        al_draw_filled_rounded_rectangle(x_fala, y_fala,
            x_fala + largura_fala,
            y_fala + altura_fala,
            10, 10,
            cor_fala);

        // Desenha a borda da caixa de diálogo
        al_draw_rounded_rectangle(x_fala, y_fala,
            x_fala + largura_fala,
            y_fala + altura_fala,
            10, 10,
            cor_borda, 2.0); // A última variável é a espessura da borda

        // Desenha o texto da introdução em múltiplas linhas
      // Desenha o texto da introdução em múltiplas linhas
        al_draw_multiline_text(fonte, cor_borda, x_fala + 10, y_fala + 10, largura_fala - 20, al_get_font_line_height(fonte), 0, introducao);


        // Cria o botão "Continuar"
        float x_botao = 300; // Posição x do botão
        float y_botao = 300; // Posição y do botão
        float largura_botao = 120; // Largura do botão
        float altura_botao = 40; // Altura do botão

        // Desenha o retângulo do botão
        al_draw_filled_rounded_rectangle(x_botao, y_botao,
            x_botao + largura_botao,
            y_botao + altura_botao,
            10, 10,
            cor_botao);

        // Desenha a borda do botão
        al_draw_rounded_rectangle(x_botao, y_botao,
            x_botao + largura_botao,
            y_botao + altura_botao,
            10, 10,
            cor_borda, 2.0); // A última variável é a espessura da borda

        // Desenha o texto "Continuar" no botão
        const char* texto_botao = "Continuar";
        // Calcula a largura do texto para centralizá-lo
        float largura_texto_botao = al_get_text_width(fonte, texto_botao);
        al_draw_text(fonte, cor_texto_botao,
            x_botao + (largura_botao - largura_texto_botao) / 2,
            y_botao + (altura_botao - al_get_font_line_height(fonte)) / 2,
            0, texto_botao);

        // Atualiza o display
        al_flip_display();
    }

    // Destrói recursos
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_bitmap(fundo);
    al_destroy_display(tela_inicial);
}


int main()
{
    inicializa_jogo();   // Depois chama a função que exibe a tela do jogo
    return 0;

}


// teste