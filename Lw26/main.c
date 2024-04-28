#include <stdio.h>
#include "udt.h"

// 2 6
// 34
// 67
// 78
// 54
// 13

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
