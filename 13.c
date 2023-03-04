#include <stdio.h>
#include <stdlib.h>

typedef struct _order
{
    int pri;
    int idx;
    int mem;
} order;

typedef struct _customer
{
    int a;
    int b;
} customer;

int compare(const void *a, const void *b)
{
    order *ordera = (order *)a;
    order *orderb = (order *)b;
    if (ordera->pri < orderb->pri)
        return 1;
    else
        return -1;
}

int compare2(const void *a, const void *b)
{
    customer *custa = (customer *)a;
    customer *custb = (customer *)b;
    return custb->b - custa->b;
}

int main()
{
    int N;
    scanf("%d", &N);
    int *group_member = (int *)malloc(N * sizeof(int));
    int *sum_make = (int *)malloc(N * sizeof(int));
    order *make_number = (order *)malloc(N * sizeof(order));
    customer **cust = (customer **)malloc(N * sizeof(customer *));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &make_number[i].mem);
        sum_make[i] = 0;
        cust[i] = (customer *)malloc(make_number[i].mem * sizeof(customer));
        for (int j = 0; j < make_number[i].mem; j++)
        {
            scanf("%d %d", &cust[i][j].a, &cust[i][j].b);
            sum_make[i] += cust[i][j].a;
        }
        make_number[i].pri = make_number[i].mem * 10000;
        make_number[i].pri = make_number[i].pri / sum_make[i];
        make_number[i].idx = i;
        qsort(cust[i], make_number[i].mem, sizeof(customer), compare2);
    }
    qsort(make_number, N, sizeof(order), compare);
    long long int wait_time = 0;
    long long int make_time_now = 0;
    long long int make_time = 0;
    long long int answer = 0;
    for (int i = 0; i < N; i++)
    {
        answer += make_time * make_number[i].mem;
        make_time += sum_make[i];
        make_time_now = 0;
        wait_time = sum_make[i] + cust[make_number[i].idx][make_number[i].mem - 1].b;
        for (int j = 0; j < make_number[i].mem; j++)
        {
            make_time_now += cust[make_number[i].idx][j].a;
            if (wait_time < make_time_now + cust[make_number[i].idx][j].b)
            {
                wait_time = make_time_now + cust[make_number[i].idx][j].b;
            }
        }
        answer += wait_time * make_number[i].mem;
    }
    printf("%lld", answer);
}