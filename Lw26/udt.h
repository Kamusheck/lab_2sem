#ifndef _UDT_H_
#define _UDT_H_

#include <stdbool.h>

typedef struct {
	int* data;
	int front;
	int rear;
	int size;
	int capacity;
} udt;

udt* udt_create(int capacity);
bool udt_is_empty (const udt *);
void udt_push(udt *, int);
void udt_pop(udt *);
void udt_print(const udt*);
int udt_get(const udt*);
int udt_size(const udt *);
void udt_insert(udt *, const int);
void udt_erase(udt *, const int key);
void udt_shift_smaller(udt *queue);
void udt_bubble_sort(udt *queue);
void udt_destroy(udt* queue);

#endif
