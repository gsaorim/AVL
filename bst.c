//Gabriela Saori Miyasaka      RA: 2475448

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int id = 0;
link novoNo (int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->N = 1;
  t->id = id++;
  t->height = 1;    //altura de um novo nó é 1 inicialmente
  return t;
}
Tree createTree(){
  Tree t = malloc (sizeof (struct tree));
  t->z = malloc (sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->N = 0;
  t->z->r = t->z;
  return t;
}

/* Retorna o maior dentre dois valores
   a, b -> altura de dois nós da arvore
*/

int maior(int a, int b){
	return(a > b)? a: b;    //Se o teste for vdd, return a, se n, return b
}

//Retorna a altura de um nó ou 0 caso ele seja NULL

int alturaDoNo(Tree t, link h){
	if (h == t->z) {
        return 0;
    }
    return h->height;
}

//Calcule e retorna o fator de balanceamento de um nó

int fatorDeBalanceamento(Tree t, link h){
	if (h == t->z) {
        return 0;
    }
    return alturaDoNo(t, h->l) - alturaDoNo(t, h->r);
}

link rotR (Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  
  // Atualiza as alturas após a rotação
  h->height = maior(alturaDoNo(t, h->l), alturaDoNo(t, h->r)) + 1;  //funcao vai devolver a maior altura e + 1
  x->height = maior(alturaDoNo(t, x->l), alturaDoNo(t, x->r)) + 1;
  
  // Atualiza as quantidades de nós
  h->N = 1 + h->l->N + h->r->N;
  x->N = 1 + x->l->N + x->r->N;
  
  return x;
}

link rotL (Tree t, link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  
  // Atualiza as alturas após a rotação
  h->height = maior(alturaDoNo(t, h->l), alturaDoNo(t, h->r)) + 1;  //funcao vai devolver a maior altura e + 1
  x->height = maior(alturaDoNo(t, x->l), alturaDoNo(t, x->r)) + 1;
  
  // Atualiza as quantidades de nós
  h->N = 1 + h->l->N + h->r->N;
  x->N = 1 + x->l->N + x->r->N;
  
  return x;
}

// Função para inserção AVL recursiva
//Mudança do nome insert para AVLinsertR

link AVLinsertR(Tree t, link h, int item) {
    if (h == t->z) {
        return novoNo(item, t->z, t->z);
    }

    if (item < h->item) {
        h->l = AVLinsertR(t, h->l, item);
    } else if (item > h->item) {
        h->r = AVLinsertR(t, h->r, item);
    } else {
        // Se o item já existe, não faz nada
        return h;
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    h->height = 1 + maior(alturaDoNo(t, h->l), alturaDoNo(t, h->r));

    // Atualiza a quantidade de nós
    h->N = 1 + h->l->N + h->r->N;

    // Calcula o fator de balanceamento
    int balance = fatorDeBalanceamento(t, h);

    // Realiza as rotações para manter o equilíbrio
    
        // Caso de rotação à direita
    if (balance > 1 && item < h->l->item) {
        return rotR(t, h);
    }   // Caso de rotação à esquerda
    if (balance < -1 && item > h->r->item) {
        return rotL(t, h);
    }  // Caso de rotação à esquerda-direita
    if (balance > 1 && item > h->l->item) {
        h->l = rotL(t, h->l);
        return rotR(t, h);
    }  // Caso de rotação à direita-esquerda
    if (balance < -1 && item < h->r->item) {
        h->r = rotR(t, h->r);
        return rotL(t, h);
    }

    // Se não houve necessidade de rotações, retorne o nó atualizado
    return h;
}

// Função pública para inserção na árvore AVL

link AVLinsert(Tree t, int item) {
    t->head = AVLinsertR(t, t->head, item);
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if(h->item == query) 
    return h;
  if (h->item >= query) 
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
} 


link search (Tree t, int query){
   return searchR(t, t->head, query);
}

void imprimeEmOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimeEmOrdem (t, h->l);
  printf("<chave: %d N: %d>", h->item, h->N); 
  imprimeEmOrdem (t, h->r);
}

void imprimePosOrdem (Tree t, link h){
  if(h == t->z) return;
  imprimePosOrdem (t, h->l);
  imprimePosOrdem (t, h->r);
  printf("<chave: %d N: %d>", h->item, h->N); 
}
void imprimePreOrdem (Tree t, link h, int k) {
  if(h == t->z) return;
  for(int i = 0; i <= k; i++)
    printf (" . ");
  printf("<chave: %d N: %d>\n", h->item, h->N); 
  imprimePreOrdem (t, h->l, k + 1); 
  imprimePreOrdem (t, h->r, k + 1);
}


void printnode (char  *x, int h) {
    int i;
    for(i = 0; i < h; i++)
        printf("\t");
    printf("%s\n", x);
}
int c = 0;
void imprimeR(Tree a, link t){
    char s[255];
    if(t==a->z) { return;}
    imprimeR(a,t->r);
    printf ("%d [ label = \"<f0>| <f1> %d (%d) | <f2>\" ]\n", t->id, t->item, t->N);
    if(t->l != a->z){
        printf("%d:f0->%d:f1;\n", t->id, t->l->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f0->z%d;\n", t->id, c);
        c++;
    }
    if(t->r != a->z){
        printf("%d:f2->%d:f1;\n", t->id, t->r->id);
    } else {
        printf("z%d [ shape=point ];\n", c);
        printf("%d:f2->z%d;\n", t->id, c );
        c++;
    }
    imprimeR(a,t->l);
}
void imprime(Tree a, char *s) {
    c = 0;
    printf("digraph %s {\n", s);
    printf ("node [shape=record,style=rounded, height=.1]\n");
    imprimeR(a, a->head);
    printf("}\n");
}
void imprimeFromNode(Tree a, link h, char *s) {
  c = 0;
  printf("digraph  {\n" );
  printf ("name [label = \"%s\",shape=plaintext]\n", s);
  printf ("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, h);
  printf("}\n");
}





