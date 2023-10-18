//Gabriela Saori Miyasaka      RA: 2475448

#ifndef BST_H
#define BST_H


typedef struct node * link;
struct node {
  link l;
  link r;
  int item;
  int N;      // quantidade de nos na subarvore
  int id;     // id da nó
  int height;      //altura
};

typedef struct tree {
  link head; // raiz
  link z;    // nó externo
} * Tree;

Tree createTree();


int maior(int a, int b);

int alturaDoNo(Tree t, link h);

int fatorDeBalanceamento(Tree t, link h);

link rotR (Tree t, link h);

link rotL (Tree t, link h);

link search (Tree h, int query);

link AVLinsert(Tree t, int item);

void imprimeEmOrdem (Tree t, link h);
void imprimePosOrdem (Tree t, link h);
void imprimePreOrdem (Tree t, link h, int k);


void imprime(Tree a, char *s);
 
#endif 
