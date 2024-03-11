#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktura reprezentująca węzeł drzewa
typedef struct TreeNode {
    char data[50];
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} TreeNode;

// Funkcja tworząca nowy węzeł drzewa
TreeNode *createNode(const char *data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        strcpy(newNode->data, data);
        newNode->left = newNode->right = newNode->parent = NULL;
    }
    return newNode;
}

// Funkcja dodająca węzeł do drzewa
TreeNode *insert(TreeNode *root, const char *data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (strcmp(data, root->data) < 0) {
        TreeNode *leftChild = insert(root->left, data);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (strcmp(data, root->data) > 0) {
        TreeNode *rightChild = insert(root->right, data);
        root->right = rightChild;
        rightChild->parent = root;
    }

    return root;
}

// Funkcja szukająca węzła w drzewie
TreeNode *search(TreeNode *root, const char *data) {
    if (root == NULL || strcmp(data, root->data) == 0) {
        return root;
    }

    if (strcmp(data, root->data) < 0) {
        return search(root->left, data);
    } else {
        return search(root->right, data);
    }
}

// Funkcja znajdująca węzeł o najmniejszej wartości w drzewie
TreeNode *minimum(TreeNode *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Funkcja znajdująca węzeł o największej wartości w drzewie
TreeNode *maximum(TreeNode *root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Funkcja usuwająca węzeł z drzewa
TreeNode *deleteNode(TreeNode *root, const char *data) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(data, root->data) < 0) {
        root->left = deleteNode(root->left, data);
    } else if (strcmp(data, root->data) > 0) {
        root->right = deleteNode(root->right, data);
    } else {
        // Węzeł do usunięcia został znaleziony

        // Węzeł z jednym lub brakiem potomków
        if (root->left == NULL) {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // Węzeł z dwoma potomkami - znalezienie następnika
        TreeNode *temp = minimum(root->right);

        // Skopiowanie danych następnika do tego węzła
        strcpy(root->data, temp->data);

        // Usunięcie następnika
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Funkcja znajdująca poprzednika węzła
TreeNode *predecessor(TreeNode *node) {
    if (node->left != NULL) {
        return maximum(node->left);
    }

    TreeNode *parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}

// Funkcja znajdująca następnika węzła
TreeNode *successor(TreeNode *node) {
    if (node->right != NULL) {
        return minimum(node->right);
    }

    TreeNode *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}


void DrukujDrzewoRekurencyjnie(TreeNode *d, int poziom)
{
    if (d == NULL)
        return;

    const int odleglosc = 8;

    DrukujDrzewoRekurencyjnie(d->left, poziom + 1);

    for (int i = 0; i < odleglosc * poziom; i++)
        putchar(' ');

    printf("%s\n", d->data);

    DrukujDrzewoRekurencyjnie(d->right, poziom + 1);
}

void printTree(TreeNode *d)
{
    DrukujDrzewoRekurencyjnie(d, 0);
    putchar('\n');
}

int main() {
    TreeNode *root = NULL;
    int klucz = 0;
    int wybor;
    char wyraz[50];

    printf("\n----   Drzewo Binarne Lancuchow Znakowych   ----\n");
    printf("UWAGA. Program nie przewiduje identycznych elementow w drzewie lecz zaklada ze kazdy element jest oryginalny.\n");
    do{
                printf("\n");
                printf("1. Dodaj nowy ciag znakow do drzewa.\n");
                printf("2. Wyswietl drzewo\n");
                printf("3. Wyznacz aktualne minimum drzewa.\n");
                printf("4. Wyznacz aktualne maksimum drzewa.\n");
                printf("5. Wyszukaj podany element z drzewa.\n");
                printf("6. Wyznacz poprzednik wskazanego elementu.\n");
                printf("7. Wyznacz nastepnik wskazanego elementu.\n");       
                printf("8. Usun podany element z drzewa.\n");
                printf("0. EXIT.\n");
                printf("Podaj numer: ");
                scanf("%d",&wybor);


                switch(wybor){

                    case 0:
                    klucz = 1;
                    break;

                    case 1:
                    printf("Podaj element(ciag znakow) ktory chcesz dodac: ");
                    scanf("%s",wyraz);
                    if(root == NULL){
                      root = insert(root, wyraz);  
                    }
                    else{
                      insert(root, wyraz);
                    }
                    break;

                    case 2:
                    printTree(root);
                    break;

                    case 3:
                    TreeNode *minNode = minimum(root);
                    printf("Minimum: %s\n", minNode->data);
                    break;

                    case 4:
                    TreeNode *maxNode = maximum(root);
                    printf("Maksimum: %s\n", maxNode->data);
                    break;

                    case 5:
                    printf("Jaki element chcesz wyszukac w drzewie?: ");
                    scanf("%s",wyraz);
                    TreeNode *foundNode = search(root, wyraz);
                    if (foundNode != NULL) {
                        printf("Element \"%s\" zostal znaleziony w drzewie.\n", wyraz);
                    } else {
                        printf("Element \"%s\" nie zostal znaleziony w drzewie.\n", wyraz);
                    }
                    break;

                    case 6:
                    printf("Poprzednika jakiego elementu chcesz wyznaczyc?: ");
                    scanf("%s",wyraz);
                    TreeNode *nodeToFind = search(root, wyraz);
                    TreeNode *predecessorNode = predecessor(nodeToFind);
                    if (predecessorNode != NULL) {
                        printf("Poprzednik elementu \"%s\": %s\n", nodeToFind->data, predecessorNode->data);
                    } else {
                        printf("Element \"%s\" nie ma poprzednika.\n", nodeToFind->data);
                    }
                    break;

                    case 7:
                    printf("Nastepnika jakiego elementu chcesz wyznaczyc?: ");
                    scanf("%s",wyraz);
                    TreeNode *nodeElement = search(root, wyraz);
                    TreeNode *successorNode = successor(nodeToFind);
                    if (successorNode != NULL) {
                        printf("Nastepnik elementu \"%s\": %s\n", nodeElement->data, successorNode->data);
                    } else {
                        printf("Element \"%s\" nie ma nastepnika.\n", nodeElement->data);
                    }
                    break;

                    case 8:
                    printf("Jaki element chcesz usunac z drzewa?: ");
                    scanf("%s",wyraz);
                    root = deleteNode(root, wyraz);


                    default :
                    printf("Nieznana operacja.\n" );

                }

    }while(klucz == 0);

    return 0;
}







