///  KOLEJKA PRIORYTETOWA

#include <stdio.h>
#include <stdlib.h>

// Struktura reprezentująca element kolejki
typedef struct {
    int value;
    int priority;
} QueueElement;

// Struktura reprezentująca kolejkę priorytetową
typedef struct {
    QueueElement *array;
    int capacity;
    int size;
} PriorityQueue;

// Funkcja inicjalizująca kolejkę priorytetową
PriorityQueue *initPriorityQueue(int capacity) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    queue->array = (QueueElement *)malloc(capacity * sizeof(QueueElement));
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

// Funkcja dodająca nowy element do kolejki priorytetowej
void enqueue(PriorityQueue *queue, int value, int priority) {
    if (queue->size == queue->capacity) {
        printf("Kolejka priorytetowa jest pełna.\n");
        return;
    }

    QueueElement newElement;
    newElement.value = value;
    newElement.priority = priority;

    // Dodawanie elementu na koniec kolejki
    queue->array[queue->size] = newElement;
    queue->size++;

    // Przywracanie porządku kopca (heapify-up)
    int i = queue->size - 1;     // ostatnie miejsce jest puste (queue->size++)
    while (i > 0 && queue->array[(i - 1) / 2].priority < queue->array[i].priority) {
        // Zamiana miejscami z rodzicem, jeśli priorytet rodzica jest mniejszy
        QueueElement temp = queue->array[i];
        queue->array[i] = queue->array[(i - 1) / 2];
        queue->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Funkcja pobierająca element o największym priorytecie z kolejki
QueueElement dequeue(PriorityQueue *queue) {
    if (queue->size == 0) {
        printf("Kolejka priorytetowa jest pusta.\n");
        QueueElement emptyElement;
        emptyElement.value = -1;  // Wartość nie ma znaczenia w przypadku pustej kolejki
        emptyElement.priority = -1;
        return emptyElement;
    }

    // Pobieranie korzenia (elementu o największym priorytecie)
    QueueElement root = queue->array[0];

    // Zamiana miejscami z ostatnim elementem
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;

    // Przywracanie porządku kopca (heapify-down)
    int i = 0;
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int maxIndex = i;

        // Sprawdzanie lewego dziecka
        if (leftChild < queue->size && queue->array[leftChild].priority > queue->array[maxIndex].priority) {
            maxIndex = leftChild;
        }

        // Sprawdzanie prawego dziecka
        if (rightChild < queue->size && queue->array[rightChild].priority > queue->array[maxIndex].priority) {
            maxIndex = rightChild;
        }

        // Jeśli priorytet i jego dzieci są w dobrej kolejności, przerwij pętlę
        if (maxIndex == i) {
            break;
        }

        // Zamiana miejscami z dzieckiem o większym priorytecie
        QueueElement temp = queue->array[i];
        queue->array[i] = queue->array[maxIndex];
        queue->array[maxIndex] = temp;
        i = maxIndex;
    }

    return root;
}

// Funkcja zmieniająca priorytet wskazanego elementu w kolejce
void changePriority(PriorityQueue *queue, int index, int newPriority) {
    if (index < 0 || index >= queue->size) {
        printf("Nieprawidłowy indeks elementu.\n");
        return;
    }

    int oldPriority = queue->array[index].priority;
    queue->array[index].priority = newPriority;

    // Sprawdzenie, czy należy dokonać przesunięcia w górę (heapify-up) lub w dół (heapify-down)
    if (newPriority > oldPriority) {
        // Przesunięcie w górę
        while (index > 0 && queue->array[(index - 1) / 2].priority < queue->array[index].priority) {
            // Zamiana miejscami z rodzicem, jeśli priorytet rodzica jest mniejszy
            QueueElement temp = queue->array[index];
            queue->array[index] = queue->array[(index - 1) / 2];
            queue->array[(index - 1) / 2] = temp;
            index = (index - 1) / 2;
        }
    } else {
        // Przesunięcie w dół
        while (1) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int maxIndex = index;

            // Sprawdzanie lewego dziecka
            if (leftChild < queue->size && queue->array[leftChild].priority > queue->array[maxIndex].priority) {
                maxIndex = leftChild;
            }

            // Sprawdzanie prawego dziecka
            if (rightChild < queue->size && queue->array[rightChild].priority > queue->array[maxIndex].priority) {
                maxIndex = rightChild;
            }

            // Jeśli priorytet i jego dzieci są w dobrej kolejności, przerwij pętlę
            if (maxIndex == index) {
                break;
            }

            // Zamiana miejscami z dzieckiem o większym priorytecie
            QueueElement temp = queue->array[index];
            queue->array[index] = queue->array[maxIndex];
            queue->array[maxIndex] = temp;
            index = maxIndex;
        }
    }
}

// Funkcja wyświetlająca zawartość kolejki priorytetowej
void displayQueue(PriorityQueue *queue) {
    printf("Kolejka priorytetowa:\n");
    for (int i = 0; i < queue->size; i++) {
        printf("(%d, %d) ", queue->array[i].value, queue->array[i].priority);
    }
    printf("\n");
}

// Funkcja zwalniająca pamięć zajmowaną przez kolejkę priorytetową
void freePriorityQueue(PriorityQueue *queue) {
    free(queue->array);
    free(queue);
}

int main() {
    // Przykładowe użycie
    PriorityQueue *queue = initPriorityQueue(10);

    // Dodawanie elementów do kolejki
    enqueue(queue, 10, 3);
    enqueue(queue, 20, 1);
    enqueue(queue, 15, 5);
    enqueue(queue, 25, 2);

    // Wyświetlanie kolejki
    displayQueue(queue);

    // Pobieranie elementów o największym priorytecie
    QueueElement element1 = dequeue(queue);
    printf("Pobrano element o najwiekszym priorytecie: (%d, %d)\n", element1.value, element1.priority);

    QueueElement element2 = dequeue(queue);
    printf("Pobrano element o najwiekszym priorytecie: (%d, %d)\n", element2.value, element2.priority);

    // Zmiana priorytetu elementu
    changePriority(queue, 0, 8);

    // Wyświetlanie zmienionej kolejki
    displayQueue(queue);

    // Zwolnienie pamięci
    freePriorityQueue(queue);

    return 0;
}


