#include<stdio.h>
#include<stdlib.h>


struct el{
    
    int klucz;
    struct el *prev;
    struct el *nast;
};

typedef struct el elListy;
typedef elListy *lista;

void WyswietlDwuKier(lista l){

    lista el = l;
    lista r = l;
    if(el == NULL){
       printf("Lista jest pusta\n");
    }
    else{
       printf(" %d ", el->klucz);
       printf("<->");
       el = el->nast; 
    }  
    while(el != r){
        
        printf(" %d ", el->klucz);
        printf("<->");
        el = el->nast;
    }
}

void WyswietlodKoncaDwuKier(lista *l){
     if (*l == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }
    lista last = (*l)->prev; 

    lista actual = last;
    do {
        printf("%d <-> ", actual->klucz);
        actual = actual->prev;
    } while (actual != last);
    printf("\n");
}

void DodajPoczatekDwuKier(lista *l, int y) {
    lista q = malloc(sizeof(elListy));

    if (q == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    q->klucz = y;

    if (*l == NULL) {
        q->nast = q;
        q->prev = q;
    } else {
        q->nast = *l;
        q->prev = (*l)->prev;
        (*l)->prev->nast = q;
        (*l)->prev = q;
    }
    *l = q;
}

void DodajKoniecDwuKier(lista *l, int y){
    
    lista q = malloc(sizeof(elListy));

    if (q == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    q->klucz = y;

    if (*l == NULL) {
        q->nast = q;
        q->prev = q;
        *l = q;
    } else {
        q->nast = *l;
        q->prev = (*l)->prev;
        (*l)->prev->nast = q;
        (*l)->prev = q;
    }
}

void UsunPierwszyDwuKier(lista *l) {
    lista r;
    if (*l == NULL) {
        printf("Lista jest pusta. Nic nie usunieto.\n");
    }
    r = *l;
    if (r->nast == r) {  // Jeśli to jedyny element na liście
        free(r);
        *l = NULL;
    } else {
        r->prev->nast = r->nast;
        r->nast->prev = r->prev;
        *l = r->nast;  
        free(r);
    }
}

void UsunOstatniDwuKier(lista *l){

    lista q;
    if (*l == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }
    if ((*l)->nast == *l) {  // Lista zawiera tylko jeden element
        printf("Usuwam ostatni element: %d\n", (*l)->klucz);
        free(*l);
        *l = NULL;
    } else {
        q = (*l)->prev;
        UsunPierwszyDwuKier(&q);
    }
}

lista* znajdz(lista *l, int y){
    if (*l != NULL) {
        lista *r = l;
        do {
            if ((*l)->nast->klucz == y) {
                return l;
            }
            l = &(*l)->nast;
        } while ((*l)->nast != *r);
    }
    return NULL;
}

lista* znajdzDwuKier(lista *l, int y){
    
    if(*l == NULL){
       return l;
    }

    lista r = *l;
    do{
        if ((*l)->klucz == y) {
            return l; 
        }
        l = &((*l)->nast);
    }while(*l != r);

    return NULL;
}

void ZnajdziUsunDwuKier(lista *l, int y)
{
    lista* q = znajdz(l, y);
    int x;
    if (*q) {
         UsunPierwszyDwuKier(q);
        printf("Usunieto element o wartosci %d.\n", x);
    } else {
        printf("Element o wartosci %d nie istnieje na liscie.\n", y);
    } 

}

void dodaj_przedDwuKier(lista *l, int y, int z)
{

    lista* q = znajdzDwuKier(l,y);
    if(q != NULL)  DodajPoczatekDwuKier(q,z);

}

void dodaj_zaDwuKier(lista *l, int y, int z){

    lista* q = znajdzDwuKier(l,y);

    if(q != NULL){
        DodajPoczatekDwuKier(&(*q)->nast,z);
    }
}

void UsuwajKty(lista *l, int k){

    if(*l == NULL){
        printf("Lista jest pusta wiec nic nie usunieto.\n");
    }
    if((*l)->prev == *l){
        printf("Na liscie jest jeden element. Nic nie usunieto.\n");
    }else{
       lista temp;
        while ((*l)->prev != *l) {
            for (int j = 0; j < k; j++) {
                *l = (*l)->nast;
            }
            temp = (*l); 
            UsunPierwszyDwuKier(&temp);
        }
    }
}

int main()
{
    lista l=NULL;
    lista* p;
    lista* pom;
    int wyjscie = 0;
    int exit1 = 0;
    int exit2 = 0;
    int wybor,nr,wart,k;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
             do{
                wyjscie = 0;
                printf("\n--  Lista Dwukierunkowa Cykliczna  --\n\n");
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
                printf("11. Usuwaj z listy co k-ty element az zostanie jeden.\n");
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
                    DodajPoczatekDwuKier(&l,element);
                    break;
        
                    case 2:
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    DodajKoniecDwuKier(&l,element);
                    break;
        
                    case 3:
                    WyswietlDwuKier(l);
                    printf("\n");
                    break;
        
                    case 4:
                    UsunPierwszyDwuKier(&l);
                    printf("\n");
                    break;
        
                    case 5:
                    UsunOstatniDwuKier(&l);
                    printf("\n");
                    break;
        
        
                    case 6:
                    WyswietlodKoncaDwuKier(&l);
                    printf("\n");
                    break;
        
        
                    case 7:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    p=znajdzDwuKier(&l,element);   
                    if(*p != NULL){
                        printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->klucz, p ,(*p)->klucz);
                    } 
                    else{
                        printf("Nie ma takiego elementu na liscie.");
                    }
                    break;
        
                    case 8:
                    printf("Element o jakiej wartosci chcesz usunac?: ");
                    scanf("%d",&element);
                    ZnajdziUsunDwuKier(&l,element);
                    printf("\n");
                    break;
        
        
                    case 9:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    printf("Jaki element chcesz dodac przed %d?: ", element);
                    scanf("%d",&element2);
                    dodaj_przedDwuKier(&l,element,element2);
                    printf("\n");
                    break;
        
                    case 10:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    printf("Jaki element chcesz dodac za %d?: ", element);
                    scanf("%d",&element2);
                    dodaj_zaDwuKier(&l,element,element2);
                    printf("\n");
                    break;


                    case 11:
                    printf("Co ktory element chcesz usuwac?: ");
                    scanf("%d",&k);
                    UsuwajKty(&l,k);
                    break;
        
                    default :
                    printf("Nieznana operacja.\n" );
                }

             }while(wyjscie== 0);

   
    return 0;     
}


