#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#define MAX 1000
#define MAXSUC 20

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

int position[303][MAXSUC];
legraphe line[303];
int poids[303];

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
  }
  if (suc == 0)
  {
    for (int i = 0; i < 407; i++)
    {
      if (x == atol(values[i].st2))
      {
        int tmp = atol(values[i].st1);
        position[x - 1][suc] = tmp - 1;
        suc++;
      }
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
      if (line[i]->vu !=1){
        if (poids[i] != -1){
          mini = i;
          temp = poids[i];
        }
      }
    }
  }
  if(mini == 250){
      for(int i = 0 ; i < 303;i++){
          if(line[i]->vu !=1){
             // printf("%d\n",poids[i]);
          }
      }
  }
  return mini;
}

void Dijkstra(int Depart, int Destination){
  for (int i = 1; i < 303; i++){
    line[i - 1]->vu = 0;
    line[i - 1]->ne = creeptnoeud(i - 1);
  }
  int distance = 0;
  int antecedent[303];
  int minline = -1;
  for (int i = 0; i < 303; i++){
    poids[i] = -1;
    if (i == Depart-1){
      poids[i] = 0;
    }
  }
  while(minline != Destination-1){
    minline = minPoids();
   // printf("%d\n",line[minline]->ne->num);
    for(int i = 0 ; i < line[minline]->ne->nbs ;i++){
      int nb = line[minline]->ne->succ[i]->num;
      int pds = poids[minline]+*line[minline]->ne->succ[i]->poids;
      if(line[nb-1]->vu == 0){
        if(poids[nb-1] > pds || poids[nb-1] <= 0 ){
          poids[nb-1] = pds;
          antecedent[nb-1] = line[minline]->ne->num;
        }
      }
    }
    line[minline]->vu = 1;
    distance++;
    if(distance == 303){
      minline = Destination-1;
    }
  }
}

int main()
{
  stockcsv();
  Dijkstra(255,196);
  return 0;
}
