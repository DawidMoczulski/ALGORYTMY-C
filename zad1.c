#include<stdio.h>
#include<stdlib.h>


struct el{
    
    int klucz;
    struct el *nast;
};

typedef struct el elListy;
typedef elListy *lista;

void Wyswietl(lista l){

    lista el = l;
    if(el == NULL)  printf("Lista jest pusta\n");
    while(el != NULL){
        printf("%d ", el->klucz);
        printf("->");
        el = el->nast;
    }
}


void WyswietlodKonca(lista *l){

    if(*l == NULL){
        return;
    }

    WyswietlodKonca(&((*l)->nast));
    printf("%d ", (*l)->klucz);
}

void DodajPoczatek(lista *l, int y)   // wskaznik na liste
{
    
   lista q = malloc(sizeof(elListy));     //alokujemy dynamicznie nową strukturę   (q zawiera adres na pierwszy element struktury)
   q->klucz = y;                          //podstawiamy wartosc y do struktury q
   q->nast = *l;                          //sprawiamy ze struktura q bedzie wskazywac na to co struktura l
   *l = q;                                //do miejsca ktore wskazuje *l podstawiamy adres q (wskazuje na nową strukturę)
}


 void DodajKoniec(lista *l, int y){
    
    while(*l != NULL)  l = &((*l)->nast);
    DodajPoczatek(l,y);
}

void UsunPierwszy(lista *l){
    
    lista q = malloc(sizeof(elListy));
    q = *l;
    if(q != NULL){
        *l = q->nast;
    }
    free(q);
}

// lista UsunPierwszy(lista l){
    
//     lista q = malloc(sizeof(elListy));
//     q = l;
//     if(q != NULL){
//         l = q->nast;
//     }
//     free(q);

//     return l;
// }

void UsunOstatni(lista *l){

    lista q = *l;
    lista prev = NULL;

    if (*l == NULL || (*l)->nast == NULL) {
        free(*l);
        *l = NULL;
        return;
    }

    while (q->nast != NULL) {
        prev = q;
        q = q->nast;
    }

    free(q);

    if (prev != NULL) {
        prev->nast = NULL;
    } else {
        *l = NULL;
    }

}

lista* znajdz(lista *l, int y){

    while( (*l != NULL) && ((*l)->klucz != y) ){
       l = &((*l)->nast);
    } 
    return l;
}

// lista znajdz(lista l, int y){

//     while( (l != NULL) && ((l)->klucz != y) ){
//        l = ((l)->nast);
//     } 
//     return l;
// }



// void ZnajdziUsun(lista *l, int y){

//     lista q = malloc(sizeof(elListy));
//     while( (*l != NULL) && ((*l)->klucz != y) ){
//        l = &((*l)->nast);
//     } 
//     q = *l;
//     if( q != NULL){
//        *l = q->nast;
//     }
//     free(q);

// }

lista ZnajdziUsun(lista l, int y){

    lista q = malloc(sizeof(elListy));
    lista p = malloc(sizeof(elListy));
    p = l;
    while( (l != NULL) && ((l)->klucz != y) ){
       p = l;
       l = ((l)->nast);
    } 
    q = l;
    if( q != NULL){
       p->nast = q->nast;
    }
    free(q);

    return p;

}


void ZnajdziUsun(lista *l, int y)
{
    lista* q = znajdz(l, y);
    if(*q)
        UsunPierwszy(q);

}


void UsunWszystkie( lista *l, int y){


    while( (*l != NULL)){
        if((*l)->klucz != y){
           l = &((*l)->nast);
        }
        else{
            UsunPierwszy(l);
        }
    } 
}



// lista UsunWszystkie(lista l, int y) {
//     lista q = NULL;
//     lista p = NULL;
//     lista r = NULL;
//     lista s = NULL;

//     while (l != NULL) {
//         if (l->klucz != y) {
//             r = l;
//             l = l->nast;
//             if (q == NULL) {
//                 q = r;
//                 p = r;
//             } else {
//                 p->nast = r;
//                 p = r;
//             }
//         } else {
//             s = l;
//             l = l->nast;
//             free(s);
//         }
//     }

//     if (q != NULL) {
//         p->nast = NULL;
//     }

//     return q;
// }




// void dodaj_przed(lista *l, int y, int z) {
//     lista *p = l;
//     while (*p != NULL && (*p)->klucz != y)
//         p = &(*p)->nast;
//     if (*p != NULL) {
//         lista nowy = malloc(sizeof(elListy));
//         nowy->klucz = z;
//         nowy->nast = *p;
//         *p = nowy;
//     }
// }

void dodaj_przed(lista *l, int y, int z)
{

    lista* q = znajdz(l,y);
    if(q != NULL)  DodajPoczatek(q,z);

}

void dodaj_za (lista *l, int y, int z){

    lista* q = znajdz(l,y);

    if(q != NULL){
        DodajPoczatek(&(*q)->nast,z);
    }
}

int main(){
     
    lista l=NULL;
    lista* p;
    int wyjscie = 0;
    int wybor;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n\n--  Lista Jednokierunkowa  --\n\n");
        printf("1. Dodaj element na poczatek listy\n");
        printf("2. Dodaj element na koniec listy\n");
        printf("3. Wyswietl liste\n");
        printf("4. Usun pierwszy element listy\n");
        printf("5. Usun ostatni element listy\n");
        printf("6. Wyswietl liste od tylu\n");
        printf("7. Wyszukaj element z listy.\n");
        printf("8. Usun z listy element o wyszukanej wartosci.\n");
        printf("9. Dodaj element przed wyszukanym elementem.\n");
        printf("10. Dodaj element za wyszukanym elementem.\n");
        printf("11. Usun wszystkie elementy o podanej wartosci.\n");
        printf("0. Wyjdz z programu.\n");
        printf("Podaj numer: ");
        scanf("%d",&wybor);

        switch(wybor){

            case 0:
            wyjscie = 1;
            break;

            case 1:
            printf("Podaj liczbe ktora chcesz dodac: ");
            scanf("%d",&element);
            DodajPoczatek(&l,element);
            break;

            case 2:
            printf("Podaj liczbe ktora chcesz dodac: ");
            scanf("%d",&element);
            DodajKoniec(&l,element);
            break;


            case 3:
            Wyswietl(l);
            printf("\n");
            break;

            case 4:
            UsunPierwszy(&l);
            printf("\n");
            break;

            case 5:
            UsunOstatni(&l);
            printf("\n");
            break;


            case 6:
            WyswietlodKonca(&l);
            printf("\n");
            break;

            

            case 7:
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            p=znajdz(&l,element);   
            if(*p != NULL){
                printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p, (*p)->klucz);
            }
            else{
                printf("Nie ma takiego elementu na liscie.");
            }
            break;

            case 8:
            printf("Element o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            ZnajdziUsun(&l,element);
            printf("\n");
            break;


            case 9:
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac przed %d?: ", element);
            scanf("%d",&element2);
            dodaj_przed(&l,element,element2);
            printf("\n");
            break;

            case 10:
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac za %d?: ", element);
            scanf("%d",&element2);
            dodaj_za(&l,element,element2);
            printf("\n");
            break;

            case 11:
            printf("Elementy o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            UsunWszystkie(&l,element);
            printf("\n");
            break;

            default :
            printf("Nieznana operacja.\n" );

        }
  
    }while(wyjscie == 0);
   
    return 0;
}