#pragma once
#include <stdio.h>
#include "allegro5/allegro5.h"
#include "allegro5/keyboard.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h" // Para usar fontes TTF
#include <stdio.h>
#include "allegro5/allegro5.h"



int mostrarFalas() // Renomeado para mostrarFalas
{
    // Inicializa o Allegro
    if (!al_init()) {
        fprintf(stderr, "ERRO AO INICIAR\n");
        return -1;
    }

    // Inicializa o teclado
    if (!al_install_keyboard()) {
        fprintf(stderr, "ERRO ao instalar teclado\n");
        return -1;
    }

    // Inicializa os addons
    if (!al_init_primitives_addon()) {
        fprintf(stderr, "ERRO ao inicializar primitives\n");
        return -1;
    }

    if (!al_init_image_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon de imagem\n");
        return -1;
    }

    if (!al_init_font_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon de fonte\n");
        return -1;
    }

    if (!al_init_ttf_addon()) {
        fprintf(stderr, "ERRO ao inicializar addon TTF\n");
        return -1;
    }

    // Cria o display
    ALLEGRO_DISPLAY* display = al_create_display(720, 400); // Renomeado para display
    if (!display) {
        fprintf(stderr, "ERRO ao criar display\n");
        return -1;
    }

    // Definição de cores
    ALLEGRO_COLOR corFundo = al_map_rgb(255, 255, 255); // Renomeado para corFundo
    ALLEGRO_COLOR corFala = al_map_rgb(245, 245, 220);   // Renomeado para corFala
    ALLEGRO_COLOR corBorda = al_map_rgb(0, 0, 0);        // Renomeado para corBorda

    // Carrega a imagem de fundo
    ALLEGRO_BITMAP* imagemFundo = al_load_bitmap("BG-1.PNG"); // Renomeado para imagemFundo
    if (!imagemFundo) {
        fprintf(stderr, "ERRO ao carregar a imagem de fundo\n");
        al_destroy_display(display);
        return -1;
    }

    // Cria fila de eventos
    ALLEGRO_EVENT_QUEUE* filaEventos = al_create_event_queue(); // Renomeado para filaEventos
    if (!filaEventos) {
        fprintf(stderr, "ERRO ao criar fila de eventos\n");
        al_destroy_bitmap(imagemFundo);
        al_destroy_display(display);
        return -1;
    }

    // Registra o teclado na fila de eventos
    al_register_event_source(filaEventos, al_get_keyboard_event_source());

    // Carrega a fonte "Roboto Light"
    ALLEGRO_FONT* fonteTexto = al_load_ttf_font("Roboto-Light.ttf", 24, 0); // Renomeado para fonteTexto
    if (!fonteTexto) {
        fprintf(stderr, "ERRO ao carregar a fonte 'Roboto Light'\n");
        al_destroy_event_queue(filaEventos);
        al_destroy_bitmap(imagemFundo);
        al_destroy_display(display);
        return -1;
    }

    // Variável para a introdução
    const char* textoIntroducao = "Introdução: Neste jogo, você assume o papel de Aleksandr Goncharov, um engenheiro nuclear que luta para manter o reator em segurança durante o desastre de Chernobyl. Sua missão é lidar com a destruição e salvar o que pode ser salvo."; // Renomeado para textoIntroducao

    // Variável para sair do loop
    bool sairLoop = false; // Renomeado para sairLoop

    // Loop principal
    while (!sairLoop) {
        ALLEGRO_EVENT evento; // Renomeado para evento
        al_wait_for_event(filaEventos, &evento);

        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                sairLoop = true; // Renomeado para sairLoop
        }

        // Limpa o display
        al_clear_to_color(corFundo); // Renomeado para corFundo

        // Desenha o fundo escalado para preencher o display
        al_draw_scaled_bitmap(imagemFundo, 0, 0,
            al_get_bitmap_width(imagemFundo),
            al_get_bitmap_height(imagemFundo),
            0, 0, 720, 400,
            0);

        // Desenha a caixa de diálogo
        float posX = 50; // Posição x da caixa de fala (renomeado para posX)
        float posY = 300; // Posição y da caixa de fala (renomeado para posY)
        float larguraCaixa = 500; // Largura da caixa de fala (renomeado para larguraCaixa)
        float alturaCaixa = 80; // Altura da caixa de fala (renomeado para alturaCaixa)

        // Desenha o r etângulo da fala
        al_draw_filled_rounded_rectangle(posX, posY,
            posX + larguraCaixa,
            posY + alturaCaixa,
            10, 10,
            corFala); // Renomeado para corFala

        // Desenha a borda da caixa de diálogo
        al_draw_rounded_rectangle(posX, posY,
            posX + larguraCaixa,
            posY + alturaCaixa,
            10, 10,
            corBorda, 2.0); // Renomeado para corBorda

        // Desenha o texto da introdução em múltiplas linhas
        al_draw_multiline_text(fonteTexto, corBorda, posX + 10, posY + 10, larguraCaixa - 20, alturaCaixa - 20, 0, textoIntroducao); // Renomeado para fonteTexto e textoIntroducao

        // Atualiza o display
        al_flip_display();
    }

    // Destrói recursos
    al_destroy_font(fonteTexto);
    al_destroy_event_queue(filaEventos);
    al_destroy_bitmap(imagemFundo);
    al_destroy_display(display);

    return 0;
}
