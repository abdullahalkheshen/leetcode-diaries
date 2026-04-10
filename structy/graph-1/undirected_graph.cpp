#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>
#include <bits/ctype_base.h>


// solve the problem of finding if there exists a path form nodeA to nodeB in a undirected graph.

std::unordered_map<std::string, std::vector<std::string>> makeGraph(std::vector<std::tuple<std::string, std::string>> edges) {
    std::unordered_map<std::string, std::vector<std::string>> graph;
    for (auto &&edge : edges) {
        auto [a,b] = edge;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    return graph;
}

bool undirectedPath(std::vector<std::tuple<std::string, std::string>> edges, std::string src, std::string dst) {
    if (src == dst) return true;
    if (visited.count(src) > 0) return false;
    visted.insert(src);

}

bool explore (std::unordered_map<std::string, std::vector<std::string>> graph, std::string src, std::string visited[]) {
    if (src == dst) return true;
    for (std::string neighbor : graph[src]) {
        if (explore(graph, neighbor, visited)) return true;
    }
    return false;
}

void main () {

}