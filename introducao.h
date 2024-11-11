// introducao.h

#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

// Declara��o das fun��es para inicializar, renderizar e destruir a introdu��o

// Inicializa a introdu��o, configurando qualquer recurso necess�rio
void inicializar_introducao();

// Renderiza a introdu��o na tela, incluindo a caixa de di�logo e o bot�o de "Avan�a"
void renderizar_introducao();

// Libera recursos utilizados na introdu��o (se houver)
void destruir_introducao();
