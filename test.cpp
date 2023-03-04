#include <iostream>
#include <algorithm>

int time_[5] = {1, 2, 3, 4, 5};
int compare2(int a, int b)
{
    if (time_[a] > time_[b])
        return 1;
    else if (time_[a] == time_[b])
        return 0;
    else
        return -1;
}
bool compare(const int &a, const int &b)
{
    return compare2(a, b) == 1;
}
int main()
{
    int N = 4;
    int needtime[N];
    for (int i = 1; i < N + 1; i++)
    {
        needtime[N] = i;
    }

    std::sort(needtime, needtime + N, compare);
}