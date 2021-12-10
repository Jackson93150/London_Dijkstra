#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#define MAX 1500
#define MAXSUC 1000

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

ptnoeud creeptnoeud(int x)
{
  ptnoeud t[303];
  int i;
  for (i = 1; i < 303; i++){
    t[i - 1] = creenoeud(i);
  }
  for (i = 1; i < 303; i++){
    if (t[i - 1]->nbs != 0){
      for (int j = 0; j <= t[i - 1]->nbs; j++){
        int tmp = position[i - 1][j];
        t[i - 1]->succ[j] = t[tmp];
      }
    }
  }
  return t[x];
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
  for (int i = 1; i < 303; i++){
    line[i - 1]->vu = 0;
    line[i - 1]->ne = creeptnoeud(i - 1);
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
  Dijkstra(164,82);
  return 0;
}
