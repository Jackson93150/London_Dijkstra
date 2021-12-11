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
  int pere;
  ptnoeud2 pt;
  int poids;
  struct aretes * suiv;
} ;
typedef struct aretes aretes;
typedef struct aretes * ptarete;

ptarete allarete [MAX];

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
legraphe2 line2[303];
int poids[303];

void stockcsv2() // stockage des donnes des ficher csv
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

void stockcsv() // la meme mais sur un autre fichier
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
ptarete creerarrete(int x , int suc,int z){ // creation de l'arrete pour les list 
  ptarete t;
  t = (ptarete)malloc(sizeof(noeud2));
  assert(t);
  if(z < suc){
    t->pere = x;
    t->pt = (ptnoeud2)0;
    int p = atol(values[position[x - 1][z]].time);
    t->poids = p;
    t->suiv = creerarrete(x,suc,z+1);
  }
  return t;
}

ptnoeud2 creenoeud2(int x){ // creation du node pour les list
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

ptnoeud2 creeptnoeud2(){ // creaation de tous les nodes des liste
  int i ;
  for (i = 0; i < 303; i++){
    t2[i] = creenoeud2(i+1);
  }
  for(i = 0; i < 303;i++){
    ptarete a = t2[i]->next;
    for(int j = 0 ; j < t2[i]->nbs ; j++){
      int p = position[i][j];
      a->pt = t2[p];
      a = a->suiv;
    }
  }
}

ptnoeud creenoeud(int x) // creation du node pour les vec
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
ptnoeud creeptnoeud() // creation de tous les nodes pour les vec
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

int minPoids(){ // recherche du poid minimum
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

int minPoids2(){ // recherche du poid minimum pour les list
  int temp = MAX;
  int mini = -1;
  for (int i = 0; i < 303; i++){
    if (poids[i] <= temp){
      if (line2[i]->vu == 0){
        if (poids[i] != -1){
          mini = i;
          temp = poids[i];
        }
      }
    }
  }
  return mini;
}

void reverse(int arr[], int n) // fonction pour reverse un vec
{
    int aux[n];
 
    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }
 
    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}

void Dijkstra2(int Depart, int Destination){// Dijkstra pour les list
  creeptnoeud2();
  for (int i = 0; i < 303; i++){ // on stock tous les node creer dans le vecteur de node
    line2[i]->vu = 0;
    line2[i]->ne = t2[i];
  }
  int distance = 0;
  int antecedent[303];
  int minline = -1;
  int nb;
  int pds;
  int compteur = 0;
  int chemin[100];
  int poidf = Destination;
  for (int i = 0; i < 303; i++){ // initialistion des poids a -1 sauf pour le poids de depart 
    poids[i] = -1;
    if (i == Depart-1){
      poids[i] = 0;
    }
  }
  while(minline != Destination-1){
    minline = minPoids2(); // on prend l'id du poids min 
    ptarete n = line2[minline]->ne->next;
    for(int i = 0 ; i < line2[minline]->ne->nbs ;i++){ // on parcour tous les succ de ce node 
      nb = n->pt->num;
      pds = poids[minline]+n->poids;
        if(poids[nb-1] > pds){ // si le parcours et moins lourd en poids en remplace et le node devient l'antecedent
          poids[nb-1] = pds;
          antecedent[nb-1] = line2[minline]->ne->num;
        }
        if(poids[nb-1] <= 0){ // si il n'a pas encore ete parcouru le node devient l'antecedent et il prend le poids du trajet
          poids[nb-1] = pds;
          antecedent[nb-1] = line2[minline]->ne->num;
        }
      n = n->suiv;
    }
    line2[minline]->vu = 1;
    distance++;
    if(distance == 500){ // si il y'a un probleme pour ne pas qu'il boucle à l'inifini
      minline = Destination-1;
    }
  }
  while(Destination != Depart){ // recherche du chemin en prenant les antecedant et on va stocker dans un vec
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
  reverse(chemin,compteur); // on rever le vec pour pouvoir print le chemin
  for(int j = 0; j < compteur;j++){
    printf("%s -> ",NomStation[chemin[j]-1].st4);
  }
  printf("Temps estimé : %d minutes \n",poids[poidf-1]);
}

void Dijkstra(int Depart, int Destination){ // meme principe qu'en haut mais pour les vec
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
}

void lancer_recherche(){
  stockcsv();
  stockcsv2();
  int Dijk;
  int a;
  int b;
  int replay;
  printf("Tapez 1 pour utilisez les 'vecteurs' et tapez 2 pour les 'listes'\n");
  scanf("%d",&Dijk);
  while(Dijk < 1 || Dijk > 2){
    printf("Tapez 1 pour utilisez les 'vecteurs' et tapez 2 pour les 'listes'\n");
    scanf("%d",&Dijk);
  }
  printf("Veuillez entrez l'ID de la station de Depart (Vous pouvez regardez le fichier london.lines pour voir la liste des stations)\n");
  scanf("%d",&a);
  while (a<0 || a>303){
    printf("Choissisez une valeur entre 1 et 302 s'il vous plait\n");
    scanf("%d",&a);
  }
  printf("Veuillez entrez l'ID de la station de d'Arrivée \n");
  scanf("%d",&b);
  while (b<0 || b>303){
    printf("Choissisez une valeur entre 1 et 302 s'il vous plait\n");
    scanf("%d",&b);
  }
  if(Dijk == 1){
    Dijkstra(a,b);
  }
  if(Dijk == 2){
    Dijkstra2(a,b);
  }
  printf("Voulez vous voir un autre trajet ?(1 : Oui / 2 : Non)\n");
  scanf("%d",&replay);
  while(replay < 1 || replay > 2){
    printf("Je n'ai pas compris Tapez 1 ou 2 \n");
    scanf("%d",&replay);
  }
  if(replay == 1){
    lancer_recherche();
  }
  if(replay == 2){
    exit;
  }
}


int main(){
  lancer_recherche();
  return 0;
}
