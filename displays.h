#ifndef DISPLAYS_H
#define DISPLAYS_H
#include <stdio.h>

//definindo struct dos displays
typedef enum {
    MENU,
    PROLOGO,
    FASE_1,
    FASE_2,
    FASE_3
} EstadoAtual;

//criando uma função pra chamar na main e um switch 
void atualizar_estado(EstadoAtual* tela) {
    switch (*tela) {
    case MENU: *tela = PROLOGO; break;
    case PROLOGO: *tela = FASE_1; break;
    case FASE_1: *tela = FASE_2; break;
    case FASE_2: *tela = FASE_3; break;
    default: break;
    }
}

#endif