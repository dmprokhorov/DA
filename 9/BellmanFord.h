
#ifndef BELLMANFORD_H
#define BELLMANFORD_H
#include <vector>

class TEdgeBellmanFord {
public:
	unsigned from, to;
	long long distance;
};

std::vector<long long> BellmanFord(const std::vector<TEdgeBellmanFord>& edges, unsigned n, long long max) {
	unsigned m = edges.size();
	std::vector<long long> distances(n, max);
	distances[0] = 0;
	bool changes = false;
    for (unsigned i = 0; i < n - 1; ++i) {
        changes = false;
        for (unsigned j = 0; j < m; ++j) {
            TEdgeBellmanFord current_edge = edges[j];
            if ((distances[current_edge.from] != max) &&
                (distances[current_edge.to] > distances[current_edge.from] + current_edge.distance)) {
                changes = true;
                distances[current_edge.to] = distances[current_edge.from] + current_edge.distance;
            }
        }
        if (!changes) {
            break;
        }
    }
    bool negative_cycle = false;
    if (changes) {
        for (unsigned j = 0; j < m; ++j) {
            TEdgeBellmanFord current_edge = edges[j];
            if ((distances[current_edge.from] != max) &&
                (distances[current_edge.to] > distances[current_edge.from] + current_edge.distance)) {
                negative_cycle = true;
                break;
            }
        }
    }
    if (negative_cycle) {
        return {};
    }
    return distances;
}

#endif BELLMANFORD_H
