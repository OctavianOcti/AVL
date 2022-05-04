#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include <time.h>
#define NR 10

// An AVL tree node 
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


// A utility function to get the height of the tree 
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

// A utility function to get maximimum of two integers 
int maxim(int a, int b)
{
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
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
//returneaza un pointer catre primul fiu
struct Node* PrimulFiu(struct Node* root, struct Node* node)
{

    if (root != NULL)
    {
        if (root == node)
            if (root->left && root->right == NULL) p = root->left;
            else
                if (root->right && root->left == NULL) p = root->right;
        PrimulFiu(root->left, node);
        PrimulFiu(root->right, node);
    }
    return p;

}
//returneaza un pointer catre radacina
struct Node* Radacina(struct Node* root)
{
    if (root == NULL)
        printf("Arbore vid\n");
    return root;
}

//returneaza un pointer catre fratele dreapta al unui nod
struct Node* FrateDreapta(struct Node* root, struct Node* node)
{
    if (root != NULL)
    {
        if (root->left && root->left == node) {
            p = root->right;
            return p;
        }
        FrateDreapta(root->left, node);
        FrateDreapta(root->right, node);
    }
    return p;
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
        else if(key<node->key)
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

//returneaza un pointer catre un nod dat prin cheie
struct Node* nod(struct Node* root, int key)
{
    if (root != NULL)
    {
        if (root->key == key) {
            p = root;
            // return p;
        }
        nod(root->left, key);
        nod(root->right, key);

    }
    return p;
}
//returneaza un pointer catre tata unui nod
struct Node* Tata(struct Node* root, struct Node* node)
{
    if (node == root) return NULL;
    if (root)
    {
        if (root->left && root->left == node) p = root;
        if (root->right && root->right == node) p = root;
        // if (root->left->key == key|| root->right->key == key) p = root;
        Tata(root->left, node);
        Tata(root->right, node);
    }
    return p;
}
struct node* suprima(struct Node* node, struct Node* root)
{

    struct Node* q;
    if (node != NULL && root != NULL)
    {

        suprima(node->left, root);
        suprima(node->right, root);
        if (node != root)
        {
            q = Tata(root, node);
            if (q->left && q->left == node)
                q->left = NULL;
            if (q->right && q->right == node)
                q->right = NULL;
        }


        if (root != node)free(node);
        else {
            root->left = root->right = NULL;
            free(root);
            root = NULL;


        }

    }
    return root;

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
        printf("%d(%d) ", root->key,root->nr);
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
void levelOrderTraversal( struct Node* root)
{
    int level = 1;
    while (printLevel(root, level))
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
           preOrder(radacina);
            break;
        case 2:printf("Afisare inordine:\n");
            inOrder(radacina);
            break;
        case 3:printf("Afisare postordine:\n");
            postOrder(radacina);
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