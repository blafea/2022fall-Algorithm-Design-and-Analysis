#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int c = *(int *)a;
    int d = *(int *)b;
    if (c < d)
    {
        return -1;
    }
    else
        return 1;
}

int *best(int W, int gems[], int N)
{
    int *remain = (int *)malloc((W + 1) * sizeof(int));
    for (int i = 0; i <= W; i++)
    {
        remain[i] = i;
    }

    for (int i = 0; i < N; i++)
    {
        if (gems[i] <= W)
        {
            remain[gems[i]] = 0;
        }
    }

    for (int i = 1; i <= W; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (gems[j] < i)
            {
                if (remain[i - gems[j]] < remain[i])
                {
                    remain[i] = remain[i - gems[j]];
                }
            }
        }
    }
    return remain;
}

int *greedy(int W, int gems[], int N)
{
    int *remain = (int *)malloc((W + 1) * sizeof(int));
    for (int i = 0; i < W + 1; i++)
    {
        remain[i] = i;
        for (int j = N - 1; j >= 0; j--)
        {
            remain[i] = remain[i] % gems[j];
        }
    }
    return remain;
}

int main()
{
    int N, W;
    scanf("%d %d", &N, &W);
    int *gems = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &gems[i]);
    qsort(gems, N, sizeof(int), compare);
    int *remain_best = (int *)malloc((W + 1) * sizeof(int));
    int *remain_greedy = (int *)malloc((W + 1) * sizeof(int));
    remain_best = best(W, gems, N);
    remain_greedy = greedy(W, gems, N);
    for (int i = 1; i < W + 1; i++)
        printf("%d\n", remain_greedy[i] - remain_best[i]);
}