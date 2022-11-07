#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <set>

class TEdgeDijkstra {
public:
    long long distance;
    unsigned goal;
};

bool operator < (const TEdgeDijkstra& left, const TEdgeDijkstra& right) {
    if (left.distance != right.distance) {
        return left.distance < right.distance;
    }
    return left.goal < right.goal;
}

std::vector<long long> Dijkstra(const std::vector<std::vector<TEdgeDijkstra>>& graph, unsigned n, unsigned start, long long max) {
    std::vector<long long> distances(n, max);
    distances[start] = 0;
    std::set<TEdgeDijkstra> vertices;
    vertices.insert({ 0, start });
    while (vertices.size()) {
        TEdgeDijkstra top = *vertices.begin();
        vertices.erase(vertices.begin());
        if (top.distance == max) {
            break;
        }
        unsigned initial = top.goal;
        unsigned size = graph[initial].size();
        for (unsigned i = 0; i < size; ++i) {
            TEdgeDijkstra local_edge = graph[initial][i];
            long long local_distance = local_edge.distance;
            unsigned local_goal = local_edge.goal;
            if (distances[local_goal] > distances[initial] + local_distance) {
                vertices.erase({ distances[local_goal], local_goal });
                distances[local_goal] = distances[initial] + local_distance;
                vertices.insert({ distances[local_goal], local_goal });
            }
        }
    }
    return distances;
}

#endif DIJKSTRA_H
