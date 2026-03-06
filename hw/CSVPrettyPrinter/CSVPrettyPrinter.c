#include "Table.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    FILE* input = fopen("input.csv", "r");
    if (input == NULL) {
        printf("Файл не найден!\n");
        return -1;
    }

    Table* table = createTable();

    char* line = NULL;
    size_t size = 0;

    while (getline(&line, &size, input) != -1) {
        line[strcspn(line, "\n")] = 0;

        addRow(table);

        int row = tablesRows(table) - 1;

        char* token = strtok(line, ",");

        while (token) {
            addCell(table, row, token);
            token = strtok(NULL, ",");
        }
    }

    free(line);
    fclose(input);

    FILE* out = fopen("output.txt", "w");

    printTable(out, table);

    fclose(out);

    freeTable(table);

    return 0;
}