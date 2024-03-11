#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define N 1000
#define M 100

void bubble_sort(int T[], int n, int *comparisonCounter, int *substitutionCounter)
{  
	 int i,j,x;
	 for (j = n - 1; j > 0; j--){
		for (i=0;  i < j; i++){
             (*comparisonCounter)++;
			 if (T[i] > T[i+1]){
			        	x = T[i];
                T[i] = T[i+1];
                T[i+1] = x;
                (*substitutionCounter)+=3; 
	          }
        }
     }

}

void SortowaniePrzezWstawianie(int a[], int n, int *comparisonCounter, int *substitutionCounter) {
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int j;

        (*substitutionCounter)++;  // Inkrementuj licznik podstawień

        for (j = i - 1; j >= 0 && x < a[j]; j--) {
            (*comparisonCounter)++;  // Inkrementuj licznik porównań
            a[j + 1] = a[j];
            (*substitutionCounter)++;  // Inkrementuj licznik podstawień
        }

        a[j + 1] = x;
        (*substitutionCounter)++;  // Inkrementuj licznik podstawień
    }
}

int Partition(int A[], int p, int r, int *comparisonCounter, int *substitutionCounter) {
    int x, y, i, j;
    x = A[r];
    i = p - 1;

    for (j = p; j <= r - 1; j++) {
        (*comparisonCounter)++;  // Inkrementuj licznik porównań
        if (A[j] <= x) {
            i++;
            y = A[i];
            A[i] = A[j];
            A[j] = y;
            (*substitutionCounter) += 3;  // Inkrementuj licznik podstawień (3 dla zamiany)
        }
    }

    y = A[i + 1];
    A[i + 1] = A[r];
    A[r] = y;
    (*substitutionCounter) += 3;  // Inkrementuj licznik podstawień (3 dla zamiany)
    
    return i + 1;
}

void QSort(int A[], int p, int r, int *comparisonCounter, int *substitutionCounter) {
    int q;
    if (p < r) {
        q = Partition(A, p, r, comparisonCounter, substitutionCounter);
        QSort(A, p, q - 1, comparisonCounter, substitutionCounter);
        QSort(A, q + 1, r, comparisonCounter, substitutionCounter);
    }
}

void sortShell(int *tab, int n, int *comparisonCounter, int *substitutionCounter) {
    int przerwa = n / 2;
    while (przerwa >= 1) {
        for (int i = przerwa; i < n; i += 1) {
            int temp = tab[i];
            int j;
            for (j = i; j >= przerwa && tab[j - przerwa] > temp; j -= przerwa) {
                (*comparisonCounter)++;  // Inkrementuj licznik porównań
                tab[j] = tab[j - przerwa];
                (*substitutionCounter)++;  // Inkrementuj licznik podstawień
            }
            tab[j] = temp;
            (*substitutionCounter)++;  // Inkrementuj licznik podstawień
        }
        przerwa /= 2;
    }
}

void print_table(int T[], int n){
    for(int i=0; i<n; i++){
        printf("%d ",T[i]);
    }
    printf("\n");
}

void Losowanie(int T[], int n){
   
   for(int i=0; i<n; i++){
      T[i] = 1 + rand() % 50;
   }
}

void SkopiujTablice(int T[], int B[], int n){

    for(int i=0; i<n; i++){
      B[i] = T[i];
    }
}


