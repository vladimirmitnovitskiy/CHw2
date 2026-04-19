#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Node Node;

/**
 * @brief Добавляет новый элемент в АВЛ-дерево.
 *
 * Если элемент с таким ключом уже существует, добавление не происходит.
 *
 * @param root Указатель на корень дерева.
 * @param code Строковый ключ (уникальный идентификатор).
 * @param name Строковое значение, связанное с ключом.
 * @param added Указатель на флаг. Установится в true, если элемент добавлен, иначе false.
 * @return Указатель на новый корень дерева (после возможных балансировок).
 */
Node* insertNode(Node* root, const char* code, const char* name, bool* added);

/**
 * @brief Удаляет узел из дерева по ключу.
 *
 * @param root Указатель на корень дерева.
 * @param code Строковый ключ удаляемого элемента.
 * @param deleted Указатель на флаг. Установится в true, если элемент удален, иначе false.
 * @return Указатель на новый корень дерева.
 */
Node* deleteNode(Node* root, const char* code, bool* deleted);

/**
 * @brief Ищет значение в дереве по ключу.
 *
 * Если элемент найден, копирует его значение в буфер outValue.
 *
 * @param root Указатель на корень дерева.
 * @param code Строковый ключ для поиска.
 * @param outValue Буфер, куда будет записано найденное значение.
 * @param maxLength Максимальный размер буфера.
 * @return true, если элемент найден, иначе false.
 */
bool searchValue(Node* root, const char* code, char* outValue, size_t maxLength);

/**
 * @brief Сохраняет все элементы дерева в файл.
 *
 * Выполняет симметричный обход (in-order), сохраняя пары "ключ:значение"
 * в алфавитном порядке ключей.
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