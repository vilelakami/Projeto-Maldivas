#ifndef INTERACOES_H
#define INTERACOES_H

#include <stdbool.h>

typedef struct {
    bool interagiu_obstaculo_2;
    bool interagiu_obstaculo_3;
    int contador_interacoes;
} Interacoes;

void init_interacoes(Interacoes* interacoes);

#endif // INTERACOES_H
