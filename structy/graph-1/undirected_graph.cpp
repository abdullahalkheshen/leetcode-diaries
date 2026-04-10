#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include <string>

std::unordered_map<std::string, std::vector<std::string>> makeGraph(std::vector<std::tuple<std::string, std::string>> edges) {
  std::unordered_map<std::string, std::vector<std::string>> graph;
  for (auto edge : edges) {
    auto [ a, b ] = edge;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  return graph;
}

bool undirectedPath(std::unordered_map<std::string, std::vector<std::string>> graph, std::string src, std::string dst, std::unordered_set<std::string> &visited) {
  if (src == dst) {
    return true;
  }
  
  if (visited.count(src) > 0) {
    return false;
  }
  
  visited.insert(src);
  
  for (std::string neighbor : graph[src]) {
    if (undirectedPath(graph, neighbor, dst, visited)) {
      return true;
    }
  }

  return false;
}

bool undirectedPath(std::vector<std::tuple<std::string, std::string>> edges, std::string src, std::string dst) {
  std::unordered_map<std::string, std::vector<std::string>> graph = makeGraph(edges); 
  std::unordered_set<std::string> visited;
  return undirectedPath(graph, src, dst, visited); 
}
