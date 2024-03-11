#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Struktura reprezentująca krawędź w grafie
struct Edge {
    int destination; // Wierzchołek docelowy krawędzi
    int weight;       // Waga krawędzi
    struct Edge* next; // Następna krawędź w liście sąsiedztwa
};

// Struktura reprezentująca wierzchołek grafu
struct Vertex {
    int value;           // Numer wierzchołka
    struct Edge* edges;  // Lista krawędzi sąsiedztwa
};

// Struktura  grafu
struct Graph {
    int verticesCount;   // Liczba wierzchołków
    struct Vertex* array; // Tablica wierzchołków
};

// Funkcja do inicjalizacji wierzchołka grafu
struct Vertex* createVertex(int value) {
    struct Vertex* vertex = (struct Vertex*)malloc(sizeof(struct Vertex));
    vertex->value = value;
    vertex->edges = NULL;
    return vertex;
}

// Funkcja do inicjalizacji grafu
struct Graph* createGraph(int verticesCount) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->verticesCount = verticesCount;
    
    // Inicjalizacja tablicy wierzchołków
    graph->array = (struct Vertex*)malloc(verticesCount * sizeof(struct Vertex));
    for (int i = 0; i < verticesCount; ++i) {
        graph->array[i].value = i;
        graph->array[i].edges = NULL;
    }
    
    return graph;
}

// Funkcja do dodawania krawędzi do grafu (wierzchołek źródłowy, wierzchołek docelowy, waga)
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->destination = dest;
    newEdge->weight = weight;
    newEdge->next = graph->array[src].edges;
    graph->array[src].edges = newEdge;
}

// Funkcja do wyznaczania najkrótszych ścieżek algorytmem Dijkstry
void dijkstra(struct Graph* graph, int startVertex) {
    int verticesCount = graph->verticesCount;
    int* distance = (int*)malloc(verticesCount * sizeof(int));
    int* visited = (int*)malloc(verticesCount * sizeof(int));

    // Inicjalizacja odległości jako nieskończoność i oznaczanie wierzchołków jako nieodwiedzone
    for (int i = 0; i < verticesCount; ++i) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // Odległość od źródła do samego siebie wynosi 0
    distance[startVertex] = 0;

    // Wyznaczanie najkrótszych ścieżek
    for (int count = 0; count < verticesCount - 1; ++count) {
        int u = -1;
        // Wybór wierzchołka o najmniejszej odległości, który nie został jeszcze odwiedzony
        for (int v = 0; v < verticesCount; ++v) {
            if (!visited[v] && (u == -1 || distance[v] < distance[u]))
                u = v;
        }

        // Oznacz wybrany wierzchołek jako odwiedzony
        visited[u] = 1;

        // Aktualizacja odległości dla sąsiadów wybranego wierzchołka
        struct Edge* edge = graph->array[u].edges;
        while (edge != NULL) {
            int v = edge->destination;
            if (!visited[v] && distance[u] != INT_MAX && distance[u] + edge->weight < distance[v])
                distance[v] = distance[u] + edge->weight;
            edge = edge->next;
        }
    }

    // Wyświetlenie wyników
    printf("Najkrotsze sciezki od wierzcholka %d:\n", startVertex);
    for (int i = 0; i < verticesCount; ++i) {
        printf("Do wierzcholka %d: %d\n", i, distance[i]);
    }

    // Zwolnienie pamięci
    free(distance);
    free(visited);
}

// Funkcja do zwalniania pamięci zaalokowanej dla grafu
void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->verticesCount; ++i) {
        struct Edge* currentEdge = graph->array[i].edges;
        while (currentEdge != NULL) {
            struct Edge* nextEdge = currentEdge->next;
            free(currentEdge);
            currentEdge = nextEdge;
        }
    }
    free(graph->array);
    free(graph);
}

int main() {

    int N, wybor,src,dest,weight,x;
    int klucz=0;
    printf("ALGORYTM DIJKSTRY WYZNACZANIA NAJKROTSZEJ SCIEZKI W GRAFIE. \n");
    printf("Podaj maksymalna ilosc wierzcholkow grafu: ");
    scanf("%d",&N);
    struct Graph* graph = createGraph(N);

    // Funkcja do dodawania krawędzi do grafu (wierzchołek źródłowy, wierzchołek docelowy, waga)
    do{
        printf("Polaczenia miedzy wierzcholkami sa domyslnie ustawione na (INT_MAX)'INFINITY' \n");
        printf("Twoja maksymalna ilosc wierzcholkow w grafie: %d \n", N);
        printf("1. Dodaj wage polaczenia miedzy dwoma wierzcholkami grafu.\n");
        printf("2. Policz najkrotsze drogi do innych wierzcholkow z jednego wybranego. \n");
        printf("0. EXIT. \n");
        printf("\n");
        printf("Twoj wybor: ");
        scanf("%d",&wybor);


          switch(wybor){
             case 0:
             klucz = 1;
             break;

             case 1:
             printf("Podaj wage polaczenia: ");
             scanf("%d",&weight);
             printf("Od jakiego wierzcholku ma byc to polaczenie?: ");
             scanf("%d", &src);
             printf("Do jakiego wierzcholku ma byc to polaczenie?: ");
             scanf("%d", &dest);
             addEdge(graph, src, dest, weight);
             printf("\n");
             break;


             case 2:
             printf("Z jakiego wierzcholka chcesz liczyc najkrotsze sciezki?: ");
             scanf("%d",&x);
             dijkstra(graph, x);
             printf("\n");
             break;

             default:
             printf("Niepoprawna opcja. \n");
             printf("\n");
             break;
          }

    }while(klucz == 0);

    // Zwolnienie pamięci
    freeGraph(graph);
    return 0;
}
