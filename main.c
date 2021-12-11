#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#define MAX 1500
#define MAXSUC 100

//vecteur de succeseur
struct noeud
{
  int num;
  int nbs;
  int poids[MAXSUC];
  struct noeud *succ[MAXSUC];
};

typedef struct noeud noeud;
typedef struct noeud *ptnoeud;

struct lesnoeuds
{
  int vu;
  ptnoeud ne;
};
typedef struct lesnoeuds legraphe[MAX];

// liste de succeseur

struct noeud2 {
  int num;
  int nbs;
  struct aretes * next;
};
typedef struct noeud2 noeud2;
typedef struct noeud2 * ptnoeud2;

struct lesnoeuds2 {
  int vu;
  ptnoeud2 ne;
};
typedef struct lesnoeuds2 legraphe2 [MAX];

struct aretes {
  ptnoeud2 pt;
  int poids;
  struct aretes * suiv;
} ;
typedef struct aretes aretes;
typedef struct aretes * ptarete;

struct csv
{
  char st1[MAX];
  char st2[MAX];
  char line[MAX];
  char time[MAX];
};
typedef struct csv dict;
dict values[MAX];

struct csv2
{
  char st1[MAX];
  char st2[MAX];
  char st3[MAX];
  char st4[MAX];
  char st5[MAX];
  char st6[MAX];
  char st7[MAX];
  char st8[MAX];
};
typedef struct csv2 dict2;
dict2 NomStation[303];

int position[303][MAXSUC];
legraphe line[303];
int poids[303];

void stockcsv2()
{
  FILE *fp = fopen("stations.csv", "r");
  if (!fp)
  {
    printf("Error");
  }
  char buff[303];
  int row = 0;
  int field_count = 0;
  int i = 0;
  while (fgets(buff, 303, fp))
  {
    field_count = 0;
    row++;
    if (row == 1)
    {
      continue;
    }
    char *field = strtok(buff, ",");
    while (field)
    {
      if (field_count == 0)
      {
        strcpy(NomStation[i].st1, field);
      }
      if (field_count == 1)
      {
        strcpy(NomStation[i].st2, field);
      }
      if (field_count == 2)
      {
        strcpy(NomStation[i].st3, field);
      }
      if (field_count == 3)
      {
        strcpy(NomStation[i].st4, field);
      }
      if (field_count == 4)
      {
        strcpy(NomStation[i].st5, field);
      }
      if (field_count == 5)
      {
        strcpy(NomStation[i].st6, field);
      }
      if (field_count == 6)
      {
        strcpy(NomStation[i].st7, field);
      }
      if (field_count == 7)
      {
        strcpy(NomStation[i].st8, field);
      }
      field = strtok(NULL, ",");
      field_count++;
    }
    i++;
  }
  fclose(fp);
}

void stockcsv()
{
  FILE *fp = fopen("london.connections.csv", "r");
  if (!fp)
  {
    printf("Error");
  }
  char buff[407];
  int row = 0;
  int field_count = 0;

  int i = 0;
  while (fgets(buff, 407, fp))
  {
    field_count = 0;
    row++;
    if (row == 1)
    {
      continue;
    }
    char *field = strtok(buff, ",");
    while (field)
    {
      if (field_count == 0)
      {
        strcpy(values[i].st1, field);
      }
      if (field_count == 1)
      {
        strcpy(values[i].st2, field);
      }
      if (field_count == 2)
      {
        strcpy(values[i].line, field);
      }
      if (field_count == 3)
      {
        strcpy(values[i].time, field);
      }
      field = strtok(NULL, ",");
      field_count++;
    }
    i++;
  }
  fclose(fp);
}

ptnoeud2 t2[303];
ptarete creerarrete(int x , int suc,int z){
  ptarete t;
  t = (ptarete)malloc(sizeof(noeud2));
  assert(t);
  if(z < suc){
    t->pt = (ptnoeud2)0;
    int p = atol(values[position[x - 1][z]].time);
    t->poids = p;
    t->suiv = creerarrete(x,suc,z+1);
  }
  return t;
}

ptnoeud2 creenoeud2(int x){
  ptnoeud2 t;
  t = (ptnoeud2)malloc(sizeof(noeud2));
  assert(t);
  t->num = x;
  int suc = 0;
  for (int i = 0; i < 407; i++)
  {
    if (x == atol(values[i].st1))
    {
      int tmp = atol(values[i].st2);
      position[x - 1][suc] = tmp - 1;
      suc++;
    }
    if (x == atol(values[i].st2))
    {
      int tmp = atol(values[i].st1);
      position[x - 1][suc] = tmp - 1;
      suc++;
    }
  }
  t->nbs = suc;
  t->next = creerarrete(x,suc,0);
  return t;
}

