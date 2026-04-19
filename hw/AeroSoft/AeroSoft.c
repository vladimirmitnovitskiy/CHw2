#include "AVLtree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 512

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Использование: %s <файл_базы>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    Node* root = NULL;
    int airportCount = 0;

    FILE* file = fopen(filename, "r");
    if (file) {
        char line[MAX_LINE_LEN];
        while (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            line[strcspn(line, "\r")] = 0;

            char* colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                bool added = false;
                root = insertNode(root, line, colon + 1, &added);
                if (added) {
                    airportCount++;
                }
            }
        }
        fclose(file);
        printf("Загружено %d аэропортов. Система готова к работе.\n", airportCount);
    } else {
        printf("Не удалось открыть файл '%s'. Начинаем с пустой базы.\n", filename);
    }

    char cmdLine[MAX_LINE_LEN];
    while (true) {
        printf("\n> ");
        if (!fgets(cmdLine, sizeof(cmdLine), stdin)) {
            break;
        }

        cmdLine[strcspn(cmdLine, "\n")] = 0;
        cmdLine[strcspn(cmdLine, "\r")] = 0;

        if (strlen(cmdLine) == 0) {
            continue;
        }

        if (strncmp(cmdLine, "find ", 5) == 0) {
            char* code = cmdLine + 5;
            char foundName[MAX_LINE_LEN];

            if (findAirport(root, code, foundName, sizeof(foundName))) {
                printf("%s → %s\n", code, foundName);
            } else {
                printf("Аэропорт с кодом '%s' не найден в базе.\n", code);
            }

        } else if (strncmp(cmdLine, "add ", 4) == 0) {
            char* args = cmdLine + 4;
            char* colon = strchr(args, ':');

            if (colon) {
                *colon = '\0';
                bool added = false;
                root = insertNode(root, args, colon + 1, &added);

                if (added) {
                    airportCount++;
                    printf("Аэропорт '%s' добавлен в базу.\n", args);
                } else {
                    printf("Аэропорт '%s' уже существует в базе.\n", args);
                }
            } else {
                printf("Ошибка формата. Используйте: add КОД:Название\n");
            }

        } else if (strncmp(cmdLine, "delete ", 7) == 0) {
            char* code = cmdLine + 7;
            bool deleted = false;
            root = deleteNode(root, code, &deleted);

            if (deleted) {
                airportCount--;
                printf("Аэропорт '%s' удалён из базы.\n", code);
            } else {
                printf("Аэропорт '%s' не найден для удаления.\n", code);
            }

        } else if (strcmp(cmdLine, "save") == 0) {
            FILE* fileOut = fopen(filename, "w");
            if (fileOut) {
                int savedCount = 0;
                saveTreeToFile(root, fileOut, &savedCount);
                fclose(fileOut);
                printf("База сохранена: %d аэропортов.\n", savedCount);
            } else {
                printf("Ошибка: не удалось сохранить в файл '%s'.\n", filename);
            }

        } else if (strcmp(cmdLine, "quit") == 0) {
            break;

        } else {
            printf("Неизвестная команда. Доступные: find, add, delete, save, quit.\n");
        }
    }

    freeTree(root);
    return 0;
}