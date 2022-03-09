#define pai(i) (((i)-1)/2)
#define esq(i) (2*(i)+1)
#define dir(i) (2*(i)+2)

#include<stdlib.h>
#include<stdio.h>

//atividades (heap simples)
typedef struct{
    int n;
    int nmax;
    int *v;
} heap;

heap* criar(int nmax);

void heap_insere(heap *h, int valor);

int heap_retira (heap *h);

void sobe(heap *h, int i);

void troca(heap *h, int i, int j);

void desce (heap *h, int i);


//categorias (union and find)
typedef struct{
	int n;
	int * v; 
} UniaoBusca;

UniaoBusca* ub_cria (int n);
void ub_libera ( UniaoBusca* ub);
int ub_busca ( UniaoBusca* ub, int x);
int ub_uniao ( UniaoBusca* ub, int x, int y);

void menu();

