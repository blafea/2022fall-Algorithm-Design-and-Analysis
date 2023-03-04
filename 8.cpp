#include <iostream>
using namespace std;

void LEGO(int start, int end)
{
    // cout << start << end << "\n";
    if (start == end)
    {
        cout << "PLACE " << start << "\n";
        cout << "PHOTO\n";
        cout << "POP\n";
        return;
    }
    int mid = (start + end) / 2 + ((start + end) % 2);
    for (int i = mid; i <= end; i++)
        cout << "PLACE " << i << "\n";
    if (start == mid - 1)
        cout << "PLACE " << start << "\n"
             << "PHOTO\n"
             << "POP\n";
    else
        LEGO(start, mid - 1);

    for (int i = mid; i <= end; i++)
        cout << "POP\n";
    for (int i = start; i < mid; i++)
        cout << "PLACE " << i << "\n";
    if (mid == end)
        cout << "PLACE " << end << "\n"
             << "PHOTO\n"
             << "POP\n";
    else
        LEGO(mid, end);
    for (int i = start; i < mid; i++)
        cout << "POP\n";
    return;
}

int main()
{
    int n;
    cin >> n;
    int a = 2 * n - 1;
    int b = n - 1;
    int c = 1;
    while (b >= 0)
    {
        a += b;
        b -= c;
        c += c;
    }
    cout << a * 2 + n << "\n";
    LEGO(1, n);
}