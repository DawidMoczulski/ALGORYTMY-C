#include <stdio.h>
#include <stdlib.h>

 struct elDrzewaB {
    int value;
    int licznik;
    struct elDrzewaB *parent;
    struct elDrzewaB *left;
    struct elDrzewaB *right;
};

 typedef struct elDrzewaB wDrzewaB;
 typedef wDrzewaB* node;


void DrukujDrzewoRekurencyjnie(node d, int poziom)
{
    if (d == NULL)
        return;

    const int odleglosc = 5;

    DrukujDrzewoRekurencyjnie(d->left, poziom + 1);

    for (int i = 0; i < odleglosc * poziom; i++)
        putchar(' ');

    printf("%d\n", d->value);

    DrukujDrzewoRekurencyjnie(d->right, poziom + 1);
}

void DrukujDrzewo(node d)
{
    DrukujDrzewoRekurencyjnie(d, 0);
    putchar('\n');
}

node* FindElement(node *d, int klucz){

    if(*d == NULL)  return NULL;
    if(klucz < (*d)->value){
        return FindElement(&(*d)->left, klucz); 
    }else if(klucz > (*d)->value){
        return FindElement(&(*d)->right, klucz);
    }else{
        return d;
    }
}

void DodajD(node* root, int value)
{
    node q = NULL;
    if((*root) == NULL){
        q=(node)malloc(sizeof(wDrzewaB));
        q->value=value;
        q->left=NULL;
        q->right=NULL;
        q->parent=NULL;
        *root=q; 
    }
    else
    {
        if((*root)->value >= value) 
        {
            DodajD(&((*root)->left), value);
            (*root)->left->parent = *root; 
        }
        else 
        {
            DodajD(&((*root)->right), value);
            (*root)->right->parent = *root; 
        }
    }
}
node* MaxElement(node *d){

    if(*d == NULL) return NULL;
    while((*d)->right){
       d = &(*d)->right;
    }
    return d;
}

node treeMin(node root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

void RemoveElement(node *d, int klucz){

    node *q;
    node us;
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
        (*d)->value = (*q)->value;
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


node successor(node n) {
    if (n == NULL) return NULL;
    if (n->right != NULL){
        return treeMin(n->right);
    } 

    node parent = n->parent;

    while (parent != NULL && n == parent->right) 
    {
        n = parent;
        parent = parent->parent;
    }

    return parent;
}


int containSameValues(node* tree1, node* tree2) {
    //int i = 1;
    if (tree1 == NULL || tree2 == NULL) return 0;

    node current1 = treeMin(*tree1);
    node current2 = treeMin(*tree2);
    //printf("Minimum z drzewa1: %d \n",current1->value);
    //printf("Minimum z drzewa2: %d \n",current2->value);

    while (current1 != NULL && current2 != NULL) {
        //printf("Porownanie %d z drzewa1: %d \n",i,current1->value);
        //printf("Porownanie %d z drzewa2: %d \n",i,current2->value);
       if (current1->value != current2->value) return 0;

        current1 = successor(current1);
        current2 = successor(current2);
        //i++;
    }

    return 1;
}


int main(){

 node T1 = NULL;
 node T2 = NULL;
 node* s = NULL;
 int wybor,klucz,element,nr;
     printf("\n----   Drzewo Binarne   ----\n");
    do{
                printf("\n");
                printf("1. Dodaj nowy element do drzewa.\n");
                printf("2. Wyswietl drzewa\n");
                printf("3. Usun element z drzewa.\n");
                printf("4. Sprawdz czy drzewa sie skladaja z tych samych elementow.\n");
                printf("0. EXIT.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);


                switch(wybor){

                    case 0:
                    klucz = 1;
                    break;

                    case 1:
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    printf("Do jakiego drzewa chcesz dodac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      DodajD(&T1,element);
                    }
                    else{
                      DodajD(&T2,element); 
                    }
                    break;

                    case 2:
                    printf("Drzewo 1: \n");
                    DrukujDrzewo(T1);
                    printf("Drzewo 2: \n"); 
                    DrukujDrzewo(T2);
                    break;


                    case 3:
                    printf("Podaj liczbe ktora chcesz usunac: ");
                    scanf("%d",&element);
                    printf("Z jakiego drzewa chcesz usunac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      RemoveElement(&T1,element);
                    }
                    else{
                      RemoveElement(&T2,element); 
                    }
                    break;

                    case 4:
                    if( containSameValues(&T1,&T2) == 1 ){
                        printf("Drzewa 1 i 2 skladaja sie z tych samych wartosci.");
                    }else{
                        printf("Drzewa 1 i 2 nie skladaja sie z tych samych wartosci.");
                    }
                    break;
                    
                    default :
                    printf("Nieznana operacja.\n" );

                }

    }while(klucz == 0);


return 0;

}







