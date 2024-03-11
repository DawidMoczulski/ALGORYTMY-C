#include<stdio.h>
#include<stdlib.h>


struct el
{
    
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

void DodajPoczatek(lista *l, int y)   
{
    
   lista q = malloc(sizeof(elListy));     
   q->klucz = y;                         
   q->nast = *l;                          
   *l = q;                                
}


 void DodajKoniec(lista *l, int y){
    
    while(*l != NULL)  l = &((*l)->nast);
    DodajPoczatek(l,y);
}

void UsunPierwszy(lista *l){
    
    lista q = *l;
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

void MostCommonElement(lista *l){

int ilosc=0;
int ilosc2=0;
int liczba=0;
int wynik=0;
lista p;
    while(*l != NULL){
        p = *l;
        liczba = (*l)->klucz;
        ilosc = 0;
        while(p != NULL){
           
          if (p->klucz == liczba){
            ilosc++;
          }  
          p = p->nast;   
        } 
        if(ilosc > ilosc2){
            wynik = liczba;
            ilosc2 = ilosc;
        }
        l = &((*l)->nast);
    }
    printf("Najczesciej wystepujaca wartosc to %d, pojawia sie %d razy.", wynik, ilosc2);

}




void usunniepodz(lista *l, int k){
    
    while( (*l != NULL)){
        if((*l)->klucz % k == 0){
           l = &((*l)->nast);
        }
        else{
            UsunPierwszy(l);
        }
    } 
    
    
}

int main(){
     
    lista l=NULL;
    lista k=NULL;
    lista* p;
    int wyjscie = 0;
    int wybor,nr;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n--  Lista Jednokierunkowa  --\n\n");
        printf("1. Dodaj element na poczatek listy\n");
        printf("2. Dodaj element na koniec listy\n");
        printf("3. Wyswietl listy\n");
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
        printf("14. Znajdz najczesciej wystepujaca wartosc w liscie.\n");
        printf("15. Usun z wybranej listy wszystkie elementy niepodzielne \n przez wybrana wartosc.\n");
        printf("Podaj numer: ");
        scanf("%d",&wybor);

        switch(wybor){

            case 1:
            printf("Do jakiej listy chcesz dodac element: (1) (2): ");
            scanf("%d",&nr);
            printf("Podaj liczbe ktora chcesz dodac: ");
            scanf("%d",&element);
            if (nr == 1){
               DodajPoczatek(&l,element);
            }else{
               DodajPoczatek(&k,element);
            }
            break;

            case 2:
            printf("Do jakiej listy chcesz dodac element: (1) (2): ");
            scanf("%d",&nr);
            printf("Podaj liczbe ktora chcesz dodac: ");
            scanf("%d",&element);
            if (nr == 1){
               DodajKoniec(&l,element);
            }else{
               DodajKoniec(&k,element);
            }
            break;


            case 3:
            printf("Lista nr 1: ");
            Wyswietl(l);
            printf("\n");
            printf("Lista nr 2: ");
            Wyswietl(k);
            printf("\n");
            break;

            case 4:
            printf("Z jakiej listy chcesz usunac element: (1) (2): ");
            scanf("%d",&nr);
            if (nr == 1){
               UsunPierwszy(&l);
               printf("\n");
            }else{
               UsunPierwszy(&k);
               printf("\n");
            }
            break;

            case 5:
            printf("Z jakiej listy chcesz usunac element: (1) (2): ");
            scanf("%d",&nr);
            if (nr == 1){
               UsunOstatni(&l);
               printf("\n");
            }else{
               UsunOstatni(&k);
               printf("\n");
            }
            break;


            case 6:
            printf("Jaka liste chcesz wyswietlic od tylu? (1) (2): ");
            scanf("%d",&nr);
            if (nr == 1){
               WyswietlodKonca(&l);
               printf("\n");
            }else{
               WyswietlodKonca(&k);
               printf("\n");
            }
            break;


            case 7:
            wyjscie = 1;
            break;

            case 8:
            printf("Jaka liste chcesz wyszukac? (1) (2): ");
            scanf("%d",&nr);
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            if(nr == 1){
                p=znajdz(&l,element);   
                if(*p != NULL){
                    printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p, (*p)->klucz);
                }
                else{
                    printf("Nie ma takiego elementu na liscie.");
                }
            }else{
               p=znajdz(&k,element);   
                if(*p != NULL){
                    printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p, (*p)->klucz);
                }
                else{
                    printf("Nie ma takiego elementu na liscie.");
                }

            }
            break;

            case 9:
            printf("Z jakiej listy chcesz usunac element? (1) (2): ");
            scanf("%d",&nr);
            printf("Element o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            if (nr == 1){
               ZnajdziUsun(&l,element);
               printf("\n");
            }else{
               ZnajdziUsun(&k,element);
               printf("\n");
            }
            break;


            case 10:
            printf("Do jakiej listy chcesz dodac element? (1) (2): ");
            scanf("%d",&nr);
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac przed %d?: ", element);
            scanf("%d",&element2);

            if (nr == 1){
               dodaj_przed(&l,element,element2);
               printf("\n");
            }else{
               dodaj_przed(&k,element,element2);
               printf("\n");
            }
            break;

            case 11:

            printf("Do jakiej listy chcesz dodac element? (1) (2): ");
            scanf("%d",&nr);
            printf("Jaki element chcesz wyszukac?: ");
            scanf("%d",&element);
            printf("Jaki element chcesz dodac za %d?: ", element);
            scanf("%d",&element2);

            if (nr == 1){
               dodaj_za(&l,element,element2);
               printf("\n");
            }else{
               dodaj_za(&k,element,element2);
               printf("\n");
            }
            break;

            case 12:
            printf("Z jakiej listy chcesz usunac elementy? (1) (2): ");
            scanf("%d",&nr);
            printf("Elementy o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            if (nr == 1){
               UsunWszystkie(&l,element);
               printf("\n");
            }else{
               UsunWszystkie(&k,element);
               printf("\n");
            }
            break;

            case 13:
            printf("Z jakiej listy chcesz usunac elementy? (1) (2): ");
            scanf("%d",&nr);
            printf("Elementy o jakiej wartosci chcesz usunac?: ");
            scanf("%d",&element);
            if (nr == 1){
               UsunWszystkieR(&l,element);
               printf("\n");
            }else{
               UsunWszystkieR(&k,element);
               printf("\n");
            }
            break;

            case 14:
            printf("Ktora liste chcesz sprawdzic? (1) (2): ");
            scanf("%d",&nr);
            if (nr == 1){
               MostCommonElement(&l);
               printf("\n");
            }else{
               MostCommonElement(&k);
               printf("\n");
            }
            break;
            
            case 15:
            printf("Ktora liste chcesz sprawdzic? (1) (2): ");
            scanf("%d",&nr);
            printf("Jaka wartosc ma byc dzielnikiem?: ");
            scanf("%d",&element);
            if (nr == 1){
               usunniepodz(&l,element);
               printf("\n");
            }else{
               usunniepodz(&k,element);
               printf("\n");
            }
            break;
            

            default :
            printf("Nieznana operacja.\n" );

        }
  
    }while(wyjscie == 0);
   
    return 0;
}