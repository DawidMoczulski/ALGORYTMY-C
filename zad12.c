#include<stdio.h>
#include<stdlib.h>


struct el{
    
    int klucz;
    struct el *prev;
    struct el *nast;
};

typedef struct el elListy;
typedef elListy *lista;

void Wyswietl(lista l){

    lista el = l;
    lista r = l;
    if(el == NULL){
       printf("Lista jest pusta\n");
    }
    else{
       printf(" %d ", el->klucz);
       printf("->");
       el = el->nast; 
    }  
    while(el != r){
        
        printf(" %d ", el->klucz);
        printf("->");
        el = el->nast;
    }

}
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

void WyswietlodKonca(lista *l){
  if (*l == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }
    lista q = *l;
    lista current = *l;
    lista prev = NULL;

    while (current->nast != q) {
        lista next = current->nast;
        current->nast = prev;
        prev = current;
        current = next;
    }

    current->nast = prev;
    *l = current;

    while (current != NULL) {
        printf(" %d ", current->klucz);
        printf("->");
        current = current->nast;
    }

    printf("\n");
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


void DodajPoPierwszym(lista *l, int y) {
    lista q = malloc(sizeof(elListy));

    if (q == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    q->klucz = y;

    if (*l == NULL) {
        q->nast = q;
        *l = q;
    } else {
        q->nast = (*l)->nast;
        (*l)->nast = q;
    }
}

void DodajPoczatek(lista *l, int y) {
     lista q = malloc(sizeof(elListy));

    if (q == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    q->klucz = y;

    if (*l == NULL) {
        q->nast = q;
        *l = q;
    } else {
        lista aktualny = *l;
        while (aktualny->nast != *l) {
            aktualny = aktualny->nast;  // Przechodzimy do ostatniego elementu
        }
        q->nast = *l;  // Ustawiamy 'nast' nowego elementu na obecny pierwszy element
        *l = q;  // Nowy element staje się pierwszym elementem
        aktualny->nast = q;  // Ustanawiamy połączenie z ostatnim elementem, tworząc cykliczną strukturę
    }
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


void DodajKoniec(lista *l, int y){
    
    lista q = malloc(sizeof(elListy));

    if (q == NULL) {
        printf("Blad alokacji pamieci\n");
        exit(EXIT_FAILURE);
    }
    q->klucz = y;

    if (*l == NULL) {
        q->nast = q;
        *l = q;
    } else {
        lista r = *l;  // Zaczynamy od pierwszego elementu
        while (r->nast != *l) {
            r = r->nast;  // Przesuwamy się do kolejnego elementu
        }
        r->nast = q;  // Teraz r wskazuje na ostatni element, ustawiamy jego 'nast' na nowy element
        q->nast = *l;  // Ustawiamy 'nast' nowego elementu na pierwszy element, tworząc cykliczną strukturę
    }
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


void UsunPierwszy(lista *l) {
    lista temp;
    if (*l == NULL) {
        printf("Lista jest pusta. Nic nie usunieto.\n");
        return;
    }
    temp = *l;
    if ((*l)->nast == *l) {  // Jeśli to jedyny element na liście
        free(temp);
        *l = NULL;
    } else {
        lista ostatni = *l;
        while (ostatni->nast != *l) {
            ostatni = ostatni->nast;  // Przesuwamy się do ostatniego elementu
        }
        ostatni->nast = (*l)->nast;  // Ustawiamy 'nast' ostatniego elementu na drugi element, tworząc cykliczną strukturę
        *l = (*l)->nast;  // Przesuwamy wskaźnik początkowy na drugi element
        free(temp);
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


void UsunOstatni(lista *l){

    lista r;
    lista q;
    if (*l == NULL) {
        printf("Lista jest pusta. Nic nie usunieto.\n");
    }
    r = *l;
    if (r->nast == r) {  // Jeśli to jedyny element na liście
        free(r);
        *l = NULL;
    } else {
        while (r->nast != *l) {
            q = r;
            r = r->nast;  // Przesuwamy się do kolejnego elementu
        }
        free(r);
        q->nast = *l;  // Ustawiamy 'nast' nowego elementu na pierwszy element, tworząc cykliczną strukturę
        
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


void ZnajdziUsun(lista *l, int y){
    lista* q = znajdz(l,y);
    if(*q != NULL){
        UsunPierwszy(&(*q)->nast);
    }
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

void dodaj_przed(lista *l, int y, int z)
{
    lista* q = znajdz(l,y);
    if(q != NULL)  DodajPoPierwszym(q,z);

}
void dodaj_przedDwuKier(lista *l, int y, int z)
{

    lista* q = znajdzDwuKier(l,y);
    if(q != NULL)  DodajPoczatekDwuKier(q,z);

}

void dodaj_za(lista *l, int y, int z){

    lista* q = znajdz(l,y);
    
    q = &((*q)->nast);
    if(q != NULL){
        DodajPoPierwszym(q,z);
    }

}
void dodaj_zaDwuKier(lista *l, int y, int z){

    lista* q = znajdzDwuKier(l,y);

    if(q != NULL){
        DodajPoczatekDwuKier(&(*q)->nast,z);
    }
}

void delete_repeats(lista* l, lista* q) {
    if (*l == NULL || *q == NULL) {
        return;
    }

    lista el = *l;
    lista eq = *q;

    if ((*l)->nast == *l) {
        if ((*q)->klucz == (*l)->klucz) {
            UsunPierwszy(l);
        }
        return;
    }

    lista origL = *l;
    lista origQ = *q;

    do {
        lista tempQ = eq;
        do {
            if (tempQ->klucz == (*l)->klucz) {
                UsunPierwszy(l);
                origL = *l;
                eq = origQ;
                break;
            }
            tempQ = tempQ->nast;
        } while (tempQ != eq);
        *l = (*l)->nast;
    } while (*l != origL);
}


int main()
{
    lista l=NULL;
    lista k=NULL;
    lista a=NULL;
    lista b=NULL;
    lista* p;
    lista* pom;
    int wyjscie = 0;
    int exit1 = 0;
    int exit2 = 0;
    int wybor,nr,wart;
    
    int x, element,element2, nowy_el;
    FILE* plik;
    
    do{
        printf("\n--  Nieposortowane Listy Cykliczne  --\n\n");
        printf("Wybierz czy chcesz dzialac na liscie jednokierunkowej czy dwukierunkowej.\n");
        printf("Jednokierunkowa: (1) ,  Dwukierunkowa: (2) , Wyjdz z programu (0) : ");
        scanf("%d",&wart);

        switch(wart){

            case 1:

            do{

                exit1 = 0;
                printf("\n--  Listy Jednokierunkowe Cykliczne  --\n\n");
                printf("1. Dodaj element na poczatek listy\n");
                printf("2. Dodaj element na koniec listy\n");
                printf("3. Wyswietl listy\n");
                printf("4. Usun pierwszy element listy\n");
                printf("5. Usun ostatni element listy\n");
                printf("6. Wyswietl liste od tylu\n");
                printf("7. Wyszukaj element z listy.\n");
                printf("8. Usun z listy element o wyszukanej wartosci.\n");
                printf("9. Dodaj element przed wyszukanym elementem.\n");
                printf("10. Dodaj element za wyszukanym elementem.\n");
                printf("11. Usun z pierwszej listy wartosci wystepujace w drugiej liscie.\n");
                printf("0. Wyjdz z programu.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);

                switch(wybor){
                    
                            
                    case 0:
                    exit1 = 1;
                    break;

                    case 1:
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    printf("Do jakiej listy chcesz dodac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      DodajPoczatek(&l,element);
                    }
                    else{
                      DodajPoczatek(&k,element); 
                    }
                    break;
        
                    case 2:
                    printf("Podaj liczbe ktora chcesz dodac: ");
                    scanf("%d",&element);
                    printf("Do jakiej listy chcesz dodac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      DodajKoniec(&l,element);
                    }
                    else{
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
                    printf("Z jakiej listy chcesz usunac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      UsunPierwszy(&l);
                    }
                    else{
                      UsunPierwszy(&k); 
                    }
                    printf("\n");
                    break;
        
                    case 5:
                    printf("Z jakiej listy chcesz usunac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      UsunOstatni(&l);
                    }
                    else{
                      UsunOstatni(&k); 
                    }
                    printf("\n");
                    break;
        
        
                    case 6:
                    printf("Lista nr 1: ");
                    WyswietlodKonca(&l);
                    printf("Lista nr 2: ");
                    WyswietlodKonca(&k);
                    printf("\n");
                    break;
        
        
                    case 7:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    printf("Z jakiej listy chcesz wyszukac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                       p=znajdz(&l,element);
                    }
                    else{
                       p=znajdz(&k,element); 
                    }
                    if(*p != NULL){
                        printf("Jest taki element o wartosci %d, jego adres wynosi %p : %d \n",(*p)->nast->klucz, p ,(*p)->nast->klucz);
                    } 
                    else{
                        printf("Nie ma takiego elementu na liscie.");
                    }  
                    break;
        
                    case 8:
                    printf("Element o jakiej wartosci chcesz usunac?: ");
                    scanf("%d",&element);
                    printf("Z jakiej listy chcesz usunac element? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                      ZnajdziUsun(&l,element);
                    }
                    else{
                      ZnajdziUsun(&k,element);
                    }
                    printf("\n");
                    break;
        
        
                    case 9:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    printf("Jaki element chcesz dodac przed %d?: ", element);
                    scanf("%d",&element2);
                    printf("Na jakiej liscie chcesz wykonac operacje? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                        dodaj_przed(&l,element,element2);
                    }else{
                        dodaj_przed(&k,element,element2);
                    }              
                    printf("\n");
                    break;
        
                    case 10:
                    printf("Jaki element chcesz wyszukac?: ");
                    scanf("%d",&element);
                    printf("Jaki element chcesz dodac za %d?: ", element);
                    scanf("%d",&element2);
                    printf("Na jakiej liscie chcesz wykonac operacje? (1) (2): ");
                    scanf("%d",&nr);
                    if(nr == 1){
                        dodaj_za(&l,element,element2);
                    }else{
                        dodaj_za(&k,element,element2);
                    }          
                    printf("\n");
                    break;


                    case 11:
                    delete_repeats(&l,&k);
                    printf("\n");
                    break;


        
                    default :
                    printf("Nieznana operacja.\n" );
                }

            }while(exit1 == 0);
            break;

            case 2:

             do{
                exit2 = 0;
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
                printf("0. Wyjdz z programu.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);

                switch(wybor){
                           
                    case 0:
                    exit2 = 1;
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


