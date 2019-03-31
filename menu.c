#include "menu.h"
#include "variaveis.h"
#include "jogo.h"
#include "save_load.h"
#include "battle.h"
#include <allegro.h>

void menu_inicial() {
    int menu_var = 0;
    int i;
    BITMAP* menu_opc[] = {
        load_bitmap("img/menu_opc1.bmp",NULL),
        load_bitmap("img/menu_opc2.bmp",NULL),
        load_bitmap("img/menu_opc3.bmp",NULL)
    };

    MIDI* menu_st = load_midi("sound/ct1000ad.mid");
    play_midi(menu_st,TRUE);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_X, TELA_Y, 0, 0);
    sel_sound = load_sample("sound/button1.wav");
    while(!fechar && menu){
        while(contador > 0 && (!fechar && menu)){
            keyboard_fix();
            sel_f(&menu_var, 2);
            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                switch(menu_var){
                    case 0:
                        jogo_f();
                        menu_f();
                        novo_jogo();
                        update_max_stat();

                        break;
                    case 1:
                        jogo_f();
                        menu_f();
                        load_game();
                        update_max_stat();

                        break;
                    case 2:
                        sair_f();
                        break;
                }
            }
            draw_sprite(buffer, menu_opc[menu_var], 0, 0);
            draw_sprite(screen, buffer, 0, 0);
            clear(buffer);
            contador--;
        }
    }
    for( i=0; i<3; i++)
        destroy_bitmap(menu_opc[i]);
    destroy_midi(menu_st);
}
