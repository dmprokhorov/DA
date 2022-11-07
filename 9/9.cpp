#include <iostream>
#include <climits>
#include "BellmanFord.h"
#include "Dijkstra.h"

long long max = 1e18;

int main()
{
    unsigned n, m;
    std::cin >> n >> m;
    std::vector<TEdgeBellmanFord> edges(m + n);
    std::vector<std::vector<TEdgeDijkstra>> graph(n + 1);
    for (unsigned i = 1; i < n + 1; ++i) {
        edges[i - 1] = { 0, i, 0 };
        graph[0].push_back({ 0, i });
    }
    for (unsigned i = 0; i < m; ++i) {
        unsigned u, v;
        long long c;
        std::cin >> u >> v >> c;
        graph[u].push_back({ c, v });
        edges[i + n] = { u, v, c };
    }
    std::vector<long long> distances_from_super_vertex = BellmanFord(edges, n + 1, max);
    if (distances_from_super_vertex.empty()) {
        std::cout << "Negative cycle\n";
    }
    else {
        for (unsigned i = 0; i < n + 1; ++i) {
            unsigned size = graph[i].size();
            for (unsigned j = 0; j < size; ++j) {
                graph[i][j].distance += distances_from_super_vertex[i] - distances_from_super_vertex[graph[i][j].goal];
            }
        }
        for (unsigned i = 1; i < n + 1; ++i) {
            std::vector<long long> distances_from_iteration = Dijkstra(graph, n + 1, i, max);
            for (unsigned j = 1; j < n + 1; ++j) {
                if (distances_from_iteration[j] != max) {
                    std::cout << distances_from_iteration[j] + distances_from_super_vertex[j] - distances_from_super_vertex[i] << " ";
                }
                else {
                    std::cout << "inf ";
                }
            }
            std::cout << "\n";
        }
    }
    return 0;
}
