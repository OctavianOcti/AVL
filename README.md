Arborii AVL sau arborii echilibrati sunt arbori binari ordonati, care au in plus o
proprietate de echilibru .
Proprietatea de echilibru e valabila pentru orice nod al arborelui si spune ca: “inaltimea
subarborelui stang al nodului difera de inaltimea subarborelui drept al nodului prin cel
mult o unitate”.

Def1: Se numeste inaltime a unui arbore ca fiind lungimea celui mai lung drum de la
nodul radacina la unul din nodurile terminale.
Def2: Se numeste factor de echilibrare diferenta dintre inaltimea subarborelui drept si
inaltimea subarborelui stang.
Def3: Atasand fiecarui nod un camp care reprezinta factorul de echilibrare al sau, se
spune ca arborele binar este echilibrat cand toti factorii de echilibrare ai nodurilor sunt
-1,0,+1.

Cele 2 coduri sursa incarcate reprezinta 2 variante pentru tratarea arborilor AVL. Acesta se populeaza cu elemente aleatorii si se afiseaza elementele in urma traversarii in pre-ordine, in-ordine, post-ordine si pe nivel. Cheiele pot fi duplicate, prin urmare daca se introduc mai multe noduri cu aceleasi chei ele vor indica spre nodul de aceeasi cheie initial adaugat. AVL.c foloseste inaltimea unui nod  in timp ce AVL_balance.c utilieaza factorul de echilibru, reprezentarea datelor realizandu-se dupa modelul pointeri la fii.
![AVL_Tree_Example](https://user-images.githubusercontent.com/101703464/168899862-3ee855da-82f8-4c4b-969a-d8a0c291afa9.gif)