ptnoeud2 creeptnoeud2(){
  int i ;
  for (i = 0; i < 303; i++){
    t2[i] = creenoeud2(i+1);
  }
  for (i = 0; i < 303; i++){
    if (t2[i]->nbs != 0){
    }
  }
}

ptnoeud creenoeud(int x)
{
  ptnoeud t;
  int suc = 0;
  t = (ptnoeud)malloc(sizeof(noeud));
  assert(t);
  t->num = x;
  for (int i = 0; i < 407; i++)
  {
    if (x == atol(values[i].st1))
    {
      int tmp = atol(values[i].st2);
      position[x - 1][suc] = tmp - 1;
      suc++;
    }
    if (x == atol(values[i].st2))
    {
      int tmp = atol(values[i].st1);
      position[x - 1][suc] = tmp - 1;
      suc++;
    }
  }
  t->nbs = suc;
  if (suc != 0)
  {
    for (int i = 0; i <= suc; i++)
    {
      t->succ[i] = (ptnoeud)0;
      int p = atol(values[position[x - 1][i]].time);
      t->poids[i] = p;
    }
  }
  if (suc == 0)
  {
    t->succ[0] = (ptnoeud)0;
    t->poids[0] = 0;
  }
  return t;
}

ptnoeud t[303];
ptnoeud creeptnoeud()
{
  int i;
  for (i = 0; i < 303; i++){
    t[i] = creenoeud(i+1);
  }
  for (i = 0; i < 303; i++){
    if (t[i]->nbs != 0){
      for (int j = 0; j <= t[i]->nbs; j++){
        int tmp = position[i][j];
        t[i]->succ[j] = t[tmp];
      }
    }
  }
}

int minPoids(){
  int temp = MAX;
  int mini = -1;
  for (int i = 0; i < 303; i++){
    if (poids[i] <= temp){
      if (line[i]->vu == 0){
        if (poids[i] != -1){
          mini = i;
          temp = poids[i];
        }
      }
    }
  }
  return mini;
}

void reverse(int arr[], int n)
{
    int aux[n];
 
    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }
 
    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}

void Dijkstra(int Depart, int Destination){
  creeptnoeud();
  for (int i = 0; i < 303; i++){
    line[i]->vu = 0;
    line[i]->ne = t[i];
  }
  int distance = 0;
  int antecedent[303];
  int minline = -1;
  int nb;
  int pds;
  int compteur = 0;
  int chemin[100];
  int poidf = Destination;
  for (int i = 0; i < 303; i++){
    poids[i] = -1;
    if (i == Depart-1){
      poids[i] = 0;
    }
  }
  while(minline != Destination-1){
    minline = minPoids();
    //printf("%d,%d,%d\n",line[minline]->ne->num,line[minline]->ne->nbs,poids[minline]);
    for(int i = 0 ; i < line[minline]->ne->nbs ;i++){
      nb = line[minline]->ne->succ[i]->num;
      pds = poids[minline]+*line[minline]->ne->succ[i]->poids;
      if(poids[nb-1] >= pds){
        poids[nb-1] = pds;
        antecedent[nb-1] = line[minline]->ne->num;
      }
      if(poids[nb-1] <= 0){
        poids[nb-1] = pds;
        antecedent[nb-1] = line[minline]->ne->num;
      }
    }
    line[minline]->vu = 1;
    distance++;
    if(distance == 500){
      minline = Destination-1;
    }
  }
  while(Destination != Depart){
    if(compteur == 0){
        chemin[compteur] = Destination;
        compteur++;
    }
    else{
        chemin[compteur] = antecedent[Destination-1];
        Destination = antecedent[Destination-1];
        compteur++;
    }
  }
  chemin[compteur] = antecedent[Destination-1];
  reverse(chemin,compteur);
  for(int j = 0; j < compteur;j++){
    printf("%s -> ",NomStation[chemin[j]-1].st4);
  }
  printf("Temps estimé : %d minutes \n",poids[poidf-1]);
  //printf("%s",NomStation[0]);
}


int main(){
  stockcsv();
  stockcsv2();
  Dijkstra(12,23);
  creeptnoeud2();
  printf("%d",t2[10]->next->pt->num);
  return 0;
}
