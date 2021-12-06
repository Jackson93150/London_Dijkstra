#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 1000

struct noeud {
  int num;
  int nbs;
  struct noeud * * succ;
  int * poids;
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
  t = (ptnoeud) malloc (sizeof(noeud));
  assert(t);
  int n = atol(values[x].st1);
  t->num = n;
  while(values[x].st1 == values[x+1].st1){
    x++;
  }
  if(x != 0){
    for(int i = 0; i <= x ; i++){
      int snb = atol(values[x+i].st2);
      t->succ[i] = (ptnoeud)snb;
    }
    int p = atol(values[x].time);
    t->poids = &p;
  }
  t->nbs = x;
  return t;
}

int main(){
  stockcsv();
  ptnoeud t[1];
  t[0] = creenoeud(0);
  printf("%d\n",t[0]->num);
  return 0;
}
