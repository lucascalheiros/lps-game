#include <stdio.h>

main(){
int matriz[24][32];
int i, j, a;
int valor, valor_troca;
char str[20];
  char *list_mapas[] = {
        "vila.txt",
        "floresta.txt",
        "floresta2.txt",
        "floresta3.txt",
        "castelo.txt",
        "castelo2.txt"
    };
while(1){
scanf("%d",&valor);
scanf(" %d",&valor_troca);

for(a=0;a<6;a++){


FILE* f = fopen(list_mapas[a], "r");

   if(f != NULL)
   {


     for(i = 0; i < 24; i++)
     {
        for(j = 0; j < 32; j++)
        {
          fscanf(f, "%d", &matriz[i][j]);
        }
     }

     fclose(f);
   }
     for(i = 0; i < 24; i++)
     {
        for(j = 0; j < 32; j++)
        {
          if(matriz[i][j] == valor)
            matriz[i][j] = valor_troca;
        }
     }

    f = fopen(list_mapas[a], "w");

   if(f != NULL)
   {


     for(i = 0; i < 24; i++)
     {
        for(j = 0; j < 32; j++)
        {
          fprintf(f, "%d ", matriz[i][j]);
        }
                 fprintf(f, "\n");

     }

     fclose(f);
   }
}
}
}
