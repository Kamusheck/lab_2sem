#ifndef _CP9_H_
#define _CP9_H_

typedef struct {
    float key[10];        // Вещественные ключи длиной в 4 байта
    char content[10][12]; // Предполагаем, что длина каждого элемента содержимого - 12 символов
    int countK;           // Количество ключей, должно быть от 8 до 10
    int countC;           // Количество элементов содержимого, должно быть от 8 до 10
} table;

void sortTable(table **Table);
void insertData(table **Table);
void binarySearch(table *Table, float key);
void printTable(table *Table);
int isAllSpaces(const char *str);
float roundFloat(float value, int places);

#endif

