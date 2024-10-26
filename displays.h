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
void atualizar_estado(EstadoAtual* tela);

#endif