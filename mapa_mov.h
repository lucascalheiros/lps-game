#ifndef MAPA_MOV_H
#define MAPA_MOV_H

int** carregar_mapa(char* nome_arquivo);
void desenhar_mapa(BITMAP* parede, BITMAP* grama, BITMAP* arvore, BITMAP* agua, BITMAP* pedra, BITMAP* pedra2, BITMAP* npc, BITMAP* save, BITMAP* stone, BITMAP* stone2, BITMAP* boss, BITMAP* princesa);
int colisao();
void troca_mapa();
void load_maps();
void npc_f(BITMAP* npc_bar, int* counter);

#endif
