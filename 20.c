#include <stdio.h>
#include <stdlib.h>

long int weight[1000000];
long int prefix[1000000];
int total = 1;

typedef struct _block
{
    long int w;
    int idx;
} block;

block list[1000000];

int compare1(const void *a, const void *b)
{
    block *blockA = (block *)a;
    block *blockB = (block *)b;

    return (blockA->w - blockB->w);
}

int compare2(const void *a, const void *b)
{
    block *blockA = (block *)a;
    block *blockB = (block *)b;

    return (blockA->idx - blockB->idx);
}

int main()
{
    int M, x, k;
    scanf("%d", &M);
    char op[4];
    scanf("%s %ld", op, &weight[0]);
    prefix[0] = weight[0];
    for (int i = 0; i < M - 1; i++)
    {
        scanf("%s", op);
        switch (op[0])
        {
        case 'P':
            scanf("%ld", &weight[total]);
            prefix[total] = prefix[total - 1] + weight[total];
            total++;
            break;
        case 'T':
            printf("%ld\n", weight[total - 1]);
            total--;
            break;
        case 'C':
        {
            scanf("%d %d", &x, &k);
            int amount = (x - 1) / k + 1;
            total -= x;
            for (int i = 0; i < x; i++)
            {
                list[i].idx = i;
                list[i].w = weight[total + i];
            }
            qsort(list, x, sizeof(block), compare1);
            long int ans = 0;
            int min_idx = __INT_MAX__;
            for (int i = x - 1; i >= x - amount; i--)
            {
                ans += list[i].w;
                if (list[i].idx < min_idx)
                    min_idx = list[i].idx;
            }
            qsort(list, x - amount, sizeof(block), compare2);
            total += min_idx;
            if (x != amount)
            {
                if (total == 0)
                {
                    weight[0] = list[0].w;
                    prefix[0] = weight[0];
                }
                else
                {
                    weight[total] = list[min_idx].w;
                    prefix[total] = prefix[total - 1] + weight[total];
                }
                for (int i = 1; i < x - amount - min_idx; i++)
                {
                    weight[total + i] = list[min_idx + i].w;
                    prefix[total + i] = prefix[total + i - 1] + weight[total + i];
                }
                total += (x - amount - min_idx);
            }
            char str[100];
            sprintf(str, "%ld", ans);
            puts(str);
            break;
        }
        case 'D':
            scanf("%d", &x);
            printf("%ld\n", prefix[total - 1] - prefix[total - x - 1]);
            // for (int i = 0; i < x; i++)
            // {
            //     printf("%ld\n", prefix[i]);
            // }
            break;

        default:
            break;
        }
    }
}