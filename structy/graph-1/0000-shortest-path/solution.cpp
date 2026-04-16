/**
 * Problem: Shortest Path
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, BFS, Shortest Path, Undirected Graph
 *
 * Date Solved: 2026-04-16
 * Time Taken: 10 min
 */

/*
    Problem Statement:
    Write a function that takes in an array of edges for an undirected graph
    and two nodes (nodeA, nodeB). The function should return the length of the
    shortest path between A and B. Consider the length as the number of edges
    in the path, not the number of nodes. If there is no path between A and B,
    then return -1.

    Example 1:
    Input: edges = [
        ['w', 'x'],
        ['x', 'y'],
        ['z', 'y'],
        ['z', 'v'],
        ['w', 'v']
    ], nodeA = 'w', nodeB = 'z'
    Output: 2
    Explanation: Shortest path is w -> v -> z (2 edges)

    Example 2:
    Input: edges = [
        ['w', 'x'],
        ['x', 'y'],
        ['z', 'y'],
        ['z', 'v'],
        ['w', 'v']
    ], nodeA = 'y', nodeB = 'x'
    Output: 1
    Explanation: Direct edge y -> x (1 edge)

    Example 3:
    Input: edges = [
        ['a', 'c'],
        ['a', 'b'],
        ['c', 'b'],
        ['c', 'd'],
        ['b', 'd'],
        ['e', 'd'],
        ['g', 'f']
    ], nodeA = 'a', nodeB = 'e'
    Output: 3
    Explanation: Shortest path is a -> c -> d -> e (3 edges)

    Example 4:
    Input: edges = [
        ['a', 'c'],
        ['a', 'b'],
        ['c', 'b'],
        ['c', 'd'],
        ['b', 'd'],
        ['e', 'd'],
        ['g', 'f']
    ], nodeA = 'b', nodeB = 'g'
    Output: -1
    Explanation: No path exists between b and g

    Constraints:
    - Graph is undirected
    - Edges are unweighted (each edge has weight 1)
    - Nodes are represented as characters/strings
    - Graph may have multiple disconnected components
*/

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <queue>

// ---------------------------------------------------------------------------

// Approach #1: BFS for Shortest Path

/*
    Intuition:
    We can use BFS to find the shortest path between two nodes in an undirected graph.
    BFS is a perfect fit for this problem because it explores all nodes at the current
    distance before moving to the next distance.

    Algorithm:
    1. Convert the edge list to an adjacency list.
    2. Use BFS to find the shortest path between the two nodes.
    3. Return the length of the shortest path.

    Complexity Analysis:
    - Time: O(V + E) where V is vertices and E is edges
    - Space: O(V) for the visited set and queue
*/

class Solution {
public:
    using Graph = std::unordered_map<std::string, std::vector<std::string>>;

    Graph make_graph(const std::vector<std::vector<std::string>>& edges) {
        Graph graph;
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        return graph;
    }

    int bfs(const Graph& graph, const std::string& nodeA, const std::string& nodeB) {
        if (graph.find(nodeA) == graph.end()) return -1;
        
        std::queue<std::tuple<std::string, int>> queue;
        queue.push({nodeA, 0});
        std::unordered_set<std::string> visited;
        visited.insert(nodeA);
        
        while (!queue.empty()) {
            auto [current, distance] = queue.front();
            queue.pop();
            
            if (current == nodeB) return distance;
            
            for (const std::string& neighbor : graph.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push({neighbor, distance + 1});
                }
            }
        }
        return -1;
    }

    int shortest_path(const std::vector<std::vector<std::string>>& edges,
                      const std::string& nodeA,
                      const std::string& nodeB) {
        Graph graph = make_graph(edges);
        return bfs(graph, nodeA, nodeB);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Path exists with length 2
    std::vector<std::vector<std::string>> edges1 = {
        {"w", "x"},
        {"x", "y"},
        {"z", "y"},
        {"z", "v"},
        {"w", "v"}
    };
    int result1 = sol.shortest_path(edges1, "w", "z");
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result1 << ")" << std::endl;

    // Test 2: Direct edge
    int result2 = sol.shortest_path(edges1, "y", "x");
    std::cout << "Test 2: " << (result2 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result2 << ")" << std::endl;

    // Test 3: Longer path
    std::vector<std::vector<std::string>> edges2 = {
        {"a", "c"},
        {"a", "b"},
        {"c", "b"},
        {"c", "d"},
        {"b", "d"},
        {"e", "d"},
        {"g", "f"}
    };
    int result3 = sol.shortest_path(edges2, "a", "e");
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result3 << ")" << std::endl;

    // Test 4: No path exists
    int result4 = sol.shortest_path(edges2, "b", "g");
    std::cout << "Test 4: " << (result4 == -1 ? "PASS" : "FAIL")
              << " (expected -1, got " << result4 << ")" << std::endl;

    // Test 5: Same node (distance 0)
    int result5 = sol.shortest_path(edges1, "w", "w");
    std::cout << "Test 5: " << (result5 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result5 << ")" << std::endl;

    return 0;
}
