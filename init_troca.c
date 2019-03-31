#include "init_troca.h"
#include "variaveis.h"
#include <allegro.h>


void sair_f() {
    fechar = TRUE;
}END_OF_FUNCTION(sair_f)

void battle_f() {
    if( battle == FALSE )
        battle = TRUE;
    else
        battle = FALSE;
}END_OF_FUNCTION(jogo_f)

void jogo_f() {
    if( jogo == FALSE )
        jogo = TRUE;
    else
        jogo = FALSE;
}END_OF_FUNCTION(jogo_f)

void menu_f() {
    if( menu == FALSE)
        menu = TRUE;
    else
        menu = FALSE;
}END_OF_FUNCTION(menu_f)

void fps_f() {
    contador++;
}END_OF_FUNCTION(fps_f)

void timer_f() {
    battle_timer++;
    anima_timer++;
}END_OF_FUNCTION(timer_f)

void init_fun() {
    allegro_init();
    install_timer();
    install_keyboard();
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_X, TELA_Y, 0, 0);

    LOCK_FUNCTION(sair_f);
    LOCK_VARIABLE(fechar);
    set_close_button_callback(sair_f);

    LOCK_FUNCTION(fps_f);
    LOCK_VARIABLE(contador);
    install_int_ex(fps_f, BPS_TO_TIMER(60));

    LOCK_FUNCTION(timer_f);
    LOCK_VARIABLE(battle_timer);
    LOCK_VARIABLE(anime_timer);
    install_int_ex(timer_f, BPM_TO_TIMER(1000));
}

void sel_f(int* sel_var, int n_opc ){
    if(anterior_UP == 0 && key[KEY_UP] != 0){
       (*sel_var)--;
        play_sample(sel_sound, 255, 128, 1000, FALSE);
        if((*sel_var) < 0)
           (*sel_var) = 0;
    }
    else if(anterior_DOWN == 0 && key[KEY_DOWN] != 0){
        (*sel_var)++;
        play_sample(sel_sound, 255, 128, 1000, FALSE);
        if((*sel_var) > n_opc)
            (*sel_var) = n_opc;
        }
}

void keyboard_fix(){
    anterior_UP = key[KEY_UP];
    anterior_DOWN = key[KEY_DOWN];
    anterior_LEFT = key[KEY_LEFT];
    anterior_RIGHT = key[KEY_RIGHT];
    anterior_SPACE = key[KEY_SPACE];
    anterior_ENTER = key[KEY_ENTER];
    anterior_ENTER_PAD = key[KEY_ENTER_PAD];
    anterior_ESC = key[KEY_ESC];
    poll_keyboard();
}
