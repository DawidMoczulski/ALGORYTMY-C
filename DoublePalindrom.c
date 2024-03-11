#include <stdio.h>
#include <stdlib.h>

// Struktura węzła listy dwukierunkowej
// struct Node {
//     int data;
//     struct Node* next;
//     struct Node* prev;
// };

// typedef struct Node Node;
// typedef Node* lista;

struct el{
    
    int klucz;
    struct el *prev;
    struct el *nast;
};

typedef struct el elListy;
typedef elListy *lista;

void Wyswietl(lista l){

    lista el = l;
    if(el == NULL)  printf("Lista jest pusta\n");
    while(el != NULL){
        printf(" %d ", el->klucz);
        printf("<->");
        el = el->nast;
    }
}

void WyswietlodKonca(lista *l){

    if(*l == NULL){
        return;
    }
    WyswietlodKonca(&((*l)->nast));
    printf("%d ", (*l)->klucz);
    printf("<->");
}

void DodajPoczatek(lista *l, int y) {

    lista q = malloc(sizeof(elListy));     
    q->klucz = y;                         
    q->nast = *l;

    if(*l != NULL){
       (*l)->prev = q; 
    } 
    q->prev = NULL;                       
    *l = q;    
}
void DodajKoniec(lista *l, int y){
    
    while(*l != NULL)  l = &((*l)->nast);
    DodajPoczatek(l,y);
}


void UsunPierwszy(lista *l) {
    
    lista q = *l;
    if(q != NULL){
         *l = q->nast;
    }
    free(q);
}


void UsunOstatni(lista *l){
    lista q = *l;
    if (*l == NULL) {
        // Lista jest pusta, nie ma co usuwać
        return;
    }
    // Przechodzimy do ostatniego elementu
    while (q->nast != NULL) {
        q = q->nast;
    }
    if (q->prev != NULL) {
        // Ostatni element nie jest jednocześnie pierwszym
        q->prev->nast = NULL;
        free(q);
    } else {
        // Ostatni element jest jednocześnie pierwszym
        free(q);
        *l = NULL;
    }
}

lista* znajdz(lista *l, int y){
    
    while(*l != NULL){
        if ((*l)->klucz == y) {
            return l; 
        }
        l = &((*l)->nast);
    }
    return l;
}

void ZnajdziUsun(lista *l, int y)
{
    lista* q = znajdz(l, y);
    int x;
    if (*q) {
         UsunPierwszy(q);
    } 
}




void UsunWszystkie(lista *l, int y){

    while( (*l != NULL)){
        if((*l)->klucz != y){
           l = &((*l)->nast);
        }
        else{
            UsunPierwszy(l);
        }
    } 
}

void UsunWszystkieR(lista *l, int y){
    
    if(*l != NULL){
        if( (*l)->klucz == y){
            UsunPierwszy(l);
        }else{
            l = &((*l)->nast);
        }
       UsunWszystkieR(l,y);
    }
}


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

void usun_powtorzeniaR(lista *l){

    if(*l != NULL){
        UsunWszystkieR(&((*l)->nast), (*l)->klucz);
        usun_powtorzeniaR(&((*l)->nast));
    }
}

void usun_powtorzenia(lista *l){

    while(*l != NULL){
        UsunWszystkie(&((*l)->nast), (*l)->klucz);
        l = &((*l)->nast);
    }
}


void OdwrocR(lista *l, lista q){

    lista r;
    if(*l == NULL){
        *l = q;
        return;
    }
    r = *l;
    *l = (*l)->nast;
    r->nast = q;
    q = r;
    OdwrocR(l,q);

}

int Palindrom(lista l, lista q){

 
    if (l->klucz != q->klucz) { return 0; }
    if (l == q) { return 1; }
    if (l->nast == q){return 1;}
    return Palindrom(l->nast,q->prev);

    // if(l->klucz == q->klucz){
    //    //printf("Funkcja jest palindromem.\n");
    //    return 1;
    // } 

    // lista p = l;
    // OdwrocR(p,q);
    // while(l != q){
    //     if(p->klucz != l->klucz){
    //        //printf("Lista nie jest palindromem.");
    //        return 0;
    //     }
    //     l = l->nast;
    //     p = p->nast;
    // }
    // printf("Lista jest palindromem.");
    // return 1;
}


int isDoublePalindrom(lista l){

    int PalCounter = 0;
    lista p = l;
    lista q = l->nast;
    while( q != NULL){
        if (Palindrom(l,q) == 0)
        {
           q = q->nast;  
        }
        else{
         PalCounter++;
         l = q->nast;
         if(l == NULL){ break; }
         q = l->nast;
        }
    }
    return PalCounter; 
}


int main(){
     
    lista l=NULL;
    lista* p;
    int wyjscie = 0;
    int wybor;
    int x = 0;
    int element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n\n--  Lista Dwukierunkowa Niecykliczna  --\n\n");
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
        printf("12. Czy funkcja sklada sie z dwoch palindromow.\n");
        printf("13. Odwroc strukture listy rekurencyjnie.\n");
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

            case 12:
            if(isDoublePalindrom(l) == 2){
                printf("Lista sklada sie z dwoch palindromow.");
            }else{
                printf("Lista nie sklada sie z dwoch palindromow.");
            }
            break;   

            case 13:
            OdwrocR(&l,NULL);
            printf("\n");
            break;   

            default :
            printf("Nieznana operacja.\n" );

        }
  
    }while(wyjscie == 0);
   
    return 0;
}