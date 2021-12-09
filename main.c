#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#define MAX 1000
#define MAXSUC 20

struct noeud {
  int num;
  int nbs;
  int poids[MAXSUC];
  struct noeud * succ[MAXSUC];
};

typedef struct noeud noeud;
typedef struct noeud * ptnoeud;

struct lesnoeuds {
  int vu;
  ptnoeud ne;
};
typedef struct lesnoeuds legraphe [MAX];

struct csv{
  char st1[MAX];
  char st2[MAX];
  char line[MAX];
  char time[MAX];
};
typedef struct csv dict;
dict values[MAX];

int position[303][MAXSUC];

void stockcsv(){
  FILE *fp = fopen("london.connections.csv", "r");
  if(!fp){
    printf("Error");
  }
  char buff[407];
  int row = 0;
  int field_count = 0;

  int i =0;
  while(fgets(buff,407,fp)){
    field_count = 0;
    row++;
    if(row == 1){
      continue;
    }
    char *field = strtok(buff, ",");
    while(field){
      if(field_count == 0){
        strcpy(values[i].st1,field);
      }
      if(field_count == 1){
        strcpy(values[i].st2,field);
      }
      if(field_count == 2){
        strcpy(values[i].line,field);
      }
      if(field_count == 3){
        strcpy(values[i].time,field);
      }
      field = strtok(NULL, ",");
      field_count++;
    }
    i++;
  }
  fclose(fp);
}

ptnoeud creenoeud (int x) {
  ptnoeud t;
  int suc = 0;
  t = (ptnoeud) malloc (sizeof(noeud));
  assert(t);
  t->num = x;
  for(int i = 0 ; i < 407;i++){
    if(x == atol(values[i].st1)){
      int tmp = atol(values[i].st2);
      position[x-1][suc] = tmp-1;
      suc++;
    }
  }
  if(suc == 0){
    for(int i = 0 ; i < 407;i++){
      if(x == atol(values[i].st2)){
        int tmp = atol(values[i].st1);
        position[x-1][suc] = tmp-1;
        suc++;
      }
    }
  }
  t->nbs = suc;
  if(suc != 0){
    for(int i = 0; i <= suc ; i++){
      t->succ[i] = (ptnoeud)0;
      int p = atol(values[position[x-1][i]].time);
      t->poids[i] = p;
    }
  }
  if(suc == 0){
    t->succ[0] = (ptnoeud)0;
    t->poids[0] = 0;
  }
  return t;
}

ptnoeud creeptnoeud (int x) {
  ptnoeud t[303];
  int i;
  for (i = 1; i < 303; i++) {
	  t[i-1] = creenoeud(i);
  }
  for(i = 1; i < 303; i++) {
    if(t[i-1]->nbs != 0){
      for(int j = 0 ; j <= t[i-1]->nbs;j++){
        int tmp = position[i-1][j];
        t[i-1]->succ[j] = t[tmp];
      }
    }
  }
  return t[x];
}

int main(){
  stockcsv();
  ptnoeud x;
  x = creeptnoeud(10);
  legraphe z[303];
  for(int i = 1 ; i < 303 ; i++){
    z[i-1]->vu = 0;
    z[i-1]->ne = creeptnoeud(i-1);
  }
  printf("%d\n",z[301]->ne->succ[0]->num);
  return 0;
}
