#include "structure.h"
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
