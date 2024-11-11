#pragma once
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>  // Necess�rio para carregar imagens

// Fun��es para inicializar, renderizar e destruir a introdu��o

void renderizar_introducao() {
    // Ajustes para posi��o e tamanho da caixa de di�logo
    float posX = 250;              // Posi��o X da caixa de di�logo
    float posY = 180;              // Posi��o Y da caixa de di�logo
    const float alturaCaixa = 150; // Altura fixa da caixa de fala

    // Texto da introdu��o
    const char* textoIntroducao = "Seja bem - vindo a Chernobyl.Voc� � Aleksandr Goncharov, um engenheiro nuclear rec�m - formado que come�a seu turno na usina de Chernobyl.Mal sabe, mas um teste de seguran�a est� prestes a desencadear uma cat�strofe.Sua dedica��o e coragem ser�o testadas enquanto tenta controlar a crise que amea�a destruir tudo.";

    // Cria��o da fonte para o texto
    ALLEGRO_FONT* font = al_create_builtin_font();

    // C�lculo da largura do texto
    float larguraTexto = al_get_text_width(font, textoIntroducao);

    // Ajuste da largura da caixa com base no texto e margem
    const float larguraCaixa = 600; // Largura fixa para a caixa de di�logo

    // Carregar a imagem de fundo
    ALLEGRO_BITMAP* imagemFundo = al_load_bitmap("assets/BG-1.png");
    if (!imagemFundo) {
        printf("Erro ao carregar a imagem de fundo!\n");
        return;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela com fundo preto

    // Desenha a imagem de fundo
    al_draw_bitmap(imagemFundo, 0, 0, 0);

    // Caixa de di�logo com borda arredondada
    al_draw_filled_rounded_rectangle(posX, posY, posX + larguraCaixa, posY + alturaCaixa, 10, 10, al_map_rgb(245, 245, 220));
    al_draw_rounded_rectangle(posX, posY, posX + larguraCaixa, posY + alturaCaixa, 10, 10, al_map_rgb(0, 0, 0), 2.0);

    // Ajustes para o tri�ngulo
    float baseTrianguloX = posX + 60;
    float pontaTrianguloY = posY + alturaCaixa + 80;

    // Desenha o tri�ngulo
    al_draw_filled_triangle(
        posX + 20, posY + alturaCaixa,
        baseTrianguloX, posY + alturaCaixa,
        posX - 20, pontaTrianguloY,
        al_map_rgb(245, 245, 220)
    );

    al_draw_triangle(
        posX + 20, posY + alturaCaixa,
        baseTrianguloX, posY + alturaCaixa,
        posX - 20, pontaTrianguloY,
        al_map_rgb(0, 0, 0),
        2.0
    );

    // Desenha o texto da introdu��o
    al_draw_text(font, al_map_rgb(0, 0, 0), posX + 10, posY + 10, ALLEGRO_ALIGN_LEFT, textoIntroducao);

    // Desenho do bot�o "Avan�a"
    float botaoX = 820;
    float botaoY = posY + alturaCaixa + 200;
    float botaoLargura = 120;
    float botaoAltura = 40;
    ALLEGRO_COLOR botaoCor = al_map_rgb(100, 100, 100);
    ALLEGRO_COLOR bordaCor = al_map_rgb(255, 255, 255);

    al_draw_filled_rectangle(botaoX, botaoY, botaoX + botaoLargura, botaoY + botaoAltura, botaoCor);
    al_draw_rectangle(botaoX, botaoY, botaoX + botaoLargura, botaoY + botaoAltura, bordaCor, 2.0);

    // Texto do bot�o "Avan�a"
    const char* textoBotao = "Avan�a";
    al_draw_text(font, al_map_rgb(255, 255, 255), botaoX + 10, botaoY + 10, ALLEGRO_ALIGN_LEFT, textoBotao);

    // Carregar a imagem do cientista
  

  

    al_flip_display(); // Atualiza a tela

    al_destroy_bitmap(imagemFundo);

}

void destruir_introducao() {
    // Nada a destruir, pois n�o usamos fontes ou imagens carregadas
}
