 #ifndef BATTLE_H
 #define BATTLE_H

void update_max_stat();
void verif_lvl();
void mons_sel_f(int* mons_sel_var, int n_mons);
int verif_win_lose(int n_mons, int verif_mons[]);
void drop_system(MONSTRO bmons);
void printf_battle_mons_selection( int mons_sel_var, MONSTRO bmons[], MONSTRO mons[], int mobs[], int n_mons );
void printf_battle_status_selection( int battle_var);
void printf_you_mobs( int n_mons, int verif_mons[], int batt_anima, BITMAP* mob_pic[], BITMAP* mob_dead_pic[], BITMAP* you, BITMAP* you_dead);
void printf_win_or_lose(int verif_wl_var, int n_mons, BITMAP* venceu, BITMAP* perdeu);
void you_anima(int* batt_anima, BITMAP* atk_pic_anima[], BITMAP* matk_pic_anima[], BITMAP* cura_pic_anima[], BITMAP* pot_pic_anima[], BITMAP* flee_pic_anima[]);
void battle_run();

#endif



