#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// Função principal do programa
int main() {

    // Inicializa a biblioteca Allegro
    al_init();
    // Inicializa o complemento de fontes do Allegro
    al_init_font_addon();

    // Cria uma janela de exibição com resolução 640x480 pixels
    ALLEGRO_DISPLAY* display = al_create_display(640, 480);
    // Define a posição da janela na tela (coordenadas 200, 200)
    al_set_window_position(display, 200, 200);

    // Cria uma fonte padrão embutida no Allegro
    ALLEGRO_FONT* font = al_create_builtin_font();
    // Cria um temporizador com 60 frames por segundo (1.0 / 60.0 = 0.01666 segundos)
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    // Cria uma fila de eventos para gerenciar eventos no jogo
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    // Registra eventos de fechamento da janela
    al_register_event_source(event_queue, al_get_display_event_source(display));
    // Registra eventos do temporizador
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    // Inicia o temporizador
    al_start_timer(timer);

    // Loop principal do jogo
    while (true) {
        ALLEGRO_EVENT event;
        // Aguarda o próximo evento da fila
        al_wait_for_event(event_queue, &event);

        // Se o evento for de fechamento da janela, o loop termina
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        // Limpa a tela com a cor branca (RGB: 255, 255, 255)
        al_clear_to_color(al_map_rgb(255, 255, 255));
        // Desenha o texto "Allegro is working!" na tela, com a cor preta (RGB: 0, 0, 0)
        al_draw_text(font, al_map_rgb(0, 0, 0), 230, 200, 0, "Allegro is working!");
        // Atualiza a exibição (troca o buffer da tela para mostrar as alterações)
        al_flip_display();
    }

    // Destroi a fonte, liberando a memória
    al_destroy_font(font);
    // Destroi a janela de exibição
    al_destroy_display(display);
    // Destroi a fila de eventos
    al_destroy_event_queue(event_queue);

    // Retorna 0 indicando que o programa terminou com sucesso
    return 0;
}
