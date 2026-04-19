#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Node Node;

/**
 * @brief Добавляет новый аэропорт в АВЛ-дерево.
 *
 * Если аэропорт с таким кодом уже существует, добавление не происходит.
 *
 * @param root Указатель на корень дерева.
 * @param code Трехбуквенный IATA код.
 * @param name Название аэропорта.
 * @param added Указатель на флаг. Установится в true, если добавлен, иначе false.
 * @return Указатель на новый корень дерева (после возможных балансировок).
 */
Node* insertNode(Node* root, const char* code, const char* name, bool* added);

/**
 * @brief Удаляет аэропорт из дерева по коду.
 *
 * @param root Указатель на корень дерева.
 * @param code Трехбуквенный IATA код для удаления.
 * @param deleted Указатель на флаг. Установится в true, если удален, иначе false.
 * @return Указатель на новый корень дерева.
 */
Node* deleteNode(Node* root, const char* code, bool* deleted);

/**
 * @brief Ищет аэропорт в дереве.
 *
 * Если аэропорт найден, копирует его название в буфер outName.
 *
 * @param root Указатель на корень дерева.
 * @param code Трехбуквенный IATA код для поиска.
 * @param outName Буфер, куда будет записано название.
 * @param maxLength Максимальный размер буфера.
 * @return true, если аэропорт найден, иначе false.
 */
bool findAirport(Node* root, const char* code, char* outName, size_t maxLength);

/**
 * @brief Сохраняет все элементы дерева в файл.
 *
 * Выполняет симметричный обход (in-order), сохраняя данные в алфавитном порядке.
 *
 * @param root Указатель на корень дерева.
 * @param file Открытый для записи файл.
 * @param count Указатель на счетчик сохраненных записей.
 */
void saveTreeToFile(Node* root, FILE* file, int* count);

/**
 * @brief Полностью удаляет дерево из памяти.
 *
 * Последовательно (post-order) освобождает память, занятую всеми узлами.
 *
 * @param root Указатель на корень дерева.
 */
void freeTree(Node* root);