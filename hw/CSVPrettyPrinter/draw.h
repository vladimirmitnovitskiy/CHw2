#pragma once

#include "Table.h"
#include <stdio.h>

/**
 * @brief Создаёт файл в который отрисовывает таблицу.
 */
void printTable(FILE* out, Table* table);