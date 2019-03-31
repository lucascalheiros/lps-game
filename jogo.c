#include "jogo.h"
#include "variaveis.h"
#include "mapa_mov.h"
#include "game_logic.h"
#include "aux.h"
#include <allegro.h>


void novo_jogo(){
    pos.x = 100;
    pos.y = 500;
    mapa_id = 0;
    stat.LIFE = 60;
    stat.MANA = 5;
    stat.POT = 0;
    stat.EXP = 0;
    max_stat.LVL = 1;
    dir = 0;
    stat.GOLD = 0;
}

void batalha(){
    if((0 == rand()%17 && (mapa[mapa_id][(pos.y+13)/PIXELS][(pos.x+13)/PIXELS] != CHAO)) && (0 == rand()%17 && (mapa[mapa_id][(pos.y+13)/PIXELS][(pos.x+13)/PIXELS] != PAREDE))){
        battle_f();
        battle_run();
    }
}

void printf_menu_jogo_selection( int menu_jogo_var){
    textprintf_ex(buffer, font, 825, 225, makecol(0,0,0), -1, "HP: %d/%d",stat.LIFE,max_stat.LIFE);
    textprintf_ex(buffer, font, 825, 235, makecol(0,0,0), -1, "MP: %d/%d",stat.MANA,max_stat.MANA);
    textprintf_ex(buffer, font, 825, 245, makecol(0,0,0), -1, "LVL: %d",max_stat.LVL);
    textprintf_ex(buffer, font, 825, 255, makecol(0,0,0), -1, "EXP: %d/%d",stat.EXP,max_stat.EXP);
    textprintf_ex(buffer, font, 825, 265, makecol(0,0,0), -1, "POT: %d",stat.POT);
    textprintf_ex(buffer, font, 825, 275, makecol(0,0,0), -1, "GOLD: %d",stat.GOLD);
    textprintf_ex(buffer, font, 825, 285, makecol(0,0,0), -1, "ATK: %d",max_stat.ATK);
    textprintf_ex(buffer, font, 825, 295, makecol(0,0,0), -1, "MATK: %d",max_stat.MAGIC);
    textprintf_ex(buffer, font, 825, 305, makecol(0,0,0), -1, "DEF: %d",max_stat.DEF);

    textout_ex(buffer, font, "Voltar", 825, 400, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Cura Magica", 825, 410, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Potion", 825, 420, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Save", 825, 430, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Sair", 825, 440, makecol(255,255,255),-1);
    switch( menu_jogo_var ){
        case 0:
            textout_ex(buffer, font, "Voltar", 825, 400, makecol(0,0,0),-1);
            break;
        case 1:
            textout_ex(buffer, font, "Cura Magica", 825, 410, makecol(0,0,0),-1);
            break;
        case 2:
            textout_ex(buffer, font, "Potion", 825, 420, makecol(0,0,0),-1);
            break;
        case 3:
            textout_ex(buffer, font, "Save", 825, 430, makecol(0,0,0),-1);
            break;
        case 4:
            textout_ex(buffer, font, "Sair", 825, 440, makecol(0,0,0),-1);
            break;
    }
}

