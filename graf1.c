#include <stdio.h>
#include <stdlib.h>

// Struktura opisująca wierzchołki grafu lub krawędzie
struct elem {
    int v;      // etykieta identyfikująca wierzchołek, 1,...,n
    float d;    // waga przypisana wierzchołkowi
};

// Struktura opisująca kopiec
struct Heap {
    struct elem *arr;   // tablica elementów kopca
    int capacity;       // pojemność kopca
    int size;           // aktualna liczba elementów w kopcu
    int *Id;            // tablica indeksów w kopcu dla wierzchołków
};

// Inicjalizacja kopca
struct Heap *initHeap(int capacity) {
    struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
    heap->arr = (struct elem *)malloc((capacity + 1) * sizeof(struct elem));
    heap->capacity = capacity;
    heap->size = 0;
    heap->Id = (int *)malloc((capacity + 1) * sizeof(int));
    return heap;
}

// Procedura przesiewania elementu w górę w kopcu
void heapifyUp(struct Heap *heap, int index) {
    while (index > 1 && heap->arr[index].d < heap->arr[index / 2].d) {
        // Zamiana miejscami elementów
        struct elem temp = heap->arr[index];
        heap->arr[index] = heap->arr[index / 2];
        heap->arr[index / 2] = temp;

        // Aktualizacja indeksów w tablicy Id
        heap->Id[heap->arr[index].v] = index;
        heap->Id[heap->arr[index / 2].v] = index / 2;

        // Przejście do rodzica
        index /= 2;
    }
}

// Procedura przesiewania elementu w dół w kopcu
void heapifyDown(struct Heap *heap, int index) {
    int smallest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    // Znajdowanie najmniejszego z dziełów
    if (left <= heap->size && heap->arr[left].d < heap->arr[smallest].d)
        smallest = left;
    if (right <= heap->size && heap->arr[right].d < heap->arr[smallest].d)
        smallest = right;

    // Zamiana miejscami i rekurencyjne przesiewanie
    if (smallest != index) {
        struct elem temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;

        heap->Id[heap->arr[index].v] = index;
        heap->Id[heap->arr[smallest].v] = smallest;

        heapifyDown(heap, smallest);
    }
}

// Dodawanie elementu do kopca
void add(struct elem x, struct Heap *heap) {
    if (heap->size == heap->capacity) {
        printf("Kopiec jest pełny. Nie można dodać więcej elementów.\n");
        return;
    }

    // Dodanie na końcu tablicy
    heap->size++;
    int index = heap->size;
    heap->arr[index] = x;
    heap->Id[x.v] = index;

    // Przesiewanie w górę
    heapifyUp(heap, index);
}

// Pobieranie minimalnego elementu z kopca
struct elem extractMin(struct Heap *heap) {
    if (heap->size <= 0) {
        struct elem emptyElem;
        emptyElem.v = -1; // Wartość reprezentująca pusty element
        emptyElem.d = 0;
        return emptyElem;
    }
    // Zapisanie minimalnego elementu
    struct elem minElem = heap->arr[1];

    // Zamiana miejscami z ostatnim elementem
    heap->arr[1] = heap->arr[heap->size];

    // Aktualizacja indeksu w tablicy Id
    heap->Id[heap->arr[1].v] = 1;

    // Zmniejszenie rozmiaru kopca
    heap->size--;

    // Przesiewanie w dół
    heapifyDown(heap, 1);

    return minElem;
}

// Zmiana priorytetu wierzchołka w kopcu
void changePriority(int v, float newPriority, struct Heap *heap, int *Id) {
    int index = Id[v];

    // Aktualizacja wagi wierzchołka
    heap->arr[index].d = newPriority;

    // Przesiewanie w górę i w dół, aby przywrócić porządek kopca
    heapifyUp(heap, index);
    heapifyDown(heap, index);

    // Aktualizacja indeksu w tablicy Id
    Id[v] = heap->Id[heap->arr[index].v];
}

// Zwalnianie pamięci zajmowanej przez kopiec
void freeHeap(struct Heap *heap) {
    free(heap->arr);
    free(heap->Id);
    free(heap);
}

int main() {
    // Przykładowe użycie
    int capacity = 10;
    struct Heap *heap = initHeap(capacity);

    struct elem elem1 = {1, 3.0};
    struct elem elem2 = {2, 5.0};
    struct elem elem3 = {3, 8.0};
    struct elem elem4 = {4, 10.0};

    add(elem1, heap);
    add(elem2, heap);
    add(elem3, heap);

    struct elem minElem = extractMin(heap);
    printf("Minimalny element: v=%d, d=%f\n", minElem.v, minElem.d);

    changePriority(2, 9.0, heap, heap->Id);

    minElem = extractMin(heap);
    printf("Minimalny element po zmianie priorytetu: v=%d, d=%f\n", minElem.v, minElem.d);

    freeHeap(heap);

    return 0;
}
