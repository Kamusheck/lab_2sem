#ifndef _CP9_H_
#define _CP9_H_

typedef struct {
    float key[10];        
    char content[10][12]; 
    int countK;           
    int countC;           
} table;

void sortTable(table **Table);
void insertData(table **Table);
void binarySearch(table *Table, float key);
void printTable(table *Table);
int isAllSpaces(const char *str);
float roundFloat(float value, int places);

#endif

