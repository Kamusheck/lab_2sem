# Отчет по курсовой работе № 9
## по курсу "Фундаментальная информатика"

Студент группы М8О-108Б-23 Исмаилова Камила 

Работа выполнена 

Преподаватель: каф. 806 Севастьянов Виктор Сергеевич

1. **Тема**: Сортировка и поиск.
2. **Цель работы**: изчуение различных алгоритмов сортировки. Приминение бинарного поиска.
3. **Задание**:
- Выполнить турнирную сортировку, тип ключа - вещественый, хранение ключей и знначений отдельно.
4. **Идея, метод, алгоритм решения задачи**: 
    - для турнирной сортировки использовать дерево победителей,оно так же эфективно для избегания утечек памяти: для сопоставления ключа и значения нужно рсаписать отдельную функцию: при составлении функции бинарного поиска следует помнить, что ключ вещественный
5. **Сценарий выполнения работы**: Определить структуру таблицы, расписать insertData - для сопоставления ключа и значений. Составить ф-цию sortTable - для сортировки, binarySearch - для бинарного поиска. Так же составляем функцию принта таблицы и вспомогательного меню команд.
6. **Протокол**: 
    ``` #include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <ctype.h>


void sortTable(table **Table);
void insertData(table **Table);
void binarySearch(table *Table, float key);
void printTable(table *Table);
void tournamentSort(float keys[], char content[][12], int size);

int main() {
    table *Table = NULL;

    char command[100];
    float key;

    while (1) {
        printf("help:\n insertData:to look original table\n sortTable:to look sorted table\n binarySearch: for find\n Enter command: \n");
        scanf("%99s", command);

        if (strcmp(command, "insertData") == 0) {
            insertData(&Table);
	    printf("unsorted Table \n");
	    printTable(Table);
        } else if (strcmp(command, "sortTable") == 0) {
            sortTable(&Table);
            printf("Table sorted using tournament sort: \n");
            printTable(Table);
        } else if (strcmp(command, "binarySearch") == 0) {
            printf("Enter key to search: \n ");
            scanf("%f", &key);
            binarySearch(Table, key);
        } else if (strcmp(command, "printTable") == 0) {
            printTable(Table);
        } else if (strcmp(command, "exit") == 0) {
            free(Table);
            break;
        } else {
            printf("unknown,try another command \n");
        }
    }
    return 0;
}

void insertData(table **Table) {
    if (*Table == NULL) {
        *Table = (table *)malloc(sizeof(table));
        if (*Table == NULL) {
            printf("Error allocating memoryn");
            exit(1);
        }
        (*Table)->countK = 0;
        (*Table)->countC = 0;
    }

    FILE *file = fopen("keys.txt", "r");
    if (file == NULL) {
        printf("Error opening filen");
        exit(1);
    }

    FILE *file2 = fopen("content.txt", "r");
    if (file2 == NULL) {
        printf("Error opening filen");
        fclose(file); 
        exit(1);
    }

    float key_value;
    char content[12];
    int keys_read = 0; 

    while (keys_read < 10 && fscanf(file, "%f", &key_value) == 1) {
        if (fgets(content, sizeof(content), file2) != NULL) {
            content[strcspn(content, "n")] = 0; 
            // Сохраняем ключ и содержимое, если содержимое не пустое
            if (content[0] != '0') { 
                (*Table)->key[(*Table)->countK++] = key_value;
                strcpy((*Table)->content[(*Table)->countC++], content);
            }
            keys_read++; 
        } else {
            break;
        }
    }

    fclose(file);
    fclose(file2);
}

void binarySearch(table *Table, float key) {
    
    int low = 0;
    int high = Table->countK - 1;
    int mid;

    while (low <= high) {
        mid = low + (high - low) / 2;
        if (Table->key[mid] == key) {
            printf("Key: %.3f, Value: %s \n", Table->key[mid], Table->content[mid]);
            return;
        } else if (Table->key[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("there is no key, try another \n");
}

void printTable(table *Table) {
    if (Table == NULL) {
        fprintf(stderr, "Table is empty n");
        return;
    }
    for (int i = 0; i < Table->countK; i++) {
        char *value = Table->content[i];
        if (value[0] != '0' && !isAllSpaces(value)) {
            printf("Key: %.3f     Value: %s \n", Table->key[i], value);
        }
    }
}

int isAllSpaces(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}


void tournamentSort(float keys[], char content[][12], int size) {
    int treeSize = 1;
    while (treeSize < size) treeSize *= 2; 
    treeSize *= 2; 

    int *indexTree = (int *)malloc(sizeof(int) * treeSize);
    if (indexTree == NULL) {
        fprintf(stderr, "Memory allocation errorn");
        exit(EXIT_FAILURE);
    }

    int i, j;
    for (i = 0; i < size; i++) {
        indexTree[treeSize / 2 + i] = i;
    }
    for (i = size; i < treeSize / 2; i++) { 
        indexTree[treeSize / 2 + i] = size - 1;
    }

    for (i = treeSize / 2 - 1; i > 0; i--) {
        indexTree[i] = (keys[indexTree[2 * i]] <= keys[indexTree[2 * i + 1]]) ? indexTree[2 * i] : indexTree[2 * i + 1];
    }
    float sortedKeys[size];
    char sortedContent[size][12];
    for (j = 0; j < size; j++) {
        int winnerIndex = indexTree[1];
        sortedKeys[j] = keys[winnerIndex];
        strcpy(sortedContent[j], content[winnerIndex]);

        keys[winnerIndex] = FLT_MAX;

        for (i = (treeSize / 2 + winnerIndex) / 2; i > 0; i /= 2) {
            indexTree[i] = (keys[indexTree[2 * i]] <= keys[indexTree[2 * i + 1]]) ? indexTree[2 * i] : indexTree[2 * i + 1];
        }
    }

    for (i = 0; i < size; i++) {
        keys[i] = sortedKeys[i];
        strcpy(content[i], sortedContent[i]);
    }

    free(indexTree);
}

void sortTable(table **Table) {
    if (*Table != NULL && (*Table)->countK > 1) {
        tournamentSort((*Table)->key, (*Table)->content, (*Table)->countK);
    }
}
```
7. **Замечания автора** Основные проблемы при выполнении были связаны с insertData.Так как для оптимальной работы было предусмотрено удаление "пустых" ключей,то нужно было находить пустые значения.Проверка if (content[0] != '0') неверна, так как она исключает строки, начинающиеся с символа '0'. Вместо этого нужно проверять, не является ли строка пустой. Проверяем строку на пустоту, а не элементю
Следуящая невнимательность, проблема с бинарным поиском. Важно поинить про максимальную длину ключа, иначе возникнут проблема с его поимком из за неточности значения.Длина 4, значит используем для принта printf("Key: %.3f"). Исправляем это везде, где надо выводить ключ(в printTable и в самой функции бинарного поиска binarySearch).
8. **Выводы**: Работа понравилось тем, что включала в себя несколько этапов. Необходтмо было продумывать каждую функцию,дабы избежать ошибок. Интересно было реализовывать функцию insertTable, так как неправильное чтение, вызовит некорректную работу дальнейших функйий. Стоит понмить, что работа идет именно с  вещественным типом ключа.
