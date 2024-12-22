#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct nod_lista {
    int cheie;
    struct nod_lista *next, *prev;
} t_nod_lista;

typedef struct {
    t_nod_lista *head;
} t_lista;

t_lista G[MAX];

void init_lista_ad(t_lista G[], int n) {
    for (int i = 0; i < n; ++i) {
        G[i].head = NULL;
    }
}

t_nod_lista* creare_nod(int cheie) {
    t_nod_lista *nod = (t_nod_lista*)malloc(sizeof(t_nod_lista));
    nod->cheie = cheie;
    nod->prev = nod->next = NULL;
    return nod;
}

void inserare_vecin(t_lista G[], int sursa, int vecin) {
    t_nod_lista *nod = creare_nod(vecin);
    nod->next = G[sursa].head;
    if (G[sursa].head != NULL) {
        G[sursa].head->prev = nod;
    }
    G[sursa].head = nod;
}

void print_lista(t_lista G[], int n) {
    printf("Lista de adiacenta:\n");
    for (int i = 0; i < n; ++i) {
        printf("%d: ", i);
        t_nod_lista *nod = G[i].head;
        while (nod != NULL) {
            printf("%d ", nod->cheie);
            nod = nod->next;
        }
        printf("\n");
    }
}

void print_path(t_lista G[], int prev[], int start, int end) {
    if (end == start) {
        printf("%d ", start);
    } else if (prev[end] == -1) {
        printf("Nu exista cale de la %d la %d\n", start, end);
    } else {
        print_path(G, prev, start, prev[end]);
        printf("%d ", end);
    }
}

//0 - while (nodul nu a fost vizitat)
//1 - gray (nodul este in proces de vizitare, adica se afla in coada)
//2 - black (nodul a fost complet vizitat)

void bfs(t_lista G[], int n, int start) {
    int culoare[MAX], d[MAX], prev[MAX];
    for (int i = 0; i < n; ++i) {
        culoare[i] = 0; //white
        d[i] = INT_MAX;
        prev[i] = -1;
    }
    culoare[start] = 1; //gray
    d[start] = 0;
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = start;
    while (front != rear) {
        int u = queue[front++];
        printf("%d ", u);
        t_nod_lista *nod = G[u].head;
        while (nod != NULL) {
            int v = nod->cheie;
            if (culoare[v] == 0) { // white
                culoare[v] = 1; // gray
                d[v] = d[u] + 1;
                prev[v] = u;
                queue[rear++] = v;
            }
            nod = nod->next;
        }
        culoare[u] = 2; // black
    }
    printf("\n");
    printf("Calea de la nodul %d la toate celelalte noduri:\n", start);
    for (int i = 0; i < n; i++) {
        printf("Nod %d: ", i);
        if (d[i] != INT_MAX) {
            print_path(G, prev, start, i);
        } else {
            printf("Nu este accesibil");
        }
        printf("\n");
    }
}

void dfs_visit(t_lista G[], int u, int culoare[], int prev[]) {
    printf("%d ", u);
    culoare[u] = 1; // gray
    t_nod_lista *nod = G[u].head;
    while (nod != NULL) {
        int v = nod->cheie;
        if (culoare[v] == 0) { //white
            prev[v] = u;
            dfs_visit(G, v, culoare, prev);
        }
        nod = nod->next;
    }
    culoare[u] = 2; // black
}

void dfs(t_lista G[], int n) {
    int culoare[MAX], prev[MAX];
    for (int i = 0; i < n; i++) {
        culoare[i] = 0; // white
        prev[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        if (culoare[i] == 0) { // white
            dfs_visit(G, i, culoare, prev);
        }
    }
}

int main() {
    int n, m;
    printf("Numarul de noduri: ");
    scanf("%d", &n);
    init_lista_ad(G, n);
    printf("Numarul de muchii: ");
    scanf("%d", &m);
    printf("Introduceti muchiile (sursa, destinatie):\n");
    for (int i = 0; i < m; i++) {
        int sursa, destinatie;
        scanf("%d %d", &sursa, &destinatie);
        inserare_vecin(G, sursa, destinatie);
    }
    printf("Parcurgere BFS: ");
    bfs(G, n, 0);
    printf("\n");
    printf("Parcurgere DFS: ");
    dfs(G, n);
    printf("\n");
    printf("Afisarea listei de adiacenta:\n");
    print_lista(G, n);
    return 0;
}
