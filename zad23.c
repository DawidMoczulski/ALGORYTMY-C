#include <stdio.h>
#include <stdlib.h>

#define N 1000
#define M 100

typedef struct {
    int comparisons;
    int assignments;
} Counter;

void Losowanie(int T[], int *k, int n){
   
   for(int i = 0; i < n; i++){
      T[i] = 1 + rand() % *k;
   }
}

void countingSort(int arr[], int n, int k, Counter *counter) {
    
    int *count = (int*)malloc((k + 1) * sizeof(int));
    int *output = (int*)malloc(n * sizeof(int));

    // Inicjalizacja tablicy count
    for (int i = 0; i <= k; i++) {
        count[i] = 0;
        
    }
    
    // Zliczanie wystąpień każdej wartości
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
        counter->assignments++; // Zlicz podstawienia
    }

    // Aktualizacja tablicy count o sumy prefiksowe
    for (int i = 1; i <= k; i++) {
        count[i] += count[i - 1];
        counter->assignments++; // Zlicz podstawienia
    }

    // Umieszczanie elementów w tablicy wynikowej
    for (int i = n - 1; i >= 0; i--) {
        int arrValue = arr[i];

        // Sprawdź, czy wartość mieści się w zakresie od 1 do k
        if (arrValue < 1 || arrValue > k) {
        fprintf(stderr, "Blad: Wartosc %d poza zakresem 1 do %d\n", arrValue, k);
        exit(EXIT_FAILURE);
        }
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
        counter->assignments += 2; // Zlicz podstawienia
        counter->comparisons++; // Zlicz porównania
    }

    // Kopiowanie tablicy wynikowej do tablicy wejściowej
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        counter->assignments++; // Zlicz podstawienia
    }

    free(count);
    free(output);

}


void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int n, k;
    Counter counter;
    Counter MainCounter;
    counter.assignments = 0;
    counter.comparisons = 0;
    MainCounter.assignments = 0;
    MainCounter.comparisons = 0;
    int arr[N];

    // printf("Podaj rozmiar tablicy: ");
    // scanf("%d", &n);
    // clearBuffer();

    printf("Podaj maksymalna wartosc k: ");
    scanf("%d", &k);
    clearBuffer();
    //int *arr = (int*)malloc(n * sizeof(int));
    

 for(int i = 0; i < M; i++){

    // printf("Podaj elementy tablicy:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("Podaj element arr[%d]: ", i);
    //     do {
    //      scanf("%d", &arr[i]);
    //      if ((arr[i] < 1) || (arr[i] > k)) {
    //         printf("BLAD: Podaj liczbe w zakresie od 1 do %d.\n", k);
    //         printf("Podaj element arr[%d]: ", i);
    //      }
    //     } while( (arr[i] < 1) || (arr[i] > k) );
    //     printf("\n");
    // }
    counter.assignments = 0;
    counter.comparisons = 0;   

    Losowanie(arr,&k,N);
    countingSort(arr, N, k, &counter);

    MainCounter.assignments += counter.assignments;
    MainCounter.comparisons += counter.comparisons;
   }

    printf("\nIlosc porownan: %d\n", MainCounter.comparisons);
    printf("Ilosc podstawien: %d\n", MainCounter.assignments);
    printf("\n");
    printf("DLA POROWNANIA: \n");
    printf("Wyniki sortowania metoda Shella: \n");
    printf("Liczba wykonanych porownan: 112835 \n");
    printf("Liczba wykonanych podstawien: 456841 \n");
    printf("\n");
    printf("Wyniki sortowania metoda Quick Sort: \n");
    printf("Liczba wykonanych porownan: 510493 \n");
    printf("Liczba wykonanych podstawien: 321832 \n");
    printf("\n");


    // printf("Posortowana tablica:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", arr[i]);
    // }


    return 0;
}
