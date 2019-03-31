#include "variaveis.h"
#include <allegro.h>
#include "battle.h"

void update_max_stat() { //fun��o para atualiza��o dos status com base no lvl
    max_stat.ATK = 8 + 3 * max_stat.LVL;
    max_stat.DEF = 6 + 3 * max_stat.LVL;
    max_stat.LIFE = 53 + 7 * max_stat.LVL;
    max_stat.MANA = 4 + 1 * max_stat.LVL;
    max_stat.EXP = 12 * max_stat.LVL;
    max_stat.MAGIC = 16 + 4 * max_stat.LVL;
}

void verif_lvl() { //verifica se passou de lvl e atualiza os status
    while(stat.EXP >= max_stat.EXP) {
        stat.EXP = stat.EXP - max_stat.EXP;
        max_stat.LVL++;
        update_max_stat();
    }
}

void mons_sel_f(int* mons_sel_var, int n_mons) {
    if(anterior_RIGHT == 0 && key[KEY_RIGHT] != 0) {
        (*mons_sel_var)--;
        play_sample(sel_sound, 255, 128, 1000, FALSE);
        if ((*mons_sel_var) < 0)
            (*mons_sel_var) = 0;
    }
    else if(anterior_LEFT == 0 && key[KEY_LEFT] != 0) {
        (*mons_sel_var)++;
        play_sample(sel_sound, 255, 128, 1000, FALSE);
        if ((*mons_sel_var) > n_mons)
            (*mons_sel_var) = n_mons;
    }
}

int verif_win_lose(int n_mons, int verif_mons[]) {
    if(stat.LIFE <= 0) {
        stat.LIFE = 0;
        return LOSE;
    }
    else
    switch(n_mons) {
        case 0:
            if(verif_mons[0] == 0)
                return WIN;
        case 1:
            if(verif_mons[0] == 0 &&  verif_mons[1] == 0)
                return WIN;
        case 2:
            if(verif_mons[0] == 0 &&  verif_mons[1] == 0 && verif_mons[2] ==0)
                return WIN;
    }
    return BATTLE;

}


void drop_system(MONSTRO bmons) {
    if(rand() % DROP_POT == 0)
        stat.POT++;
    if(rand() % DROP_MANA == 0)
        stat.MANA++;
    stat.EXP += bmons.EXP;
    stat.GOLD += bmons.GOLD - rand() % (bmons.GOLD/2+1);

}

void printf_battle_mons_selection( int mons_sel_var, MONSTRO bmons[], MONSTRO mons[], int mobs[], int n_mons ) {
    switch( n_mons ){
        case 2:
            textprintf_ex(buffer, font, 200, 535, makecol(100,0,0), -1, "%s",bmons[2].NOME);
            textprintf_ex(buffer, font, 200, 545, makecol(100,0,0), -1, "HP: %d/%d",bmons[2].LIFE,mons[mobs[2]].LIFE);
            if( mons_sel_var == 2 ){
                textprintf_ex(buffer, font, 200, 535, makecol(255,255,255), -1, "%s",bmons[2].NOME);
                textprintf_ex(buffer, font, 200, 545, makecol(255,255,255), -1, "HP: %d/%d",bmons[2].LIFE,mons[mobs[2]].LIFE);
            }
        case 1:
            textprintf_ex(buffer, font, 350, 535, makecol(100,0,0), -1, "%s",bmons[1].NOME);
            textprintf_ex(buffer, font, 350, 545, makecol(100,0,0), -1, "HP: %d/%d",bmons[1].LIFE,mons[mobs[1]].LIFE);
            if(mons_sel_var == 1 && n_mons >=1){
                textprintf_ex(buffer, font, 350, 535, makecol(255,255,255), -1, "%s",bmons[1].NOME);
                textprintf_ex(buffer, font, 350, 545, makecol(255,255,255), -1, "HP: %d/%d",bmons[1].LIFE,mons[mobs[1]].LIFE);
            }
        case 0:
            textprintf_ex(buffer, font, 500, 535, makecol(100,0,0), -1, "%s",bmons[0].NOME);
            textprintf_ex(buffer, font, 500, 545, makecol(100,0,0), -1, "HP: %d/%d",bmons[0].LIFE,mons[mobs[0]].LIFE);
            if(mons_sel_var==0 ){
                textprintf_ex(buffer, font, 500, 535, makecol(255,255,255), -1, "%s",bmons[0].NOME);
                textprintf_ex(buffer, font, 500, 545, makecol(255,255,255), -1, "HP: %d/%d",bmons[0].LIFE,mons[mobs[0]].LIFE);
            }
    }
}

