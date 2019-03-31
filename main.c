#include <allegro.h>
#include <stdio.h>

#include "variaveis.h"
#include "init_troca.c"
#include "menu.c"
#include "mapa_mov.c"
#include "battle.c"
#include "jogo.c"
#include "save_load.c"
#include "aux.c"
#include "game_logic.c"

int main(){
    init_fun();
    srand(time(NULL));
    buffer = create_bitmap(SCREEN_W+200, SCREEN_H);
    load_maps();



    while(!fechar){
        if(menu){
            set_window_title("RPG - Menu");
            menu_inicial();
        }
       if(jogo){
            set_window_title("RPG - Jogo");
            jogo_run();

        }
    }

  return 0;
}END_OF_MAIN();
