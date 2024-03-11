#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Struktura węzła drzewa binarnego
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Struktura węzła kolejki do BFS
struct QueueNode {
    struct Node* node;
    int level;
};

// Funkcja pomocnicza do dodawania węzłów do kolejki
void enqueue(struct QueueNode* queue, int* front, int* rear, struct Node* node, int level) {
    (*rear)++;
    queue[*rear].node = node;
    queue[*rear].level = level;
}

// Funkcja pomocnicza do usuwania węzłów z kolejki
struct QueueNode dequeue(struct QueueNode* queue, int* front) {
    struct QueueNode temp = queue[*front];
    (*front)++;
    return temp;
}

// Funkcja sprawdzająca czy drzewo jest puste
int isEmptyQueue(int front, int rear) {
    return front > rear;
}

// Funkcja min_level - znajduje minimalną wartość na danym poziomie
int min_level(struct Node* root, int k) {
    if (root == NULL || k < 1) {
        return INT_MAX;
    }

    int front = 0, rear = -1;
    struct QueueNode* queue = (struct QueueNode*)malloc(sizeof(struct QueueNode) * 1000);

    enqueue(queue, &front, &rear, root, 1);

    int min_value = INT_MAX;

    while (!isEmptyQueue(front, rear)) {
        struct QueueNode current = dequeue(queue, &front);

        if (current.level == k) {
            if (current.node->data < min_value) {
                min_value = current.node->data;
            }
        }

        if (current.node->left != NULL) {
            enqueue(queue, &front, &rear, current.node->left, current.level + 1);
        }

        if (current.node->right != NULL) {
            enqueue(queue, &front, &rear, current.node->right, current.level + 1);
        }
    }

    free(queue);
    return min_value;
}

// Funkcja max_level - znajduje maksymalną wartość na danym poziomie
int max_level(struct Node* root, int k) {
    if (root == NULL || k < 1) {
        return INT_MIN;
    }

    int front = 0, rear = -1;
    struct QueueNode* queue = (struct QueueNode*)malloc(sizeof(struct QueueNode) * 1000);

    enqueue(queue, &front, &rear, root, 1);

    int max_value = INT_MIN;

    while (!isEmptyQueue(front, rear)) {
        struct QueueNode current = dequeue(queue, &front);

        if (current.level == k) {
            if (current.node->data > max_value) {
                max_value = current.node->data;
            }
        }

        if (current.node->left != NULL) {
            enqueue(queue, &front, &rear, current.node->left, current.level + 1);
        }

        if (current.node->right != NULL) {
            enqueue(queue, &front, &rear, current.node->right, current.level + 1);
        }
    }

    free(queue);
    return max_value;
}

int main() {
    // Przykładowe użycie funkcji
    struct Node* root = (struct Node*)malloc(sizeof(struct Node));
    root->data = 1;
    root->left = (struct Node*)malloc(sizeof(struct Node));
    root->left->data = 2;
    root->right = (struct Node*)malloc(sizeof(struct Node));
    root->right->data = 3;

    // Dodaj więcej węzłów do drzewa w celu przetestowania
    // ...

    int k = 2;
    printf("Minimalna wartość na poziomie %d: %d\n", k, min_level(root, k));
    printf("Maksymalna wartość na poziomie %d: %d\n", k, max_level(root, k));

    // Zwolnij pamięć
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}