void printf_battle_status_selection( int battle_var) {

    textprintf_ex(buffer, font, 700, 525, makecol(0,0,0), -1, "HP: %d/%d",stat.LIFE,max_stat.LIFE);
    textprintf_ex(buffer, font, 700, 535, makecol(0,0,0), -1, "MP: %d/%d",stat.MANA,max_stat.MANA);
    textprintf_ex(buffer, font, 700, 545, makecol(0,0,0), -1, "LVL: %d",max_stat.LVL);
    textprintf_ex(buffer, font, 700, 555, makecol(0,0,0), -1, "EXP: %d/%d",stat.EXP,max_stat.EXP);
    textprintf_ex(buffer, font, 700, 565, makecol(0,0,0), -1, "POT: %d",stat.POT);
    textprintf_ex(buffer, font, 700, 575, makecol(0,0,0), -1, "GOLD: %d",stat.GOLD);
    textprintf_ex(buffer, font, 600, 535, makecol(0,0,0), -1, "ATK: %d",max_stat.ATK);
    textprintf_ex(buffer, font, 600, 545, makecol(0,0,0), -1, "MATK: %d",max_stat.MAGIC);
    textprintf_ex(buffer, font, 600, 555, makecol(0,0,0), -1, "DEF: %d",max_stat.DEF);

    textout_ex(buffer, font, "Ataque Normal", 10, 530, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Ataque Magico", 10, 540, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Cura Magica", 10, 550, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Potion", 10, 560, makecol(255,255,255),-1);
    textout_ex(buffer, font, "Fugir", 10, 570, makecol(255,255,255),-1);
    switch( battle_var ){
        case 0:
            textout_ex(buffer, font, "Ataque Normal", 10, 530, makecol(0,0,0),-1);
            break;
        case 1:
            textout_ex(buffer, font, "Ataque Magico", 10, 540, makecol(0,0,0),-1);
            break;
        case 2:
            textout_ex(buffer, font, "Cura Magica", 10, 550, makecol(0,0,0),-1);
            break;
        case 3:
            textout_ex(buffer, font, "Potion", 10, 560, makecol(0,0,0),-1);
            break;
        case 4:
            textout_ex(buffer, font, "Fugir", 10, 570, makecol(0,0,0),-1);
            break;
    }
}


void printf_you_mobs( int n_mons, int verif_mons[], int batt_anima, BITMAP* mob_pic[], BITMAP* mob_dead_pic[], BITMAP* you, BITMAP* you_dead){

    if(stat.LIFE != 0 && batt_anima == 0)
        draw_sprite(buffer, you, 100, 250);
    else if(stat.LIFE == 0 && batt_anima == 0)
        draw_sprite(buffer, you_dead, 100, 250);

    if(mapa[mapa_id][(pos.y+28)/PIXELS][(pos.x+13)/PIXELS] == BOSS){
         if(verif_mons[0])
                draw_sprite(buffer, mob_pic[0], 400, 200);
            else
                draw_sprite(buffer, mob_dead_pic[0], 400, 200);
    }
     else
    switch(n_mons){
        case 2:
            if(verif_mons[2])
                draw_sprite(buffer, mob_pic[2], 400, 200);
            else
                draw_sprite(buffer, mob_dead_pic[2], 400, 200);

        case 1:
            if(verif_mons[1])
                draw_sprite(buffer, mob_pic[1], 500, 250);
            else
                draw_sprite(buffer, mob_dead_pic[1], 500, 250);
        case 0:
            if(verif_mons[0])
                draw_sprite(buffer, mob_pic[0], 600, 300);
            else
                draw_sprite(buffer, mob_dead_pic[0], 600, 300);
            break;
    }
}

void printf_win_or_lose(int verif_wl_var, int n_mons, BITMAP* venceu, BITMAP* perdeu){
    if(verif_wl_var == LOSE && battle_timer > 8){
        draw_sprite(buffer, perdeu, 0, 0);
        textout_ex(buffer, font, "DICAS: ", 230, 200, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Preste atencao em sua vida ", 230, 210, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Use potions e curas para recupera-la ", 230, 220, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Tome cuidado com sua mana ", 230, 240, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Se ela zerar voce nao podera fazer muita coisa ", 230, 250, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Se estiver fraco va aos mapas iniciais ", 230, 270, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Os monstros la sao mais fracos ", 230, 280, makecol(0,0,0),-1);
        textout_ex(buffer, font, "Use os saves ao seu favor ", 230, 300, makecol(0,0,0),-1);
    }
    else if(verif_wl_var == WIN && battle_timer > 8){
        draw_sprite(buffer, venceu, 0, 0);
        textprintf_ex(buffer, font, 230, 200, makecol(0,0,0), -1, "HP: %d/%d",stat.LIFE,max_stat.LIFE);
        textprintf_ex(buffer, font, 230, 210, makecol(0,0,0), -1, "MP: %d/%d",stat.MANA,max_stat.MANA);
        textprintf_ex(buffer, font, 230, 220, makecol(0,0,0), -1, "LVL: %d",max_stat.LVL);
        textprintf_ex(buffer, font, 230, 230, makecol(0,0,0), -1, "EXP: %d/%d",stat.EXP,max_stat.EXP);
        textprintf_ex(buffer, font, 230, 240, makecol(0,0,0), -1, "POT: %d",stat.POT);
        textprintf_ex(buffer, font, 230, 250, makecol(0,0,0), -1, "GOLD: %d",stat.GOLD);
        textprintf_ex(buffer, font, 230, 260, makecol(0,0,0), -1, "ATK: %d",max_stat.ATK);
        textprintf_ex(buffer, font, 230, 270, makecol(0,0,0), -1, "MATK: %d",max_stat.MAGIC);
        textprintf_ex(buffer, font, 230, 280, makecol(0,0,0), -1, "DEF: %d",max_stat.DEF);
        textout_ex(buffer, font, "Bonus de vitoria: ", 230, 300, makecol(0,0,0),-1);
        textprintf_ex(buffer, font, 230, 310, makecol(0,0,0), -1, "1 Ponto de mana");
        textprintf_ex(buffer, font, 230, 320, makecol(0,0,0), -1, "%d Pontos de vida",(n_mons+1) * 3);
        textprintf_ex(buffer, font, 230, 330, makecol(0,0,0), -1, "%d Pontos de EXP",(n_mons+1) * 3);
        textprintf_ex(buffer, font, 230, 340, makecol(0,0,0), -1, "%d Unidades de ouro",(n_mons+1) * 3);
    }
}

void you_anima(int* batt_anima, BITMAP* atk_pic_anima[], BITMAP* matk_pic_anima[], BITMAP* cura_pic_anima[], BITMAP* pot_pic_anima[], BITMAP* flee_pic_anima[]){
    switch((*batt_anima)){
        case 1:
            draw_sprite(buffer, atk_pic_anima[battle_timer],100, 250 );
                if(battle_timer == 5)
                    (*batt_anima) = 0;
            break;
        case 2:
            draw_sprite(buffer, matk_pic_anima[battle_timer],100, 250 );
                if(battle_timer == 5)
                    (*batt_anima) = 0;
            break;
        case 3:
            draw_sprite(buffer, cura_pic_anima[battle_timer],100, 250 );
                if(battle_timer == 5)
                    (*batt_anima) = 0;
            break;
        case 4:
            draw_sprite(buffer, pot_pic_anima[battle_timer],100, 250 );
                if(battle_timer == 5)
                    (*batt_anima) = 0;
            break;
        case 5:
            draw_sprite(buffer, flee_pic_anima[battle_timer],100, 250 );
                if(battle_timer == 5)
                    (*batt_anima) = 0;
            break;
    }
}




void battle_run() {

    char *name_batt_st[] = { // ponteiro de strings para carregar diferentes sons de fundo de batalha
        "sound/batt.mid",
        "sound/batt2.mid",
        "sound/batt3.mid",
        "sound/batt4.mid",
        "sound/batt5.mid",
        "sound/batt6.mid",
        "sound/batt7.mid",
    };

    char *name_batt_pics[] = { // ponteiro de strings para carregar diferentes fundos de batalha
        "img/batt.bmp",
        "img/batt2.bmp",
        "img/batt3.bmp",
        "img/batt4.bmp",
        "img/batt5.bmp",
        "img/batt6.bmp",
        "img/batt7.bmp"
    };

    char *name_mob_pics[] = { // ponteiro de strings para carregar imagens de monstros
        "img/goblin.bmp",
        "img/orc.bmp",
        "img/zombie.bmp",
        "img/cyclops.bmp",
        "img/elf.bmp",
        "img/phantom.bmp",
        "img/boss.bmp"
    };

    char *name_dead_mob_pics[] = { // ponteiro de strings para carregar imagens de monstros derrotados
        "img/goblin_dead.bmp",
        "img/orc_dead.bmp",
        "img/zombie_dead.bmp",
        "img/cyclops_dead.bmp",
        "img/elf_dead.bmp",
        "img/phantom_dead.bmp",
        "img/boss_dead.bmp"
    };

    MONSTRO mons[] = {//declara��o do nome, ataque, vida e exp dropada dos monstros(base)
        {"Goblin" ,  7,  25,   5,  3},
        {"Orc"    , 25,  50,  17, 5},
        {"Zombie" , 30, 100,  50, 20},
        {"Cyclops", 60, 150,  100, 30},
        {"Elf"    , 70, 150, 150, 50},
        {"Phantom", 90, 250, 200, 80},
        {"REI DO MAL", 150, 10000, 10000, 10000}
    };

    int i;
    int battle_var = 0;
    int mons_sel_var = 0;
    int verif_mons[3]={1,1,1};
    int n_mons = rand() % 3;
    int turn_counter = 0;
    int verif_wl_var = BATTLE;
    int regen = 1;
    int batt_anima = 0;
    float def;
    int mobs_id[]={
        mapa_id-1+rand()%(2),
        mapa_id-1+rand()%(2),
        mapa_id-1+rand()%(2)
    };
    if(mapa_id == 0){
        mobs_id[0]= 0;
        mobs_id[1]= 0;
        mobs_id[2]= 0;
    }
    sel_sound = load_sample("sound/button2.wav");


    MONSTRO bmons[3]={ mons[mobs_id[0]], mons[mobs_id[1]], mons[mobs_id[2]] };

    BITMAP* you = load_bitmap("img/battle_char.bmp",NULL);
    BITMAP* you_dead = load_bitmap("img/battle_char_dead.bmp",NULL);


    BITMAP* mob_pic[] = {
        load_bitmap( name_mob_pics[mobs_id[0]], NULL ),
        load_bitmap( name_mob_pics[mobs_id[1]], NULL ),
        load_bitmap( name_mob_pics[mobs_id[2]], NULL )
    };
    BITMAP* mob_dead_pic[] = {
        load_bitmap( name_dead_mob_pics[mobs_id[0]], NULL ),
        load_bitmap( name_dead_mob_pics[mobs_id[1]], NULL ),
        load_bitmap( name_dead_mob_pics[mobs_id[2]], NULL )
    };
    BITMAP* atk_pic_anima[]={
        load_bitmap( "img/atk_frame1.bmp", NULL ),
        load_bitmap( "img/atk_frame2.bmp", NULL ),
        load_bitmap( "img/atk_frame3.bmp", NULL ),
        load_bitmap( "img/atk_frame4.bmp", NULL ),
        load_bitmap( "img/atk_frame5.bmp", NULL ),
        load_bitmap( "img/atk_frame6.bmp", NULL )
    };
    BITMAP* matk_pic_anima[]={
        load_bitmap( "img/matk_frame1.bmp", NULL ),
        load_bitmap( "img/matk_frame2.bmp", NULL ),
        load_bitmap( "img/matk_frame3.bmp", NULL ),
        load_bitmap( "img/matk_frame4.bmp", NULL ),
        load_bitmap( "img/matk_frame5.bmp", NULL ),
        load_bitmap( "img/matk_frame6.bmp", NULL )
    };
    BITMAP* cura_pic_anima[]={
        load_bitmap( "img/cura_frame1.bmp", NULL ),
        load_bitmap( "img/cura_frame2.bmp", NULL ),
        load_bitmap( "img/cura_frame3.bmp", NULL ),
        load_bitmap( "img/cura_frame4.bmp", NULL ),
        load_bitmap( "img/cura_frame5.bmp", NULL ),
        load_bitmap( "img/cura_frame6.bmp", NULL )
    };
    BITMAP* pot_pic_anima[]={
        load_bitmap( "img/pot_frame1.bmp", NULL ),
        load_bitmap( "img/pot_frame2.bmp", NULL ),
        load_bitmap( "img/pot_frame3.bmp", NULL ),
        load_bitmap( "img/pot_frame4.bmp", NULL ),
        load_bitmap( "img/pot_frame5.bmp", NULL ),
        load_bitmap( "img/pot_frame6.bmp", NULL )
    };
    BITMAP* flee_pic_anima[]={
        load_bitmap( "img/flee_frame1.bmp", NULL ),
        load_bitmap( "img/flee_frame2.bmp", NULL ),
        load_bitmap( "img/flee_frame3.bmp", NULL ),
        load_bitmap( "img/flee_frame4.bmp", NULL ),
        load_bitmap( "img/flee_frame5.bmp", NULL ),
        load_bitmap( "img/flee_frame6.bmp", NULL )
    };


    BITMAP* venceu = load_bitmap("img/venceu.bmp",NULL);
    BITMAP* perdeu = load_bitmap("img/perdeu.bmp",NULL);

    BITMAP* battle_m = load_bitmap(name_batt_pics[mapa_id],NULL);

    MIDI* battle_st = load_midi(name_batt_st[mapa_id]);
    MIDI* jogo_st = load_midi("sound/ct600ad.mid");
    SAMPLE* sword = load_sample("sound/sword.wav");
    SAMPLE* matk = load_sample("sound/matk.wav");
    SAMPLE* heal = load_sample("sound/heal.wav");
    SAMPLE* pot = load_sample("sound/pot.wav");


    play_midi(battle_st,TRUE);

    while(!fechar && battle){
        while(contador > 0 && (!fechar && battle)){
            keyboard_fix();
            sel_f( &battle_var, 4 );
            if(stat.LIFE > 0 && verif_wl_var == BATTLE && turn_counter == MEU_TURNO){
                switch(battle_var){
                    case 0: // ATAQUE NORMAL
                        mons_sel_f(&mons_sel_var, n_mons );
                            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                                batt_anima = 1;
                                battle_timer = 0;
                                play_sample(sword, 255, 128, 1000, FALSE);
                                switch(mons_sel_var){
                                    case 0:
                                        if(verif_mons[0]){
                                            bmons[0].LIFE-=max_stat.ATK - rand() % (max_stat.ATK/2) + rand() % (max_stat.ATK/4) ;
                                            turn_counter = MOB_TURNO;
                                        }
                                        break;
                                    case 1:
                                        if(verif_mons[1]){
                                            bmons[1].LIFE-=max_stat.ATK - rand() % (max_stat.ATK/2) + rand() % (max_stat.ATK/4) ;
                                            turn_counter = MOB_TURNO;
                                        }
                                        break;
                                    case 2:
                                        if(verif_mons[2]){
                                            bmons[2].LIFE-=max_stat.ATK - rand() % (max_stat.ATK/2) + rand() % (max_stat.ATK/4) ;
                                            turn_counter = MOB_TURNO;
                                        }
                                        break;
                                }
                            }
                            break;
                        case 1: //ATAQUE MAGICO
                            mons_sel_f(&mons_sel_var, n_mons  );
                            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                                batt_anima = 2;
                                battle_timer = 0;
                                play_sample(matk, 255, 128, 1000, FALSE);
                                switch(mons_sel_var){
                                    case 0:
                                        if(verif_mons[0]){
                                            if(stat.MANA > 0){
                                                bmons[0].LIFE-=max_stat.MAGIC - rand() % (max_stat.ATK/4) + rand() % (max_stat.ATK/6);
                                                stat.MANA--;
                                                turn_counter = MOB_TURNO;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(verif_mons[1]){
                                            if(stat.MANA > 0){
                                                bmons[1].LIFE-=max_stat.MAGIC - rand() % (max_stat.ATK/4) + rand() % (max_stat.ATK/6);
                                                stat.MANA--;
                                                turn_counter = MOB_TURNO;
                                            }
                                        }
                                        break;
                                    case 2:
                                        if(verif_mons[2]){
                                            if(stat.MANA > 0){
                                                bmons[2].LIFE-=max_stat.MAGIC - rand() % (max_stat.ATK/4) + rand() % (max_stat.ATK/6);
                                                stat.MANA--;
                                                turn_counter = MOB_TURNO;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 2: //CURA
                            mons_sel_f(&mons_sel_var, n_mons );
                            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                                batt_anima = 3;
                                battle_timer = 0;
                                play_sample(heal, 255, 128, 1000, FALSE);
                                if(stat.MANA > 0 && max_stat.LIFE > stat.LIFE){
                                    stat.LIFE += max_stat.MAGIC;
                                    stat.MANA--;
                                    turn_counter = MOB_TURNO;
                                    }

                            }
                            break;
                        case 3: //PO��O
                            mons_sel_f( &mons_sel_var, n_mons );
                            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                                batt_anima = 4;
                                battle_timer = 0;
                                play_sample(pot, 255, 128, 1000, FALSE);
                                if(stat.POT > 0 && max_stat.LIFE > stat.LIFE){
                                    stat.LIFE += max_stat.LIFE / 2;
                                    stat.POT--;
                                    turn_counter = MOB_TURNO;
                                }
                            }
                            break;
                        case 4: //FUGIR
                            mons_sel_f( &mons_sel_var, n_mons );
                            if( (anterior_ENTER == 0 && key[KEY_ENTER] != 0) || (anterior_ENTER_PAD == 0 && key[KEY_ENTER_PAD] != 0) ){
                                batt_anima = 5;
                                battle_timer = 0;
                                if(0 == rand() % 5){
                                    battle_f();
                                    }
                                else
                                    turn_counter = MOB_TURNO;
                            }
                            break;

                        }
                    }
                    for( i = 0; i < 3; i++ ){ //verifica se os monstros morreram, caso algum tenha morrido seu verificador � igualado a 0, e os itens dropados s�o recebidos
                        if( bmons[i].LIFE <= 0 ){
                            bmons[i].LIFE = 0;
                            if(verif_mons[i]){
                                verif_mons[i] = 0;
                                drop_system(bmons[i]);
                            }
                        }
                    }
                    if(stat.MANA > max_stat.MANA)
                                stat.MANA = max_stat.MANA;
                    if(stat.LIFE > max_stat.LIFE)
                                stat.LIFE = max_stat.LIFE;
                    def = max_stat.DEF/(max_stat.DEF+25);
                    if(turn_counter == MOB_TURNO && battle_timer > 5){
                        switch(n_mons){
                            case 2:
                                if(verif_mons[2]){
                                    stat.LIFE -= (bmons[2].ATK - rand() % (bmons[2].ATK/2) + rand() % (bmons[2].ATK/4)) - (bmons[2].ATK - rand() % (bmons[2].ATK/2) + rand() % (bmons[2].ATK/3)) * def;
                                }

                            case 1:
                                if(verif_mons[1]){
                                    stat.LIFE -= (bmons[1].ATK -  rand() % (bmons[1].ATK/2) + rand() % (bmons[1].ATK/4)) - (bmons[2].ATK - rand() % (bmons[2].ATK/2) + rand() % (bmons[2].ATK/3)) * def;
                                }
                            case 0:
                                if(verif_mons[0]){
                                    stat.LIFE -= (bmons[0].ATK  - rand() % (bmons[0].ATK/2) + rand() % (bmons[0].ATK/4)) - (bmons[2].ATK - rand() % (bmons[2].ATK/2) + rand() % (bmons[2].ATK/3)) * def;
                                }
                                turn_counter = MEU_TURNO;
                                break;
                        }
                    }
                    verif_lvl();
                    verif_wl_var = verif_win_lose(n_mons, verif_mons);
                    switch(verif_wl_var){
                        case WIN:
                            if(regen){
                                stat.MANA++;
                                stat.LIFE += (n_mons + 1) * 3;
                                stat.EXP += (n_mons + 1) * 3;
                                stat.GOLD += (n_mons + 1) * 3;
                                regen=0;
                            }
                            if(key[KEY_SPACE]){
                                battle_f();
                            }
                            break;
                        case LOSE:
                            if(key[KEY_SPACE]){
                                battle_f();
                                jogo_f();
                                menu_f();
                            break;
                        }
                    }

                    draw_sprite(buffer, battle_m, 0, 0);


                    you_anima(&batt_anima, atk_pic_anima,  matk_pic_anima, cura_pic_anima, pot_pic_anima, flee_pic_anima);
                    printf_you_mobs( n_mons, verif_mons, batt_anima, mob_pic, mob_dead_pic, you, you_dead );
                    printf_battle_status_selection( battle_var);
                    printf_battle_mons_selection( mons_sel_var, bmons, mons, mobs_id, n_mons);
                    printf_win_or_lose(verif_wl_var, n_mons, venceu, perdeu);



     draw_sprite(screen, buffer, 0, 0);
     clear(buffer);

    contador--;
    }
}
    for( i = 0; i < 3; i++ ){
        destroy_bitmap(mob_pic[i]);
        destroy_bitmap(mob_dead_pic[i]);
    }
    for( i = 0; i < 6; i++ ){
        destroy_bitmap(atk_pic_anima[i]);
        destroy_bitmap(matk_pic_anima[i]);
        destroy_bitmap(cura_pic_anima[i]);
        destroy_bitmap(pot_pic_anima[i]);
        destroy_bitmap(flee_pic_anima[i]);
    }
    destroy_bitmap(you);
    destroy_bitmap(you_dead);
    destroy_bitmap(perdeu);
    destroy_bitmap(venceu);
    destroy_bitmap(battle_m);
    destroy_midi(battle_st);
    destroy_sample(sword);
    destroy_sample(matk);
    destroy_sample(heal);
    destroy_sample(pot);
    play_midi(jogo_st,TRUE);

    if(mapa[mapa_id][(pos.y+28)/PIXELS][(pos.x+13)/PIXELS] == BOSS && verif_mons[0] == 0 ){
        mapa[mapa_id][(pos.y+28)/PIXELS][(pos.x+13)/PIXELS] = 2;
    }

}

