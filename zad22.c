#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

#define N 5

// Funkcja zamieniająca dwa łańcuchy znakowe w tablicy
void swap(char *a, char *b) {
    char temp[50];
    strcpy(temp, a);
    strcpy(a, b);
    strcpy(b, temp);
}

// Funkcja budująca kopiec dla danej tablicy
void heapify(char arr[][50], int n, int i) {
    int largest = i; // Inicjalizacja największego elementu jako korzeń
    int left = 2 * i + 1; // Indeks lewego potomka w tablicy
    int right = 2 * i + 2; // Indeks prawego potomka w tablicy

    // Sprawdzenie, czy lewy potomek jest większy od korzenia
    if (left < n && strcmp(arr[left], arr[largest]) > 0) {
        largest = left;
    }

    // Sprawdzenie, czy prawy potomek jest większy od korzenia
    if (right < n && strcmp(arr[right], arr[largest]) > 0) {
        largest = right;
    }

    // Jeśli największy element nie jest korzeniem, zamiana miejscami
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Rekurencyjne wywołanie dla poddrzewa, które może być naruszone
        heapify(arr, n, largest);
    }
}

// Funkcja sortująca przez kopiec
void heapSort(char arr[][50], int n) {
    // Budowanie kopca (reorganizacja tablicy)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Wyciąganie elementów z kopca i sortowanie
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]); // Zamiana korzenia z ostatnim elementem
        heapify(arr, i, 0);   // Ponowne utworzenie kopca dla zmniejszonej tablicy
    }
}


// Funkcja wyświetlająca tablicę łańcuchów
void printArray(char arr[][50], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%s", arr[i]);
        if (i < size - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    char arr[][50] = {"GGXYXYXY", "AAABBB", "ZZZ","CCDDEF","KKKCCLLL"};

    printf("\n"); 
    printf("Tablica przed sortowaniem:\n");
    printArray(arr, N);

    heapSort(arr, N);
    
    printf("\n");
    printf("\nTablica po sortowaniu:\n");
    printArray(arr, N);

    return 0;
}