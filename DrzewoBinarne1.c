#include<stdio.h>
#include<stdlib.h>

struct elDrzewaB
{
 int klucz;
 int licznik;
 struct elDrzewaB *left;
 struct elDrzewaB *right;
 struct elDrzewaB *root;
};
 typedef struct elDrzewaB wDrzewaB;
 typedef wDrzewaB* drzewo;


// void DrukujDrzewo0(drzewo d, int glebokosc){
//  if (d == 0) return;
//  DrukujDrzewo0(d->left, glebokosc + 1);
//  for (int i = 0; i < glebokosc; i++)
//  putchar('_' );
//  printf ("%d\n", d->klucz);
//  DrukujDrzewo0(d->right, glebokosc + 1);
// }

// void DrukujDrzewo(drzewo d){
//  DrukujDrzewo0(d, 0);
//  putchar('\n');
// }

void DrukujDrzewoRekurencyjnie(drzewo d, int poziom)
{
    if (d == NULL)
        return;

    const int odleglosc = 5;

    DrukujDrzewoRekurencyjnie(d->left, poziom + 1);

    for (int i = 0; i < odleglosc * poziom; i++)
        putchar(' ');

    printf("%d\n", d->klucz);

    DrukujDrzewoRekurencyjnie(d->right, poziom + 1);
}

void DrukujDrzewo(drzewo d)
{
    DrukujDrzewoRekurencyjnie(d, 0);
    putchar('\n');
}


drzewo* FindElement(drzewo *d, int klucz){

    if(*d == NULL)  return NULL;
    if(klucz < (*d)->klucz){
        return FindElement(&(*d)->left, klucz); 
    }else if(klucz > (*d)->klucz){
        return FindElement(&(*d)->right, klucz);
    }else{
        return d;
    }
}


drzewo* MaxElement(drzewo *d){

    if(*d == NULL) return NULL;
    while((*d)->right){
       d = &(*d)->right;
    }
    return d;
}

drzewo* MinElement(drzewo *d){

    if(*d == NULL) return NULL;
    while((*d)->left){
       d = &(*d)->left;
    }
    return d;
}

void DodajD(drzewo *d, int klucz){
  if (*d == 0)
  { *d = (drzewo)malloc(sizeof(wDrzewaB)); 
    (*d)->klucz = klucz; 
    (*d)->licznik = 1; 
    (*d)->left = (*d)->right = 0; 
  }
    else if(klucz < (*d)->klucz)  
      DodajD(&(*d)->left, klucz);
    else if (klucz >(*d)->klucz)
      DodajD(&(*d)->right, klucz);
  else
  (*d)->licznik++;
}

void RemoveElement(drzewo *d, int klucz){

    drzewo *q;
    drzewo us;
    if(*d == NULL) return;
    d = FindElement(d,klucz);
    if(d == NULL) return;
    if((*d)->licznik > 1){
        (*d)->licznik--;
        return;
    }
    if((*d)->left == NULL || (*d)->right == NULL){
        q = d;
    }else{
        q = MaxElement(&(*d)->left);
        (*d)->klucz = (*q)->klucz;
        (*d)->licznik = (*q)->licznik;
    }
    us = *q;
    if((*q)->left == NULL){
        *q = (*q)->right;
    }else{
        *q = (*q)->left;  
    }
    free(us);
}

void RemoveFound(drzewo *d) {
    drzewo us = *d;

    if (*d == NULL) {
        return; // Drzewo jest już puste
    }
    if ((*d)->licznik > 1) {
        (*d)->licznik--; // Zmniejszamy licznik, ale nie usuwamy całkowicie elementu
        return;
    }
    if ((*d)->left == NULL) {
        *d = (*d)->right;
    } else if ((*d)->right == NULL) {
        *d = (*d)->left;
    } else {
        // Mamy obie gałęzie, znajdujemy największy element w lewej gałęzi i zamieniamy miejscami
        drzewo *q = MaxElement(&(*d)->left);
        (*d)->klucz = (*q)->klucz;
        (*d)->licznik = (*q)->licznik;
        us = *q;
        *q = (*q)->left;
    }
    free(us);
}

int szer(drzewo T) {
    if (T == NULL) {
        return 0;
    }

    int maxNodes = 0;
    int currentLevelNodes = 0;

    drzewo marker = NULL; // Marker oznaczający koniec poziomu
    drzewo* queue = NULL;  // Tablica dla kolejki
    int front = 0;
    int rear = -1;

    drzewo tempQueue[100]; // Ustal maksymalny rozmiar kolejki (do dostosowania)

    queue = tempQueue;

    queue[++rear] = T;
    queue[++rear] = marker;

    while (front <= rear) {
        drzewo current = queue[front++];

        if (current == marker) {
            // Koniec poziomu, zwiększ licznik poziomu
            if (currentLevelNodes > maxNodes) {
                maxNodes = currentLevelNodes;
            }
            currentLevelNodes = 0;

            // Jeśli kolejka nie jest pusta, dodaj marker dla kolejnego poziomu
            if (front <= rear) {
                queue[++rear] = marker;
            }
        } else {
            // Normalny węzeł, zwiększ licznik węzłów na bieżącym poziomie
            currentLevelNodes++;

            // Dodaj lewe i prawe dziecko, jeśli istnieją
            if (current->left != NULL) {
                queue[++rear] = current->left;
            }
            if (current->right != NULL) {
                queue[++rear] = current->right;
            }
        }
    }

    return maxNodes;
}

int tree_equal(drzewo T1, drzewo T2){

    if( (T1 == NULL) || (T2 == NULL)){ 
        return T1 == T2; 
    }

    return( (T1->klucz == T2->klucz) && tree_equal(T1->left,T2->left) && tree_equal(T1->right,T2->right) );
}



int main(){
drzewo T1 = NULL;
drzewo T2 = NULL;
drzewo* s = NULL;
DodajD(&T1, 44);
DodajD(&T1, 17);
DodajD(&T1, 63);
DodajD(&T1, 19);
DodajD(&T1, 15);
s = FindElement(&T1, 15);
RemoveFound(s);
RemoveElement(&T1,17);
int width1 = szer(T1);
printf("Szerokosc drzewa: %d\n", width1);
DrukujDrzewo(T1);
DodajD(&T2, 44);
DodajD(&T2, 17);
DodajD(&T2, 63);
DodajD(&T2, 19);
DodajD(&T2, 15);
s = FindElement(&T2, 15);
RemoveFound(s);
//RemoveElement(&T,17);
int width2 = szer(T2);
printf("Szerokosc drzewa: %d\n", width2);
DrukujDrzewo(T2);

if(!tree_equal(T1,T2)){
    printf("Drzewa T1 i T2 nie sa rowne");
}
else{
    printf("Drzewa T1 i T2 sa rowne");
}

}
