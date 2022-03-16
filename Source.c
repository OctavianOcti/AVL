/*Traversarea arborilor AVL – Se dă un arbore AVL care se populează cu elemente aleatorii.Să
se afișeze elementele în urmă traversării arborelui în „pre - ordine”, „in - ordine”, „post - ordine”
și pe „nivel”(level - order traversal).
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct nod
{
    int cheie; //nodul de inserat
    struct nod* stanga; //pointer spre fiu stanga
    struct nod* dreapta; //pointer spre fiu dreapta
    int inaltime; //inaltimea
}nod;

nod* radacina;
int avl_echilibrat = 1, contor = 0, vector_sterg[20];

nod* initializare(nod* radacina)
{
    if (radacina != NULL)
        free(radacina);
    radacina = NULL;
    return radacina;
}

int maxim(int x, int y)
{
    if (x > y)
        return x;
    return y;
}

int inalt(nod* n) //inaltime
{
    if (n != NULL)
    {
        int inaltime_stanga = inalt(n->stanga);
        int inaltime_dreapta = inalt(n->dreapta);
        return(1 + maxim(inaltime_stanga, inaltime_dreapta));
    }
    return -1;
}



nod* inserare(nod* n, int ch)
{
    if (n == NULL)
    {
        nod* nd;
        nd = (nod*)malloc(sizeof(nod));
        if (nd == NULL)
        {
            printf("Eroare la alocarea noului nod\n");
            exit(EXIT_FAILURE);
        }
        nd->cheie = ch;
        nd->dreapta = NULL;
        nd->stanga = NULL;
        nd->inaltime = 1;
        return nd;
    }
    if (n != NULL)
    {
        if (ch < n->cheie) //cheia=radacina < cheia nodului 
            n->stanga = inserare(n->stanga, ch); //nodul se insereaza in stanga
        else
        {
            if (ch > n->cheie) //radacina > cheia nodului
                n->dreapta = inserare(n->dreapta, ch); //nodul este inserat in dreapta
            else
                return n;
        }
    }
    if (n != NULL && n->stanga != NULL && n->dreapta != NULL) //daca exista elemente atat in stanga cat si in dreapta nodului 
        n->inaltime = maxim(n->stanga->inaltime, n->dreapta->inaltime) + 1; //intaltimea= maximul dintre inaltimile din ambele parti +1 (nodul)
    else
    {
        if (n != NULL && n->stanga == NULL && n->dreapta != NULL) //daca avem noduri doar in partea dreapta
            n->inaltime = maxim(0, n->dreapta->inaltime) + 1; //inaltimea= inaltimea din dreapta +1
        else
        {
            if (n != NULL && n->stanga != NULL && n->dreapta == NULL) //noduri doar in partea stanga
                n->inaltime = maxim(n->stanga->inaltime, 0) + 1; //inaltimea= inaltimea din stanga +1
            else
            {
                if (n != NULL && n->stanga == NULL && n->dreapta == NULL)
                    n->inaltime = 1; //daca nu sunt noduri nici in stanga nici in dreapta => inaltimea=1 (nodul)

            }
        }

    }
    return n; //intoarcem datele nodului 
}

void inordine(nod* radacina)
{
    if (radacina != NULL)
    {
        inordine(radacina->stanga); //stanga
        if (radacina->cheie % 2 != 0) //verificam daca numarul este impar
        {
            vector_sterg[contor] = radacina->cheie; //retinem valorile in vector pentru a fi sterse ulterior
            contor++;
        }
        printf("%d ", radacina->cheie);
        inordine(radacina->dreapta); //dreapta
    }
}

void preordine(nod* radacina)
{
    if (radacina != NULL)
    {
        printf("%d ", radacina->cheie); //radacina
        preordine(radacina->stanga); //stanga
        preordine(radacina->dreapta); //dreapta
    }
}
void postordine(nod* radacina)
{
    if (radacina != NULL)
    {
        postordine(radacina->stanga);
        postordine(radacina->dreapta);
        printf("%d ", radacina->cheie);

    }

}

int main()
{
    radacina = initializare(radacina);
    radacina = inserare(radacina, 12);
    radacina = inserare(radacina, -7);
    radacina = inserare(radacina, 45);
    radacina = inserare(radacina, 32);
    radacina = inserare(radacina, 2);
    radacina = inserare(radacina, 22);
    radacina = inserare(radacina, 1);
    radacina = inserare(radacina, 2);
    radacina = inserare(radacina, 3);
    radacina = inserare(radacina, 4);
    radacina = inserare(radacina, 90);
    radacina = inserare(radacina, 89);
    radacina = inserare(radacina, 225);
    radacina = inserare(radacina, 0);
    printf("Parcurgerea in preordine: "); 
    preordine(radacina);
    printf("\nParcurgerea in inordine: ");
    inordine(radacina);
    printf("\nParcurgerea in postordine: ");
   postordine(radacina);
    return 0;
}