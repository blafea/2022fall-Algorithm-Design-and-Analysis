#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (strcmp((char *)a, (char *)b));
}

int main()
{
    char input[1000000];
    int K;
    scanf("%s %d", input, &K);
    int N = strlen(input);
    char *cp = (char *)malloc(N * sizeof(char));
    strncpy(cp, input, N);
    qsort(cp, N, sizeof(char), compare);
    printf("%s", cp);
}