void jogo_run(){
    int menu_jogo = 0;
    int menu_jogo_var = 0;
    int i;
    int counter=0;
    BITMAP* menu_jogo_bmp = load_bitmap("img/menu_jogo.bmp",NULL);

    BITMAP* personagem[]={
        load_bitmap("img/char_e.bmp",NULL),
        load_bitmap("img/char_d.bmp",NULL),
        load_bitmap("img/char_f.bmp",NULL),
        load_bitmap("img/char_t.bmp",NULL)
       
    };
    BITMAP* you = load_bitmap("img/battle_char.bmp",NULL);
    BITMAP* npc_bar = load_bitmap("img/npc_bar.bmp",NULL);

    BITMAP* parede = load_bitmap("img/parede.bmp",NULL);
    BITMAP* grama = load_bitmap("img/grama.bmp",NULL);
    BITMAP* arvore = load_bitmap("img/arvore.bmp",NULL);
    BITMAP* agua = load_bitmap("img/agua.bmp",NULL);
    BITMAP* pedra = load_bitmap("img/pedra.bmp",NULL);
    BITMAP* pedra2 = load_bitmap("img/pedra2.bmp",NULL);
    BITMAP* npc = load_bitmap("img/npc.bmp",NULL);
    BITMAP* save = load_bitmap("img/save.bmp",NULL);
    BITMAP* stone = load_bitmap("img/stone.bmp",NULL);
    BITMAP* stone2 = load_bitmap("img/stone2.bmp",NULL);
    BITMAP* boss = load_bitmap("img/boss2.bmp",NULL);
    BITMAP* princesa = load_bitmap("img/princesa.bmp",NULL);
    BITMAP* atk_pic_anima[6];
    atk_pic_anima[0]=load_bitmap( "img/atk_frame1.bmp", NULL );
    atk_pic_anima[1]=load_bitmap( "img/atk_frame2.bmp", NULL );
    atk_pic_anima[2]=load_bitmap( "img/atk_frame3.bmp", NULL );
    atk_pic_anima[3]=load_bitmap( "img/atk_frame4.bmp", NULL );
    atk_pic_anima[4]=load_bitmap( "img/atk_frame5.bmp", NULL );
    atk_pic_anima[5]=load_bitmap( "img/atk_frame6.bmp", NULL );
    for( int i = 0; i<6; i++ ) {
        atk_pic_anima[i] = resize(atk_pic_anima[i], PIXELS, PIXELS);
    }
    for( int i = 0; i<4; i++ ) {
        personagem[i] = resize(personagem[i], PIXELS, PIXELS);
    }
    parede = resize(parede, PIXELS, PIXELS);
    grama = resize(grama, PIXELS, PIXELS);
    arvore = resize(arvore, PIXELS, PIXELS);
    agua = resize(agua, PIXELS, PIXELS);
    pedra = resize(pedra, PIXELS, PIXELS);
    pedra2 = resize(pedra2, PIXELS, PIXELS);
    stone = resize(stone, PIXELS, PIXELS);
    stone2 = resize(stone2, PIXELS, PIXELS);


    MIDI* jogo_st = load_midi("sound/ct600ad.mid");
    play_midi(jogo_st,TRUE);
    while(!fechar && jogo){
        while(contador > 0 && (!fechar && jogo)){
            keyboard_fix();
            if(anterior_ESC == 0 && key[KEY_ESC] != 0){ // ao pressionar esc abre o menu do jogo
                if(menu_jogo){
                    set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_X, TELA_Y, 0, 0);
                    menu_jogo = 0;
                    midi_resume();
                }
                else{
                    set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_X + 200, TELA_Y, 0, 0);
                    menu_jogo = 1;
                    midi_pause();
                }
            }

            if(menu_jogo){ // menu do jogo
                sel_f(&menu_jogo_var,3);
                if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                    switch( menu_jogo_var ){
                        case 0:
                            set_gfx_mode(GFX_AUTODETECT_WINDOWED, TELA_X, TELA_Y, 0, 0);
                            menu_jogo = 0;
                            midi_resume();
                            break;
                        case 1:
                            if(stat.MANA > 0 && max_stat.LIFE > stat.LIFE){
                                stat.LIFE += max_stat.MAGIC;
                                stat.MANA--;
                                if(stat.LIFE > max_stat.LIFE)
                                stat.LIFE = max_stat.LIFE;
                            }
                            break;
                        case 2:
                            if(stat.POT > 0 && max_stat.LIFE > stat.LIFE){
                                stat.LIFE += max_stat.LIFE / 2;
                                stat.POT--;
                                if(stat.LIFE > max_stat.LIFE)
                                stat.LIFE = max_stat.LIFE;
                            }
                            break;
                        case 3:
                            save_game();
                            break;
                        case 4:
                            jogo_f();
                            menu_f();
                            break;
                    }
                }
            }
            if(!menu_jogo){
                if(!dead) {
                    game();
                    action();
                    troca_mapa();
                }
            }

            desenhar_mapa(parede, grama, arvore, agua, pedra, pedra2, npc, save, stone, stone2, boss, princesa);
            draw_monsters();
            if(attacking) {
                if(anima(atk_pic_anima, 6, pos))
                    attacking = FALSE;
                if(dir == LEFT)
                    rect(buffer, pos.x+25-40, pos.y+10, pos.x+25, pos.y+40, 1);
                if(dir == RIGHT)
                    rect(buffer, pos.x+25, pos.y+10, pos.x+25+40, pos.y+40, 1);
            }
            else {
                draw_sprite(buffer, personagem[dir], pos.x, pos.y);
            }
            npc_f(npc_bar,&counter);
            if(menu_jogo) {
                draw_sprite(buffer, menu_jogo_bmp, 0, 0);
                draw_sprite(buffer, you, 825, 25);
                printf_menu_jogo_selection(menu_jogo_var);
            }
            draw_sprite(screen, buffer, 0, 0);
            clear(buffer);
            contador--;
            }
        }
    destroy_bitmap(menu_jogo_bmp);
    for( i=0; i<4; i++)
        destroy_bitmap(personagem[i]);
    destroy_bitmap(you);
    destroy_bitmap(npc_bar);
    destroy_bitmap(parede);
    destroy_bitmap(grama);
    destroy_bitmap(arvore);
    destroy_bitmap(pedra);
    destroy_bitmap(pedra2);
    destroy_bitmap(npc);
    destroy_bitmap(save);
    destroy_bitmap(stone);
    destroy_bitmap(stone2);
    destroy_bitmap(boss);
    destroy_bitmap(princesa);
    destroy_midi(jogo_st);
}
