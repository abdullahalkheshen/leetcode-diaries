#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

std::unordered_map<std::string, std::vector<std::string>> make_graph(
    std::vector<std::tuple<std::string, std::string>> edges)
{
  std::unordered_map<std::string, std::vector<std::string>> graph;
  for (auto edge : edges) {
    auto [a, b] = edge;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  return graph;
}

bool dfs(std::unordered_map<std::string, std::vector<std::string>>& graph,
         std::string src, std::string dst,
         std::unordered_set<std::string>& visited)
{
  if (src == dst) return true;
  if (visited.count(src) > 0) return false;

  visited.insert(src);
  for (std::string neighbor : graph[src]) {
    if (dfs(graph, neighbor, dst, visited)) return true;
  }
  return false;
}

bool undirectedPath(std::vector<std::tuple<std::string, std::string>> edges,
                    std::string src, std::string dst)
{
  auto graph = make_graph(edges);
  std::unordered_set<std::string> visited;
  return dfs(graph, src, dst, visited);
}

int main() {
  std::vector<std::tuple<std::string, std::string>> edges = {
    {"a", "b"},
    {"b", "c"},
    {"c", "d"},
    {"d", "e"},
    {"f", "g"}
  };

  std::cout << undirectedPath(edges, "a", "e") << "\n"; // 1 (true)
  std::cout << undirectedPath(edges, "a", "f") << "\n"; // 0 (false)

  return 0;
}