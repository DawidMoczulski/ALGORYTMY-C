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


void ZnajdziUsun(lista *l, int y)
{
    lista* q = znajdz(l, y);
    if(*q)
        UsunPierwszy(q);

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


int main(){
     
    lista l=NULL;
    lista* p;
    int wyjscie = 0;
    int wybor;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n--  Lista Jednokierunkowa  --\n\n");
        printf("1. Dodaj element na poczatek listy\n");
        printf("2. Dodaj element na koniec listy\n");
        printf("3. Wyswietl liste\n");
        printf("4. Usun pierwszy element listy\n");
        printf("5. Usun ostatni element listy\n");
        printf("6. Wyswietl liste od tylu\n");
        printf("7. Wyjdz z programu.\n");
        printf("8. Wyszukaj element z listy.\n");
        printf("9. Usun z listy element o wyszukanej wartosci.\n");
        printf("10. Dodaj element przed wyszukanym elementem.\n");
        printf("11. Dodaj element za wyszukanym elementem.\n");
        printf("12. Usun NIErekurencyjnie wszystkie elementy o podanej wartosci.\n");
        printf("13. Usun rekurencyjnie wszystkie elementy o wybranej wartosci.\n");
        printf("14. Usun rekurencyjnie wszystkie powtorzenia elementow z listy.\n");
        printf("15. Usun NIErekurencyjnie wszystkie powtorzenia elementow z listy.\n");
        printf("16. Odwroc strukture listy rekurencyjnie.\n");
        printf("Podaj numer: ");
        scanf("%d",&wybor);

        switch(wybor){

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
            wyjscie = 1;
            break;

            case 8:
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

            case 9:
            printf("Element o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            ZnajdziUsun(&l,element);
            printf("\n");
            break;


            case 10:
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac przed %d?: ", element);
            scanf("%d",&element2);
            dodaj_przed(&l,element,element2);
            printf("\n");
            break;

            case 11:
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac za %d?: ", element);
            scanf("%d",&element2);
            dodaj_za(&l,element,element2);
            printf("\n");
            break;

            case 12:
            printf("Elementy o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            UsunWszystkie(&l,element);
            printf("\n");
            break;

            case 13:
            printf("Elementy o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            UsunWszystkieR(&l,element);
            printf("\n");
            break;

            case 14:
            usun_powtorzeniaR(&l);
            printf("\n");
            break;

            case 15:
            usun_powtorzenia(&l);
            printf("\n");
            break;

            case 16:
            OdwrocR(&l,NULL);
            printf("\n");
            break;



            default :
            printf("Nieznana operacja.\n" );

        }
  
    }while(wyjscie == 0);
   
    return 0;
}