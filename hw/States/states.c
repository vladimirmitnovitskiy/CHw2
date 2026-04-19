#include "graph.h"
#include "minHeap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Использование: %s <входной_файл>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Ошибка: Не удалось открыть файл '%s'\n", argv[1]);
        return 1;
    }

    int n, m;
    if (fscanf(file, "%d %d", &n, &m) != 2) {
        fclose(file);
        return 1;
    }

    Graph* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        int from, to, weight;
        fscanf(file, "%d %d %d", &from, &to, &weight);
        addEdge(graph, from, to, weight);
    }

    int k;
    fscanf(file, "%d", &k);

    int* capitals = (int*)malloc((k + 1) * sizeof(int));
    for (int i = 1; i <= k; i++) {
        fscanf(file, "%d", &capitals[i]);
    }
    fclose(file);

    int* owner = (int*)calloc(n + 1, sizeof(int));
    MinHeap** stateHeaps = (MinHeap**)malloc((k + 1) * sizeof(MinHeap*));
    int unassignedCount = n;

    for (int state = 1; state <= k; state++) {
        int capital = capitals[state];
        owner[capital] = state;
        unassignedCount--;

        stateHeaps[state] = createMinHeap(16);

        int degree = getVertexDegree(graph, capital);
        for (int i = 0; i < degree; i++) {
            int to, weight;
            getNeighbor(graph, capital, i, &to, &weight);
            pushHeap(stateHeaps[state], to, weight);
        }
    }

    while (unassignedCount > 0) {
        for (int state = 1; state <= k; state++) {
            if (unassignedCount == 0)
                break;

            int targetCity = -1;

            while (!isHeapEmpty(stateHeaps[state])) {
                int to, weight;
                popHeap(stateHeaps[state], &to, &weight);

                if (owner[to] == 0) {
                    targetCity = to;
                    break;
                }
            }

            if (targetCity != -1) {
                owner[targetCity] = state;
                unassignedCount--;

                int degree = getVertexDegree(graph, targetCity);
                for (int i = 0; i < degree; i++) {
                    int to, weight;
                    getNeighbor(graph, targetCity, i, &to, &weight);

                    if (owner[to] == 0) {
                        pushHeap(stateHeaps[state], to, weight);
                    }
                }
            }
        }
    }

    for (int state = 1; state <= k; state++) {
        printf("Государство %d (столица %d):", state, capitals[state]);
        for (int city = 1; city <= n; city++) {
            if (owner[city] == state) {
                printf(" %d", city);
            }
        }
        printf("\n");
    }

    for (int state = 1; state <= k; state++) {
        freeMinHeap(stateHeaps[state]);
    }
    free(stateHeaps);
    free(owner);
    free(capitals);
    freeGraph(graph);

    return 0;
}