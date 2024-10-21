#include "displays.h"

void atualizar_estado(EstadoAtual* tela) {
    switch (*tela) {
    case MENU: *tela = PROLOGO; break;
    case PROLOGO: *tela = FASE_1; break;
    case FASE_1: *tela = FASE_2; break;
    case FASE_2: *tela = FASE_3; break;
    default: break; 
    }
}
