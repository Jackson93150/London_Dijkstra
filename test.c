
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 5

struct noeud {
  int n;
  int h;
  float l;
  float surf;
  struct noeud * suc [3];
} ;
typedef struct noeud noeud;
typedef struct noeud * tas;
tas creenoeud (int nb) {
  tas t;
  t = (tas) malloc (sizeof(noeud));
  assert(t);
  t->n = nb;
  t->h = nb + 4;
  t->l = 11.0 - (float) ((t->h) << 1);
  if (t->l < 0)
	t->l *= -1.0;
  t->suc[0] = (tas) 0;
  t->suc[1] = (tas) 0;
  t->suc[2] = (tas) 0;
  t->surf   = 0.0;
  return t;
}
tas creetas () {
  tas t[5];
  int i;
  for (i = 0; i < 5; i++) {
	t[i] = creenoeud (i);
  }
  t[0]->suc[0] = t[4];
  t[0]->suc[1] = (tas) 0;
  t[0]->suc[2] = t[2];
  t[1]->suc[0] = t[0];
  t[1]->suc[2] = (tas) 0;
  t[1]->suc[1] = t[3];
  t[2]->suc[0] = (tas) 0;
  t[2]->suc[1] = (tas) 0;
  t[2]->suc[2] = t[4];
  t[3]->suc[0] = (tas) 0;
  t[3]->suc[1] = t[0];
  t[3]->suc[2] = t[2];
  t[4]->suc[0] = t[2];
  t[4]->suc[1] = t[3];
  t[4]->suc[2] = t[1];
  return t[0];
}
void goaffichetas (tas t, char boo [MAX]) {

  if (!t)
	return;
  if (boo [t->n])
	  return;
  printf(" %d \t %d \t %f \t%f \n", t->n, t->h, t->l, t->surf);
  printf(" %d \t %d",  (int) ((long long int) t % 10000), (int) ((long long int) t->suc[0] % 10000));
  printf(" %d \t %d  \n", (int) ((long long int) t->suc[1] % 10000), (int) ((long long int) t->suc[2] % 10000));
  boo[t->n] = 1;
  goaffichetas(t->suc[0], boo);
  goaffichetas(t->suc[1], boo);
  goaffichetas(t->suc[2], boo);
}
void affichetas (tas t) {
  char boo [MAX];
  int i;
  for (i = 0; i < MAX; i++)
	boo[i] = 0;
  goaffichetas (t, boo);
}
float absf (float x) {
  if (x < 0.0)
	return - x;
  return x;
}
void remplirsurf (tas t) {
  if (! t)
	return;
  if (t->surf != 0.0)
	return;
  t->surf = t->h * t->l;
  remplirsurf (t->suc[0]);
  remplirsurf (t->suc[1]);
  remplirsurf (t->suc[2]);
}


int main () {
  tas t;
  t = creetas ();
  affichetas(t);
  printf("\n\n");
  remplirsurf(t);
  affichetas(t);
}