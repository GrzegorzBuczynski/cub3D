#include "garbage_collector.h"

int main()
{
    int *a = (int *)gmalloc(sizeof(int));
    int *b = (int *)gmalloc(sizeof(int));
    *a = 10;
    printf("a = %d\n", *a);
    gfree(a);
    gexit(0);
}