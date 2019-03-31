#include "game_logic.h"
#include <allegro.h>
#include "variaveis.h"
#include "mapa_mov.h"
#include "aux.h"
#include <stdlib.h>

int jumping;
int jump_step;
int loaded_game_staff = FALSE;
int nmonster=3;
MONSTER monster_array[3];

void gravity(VECTOR* pos) {
    if(!colision(DOWN, *pos)) {
        action_mov(pos, DOWN, GRAVITY);
    }
}
int mcolision_aux(VECTOR mpos) {
    VECTOR atkpos = {mpos.x+10, mpos.x+25};
    if(attack_verif(atkpos,pos, mpos.y+25)){
            return 1;
    }
    atkpos.x =mpos.x+40;
    atkpos.y = mpos.x+25;
    if(attack_verif(atkpos,pos, mpos.y+25)){
            return 1;
    }
    return 0;
}

int monster_colision() {
    for(int i = 0; i <nmonster; i++) {
        if(!monster_array[i].dead) {
            mcolision_aux(monster_array[i].pos);
            VECTOR atkpos = {monster_array[i].pos.x+10, monster_array[i].pos.x+40};
            if(attack_verif(atkpos,pos, monster_array[i].pos.y+25)){
                    return 1;
             }
        }
    }
    return 0;
}

void jump() {
    if(colision(DOWN, pos)) {
        jumping = TRUE;
    }
}

void jump_aux() {
    if(jumping) {
        action_mov(&pos, UP, jump_step);
        jump_step--;
    }
    if(jump_step <= 0) {
        jump_step = 17;
        jumping = FALSE;
    }
}

void phisics() {
    gravity(&pos);
    for(int i=0; i<nmonster;i++){
        gravity(&monster_array[i].pos);
        if(!monster_array[i].dead) {
            if(i==0) {
                int random = rand()%2;
                action_mov(&monster_array[i].pos, random, 2*VEL);
            }
            if(i==1){
                if(pos.x > monster_array[i].pos.x)
                    action_mov(&monster_array[i].pos, RIGHT, VEL/2);
                else
                    action_mov(&monster_array[i].pos, LEFT, VEL/2);
            }   
            if(i==2){
                if(!colision(monster_array[i].dir, monster_array[i].pos))
                    action_mov(&monster_array[i].pos, monster_array[i].dir, VEL);
                else
                    monster_array[i].dir = monster_array[i].dir==RIGHT?LEFT:RIGHT; 
            }
        }
    } 
    jump_aux();
}

int attack_verif(VECTOR atkpos,VECTOR mpos, int y) {
    if(mpos.x < atkpos.x && mpos.x+50 > atkpos.x || mpos.x < atkpos.y && mpos.x+50 > atkpos.y ) {
        if(mpos.y < y+25 && mpos.y+40 > y+25 )
            return 1;
    }
    return 0;
}

void attack(int dir) {
    attacking = TRUE;
    if(dir == RIGHT) {
        for(int i = 0; i <nmonster; i++) {
            if(!monster_array[i].dead) {
                VECTOR atkpos = {pos.x+75, pos.x+25};
                if(attack_verif(atkpos, monster_array[i].pos, pos.y) == 1) {
                    monster_array[i].dead = 1;
                }
            }
        }
    }
    if(dir == LEFT) {
        for(int i = 0; i <nmonster; i++) {
            if(!monster_array[i].dead) {
                VECTOR atkpos = {pos.x+25-50, pos.x+25};
                if(attack_verif(atkpos, monster_array[i].pos, pos.y) == 1) {
                    monster_array[i].dead = 1;
                }
            }
        }

    }

}

void action() {
    phisics();
    poll_keyboard();
    if(key[KEY_UP]) {
        jump();
        // batalha();
    }
    if(key[KEY_DOWN]) {
        action_mov(&pos, DOWN, VEL);
        // batalha();
    }
    if(key[KEY_LEFT]) {
        action_mov(&pos, LEFT, VEL);
        dir = LEFT;
        // batalha();
    }
    if(key[KEY_RIGHT]) {
        action_mov(&pos, RIGHT, VEL);
        dir = RIGHT;
        // batalha();
    }
    if(key[KEY_SPACE]) {
        attack(dir);
    }
}

void init_game() {
    monster_array[0].pos.x=100;
    monster_array[0].pos.y=200;
    monster_array[0].pic[0]=resize(load_bitmap("img/goblin.bmp",NULL), PIXELS, PIXELS);
    monster_array[0].pic[1]=resize(load_bitmap("img/goblin_dead.bmp",NULL), PIXELS, PIXELS);
    monster_array[0].dir=0;
    monster_array[0].dead=0;
    monster_array[1].pos.x=300;
    monster_array[1].pos.y=200;
    monster_array[1].pic[0]=resize(load_bitmap("img/orc.bmp",NULL), PIXELS, PIXELS);
    monster_array[1].pic[1]=resize(load_bitmap("img/orc_dead.bmp",NULL), PIXELS, PIXELS);
    monster_array[1].dir=0;
    monster_array[1].dead=0;
    monster_array[2].pos.x=500;
    monster_array[2].pos.y=200;
    monster_array[2].pic[0]=resize(load_bitmap("img/elf.bmp",NULL), PIXELS, PIXELS);
    monster_array[2].pic[1]=resize(load_bitmap("img/elf_dead.bmp",NULL), PIXELS, PIXELS);
    monster_array[2].dir=0;
    monster_array[2].dead=0;

}
void game() {
    if(!loaded_game_staff){
        init_game();
        loaded_game_staff = TRUE;
    }
    if(monster_colision()){
        dead=1;
    }

}
void draw_monsters(){
    for(int i=0; i<nmonster;i++){
        draw_sprite(buffer, monster_array[i].pic[monster_array[i].dead], monster_array[i].pos.x, monster_array[i].pos.y);
    }
}
