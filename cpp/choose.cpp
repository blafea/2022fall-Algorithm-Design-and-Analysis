#include "choose.h"
#include <iostream>
#include <algorithm>

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/

// this is an example usage
bool compare(int a, int b)
{
    return compare_task(a, b) == 1;
}

void schedule(int N)
{
    if (N == 1)
        assign_task(1, 1);
    if (N == 2)
    {
        assign_task(1, 1);
        assign_task(2, 2);
    }
    if (N > 2)
    {
        int needtime[N], endtimea, endtimeb;
        for (int i = 1; i < N + 1; i++)
        {
            needtime[i - 1] = i;
        }
        std::sort(needtime, needtime + N, compare);

        int i = 2;
        endtimea = assign_task(1, needtime[0]);
        endtimeb = assign_task(2, needtime[1]);
        while (i != N)
        {
            if (endtimea < endtimeb)
                endtimea = assign_task(1, needtime[i++]);
            else
                endtimeb = assign_task(2, needtime[i++]);
        }
    }
}
