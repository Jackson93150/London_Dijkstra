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

int NodeVec[MAX];

struct csv{
  char st1[MAX];
  char st2[MAX];
  char line[MAX];
  char time[MAX];
};
typedef struct csv dict;
dict values[MAX];

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
  int position[MAXSUC];
  t = (ptnoeud) malloc (sizeof(noeud));
  assert(t);
  t->num = x;
  for(int i = 0 ; i < 407;i++){
    if(x == atol(values[i].st1)){
      position[suc] = i;
      suc++;
    }
  }
  t->nbs = suc;
  if(suc != 0){
    for(int i = 0; i <= suc ; i++){
      t->succ[i] = (ptnoeud)0;
      int p = atol(values[position[i]].time);
      t->poids[i] = p;
    }
  }
  if(suc == 0){
    t->succ[0] = (ptnoeud)0;
    t->poids[0] = 0;
  }
  return t;
}

ptnoeud creeptnoeud () {
  ptnoeud t[303];
  int i;
  for (i = 1; i < 303; i++) {
	  t[i-1] = creenoeud(i);
  }
  return t[0];
}

int main(){
  stockcsv();
  ptnoeud x;
  x = creeptnoeud();
  printf("%d\n",x->poids[0]);
  return 0;
}
