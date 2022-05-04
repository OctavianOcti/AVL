#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <time.h>
#define NR 10
int v[NR];

typedef struct nod {
    int cheie;
    struct nod* stanga;
    struct nod* dreapta;
    int inaltime;
    int nr;
} nod;

int maxim(int a, int b)
{
    if (a > b) return a;
    return b;
}
int height(nod* node)
{
    if (node == NULL) return 0;
    return node->inaltime;
}

nod* initializare(int cheie)
{
    nod* node = (nod*)malloc(sizeof(nod));
    node->cheie = cheie;
    node->stanga = NULL;
    node->dreapta = NULL;
    node->inaltime = 1;
    node->nr = 1;
    return node;

}

nod* rightRotate(nod* b)
{
    nod* a = b->stanga;
    nod* aux = a->dreapta;
    //rotatie
    a->dreapta = b;
    b->stanga = aux;
    //actualizam inaltimile
    b->inaltime = maxim(height(b->stanga), height(b->dreapta)) + 1;
    a->inaltime = maxim(height(a->stanga), height(a->dreapta)) + 1;
    return a;
}

nod* leftRotate(nod* b)
{
    struct nod* y = b->dreapta;
    struct nod* aux = y->stanga;

    // rotatie
    y->stanga = b;
    b->dreapta = aux;

    //actualizam inaltimile
    b->inaltime = maxim(height(b->stanga), height(b->dreapta)) + 1;
    y->inaltime = maxim(height(y->stanga), height(y->dreapta)) + 1;

    return y;

}
int getBalance(nod* node)
{
    if (node == NULL)
        return 0;
    return height(node->stanga) - height(node->dreapta);
}
nod* insert(nod* node, int key)
{
    int balance;

    if (node == NULL)
        return(initializare(key));
    if (key == node->cheie)
    {
        (node->nr)++;
        return node;
    }

    if (key < node->cheie)
        node->stanga = insert(node->stanga, key);
    else if (key > node->cheie)
        node->dreapta = insert(node->dreapta, key);



    node->inaltime = maxim(height(node->stanga), height(node->dreapta)) + 1;


    balance = getBalance(node);


    if (balance > 1 && key < node->stanga->cheie)
        return rightRotate(node);


    if (balance < -1 && key > node->dreapta->cheie)
        return leftRotate(node);


    if (balance > 1 && key > node->stanga->cheie)
    {
        node->stanga = leftRotate(node->stanga);
        return rightRotate(node);
    }


    if (balance < -1 && key < node->dreapta->cheie)
    {
        node->dreapta = rightRotate(node->dreapta);
        return leftRotate(node);
    }


    return node;
}
void inordine(nod* radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga);
        printf("%d(%d) ", radacina->cheie, radacina->nr);
        inordine(radacina->dreapta);
    }
}

void preordine(nod* radacina)
{
    if (radacina != NULL)
    {
        printf("%d(%d) ", radacina->cheie, radacina->nr);
        preordine(radacina->stanga);
        preordine(radacina->dreapta);
    }
}
void postordine(nod* radacina)
{
    if (radacina != NULL)
    {
        postordine(radacina->stanga);
        postordine(radacina->dreapta);
        printf("%d(%d) ", radacina->cheie, radacina->nr);

    }

}
bool printLevel(nod* radacina, int level)
{
    if (radacina == NULL) return false;
    if (level == 1)
    {
        printf("%d(%d) ", radacina->cheie, radacina->nr);
        return true;
    }
    bool left = printLevel(radacina->stanga, level - 1);
    bool right = printLevel(radacina->dreapta, level - 1);
    return left || right;
}
void levelOrderTraversal(nod* radacina)
{
    int level = 1;
    while (printLevel(radacina, level))
        level++;
}
void Random() {

    int i;
    time_t t1; // declare time variable  
    srand((unsigned)time(&t1));
    for (i = 0; i < NR; i++)
    {
        v[i] = rand() % 10;
        printf("%d ", v[i]);

    }
    printf("\n");
}


void meniu()
{
    printf("\n1.Parcurgere in preordine \n");
    printf("2.Parcurgere in inordine \n");
    printf("3.Parcurgere in postordine \n");
    printf("4.Parcurgerea pe nivele \n");
    printf("0.Iesire \n");
    printf("Selectati o optiune: ");
}






int main()
{
    int opt, x, i;
    struct nod* radacina = NULL;
    Random();
    for (i = 0; i < NR; i++)
    {
        radacina = insert(radacina, v[i]);
    }

    do {
        meniu();
        scanf("%d", &opt);
        switch (opt)
        {
        case 0:break;
        case 1: printf("Afisare preordine:\n");
            preordine(radacina);
            break;
        case 2:printf("Afisare inordine:\n");
            inordine(radacina);
            break;
        case 3:printf("Afisare postordine:\n");
            postordine(radacina);
            break;
        case 4:printf("Afisare pe nivele\n");
            levelOrderTraversal(radacina);
            break;
        default:printf("Introduceti o optiune valida!\n");
            break;
        }


    } while (opt != 0);





    return 0;
}


