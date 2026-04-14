//
// Created by abdul on 4/13/2026.
//

#include "solution.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>


void dfs(std::unordered_map<int, std::vector<int>> graph, int node, std::unordered_set<int> &visited) {
  if (visited.count(node)) return;
  visited.insert(node);
  for (auto neighbor : graph[node]) {
    dfs(graph, neighbor, visited);
  }
}


int connectedComponentsCount(std::unordered_map<int, std::vector<int>> graph) {
  std::unordered_set<int> visited;
  int count = 0;
  for (auto [node, _] : graph) {
    if (visited.count(node)) continue;
    dfs(graph, node, visited);
    count++;
  }
  return count;
}


int main() {
  std::unordered_map<int, std::vector<int>> graph = {
    {0, {1, 2}},
    {1, {0, 2}},
    {2, {0, 1}},
    {3, {4}},
    {4, {3}}
  };
  std::cout << connectedComponentsCount(graph) << std::endl;
  return 0;
}