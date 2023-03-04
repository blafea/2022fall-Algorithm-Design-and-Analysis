#include <iostream>
#include <vector>
using namespace std;

int distance(string x, string y)
{
    int m = x.size(), n = y.size(), pre, temp;
    vector<int> dp(n + 1, 0);
    for (int j = 1; j <= n; j++)
    {
        dp[j] = j;
    }
    for (int i = 1; i <= m; i++)
    {
        pre = dp[0];
        dp[0] = i;
        for (int j = 1; j <= n; j++)
        {
            temp = dp[j];
            if (x[i - 1] == y[j - 1])
            {
                dp[j] = pre;
            }
            else
            {
                dp[j] = min(pre, min(dp[j - 1], dp[j])) + 1;
            }
            pre = temp;
        }
    }
    return dp[n];
}

int main()
{
    string a, b;
    cin >> a >> b;
    cout << distance(a, b);
}