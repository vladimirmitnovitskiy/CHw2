#pragma once

#include <stdbool.h>

typedef struct MinHeap MinHeap;

/**
 * @brief Создает новую минимальную кучу (очередь с приоритетом).
 *
 * @param initialCapacity Начальная вместимость внутреннего массива (например, 16).
 * @return Указатель на созданную кучу.
 */
MinHeap* createMinHeap(int initialCapacity);

/**
 * @brief Добавляет элемент в кучу.
 *
 * @param heap Указатель на кучу.
 * @param to Идентификатор связанной вершины или объекта.
 * @param weight Вес (приоритет) элемента.
 */
void pushHeap(MinHeap* heap, int to, int weight);

/**
 * @brief Извлекает из кучи элемент с минимальным весом.
 *
 * @param heap Указатель на кучу.
 * @param outTo Указатель, куда будет записан идентификатор вершины/объекта.
 * @param outWeight Указатель, куда будет записан вес элемента.
 * @return true, если извлечение успешно, иначе false (если куча пуста).
 */
bool popHeap(MinHeap* heap, int* outTo, int* outWeight);

/**
 * @brief Проверяет, пуста ли куча.
 *
 * @param heap Указатель на кучу.
 * @return true, если в куче нет элементов, иначе false.
 */
bool isHeapEmpty(MinHeap* heap);

/**
 * @brief Освобождает память, выделенную под кучу.
 *
 * @param heap Указатель на кучу.
 */
void freeMinHeap(MinHeap* heap);