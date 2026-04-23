#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct AVLtree AVLtree;

/**
 * @brief Создаёт новое пустое АВЛ-дерево.
 *
 * @return Указатель на структуру дерева.
 */
AVLtree* createTree();

/**
 * @brief Добавляет новый элемент в АВЛ-дерево.
 *
 * Если элемент с таким ключом уже существует, добавление не происходит.
 *
 * @param root Указатель на дерево.
 * @param code Строковый ключ (уникальный идентификатор).
 * @param name Строковое значение, связанное с ключом.
 * @param added Указатель на флаг. Установится в true, если элемент добавлен, иначе false.
 */
void insertValue(AVLtree* tree, const char* code, const char* name, bool* added);

/**
 * @brief Удаляет элемент из дерева по ключу.
 *
 * @param tree Указатель на дерево.
 * @param code Строковый ключ удаляемого элемента.
 * @param deleted Указатель на флаг. Установится в true, если элемент удален, иначе false.
 */
void deleteValue(AVLtree* tree, const char* code, bool* deleted);

/**
 * @brief Ищет значение в дереве по ключу.
 *
 * Если элемент найден, копирует его значение в буфер outValue.
 *
 * @param tree Указатель на дерево.
 * @param code Строковый ключ для поиска.
 * @param outValue Буфер, куда будет записано найденное значение.
 * @param maxLength Максимальный размер буфера.
 * @return true, если элемент найден, иначе false.
 */
bool searchValue(AVLtree* tree, const char* code, char* outValue, size_t maxLength);

/**
 * @brief Сохраняет все элементы дерева в файл.
 *
 * Выполняет симметричный обход (in-order), сохраняя пары "ключ:значение"
 * в алфавитном порядке ключей.
 *
 * @param tree Указатель на дерево.
 * @param file Открытый для записи файл.
 * @param count Указатель на счетчик сохраненных записей.
 */
void saveTreeToFile(AVLtree* tree, FILE* file, int* count);

/**
 * @brief Загружает элементы в дерево из файла (формат "код:название").
 *
 * @param tree Указатель на дерево.
 * @param file Открытый для чтения файл.
 * @param count Указатель на счетчик загруженных записей.
 */
void loadTreeFromFile(AVLtree* tree, FILE* file, int* count);

/**
 * @brief Полностью удаляет дерево из памяти.
 *
 *
 * @param root Указатель на корень дерева.
 */
void freeTree(AVLtree* tree);