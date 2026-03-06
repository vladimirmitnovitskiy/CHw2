#include "Table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cell {
    char* text;
} Cell;

typedef struct Row {
    Cell* cells;
    int count;
} Row;

struct Table {
    Row* rows;
    int rowsCount;
    int colsCount;
    int* widths;
};

Table* createTable()
{
    Table* table = malloc(sizeof(Table));

    table->rows = NULL;
    table->rowsCount = 0;
    table->colsCount = 0;
    table->widths = NULL;

    return table;
}

void addRow(Table* table)
{
    table->rows = realloc(table->rows, (table->rowsCount + 1) * sizeof(Row));

    Row* row = &table->rows[table->rowsCount];

    row->cells = NULL;
    row->count = 0;

    table->rowsCount++;
}

void addCell(Table* table, int row, const char* text)
{
    Row* r = &table->rows[row];

    r->cells = realloc(r->cells, (r->count + 1) * sizeof(Cell));

    Cell* c = &r->cells[r->count];

    c->text = malloc(strlen(text) + 1);
    strcpy(c->text, text);

    if (row == 0) {
        table->widths = realloc(table->widths, (r->count + 1) * sizeof(int));
        table->widths[r->count] = 0;
        table->colsCount++;
    }

    int len = strlen(text);

    if (len > table->widths[r->count]) {
        table->widths[r->count] = len;
    }

    r->count++;
}

const char* getTable(Table* table, int row, int col)
{
    return table->rows[row].cells[col].text;
}

int tablesRows(Table* table)
{
    return table->rowsCount;
}

int tablesCols(Table* table)
{
    return table->colsCount;
}

int* tablesWidths(Table* table)
{
    return table->widths;
}

void freeTable(Table* table)
{
    for (int i = 0; i < table->rowsCount; i++) {
        for (int j = 0; j < table->rows[i].count; j++) {
            free(table->rows[i].cells[j].text);
        }

        free(table->rows[i].cells);
    }

    free(table->rows);
    free(table->widths);
    free(table);
}