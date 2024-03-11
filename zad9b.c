#include<stdio.h>
#include<stdlib.h>

struct el
{
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
void WyswietlWart(lista l){

    lista el = l;
    if(el->klucz == INT_MAX)  printf("Lista jest pusta\n");
    while(el->klucz != INT_MAX){
        printf(" %d ", el->klucz);
        printf("<->");
        el = el->nast;
    }
}
void WyswietlodKoncaWart(lista *l){

    if((*l)->klucz == INT_MAX){
        return;
    }
    WyswietlodKoncaWart(&((*l)->nast));
    printf("%d ", (*l)->klucz);
    printf("<->");
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

void DodajNowyElWart(lista *l, int y){
    
    if ((*l)->klucz == INT_MAX) {
        //printf("(*l)->klucz: %d ",(*l)->klucz );
        DodajPoczatek(l, y);
        return;
    }
    while ( ((*l)->klucz != INT_MAX) && ((*l)->klucz <= y) ) {
        //printf("(*l)->klucz: %d \n", (*l)->klucz);
         l = &((*l)->nast); 
    }
    DodajPoczatek(l,y);
}

void DodajNowyEl(lista *l, int y){
    if(*l == NULL){
       DodajPoczatek(l,y); 
       return;
    }
    while( (*l != NULL) && ((*l)->klucz <= y) ){
          l = &((*l)->nast);
   }
   DodajPoczatek(l,y);
}

void PobierzPierwszy(lista *l){
    
    if(*l == NULL){
      printf("Niestety, wyglada na to ze lista jest pusta.");
      return;
    }
    printf("Pierwszy element pobrany z listy wynosi: %d ", (*l)->klucz);
    printf("Jego adres wynosi: %p ", (*l));
}

void PobierzPierwszyWart(lista *l){
    
    if((*l)->klucz == INT_MAX){
      printf("Niestety, wyglada na to ze lista jest pusta.");
      return;
    }
    else{
     printf("Pierwszy element pobrany z listy wynosi: %d ", (*l)->klucz);
     printf("Jego adres wynosi: %p ", (*l));
    }
}

void PobierzOstatni(lista *l){

    while(*(&(*l)->nast) != NULL){
      l = &((*l)->nast);
    }
    printf("Ostatni element pobrany z listy wynosi: %d ", (*l)->klucz);
    printf("Jego adres wynosi: %p ", (*l));
}

void PobierzOstatniWart(lista *l){

    while((*(&(*l)->nast))->klucz != INT_MAX){
      l = &((*l)->nast);
    }
    printf("Ostatni element pobrany z listy wynosi: %d ", (*l)->klucz);
    printf("Jego adres wynosi: %p ", (*l));
}

void UsunPierwszy(lista *l){
    
    lista q = *l;
    if(q != NULL){
        *l = q->nast;
        if(q->prev != NULL){
          (*l)->prev = q->prev;
          q->prev->nast = *l;
        }
    }
    free(q);
}

lista* znajdz(lista *l, int y){

    while( (*l != NULL) && ((*l)->klucz != y) ){
       l = &((*l)->nast);
    } 
    return l;
}

lista* znajdzWart(lista *l, int y){

    while( ( (*(&(*l)->nast))->klucz != INT_MAX) && ((*l)->klucz != y)  ){
    printf("(*(&(*l)->nast))->klucz: %d, (*l)->klucz: %d \n", (*(&(*l)->nast))->klucz,(*l)->klucz );
       l = &((*l)->nast);
    } 
    return l;
}

void ZnajdziUsun(lista *l, int y){
    lista* q = znajdz(l, y);
    if(*q){
        UsunPierwszy(q);
    }
}

void ZnajdziUsunWart(lista *l, int y){
    lista *q = znajdzWart(l, y);
    
    if ( (*q)->klucz == y) {
        UsunPierwszy(q);
    } else {
        printf("(*q)->nast->klucz: %d \n", (*q)->nast->klucz );
        printf("Brak elementu %d do usuniecia.\n", y);
    }
}

void stworzListeZWartownikiem(lista *l){
    lista wartownik = malloc(sizeof(elListy));
    wartownik->klucz = INT_MAX;
    wartownik->nast = *l;
    wartownik->prev = NULL;
    *l = wartownik;  
}

int main(){
     
    lista l=NULL;
    lista k=NULL;
    lista a=NULL;
    lista b=NULL;
    stworzListeZWartownikiem(&a);
    stworzListeZWartownikiem(&b);
    lista* p;
    int wyjscie = 0;
    int exit1 = 0;
    int exit2 = 0;
    int wybor,nr,wart;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n\n--  Lista Dwukierunkowa Posortowana  --\n\n");
        printf("Wybierz czy chcesz dzialac na liscie z wartownikiem czy bez wartownika.\n");
        printf("Z wartownikiem: (1) ,  Bez wartownika (2) , Wyjdz z programu (0) : ");
        scanf("%d",&wart);

        switch(wart){

            case 1:

            do{

                exit1 = 0;
                printf("\n");
                printf("1. Dodaj nowy element do listy\n");
                printf("2. Wyswietl listy\n");
                printf("3. Pobierz i wyswietl pierwszy element listy\n");
                printf("4. Pobierz i wyswietl ostatni element listy\n");
                printf("5. Wyswietl liste od tylu\n");
                printf("6. Wyszukaj element z listy.\n");    
                printf("7. Usun z listy element o wyszukanej wartosci.\n");  
                printf("0. Wstecz.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);

                switch(wybor){


                    case 0:
                    exit1 = 1;
                    break;

                    case 1:
                    printf("Do jakiej listy chcesz dodac element: (1) (2): ");
                    scanf("%d",&nr);
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    if (nr == 1){
                    DodajNowyElWart(&a,element);
                    }else{
                    DodajNowyElWart(&b,element);
                    }
                    printf("\n");
                    break;

                    case 2:
                    printf("Lista nr 1: ");
                    WyswietlWart(a);
                    printf("\n");
                    printf("Lista nr 2: ");
                    WyswietlWart(b);
                    printf("\n");
                    break;

                    case 3:
                    printf("Z jakiej listy chcesz pobrac element: (1) (2): ");
                    scanf("%d",&nr);
                    if (nr == 1){
                    PobierzPierwszyWart(&a);
                    printf("\n");
                    }else{
                    PobierzPierwszyWart(&b);
                    printf("\n");
                    }
                    break;

                    case 4:
                    printf("Z jakiej listy chcesz pobrac element: (1) (2): ");
                    scanf("%d",&nr);
                    if (nr == 1){
                    PobierzOstatniWart(&a);
                    printf("\n");
                    }else{
                    PobierzOstatniWart(&b);
                    printf("\n");
                    }
                    break;


                    case 5:
                    printf("Jaka liste chcesz wyswietlic od tylu? (1) (2): ");
                    scanf("%d",&nr);
                    if (nr == 1){
                    WyswietlodKoncaWart(&a);
                    printf("\n");
                    }else{
                    WyswietlodKoncaWart(&b);
                    printf("\n");
                    }
                    break;

                    case 6:
                    printf("Jaka liste chcesz wyszukac? (1) (2): ");
                    scanf("%d",&nr);
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    if(nr == 1){
                        p=znajdzWart(&a,element);   
                        if( (*p)->nast->klucz != INT_MAX ){
                            printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p, (*p)->klucz);
                        }
                        else{
                            printf("Nie ma takiego elementu na liscie.");
                        }
                    }else{
                    p=znajdzWart(&b,element);   
                        if( (*p)->nast->klucz != INT_MAX ){
                            printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p, (*p)->klucz);
                        }
                        else{
                            printf("Nie ma takiego elementu na liscie.");
                        }

                    }
                    printf("\n");
                    break;

                    case 7:
                    printf("Z jakiej listy chcesz usunac element? (1) (2): ");
                    scanf("%d",&nr);
                    printf("Element o jakiej wartosci chcesz usunac?: ");
                    scanf("%d",&element);
                    if (nr == 1){
                    ZnajdziUsunWart(&a,element);
                    printf("\n");
                    }else{
                    ZnajdziUsunWart(&b,element);
                    printf("\n");
                    }
                    break;


                    default :
                    printf("Nieznana operacja.\n" );

                }

            }while(exit1 == 0);
            break;

            case 2:

             do{
                exit2 = 0;
                printf("\n");
                printf("1. Dodaj nowy element do listy\n"); 
                printf("2. Wyswietl listy\n");
                printf("3. Pobierz i wyswietl pierwszy element listy\n");
                printf("4. Pobierz i wyswietl ostatni element listy\n");
                printf("5. Wyswietl liste od tylu\n");
                printf("6. Wyszukaj element z listy.\n");    
                printf("7. Usun z listy element o wyszukanej wartosci.\n");  
                printf("0. Wstecz.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);

                switch(wybor){


                    case 0:
                    exit2 = 1;
                    break;

                    case 1:
                    printf("Do jakiej listy chcesz dodac element: (1) (2): ");
                    scanf("%d",&nr);
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    if (nr == 1){
                    DodajNowyEl(&l,element);
                    }else{
                    DodajNowyEl(&k,element);
                    }
                    break;

                    case 2:
                    printf("Lista nr 1: ");
                    Wyswietl(l);
                    printf("\n");
                    printf("Lista nr 2: ");
                    Wyswietl(k);
                    printf("\n");
                    break;

                    case 3:
                    printf("Z jakiej listy chcesz pobrac element: (1) (2): ");
                    scanf("%d",&nr);
                    if (nr == 1){
                    PobierzPierwszy(&l);
                    printf("\n");
                    }else{
                    PobierzPierwszy(&k);
                    printf("\n");
                    }
                    break;

                    case 4:
                    printf("Z jakiej listy chcesz pobrac element: (1) (2): ");
                    scanf("%d",&nr);
                    if (nr == 1){
                    PobierzOstatni(&l);
                    printf("\n");
                    }else{
                    PobierzOstatni(&k);
                    printf("\n");
                    }
                    break;


                    case 5:
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

                    case 6:
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

                    case 7:
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

            
                   default :
                   printf("Nieznana operacja.\n" );

                }

             }while(exit2 == 0);
             break;


                case 0:
                wyjscie = 1;
                break;
                
                default :
                printf("Niepoprawny numer.\n" );
        }
  
    }while(wyjscie == 0);
   
    return 0;
}