#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

int teleport(int arr[], int N)
{
    int **dp = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        dp[i] = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        dp[i][i] = i;
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; i + j < N; j++)
        {
            dp[j][i + j] = min(dp[j + 1][i + j], dp[j][i + j - 1]);
        }
    }
    int count;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (abs(arr[i] - arr[j]) == dp[j][i])
                count++;
        }
    }
    return count;
}

int main()
{
    int N;
    scanf("%d", &N);
    int *arr = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    int count;
    count = teleport(arr, N);
    printf("%d", count);
}