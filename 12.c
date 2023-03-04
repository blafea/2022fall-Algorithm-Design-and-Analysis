#include <stdio.h>
#include <stdlib.h>

void cal_maxsub(long long int N, int *nums, long long int **maxsub, int start)
{
    maxsub[start][start] = nums[start];
    int now = nums[start];
    for (int i = start + 1; i < N; i++)
    {
        if (now > 0)
            now = now + nums[i];
        else
            now = nums[i];
        if (maxsub[start][i - 1] < now)
            maxsub[start][i] = now;
        else
            maxsub[start][i] = maxsub[start][i - 1];
    }
    if (start < N - 1)
        cal_maxsub(N, nums, maxsub, start + 1);
}

void cal_ans(long long int N, long long int K, long long int **maxsub, long long int **ans)
{
    for (int i = 0; i < N; i++)
        ans[0][i] = maxsub[0][i] * (i + 1);
    for (int i = 1; i < K; i++)
    {
        for (int j = i; j < N; j++)
        {
            ans[i][j] = __INT64_MAX__;
            for (int k = 0; k < j; k++)
            {
                if (ans[i][j] > ans[i - 1][k] + maxsub[k + 1][j] * (j - k))
                    ans[i][j] = ans[i - 1][k] + maxsub[k + 1][j] * (j - k);
            }
        }
    }
}

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);
    int *nums = (int *)malloc(N * sizeof(int));
    long long int **maxsub = (long long int **)malloc(N * sizeof(long long int *));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &nums[i]);
        maxsub[i] = (long long int *)malloc(N * sizeof(long long int));
    }
    cal_maxsub(N, nums, maxsub, 0);
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = i; j < N; j++)
    //         printf("%d ", maxsub[i][j]);
    //     printf("\n");
    // }
    long long int **ans = (long long int **)malloc(K * sizeof(long long int *));
    for (int i = 0; i < K; i++)
    {
        ans[i] = (long long int *)malloc(N * sizeof(long long int));
    }
    cal_ans(N, K, maxsub, ans);
    // for (int i = 0; i < K; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //         printf("%d ", ans[i][j]);
    //     printf("\n");
    // }
    printf("%lld", ans[K - 1][N - 1]);
}