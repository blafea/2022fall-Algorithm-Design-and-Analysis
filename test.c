#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main()
{
    // int a[5] = {5, 2, 3, 4, 7};
    // qsort(a, 5, sizeof(int), cmp);
    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d", a[i]);
    // }
    // int a[5] = {1, 2, 3, 4, 5};
    // printf("%d", -a[3]);
    int a = 100 * 0.875;
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", rand());
    }
}