int main(){

  srand(time(NULL));
  long long averageSub1 = 0, averageSub2 = 0, averageSub3 = 0, averageSub4 = 0;
  long long averageCom1 = 0, averageCom2 = 0, averageCom3 = 0, averageCom4 = 0;
  int comparisonCounter1 = 0;
  int substitutionCounter1 = 0;
  int comparisonCounter2 = 0;
  int substitutionCounter2 = 0;
  int comparisonCounter3 = 0;
  int substitutionCounter3 = 0;
  int comparisonCounter4 = 0;
  int substitutionCounter4 = 0;
  int klucz = 0;
  int countMinCom1=0,countMinCom2=0,countMinCom3=0,countMinCom4=0;
  int countMaxCom1=0,countMaxCom2=0,countMaxCom3=0,countMaxCom4=0;
  int countMinSub1=0,countMinSub2=0,countMinSub3=0,countMinSub4=0;
  int countMaxSub1=0,countMaxSub2=0,countMaxSub3=0,countMaxSub4=0;

  int mainTab[N];
  int tab1[N];
  int tab2[N];
  int tab3[N];
  int tab4[N];

 for(int i = 0; i < M; i++){
 
    Losowanie(mainTab,N);
    SkopiujTablice(mainTab,tab1,N);
    SkopiujTablice(mainTab,tab2,N);
    SkopiujTablice(mainTab,tab3,N);
    SkopiujTablice(mainTab,tab4,N);
    bubble_sort(tab1,N, &comparisonCounter1,&substitutionCounter1);
    SortowaniePrzezWstawianie(tab2,N, &comparisonCounter2,&substitutionCounter2);
    sortShell(tab3,N, &comparisonCounter3,&substitutionCounter3);
    QSort(tab4,0,N,&comparisonCounter4,&substitutionCounter4);
    if(klucz == 0){
      countMinCom1 = comparisonCounter1;
      countMinCom2 = comparisonCounter2;
      countMinCom3 = comparisonCounter3;
      countMinCom4 = comparisonCounter4;
      countMinSub1 = substitutionCounter1;
      countMinSub2 = substitutionCounter2;
      countMinSub3 = substitutionCounter3;
      countMinSub4 = substitutionCounter4;
      klucz = 1;
    }

    averageCom1 = averageCom1 + comparisonCounter1;
    averageCom2 = averageCom2 + comparisonCounter2;
    averageCom3 = averageCom3 + comparisonCounter3;
    averageCom4 = averageCom4 + comparisonCounter4;
    averageSub1 = averageSub1 + substitutionCounter1;
    averageSub2 = averageSub2 + substitutionCounter2;
    averageSub3 = averageSub3 + substitutionCounter3;
    averageSub4 = averageSub4 + substitutionCounter4;


    if(substitutionCounter1 > countMaxSub1){
      countMaxSub1 = substitutionCounter1; 
    }
    if(substitutionCounter2 > countMaxSub2){
      countMaxSub2 = substitutionCounter2; 
    }
    if(substitutionCounter3 > countMaxSub3){
      countMaxSub3 = substitutionCounter3; 
    }
    if(substitutionCounter4 > countMaxSub4){
      countMaxSub4 = substitutionCounter4; 
    }

    if(substitutionCounter1 < countMinSub1){
      countMinSub1 = substitutionCounter1; 
    }
    if(substitutionCounter2 < countMinSub2){
      countMinSub2 = substitutionCounter2; 
    }
    if(substitutionCounter3 < countMinSub3){
      countMinSub3 = substitutionCounter3; 
    }
    if(substitutionCounter4 < countMinSub4){
      countMinSub4 = substitutionCounter4; 
    }
    //////////////////////////////////////////////////////////////////////////////

    if(comparisonCounter1 > countMaxCom1){
      countMaxCom1 = comparisonCounter1; 
    }
    if(comparisonCounter2 > countMaxCom2){
      countMaxCom2 = comparisonCounter2; 
    }
    if(comparisonCounter3 > countMaxCom3){
      countMaxCom3 = comparisonCounter3; 
    }
    if(comparisonCounter4 > countMaxCom4){
      countMaxCom4 = comparisonCounter4; 
    }

    if(comparisonCounter1 < countMinCom1){
      countMinCom1 = comparisonCounter1; 
    }
    if(comparisonCounter2 < countMinCom2){
      countMinCom2 = comparisonCounter2; 
    }
    if(comparisonCounter3 < countMinCom3){
      countMinCom3 = comparisonCounter3; 
    }
    if(comparisonCounter4 < countMinCom4){
      countMinCom4 = comparisonCounter4; 
    }

 }


averageCom1 = averageCom1 / M;
averageCom2 = averageCom2 / M;
averageCom3 = averageCom3 / M;
averageCom4 = averageCom4 / M;
averageSub1 = averageSub1 / M;
averageSub2 = averageSub2 / M;
averageSub3 = averageSub3 / M;
averageSub4 = averageSub4 / M;

  printf("Wyniki dla sortowania babelkowego: \n");
  printf("Maksymalna liczba wykonanych porownan: %d \n", countMaxCom1);
  printf("Minimalna liczba wykonanych porownan: %d \n", countMinCom1);
  printf("Maksymalna liczba wykonanych podstawien: %d \n", countMaxSub1);
  printf("Minimalna liczba wykonanych podstawien: %d \n", countMinSub1);
  printf("Srednia liczba wykonanych porownan: %d \n",averageCom1);
  printf("Srednia liczba wykonanych podstawien: %d \n",averageSub1);
  printf("\n");
  printf("Wyniki dla sortowania przez wstawianie: \n");
  printf("Maksymalna liczba wykonanych porownan: %d \n", countMaxCom2);
  printf("Minimalna liczba wykonanych porownan: %d \n", countMinCom2);
  printf("Maksymalna liczba wykonanych podstawien: %d \n", countMaxSub2);
  printf("Minimalna liczba wykonanych podstawien: %d \n", countMinSub2);
  printf("Srednia liczba wykonanych porownan: %d \n",averageCom2);
  printf("Srednia liczba wykonanych podstawien: %d \n",averageSub2);
  printf("\n");
  printf("Wyniki dla sortowania metoda Shella: \n");
  printf("Maksymalna liczba wykonanych porownan: %d \n", countMaxCom3);
  printf("Minimalna liczba wykonanych porownan: %d \n", countMinCom3);
  printf("Maksymalna liczba wykonanych podstawien: %d \n", countMaxSub3);
  printf("Minimalna liczba wykonanych podstawien: %d \n", countMinSub3);
  printf("Srednia liczba wykonanych porownan: %d \n",averageCom3);
  printf("Srednia liczba wykonanych podstawien: %d \n",averageSub3);
  printf("\n");
  printf("Wyniki dla sortowania Quick Sort: \n");
  printf("Maksymalna liczba wykonanych porownan: %d \n", countMaxCom4);
  printf("Minimalna liczba wykonanych porownan: %d \n", countMinCom4);
  printf("Maksymalna liczba wykonanych podstawien: %d \n", countMaxSub4);
  printf("Minimalna liczba wykonanych podstawien: %d \n", countMinSub4);
  printf("Srednia liczba wykonanych porownan: %d \n",averageCom4);
  printf("Srednia liczba wykonanych podstawien: %d \n",averageSub4);
 
 return 0;

}