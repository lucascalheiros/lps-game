#include "aux.h"
#include "variaveis.h"

BITMAP* resize(BITMAP* a, int height, int weight) {
    BITMAP* b = create_bitmap(height,weight);
    stretch_blit(a, b, 0, 0, a->w, a->h, 0, 0, b->w, b->h);
    return b;
}


int anima(BITMAP* frames[], int nframes, VECTOR pos) {
    anima_timer=anima_timer>5?0:anima_timer;
    draw_sprite(buffer, frames[anima_timer], pos.x, pos.y);
    if(anima_timer==5)
        return 1;
    else
        return 0;
}