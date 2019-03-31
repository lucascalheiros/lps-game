#include "save_load.h"
#include "variaveis.h"
 #include <stdio.h>

void save_game() {
    FILE *save;
    save = fopen("save/save.dat", "wb");
    fprintf(save, "%d %d %d %d %d %d %d %d %d", pos.x, pos.y, mapa_id, stat.LIFE, stat.MANA, stat.POT, stat.EXP, max_stat.LVL, stat.GOLD );
    fclose(save);
}

void load_game() {
    FILE *save;
    save = fopen("save/save.dat", "rb");
    fscanf(save, "%d %d %d %d %d %d %d %d %d", &pos.x, &pos.y, &mapa_id, &stat.LIFE, &stat.MANA, &stat.POT, &stat.EXP, &max_stat.LVL, &stat.GOLD );
    fclose(save);
}
