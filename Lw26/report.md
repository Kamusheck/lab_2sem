# Отчёт по лабораторной работе №26

---

## по курсу "Алгоритмы и структуры данных"


Студент группы М8О-108Б-23 Исмаилова Камила

Работа выполнена

Преподаватель: каф.806 Севастьянов Виктор Сергеевич
1. Тема: Абстрактные типы данных. Рекурсия. Модульное программирование на языке Си.
2. Цель работы: составить и отладить модуль определений и модуль реализации по заданной схеме модуля определений для абстрактного типа данных.
3. Задание: 2-4 (поиск в очереди элементов,первый из которых больше второго, ваполнить перестановку методом пузырька
4. Идея, метод, алгоритм решения задачи:
   - определиться с основными функциями из схемы.
   - прописать основные функции,удаление, добавление элементф и т.д.;
   - пропимать функцию сортировки и сделать makefile;
   - протестить ;
5. Сценарий выполнения работы:
    Многострадальные тесты:

|Входные данные|Выходные данные|
|--------------|---------------|
|      2       |       1       |
|      3       |       2       |
|      1       |       3       |

6. Протокол:
    ```
#include "udt.h"
#include <stdlib.h>
#include <stdio.h>

udt* udt_create(int capacity) {
	udt* queue = (udt*)malloc(sizeof(udt));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->data = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

bool udt_is_empty(const udt *queue) {
	return (queue->size == 0);
}

void udt_push(udt *queue, int item) {
	if (queue->size == queue->capacity) return;
	queue->rear = (queue->rear + 1)%queue->capacity;
	queue->data[queue->rear] = item;
	queue->size = queue->size + 1;
}

void udt_pop(udt *queue) {
	if (udt_is_empty(queue)) return;
	queue->front = (queue->front + 1)%queue->capacity;
	queue->size = queue->size - 1;
}

int udt_get(const udt* queue) {
	return queue->data[queue->front];
}

void udt_print(const udt* queue) {
	int i;
	for (i = 0; i < queue->size; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

int udt_size(const udt *queue) {
	return queue->size;
}

void udt_destroy(udt* queue) {
    free(queue->data);
    free(queue);
}

void udt_find_and_swap(udt* queue) {
    for (int i = 0; i < queue->size - 1; i++) {
        int current = queue->data[i];
        int next = queue->data[i + 1];
        if (current > next) {
            queue->data[i] = next;
            queue->data[i + 1] = current;
            break;
        }
    }
}

void udt_bubble_sort(udt* queue) {
    int size = queue->size;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            udt_find_and_swap(queue);
        }
    }
}
```

```
#include <stdio.h>
#include "udt.h"

int main(int argc, char *argv[])
{
    int val;
    udt *q = udt_create(100);

    while (scanf("%d", &val) == 1)
        udt_push(q, val);

    udt_bubble_sort(q);

    printf("\n");
    while (!udt_is_empty(q)) {
        val = udt_get(q);
        printf("%d\n", val);
        udt_pop(q);
    }

    udt_destroy(q);

    return 0;
}
```
8. Вывод: Интересная работа, которая дала попрактиваться в работе с очередью и вспомнить про сортировку пузырьком.Прописывание функций и внедрение  в файл было не супер сложным,но прописывать надо внимательно.
