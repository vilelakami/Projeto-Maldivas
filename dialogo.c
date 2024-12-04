// dialogo.c

#include "dialogo.h"

void init_dialogues(Dialogue* dialogues) {
    dialogues[0].texto = "Akimov: Camarada Dyatlov, boa tarde. Iremos hoje finalmente finalizar o teste de seguranca.";
    dialogues[1].texto = "Dyatlov: Camarada Akimov, acabei de receber um telefonema de Moscou. Nao permitiram reduzir a producao de energia ainda mais.";
    dialogues[2].texto = "Akimov: M-mas e necessario reduzir a producao gradativamente para realizar o teste, ele simula uma falta de energia por um ataque ou desastre natural...";
    dialogues[3].texto = "Dyatlov: FACA O TESTE ASSIM MESMO!!! O teste no ano passado foi um fracasso e nao vamos esperar outro ano para tentar novamente! Iremos realizar o teste nesta madrugada.";
    dialogues[4].texto = "Akimov: C-certo entao. Eu pessoalmente irei supervisionar o teste.";
}
