#include "draw.h"
#include "Table.h"
#include <ctype.h>
#include <stdio.h>

int isNumber(const char* s)
{
    if (*s == '-' || *s == '+') {
        s++;
    }

    int hasDigit = 0;

    while (*s) {
        if (!isdigit(*s) && *s != '.') {
            return 0;
        }

        if (isdigit(*s)) {
            hasDigit = 1;
        }

        s++;
    }

    return hasDigit;
}

void drawLine(FILE* out, Table* table, char fill)
{
    int cols = tablesCols(table);
    int* widths = tablesWidths(table);

    fprintf(out, "+");

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < widths[i] + 2; j++) {
            fprintf(out, "%c", fill);
        }
        fprintf(out, "+");
    }
    fprintf(out, "\n");
}

void printTable(FILE* out, Table* table)
{
    int rows = tablesRows(table);
    int cols = tablesCols(table);
    int* widhts = tablesWidths(table);

    drawLine(out, table, '=');

    for (int r = 0; r < rows; r++) {
        fprintf(out, "|");

        for (int c = 0; c < cols; c++) {
            const char* text = getTable(table, r, c);

            if (r == 0) {
                fprintf(out, " %-*s |", widhts[c], text);
            } else if (isNumber(text)) {
                fprintf(out, " %*s |", widhts[c], text);
            } else {
                fprintf(out, " %-*s |", widhts[c], text);
            }
        }
        fprintf(out, "\n");

        if (r == 0) {
            drawLine(out, table, '=');
        } else {
            drawLine(out, table, '=');
        }
    }
}