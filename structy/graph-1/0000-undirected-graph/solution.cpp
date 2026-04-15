/**
 * Problem: Undirected Path
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, DFS, Undirected Graph, Path Finding
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Write a function that takes in an array of edges for an undirected graph
    and two nodes (src, dst). The function should return a boolean indicating
    whether or not there exists a path between src and dst.

    Example 1:
    Input: edges = [["a","b"],["b","c"],["c","d"],["d","e"],["f","g"]], 
           src = "a", dst = "e"
    Output: true
    Explanation: Path exists: a -> b -> c -> d -> e

    Example 2:
    Input: edges = [["a","b"],["b","c"],["c","d"],["d","e"],["f","g"]], 
           src = "a", dst = "f"
    Output: false
    Explanation: No path between "a" and "f" (different components)

    Constraints:
    - Graph is undirected
    - Graph may have cycles
    - Nodes are strings
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <unordered_map>
#include <unordered_set>

// ---------------------------------------------------------------------------

// Approach #1: DFS with Edge List to Adjacency List Conversion

/*
    Intuition:
    First convert the edge list to an adjacency list for efficient traversal.
    Then use DFS with a visited set to find if a path exists between src and
    dst. The visited set prevents infinite loops in cyclic graphs.

    Algorithm:
    1. Build adjacency list from edge list (add both directions for undirected)
    2. DFS from src:
       a. If current node equals dst, return true
       b. If current node is visited, return false
       c. Mark current as visited
       d. Recursively check all neighbors
    3. Return false if no path found

    Complexity Analysis:
    - Time: O(V + E) where V is vertices and E is edges
    - Space: O(V + E) for adjacency list and visited set
*/

class Solution {
public:
    using Graph = std::unordered_map<std::string, std::vector<std::string>>;
    using EdgeList = std::vector<std::tuple<std::string, std::string>>;

    Graph make_graph(const EdgeList& edges) {
        Graph graph;
        for (const auto& edge : edges) {
            auto [a, b] = edge;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        return graph;
    }

    bool dfs(Graph& graph, const std::string& src, const std::string& dst,
             std::unordered_set<std::string>& visited) {
        if (src == dst) return true;
        if (visited.count(src) > 0) return false;

        visited.insert(src);
        for (const std::string& neighbor : graph[src]) {
            if (dfs(graph, neighbor, dst, visited)) return true;
        }
        return false;
    }

    bool undirected_path(const EdgeList& edges, 
                         const std::string& src, 
                         const std::string& dst) {
        Graph graph = make_graph(edges);
        std::unordered_set<std::string> visited;
        return dfs(graph, src, dst, visited);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    Solution::EdgeList edges = {
        {"a", "b"},
        {"b", "c"},
        {"c", "d"},
        {"d", "e"},
        {"f", "g"}
    };

    // Test 1: Path exists
    bool result1 = sol.undirected_path(edges, "a", "e");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;

    // Test 2: No path (different components)
    bool result2 = sol.undirected_path(edges, "a", "f");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;

    // Test 3: Same source and destination
    bool result3 = sol.undirected_path(edges, "a", "a");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;

    // Test 4: Adjacent nodes
    bool result4 = sol.undirected_path(edges, "a", "b");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;

    // Test 5: Path in isolated component
    bool result5 = sol.undirected_path(edges, "f", "g");
    std::cout << "Test 5: " << (result5 == true ? "PASS" : "FAIL") << std::endl;

    return 0;
}
