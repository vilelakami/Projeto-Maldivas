// introducao.h

#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

// Declaração das funções para inicializar, renderizar e destruir a introdução

// Inicializa a introdução, configurando qualquer recurso necessário
void inicializar_introducao();

// Renderiza a introdução na tela, incluindo a caixa de diálogo e o botão de "Avança"
void renderizar_introducao();

// Libera recursos utilizados na introdução (se houver)
void destruir_introducao();
