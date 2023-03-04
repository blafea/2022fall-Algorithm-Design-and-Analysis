#include <stdio.h>
#include <stdlib.h>

long long int dp[400][400];
long long int answer[400][400];
int table[400][400];

int main()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &table[i][j]);
        }
    }
    // cut = (cut-1, cut)
    long long int sum, sum2;
    for (int cut = 0; cut < N - 1; cut++)
    {
        dp[cut][0] = table[cut][cut];
        answer[cut][0] = dp[cut][0];
        for (int cut2 = cut + 1; cut2 < N; cut2++)
        {
            dp[cut2][0] = table[cut2][cut];
        }

        for (int k = 1; k < N - cut; k++)
        {
            sum = table[cut][cut + 1] + dp[cut + 1][k - 1];
            for (int cut2 = cut + 1; cut2 < N - (k - 1); cut2++)
            {
                sum2 = table[cut2][cut2 + 1] + dp[cut2 + 1][k - 1];
                for (int cut_end = cut2 + 2; cut_end < N - (k - 1); cut_end++)
                {
                    if (sum2 < table[cut2][cut_end] + dp[cut_end][k - 1])
                        sum2 = table[cut2][cut_end] + dp[cut_end][k - 1];
                }
                dp[cut2][k] = sum2;
            }

            for (int cut2 = cut + 2; cut2 < N - (k - 1); cut2++)
            {

                if (sum < table[cut][cut2] + dp[cut2][k - 1])
                {
                    sum = table[cut][cut2] + dp[cut2][k - 1];
                }
            }
            dp[cut][k] = sum;
            answer[cut][k] = sum;
        }
        // if (cut == 1)
        // {
        //     printf("AAA%dAAA\n", dp[2][1]);
        // }
    }
    // printf("\n");
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%d ", answer[i][j]);
    //     }
    //     printf("\n");
    // }
    answer[N - 1][0] = table[N - 1][N - 1];
    long long int max = 0;
    for (int j = 0; j < N - 1; j++)
    {
        for (int i = 0; i < N - j; i++)
        {
            if (max < answer[i][j])
                max = answer[i][j];
        }
        printf("%lld ", max);
        max = 0;
    }
    for (int i = 0; i < N - 1; i++)
    {
        max += table[i][i + 1];
    }
    printf("%lld", max + table[N - 1][0]);
}