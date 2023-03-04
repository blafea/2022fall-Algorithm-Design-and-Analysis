#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void flip_coin(bool *truth_value, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (rand() > RAND_MAX / 2)
            truth_value[i] = true;
        else
            truth_value[i] = false;
    }
}

int _ceil(float num)
{
    int inum = (int)num;
    if (num == (float)inum)
    {
        return inum;
    }
    return inum + 1;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    bool *truth_value = (bool *)malloc(n * sizeof(bool));
    int **clause = (int **)malloc(m * sizeof(int *));
    bool **negative = (bool **)malloc(m * sizeof(bool *));
    int answer = 0;
    double answer_must = _ceil(m * 0.875);
    int wrong = 0;
    double wrong_must = _ceil(m * 0.125);
    for (int i = 0; i < m; i++)
    {
        clause[i] = (int *)malloc(3 * sizeof(int));
        negative[i] = (bool *)malloc(3 * sizeof(bool));
        scanf("%d %d %d", &clause[i][0], &clause[i][1], &clause[i][2]);
        for (int j = 0; j < 3; j++)
        {
            if (clause[i][j] < 0)
            {
                clause[i][j] = -clause[i][j];
                negative[i][j] = true;
            }
            clause[i][j]--;
        }
    }
    while (answer < answer_must)
    {
        answer = 0;
        wrong = 0;
        flip_coin(truth_value, n);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if ((!negative[i][clause[i][j]] && truth_value[clause[i][j]]) || (negative[i][clause[i][j]] && !truth_value[clause[i][j]]))
                {
                    answer++;
                    break;
                }

                else if (j == 2)
                    wrong++;
            }
            if (wrong > wrong_must)
                break;
            else if (answer > answer_must)
                break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (truth_value[i])
            printf("1 ");
        else
            printf("-1 ");
    }
}