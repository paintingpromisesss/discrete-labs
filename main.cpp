#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

void dfs(int v, std::vector<std::vector<int>> &graph, std::vector<int> &color, std::vector<int> &result, bool &is_cycle)
{
    color[v] = 1;
    for (int u : graph[v])
    {
        if (color[u] == 1)
        {
            is_cycle = true;
            return;
        }
        if (color[u] == 0)
            dfs(u, graph, color, result, is_cycle);
    }
    color[v] = 2;
    result.push_back(v);
}

int main()
{
    bool is_cycle = false;

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n + 1);

    std::vector<int> color(n + 1, 0), result;

    int arg = INT32_MAX;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
    {
        if (color[i] == 0) dfs(i, graph, color, result, is_cycle);
    }

    if (is_cycle)
    {
        std::cout << -1 << std::endl;
    }
    else
    {
        for (int i = n - 1; i > 0; i--)
        {
            std::cout << result[i] << " " << result[i - 1] << std::endl;
        }
    }
}