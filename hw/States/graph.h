#pragma once

typedef struct Graph Graph;

/**
 * @brief Создает взвешенный неориентированный граф.
 *
 * @param numVertices Количество вершин в графе (используется 1-индексация).
 * @return Указатель на созданный граф.
 */
Graph* createGraph(int numVertices);

/**
 * @brief Добавляет неориентированное (двунаправленное) ребро между вершинами.
 *
 * @param graph Указатель на граф.
 * @param from Номер первой вершины.
 * @param to Номер второй вершины.
 * @param weight Вес ребра.
 */
void addEdge(Graph* graph, int from, int to, int weight);

/**
 * @brief Возвращает степень вершины (количество инцидентных ей ребер).
 *
 * @param graph Указатель на граф.
 * @param vertex Номер вершины.
 * @return Количество соседей данной вершины.
 */
int getVertexDegree(Graph* graph, int vertex);

/**
 * @brief Получает данные о смежной вершине (соседе) и весе ребра по индексу.
 *
 * @param graph Указатель на граф.
 * @param vertex Номер исходной вершины.
 * @param index Индекс соседа (от 0 до degree - 1).
 * @param outTo Указатель, куда будет записан номер смежной вершины.
 * @param outWeight Указатель, куда будет записан вес ребра.
 */
void getNeighbor(Graph* graph, int vertex, int index, int* outTo, int* outWeight);

/**
 * @brief Полностью освобождает память графа.
 *
 * @param graph Указатель на граф.
 */
void freeGraph(Graph* graph);