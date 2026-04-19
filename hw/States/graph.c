#include "graph.h"

#include <stdlib.h>

typedef struct Neighbor {
    int to;
    int weight;
} Neighbor;

struct Graph {
    int numVertices;
    Neighbor** adjList;
    int* adjCount;
    int* adjCapacity;
};

Graph* createGraph(int numVertices)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph)
        return NULL;

    graph->numVertices = numVertices;

    graph->adjList = (Neighbor**)calloc(numVertices + 1, sizeof(Neighbor*));
    graph->adjCount = (int*)calloc(numVertices + 1, sizeof(int));
    graph->adjCapacity = (int*)calloc(numVertices + 1, sizeof(int));

    return graph;
}

void addEdge(Graph* graph, int from, int to, int weight)
{
    if (graph->adjCount[from] == graph->adjCapacity[from]) {
        int newCap = graph->adjCapacity[from] == 0 ? 4 : graph->adjCapacity[from] * 2;
        graph->adjList[from] = (Neighbor*)realloc(graph->adjList[from], newCap * sizeof(Neighbor));
        graph->adjCapacity[from] = newCap;
    }
    int idx = graph->adjCount[from]++;
    graph->adjList[from][idx].to = to;
    graph->adjList[from][idx].weight = weight;

    if (graph->adjCount[to] == graph->adjCapacity[to]) {
        int newCap = graph->adjCapacity[to] == 0 ? 4 : graph->adjCapacity[to] * 2;
        graph->adjList[to] = (Neighbor*)realloc(graph->adjList[to], newCap * sizeof(Neighbor));
        graph->adjCapacity[to] = newCap;
    }
    idx = graph->adjCount[to]++;
    graph->adjList[to][idx].to = from;
    graph->adjList[to][idx].weight = weight;
}

int getVertexDegree(Graph* graph, int vertex)
{
    if (!graph || vertex <= 0 || vertex > graph->numVertices) {
        return 0;
    }
    return graph->adjCount[vertex];
}

void getNeighbor(Graph* graph, int vertex, int index, int* outTo, int* outWeight)
{
    if (!graph || vertex <= 0 || vertex > graph->numVertices) {
        return;
    }
    if (index < 0 || index >= graph->adjCount[vertex]) {
        return;
    }

    *outTo = graph->adjList[vertex][index].to;
    *outWeight = graph->adjList[vertex][index].weight;
}

void freeGraph(Graph* graph)
{
    if (graph) {
        for (int i = 0; i <= graph->numVertices; i++) {
            if (graph->adjList[i]) {
                free(graph->adjList[i]);
            }
        }
        free(graph->adjList);
        free(graph->adjCount);
        free(graph->adjCapacity);
        free(graph);
    }
}