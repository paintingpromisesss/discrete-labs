#include <vector>
#include <iostream>

const long long INF = 1e18;
struct Edge
{
    int from, to;
    long long weight;
};

long long BellmanFord(int n, int m, int start, int finish, const std::vector<Edge> &edges)
{

    std::vector<long long> dist(n + 1, INF);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        bool changed = false;
        std::vector<long long> prev_dist = dist;
        for (const auto &edge : edges)
        {
            if (prev_dist[edge.from] != INF && prev_dist[edge.from] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = prev_dist[edge.from] + edge.weight;
                changed = true;
            }
        }
        if (dist[finish] != INF && !changed)
        {
            break;
        }
    }

    if (dist[finish] == INF)
    {
        return -1;
    }
    else
    {
        return dist[finish];
    }
}

int main()
{
    int n, m, start, finish;
    std::cin >> n >> m >> start >> finish;

    std::vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    long long result = BellmanFord(n, m, start, finish, edges);
    if (result == -1)
    {
        std::cout << "No solution" << std::endl;
    }
    else
    {
        std::cout << result << std::endl;
    }
}