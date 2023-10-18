//Gabriela Saori Miyasaka      RA: 2475448

#include <stdio.h>
#include "bst.h"

int main(int argc, char **argv) {
    Tree t = createTree();
    link x;
    AVLinsert(t, 99);
    imprime(t, "oi");
    AVLinsert(t, 88);
    imprime(t, "oi");
    AVLinsert(t, 77);
    imprime(t, "oi");


    return 0;
}
