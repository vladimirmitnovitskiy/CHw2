#pragma once

typedef struct Table Table;

/**
 * @brief Создаёт таблицу.
 * @return Указатель на таблицу.
 */
Table* createTable();

/**
 * @brief Добавляет новую строку в таблицу.
 * @param table Указатель на таблицу.
 */
void addRow(Table* table);

/**
 * @brief Добавляет ячейку в указанную строку таблицы.
 * @param table Указатель на таблицу.
 * @param row Индекс строки.
 * @param text Текст, который будет записан в ячейку.
 */
void addCell(Table* table, int row, const char* text);

/**
 * @brief Возвращает содержимое ячейки.
 * @param table Указатель на таблицу.
 * @param row Индекс строки.
 * @param col Индекс колонки.
 * @return Указатель на строку с текстом ячейки.
 */
const char* getTable(Table* table, int row, int col);

/**
 * @brief Возвращает количество строк в таблице.
 * @param table Указатель на таблицу.
 * @return Количество строк.
 */
int tablesRows(Table* table);

/**
 * @brief Возвращает количество колонок в таблице.
 * @param table Указатель на таблицу.
 * @return Количество колонок.
 */
int tablesCols(Table* table);

/**
 * @brief Возвращает массив ширин колонок.
 * @param table Указатель на таблицу.
 * @return Указатель на массив ширин колонок.
 */
int* tablesWidths(Table* table);

/**
 * @brief Освобождает всю память, выделенную для таблицы.
 * @param table Указатель на таблицу.
 */
void freeTable(Table* table);