#include "ypglpk.hpp"
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ypglpk::set_output(true);
    int N, M;
    std::cin >> N >> M;
    int NN = N + M;
    int MM = M + 3 * N;
    std::vector<std::vector<double>> A(MM, std::vector<double>(NN));
    std::vector<double> b(MM), c(NN);
    std::vector<int> vartype(NN);
    int u, v, w;
    for (int i = 0; i < M; i++)
    {
        std::cin >> u >> v >> w;
        A[i][u - 1] = 1;
        A[i][v - 1] = -1;
        A[i][N + i] = 10000;
        b[i] = 9999;
        c[N + i] = w;
        A[M + u - 1][N + i] = -1;
        A[M + v - 1][N + i] = 1;
        A[M + N + u - 1][N + i] = 1;
        A[M + N + v - 1][N + i] = -1;
        A[M + 2 * N + u - 1][N + i] = 1;
    }
    for (int i = 0; i < N - 1; i++)
    {
        b[M + 2 * N + i] = 1;
    }
    for (int i = 0; i < N; i++)
    {
        vartype[i] = GLP_IV;
    }
    for (int i = N; i < NN; i++)
    {
        vartype[i] = GLP_BV;
    }

    b[M] = -1;
    b[M + N - 1] = 1;
    b[M + N] = 1;
    b[M + 2 * N - 1] = -1;
    std::pair<double, std::vector<double>> res;
    res = ypglpk::mixed_integer_linear_programming(A, b, c, vartype);
    // std::pair<double, std::vector<double>> res;
    // res = ypglpk::linear_programming(A, b, c);

    if (res.first == -ypglpk::INF)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << (long long)res.first << "\n";
        for (int i = N; i < NN; i++)
        {
            std::cout << res.second[i];
        }
    }
}