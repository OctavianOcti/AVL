#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include <time.h>
#define NR 10

 
struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    int balance;
    int nr;
};
struct Node* p;
int v[NR];



int height(struct Node* node)
{
    int st = 0, dr = 0;
    if (node == NULL)
        return 0;
    if (node->left == NULL) st = 0;
    else
        st += node->left->balance + 1;
    if (node->right == NULL) dr = 0;
    else
        dr += node->right->balance + 1;
    return maxim(st, dr);

}
//returneaza factorul de echilibru al unui nod
int factor(struct Node* node)
{
    int st = 0, dr = 0;
    if (node == NULL)
        return 0;
    if (node->left == NULL) st = 0;
    else
        st += node->left->balance + 1;
    if (node->right == NULL) dr = 0;
    else
        dr += node->right->balance + 1;
    return (st - dr);
}
//efectueaza rotatie simpla la dreapta
struct Node* s_rot_right(struct Node* node)
{
    struct Node* x;
    x = node->left;
    node->left = x->right;
    x->right = node;
    node->balance = height(node);
    x->balance = height(x);
    return x;
}
//efectueaza rotatie simpla la stanga
struct Node* s_rot_left(struct Node* node)
{
    struct Node* x;
    x = node->right;
    node->right = x->left;
    x->left = node;
    node->balance = height(node);
    x->balance = height(x);
    return x;
}
//efectueaza rotatie dubla la dreapta
struct Node* d_rot_right(struct Node* node)
{
    node->left = s_rot_left(node->left);
    node = s_rot_right(node);
    return node;
}
//efectueaza rotatie dubla la stanga
struct Node* d_rot_left(struct Node* node)
{
    node->right = s_rot_right(node->right);
    node = s_rot_left(node);
    return node;
}

int maxim(int a, int b)
{
    return (a > b) ? a : b;
}


struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->balance = 0;
    node->nr = 1;
    return node;
}


//returneaza cheia unui nod 
int cheie(struct Node* root, struct Node* node)
{
    if (node->key) return node->key;
    return -1;//daca nu a gasit nodul cautat

}

//returneaza un pointer catre radacina
struct Node* Radacina(struct Node* root)
{
    if (root == NULL)
        printf("Arbore vid\n");
    return root;
}


// insereaza un nod
struct Node* insert(struct Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    else {
        if (key > node->key)
        {
            node->right = insert(node->right, key);
            if (factor(node) == -2)
                if (key > node->right->key)
                    node = s_rot_left(node);
                else node = d_rot_left(node);
        }
        else if (key < node->key)
        {
            node->left = insert(node->left, key);
            if (factor(node) == 2)
                if (key < node->left->key)
                    node = s_rot_right(node);
                else
                    node = d_rot_right(node);

        }
        else if (key == node->key)
        {
            (node->nr)++;

        }




        node->balance = height(node);
        return node;
    }

}




void preOrder(struct Node* root)
{
    if (root != NULL)
    {
        printf("%d(%d) ", root->key, root->nr);
        preOrder(root->left);
        preOrder(root->right);
    }

}


void inOrder(struct Node* root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d(%d) ", root->key, root->nr);
        inOrder(root->right);
    }
}
void postOrder(struct Node* root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d(%d) ", root->key, root->nr);
    }
}
bool printLevel(struct Node* root, int level)
{
    if (root == NULL) return false;
    if (level == 1)
    {
        printf("%d(%d) ", root->key, root->nr);
        return true;
    }
    bool left = printLevel(root->left, level - 1);
    bool right = printLevel(root->right, level - 1);
    return left || right;
}
void levelOrderTraversal(struct Node* root)
{
    int level = 1;
    while (printLevel(root, level))
        level++;
}
void Random() {

    int i;
    time_t t1; 
    srand((unsigned)time(&t1));
    for (i = 0; i < NR; i++)
    {
        v[i] = rand() % 15;
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
        case 1: printf("\nAfisare preordine:\n");
            preOrder(radacina);
            break;
        case 2:printf("\nAfisare inordine:\n");
            inOrder(radacina);
            break;
        case 3:printf("\nAfisare postordine:\n");
            postOrder(radacina);
            break;
        case 4:printf("\nAfisare pe nivele\n");
            levelOrderTraversal(radacina);
            break;
        default:printf("\nIntroduceti o optiune valida!\n");
            break;
        }


    } while (opt != 0);





    return 0;
}