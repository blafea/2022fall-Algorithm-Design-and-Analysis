#include <stdio.h>
#include <stdlib.h>

typedef struct _point
{
    int x, y;
    long long int from_up, from_down;
} point;

int compare(const void *a, const void *b)
{
    point *c = (point *)a;
    point *d = (point *)b;
    if (c->from_up < d->from_up)
    {
        return -1;
    }
    else if (c->from_up == d->from_up)
    {
        if (c->from_down > d->from_down)
        {
            return -1;
        }
        else
            return 1;
    }
    else
        return 1;
}

int merge(point arr[], point temp[], int left, int mid, int right)
{
    int i, j, k;
    long long int count = 0;

    i = left;
    j = mid;
    k = left;
    while ((i <= mid - 1) && (j <= right))
    {
        if (arr[i].from_down < arr[j].from_down)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            count += mid - i;
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return count;
}

int mergeSort(point arr[], point temp[], int left, int right)
{
    int mid;
    long long int count = 0;
    if (right > left)
    {
        mid = (right + left) / 2;

        count += mergeSort(arr, temp, left, mid);
        count += mergeSort(arr, temp, mid + 1, right);
        count += merge(arr, temp, left, mid + 1, right);
    }
    return count;
}

int main()
{
    int n, lcm;
    scanf("%d", &n);
    long long int l1, l2, r1, r2, temp;
    scanf("%lld %lld %lld %lld", &l1, &l2, &r1, &r2);
    // printf("AAA%d\n", lcm);
    point *points = (point *)malloc(n * sizeof(point));
    point *points2 = (point *)malloc(n * sizeof(point));
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &points[i].x, &points[i].y);
        points[i].from_up = points[i].y * l2 - l1 * points[i].x;
        points[i].from_down = points[i].y * r2 - r1 * points[i].x;
    }
    qsort(points, n, sizeof(point), compare);
    // for (int i = 0; i < 5; i++)
    //     printf("%d %d %ld %ld\n", points[i].x, points[i].y, points[i].from_up, points[i].from_down);
    // printf("\n");
    long long int count;
    count = mergeSort(points, points2, 0, n - 1);
    printf("%lld", count);
    // for (int i = 0; i < 5; i++)
    //     printf("%d %d %ld %ld\n", points[i].x, points[i].y, points[i].from_up, points[i].from_down);
}