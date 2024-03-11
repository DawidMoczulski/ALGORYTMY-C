#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define N 1000

void bubble_sort(int T[], int n)
{    int comparisonCounter = 0;
     int substitutionCounter = 0; 
	 int i,j,x;
	 for (j = n - 1; j > 0; j--){
		for (i=0;  i < j; i++){
             comparisonCounter++;
			 if (T[i] > T[i+1]){
				x = T[i];
                T[i] = T[i+1];
                T[i+1] = x;
                substitutionCounter += 3; 
	          }
        }
     }
     printf("Liczba podstawien bubble_sort: %d   ", substitutionCounter);
     printf("Liczba porownan bubble_sort: %d \n", comparisonCounter);
}

void optimized_bubble_sort(int T[], int n)
{
    int i, j, x, k=0;
    int comparisonCounter = 0;
    int substitutionCounter = 0; 
    
    for (j = n - 1; j > 0; j = k) {
        k = 0;  
        for (i = 0; i < j; i++) {
            comparisonCounter++;
            if (T[i] > T[i + 1]) {
                x = T[i];
                T[i] = T[i + 1];
                T[i + 1] = x;
                substitutionCounter += 3;
                k = i;
            }
        }
    }
    printf("Liczba podstawien optimized_bubble_sort: %d   ", substitutionCounter);
    printf("Liczba porownan optimized_bubble_sort: %d \n", comparisonCounter);
}

void better_bubble_sort(int T[], int n) {
    int i, j, x;
    int changes;  // Zmienna, aby śledzić, czy wystąpiła zmiana podczas iteracji
    int comparisonCounter = 0;   // ilosc porownan
    int substitutionCounter = 0; // ilosc podstawien

    for (j = n - 1; j > 0; j--) {
        changes = 0;  // Resetujemy licznik zmian przed każdym przebiegiem pętli

        for (i = 0; i < j; i++) {
            comparisonCounter++;
            if (T[i] > T[i + 1]) {
                x = T[i];
                T[i] = T[i + 1];
                T[i + 1] = x;
                substitutionCounter += 3;
                changes = 1;  // Ustawiamy zmianę na 1, jeżeli wykonano zamianę
            }
        }

        if (changes == 0) {
            // Jeżeli nie wykonano żadnej zmiany, to tablica jest już posortowana
            break;
        }
    }
    printf("Liczba podstawien better_bubble_sort: %d   ", substitutionCounter);
    printf("Liczba porownan better_bubble_sort: %d \n", comparisonCounter);
}


void print_table(int T[], int n){
    for(int i=0; i<n; i++){
        printf("%d ",T[i]);
    }
    printf("\n");
}

void Losowanie(int T[], int n){
   
   for(int i=0; i<n; i++){
      T[i] = 1 + rand() % 27;
   }
}

void SkopiujTablice(int T[], int B[], int n){

    for(int i=0; i<n; i++){
      B[i] = T[i];
    }
}


int main(){

 srand(time(NULL));
 int mainTab[N];
 int tab1[N];
 int tab2[N];
 int tab3[N];
 Losowanie(mainTab,N);
 SkopiujTablice(mainTab,tab1,N);
 SkopiujTablice(mainTab,tab2,N);
 SkopiujTablice(mainTab,tab3,N);

//  printf("Elementy tablicy 1 przed sortowaniem: ");
//  print_table(tab1,N);
//  printf("Elementy tablicy 2 przed sortowaniem: ");
//  print_table(tab2,N);
//  printf("Elementy tablicy 3 przed sortowaniem: ");
//  print_table(tab3,N);

 bubble_sort(tab1,N);
 optimized_bubble_sort(tab2,N);
 better_bubble_sort(tab3,N);

//  printf("Elementy tablicy 1 po sortowaniu: ");
//  print_table(tab1,N);
//  printf("Elementy tablicy 2 po sortowaniu: ");
//  print_table(tab2,N);
//  printf("Elementy tablicy 3 po sortowaniu: ");
//  print_table(tab3,N);

 return 0;
}
