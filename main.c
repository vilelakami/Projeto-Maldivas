#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <windows.h>
int main() {

    ALLEGRO_BITMAP* icon = NULL;
    
    //icone para a janela

    al_init();
    al_init_font_addon();
    //inicia as funcoes basicas de allegro e de fonte nativa
    al_init_image_addon();
    //inicia a biblioteca que permite inserir imagem

    

    ALLEGRO_DISPLAY* display = al_create_display(960, 540);    
    al_set_window_position(display, 200, 200);
    //cria a janela, seu tamanho e onde ela será aberta. respectivamente.
    al_set_window_title(display, "Chernobyl Game.");
    //titulo na janela.
    

    icon = al_load_bitmap("icon.bmp");
    //icone para a janela

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    //timer - fps da tela e timer necessari opara alguns eventos.
    

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }


        al_set_display_icon(display, icon);
        al_clear_to_color(al_map_rgb(255, 255, 255));
        
        al_draw_text(font, al_map_rgb(0, 0, 0), 230, 200, 0, "GAME OVER!");

        
       
        

        al_flip_display();
    }
    //quando clica em fechar ele sai do loop que roda a tela e destroi o que foi criando.
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(icon);

    return 0;
}