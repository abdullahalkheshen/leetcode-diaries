/**
 * Problem: Connected Components Count
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, DFS, Connected Components, Undirected Graph
 *
 * Date Solved: 2026-04-13
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Write a function that takes in the adjacency list of an undirected graph
    and returns the number of connected components within the graph.

    Example 1:
    Input: graph = {
        0: [1, 2],
        1: [0, 2],
        2: [0, 1],
        3: [4],
        4: [3]
    }
    Output: 2
    Explanation: Component 1: {0, 1, 2}, Component 2: {3, 4}

    Example 2:
    Input: graph = {
        0: [1],
        1: [0],
        2: []
    }
    Output: 3
    Explanation: Three separate components

    Constraints:
    - Graph is undirected
    - Graph may have multiple disconnected components
    - Nodes are integers
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// ---------------------------------------------------------------------------

// Approach #1: DFS with Visited Set

/*
    Intuition:
    A connected component is a group of nodes where every node can reach every
    other node. We iterate through all nodes, and for each unvisited node, we
    perform DFS to mark all nodes in its component as visited, then increment
    our count.

    Algorithm:
    1. Initialize a visited set and count = 0
    2. For each node in the graph:
       a. If node is not visited, perform DFS from that node
       b. DFS marks all reachable nodes as visited
       c. Increment count (found a new component)
    3. Return count

    Complexity Analysis:
    - Time: O(V + E) where V is vertices and E is edges
    - Space: O(V) for the visited set and recursion stack
*/

class Solution {
public:
    using Graph = std::unordered_map<int, std::vector<int>>;

    void dfs(const Graph& graph, int node, std::unordered_set<int>& visited) {
        if (visited.count(node)) return;
        visited.insert(node);

        for (int neighbor : graph.at(node)) {
            dfs(graph, neighbor, visited);
        }
    }

    int connected_components_count(const Graph& graph) {
        std::unordered_set<int> visited;
        int count = 0;

        for (const auto& [node, _] : graph) {
            if (visited.count(node)) continue;
            dfs(graph, node, visited);
            count++;
        }

        return count;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Two components
    Solution::Graph graph1 = {
        {0, {1, 2}},
        {1, {0, 2}},
        {2, {0, 1}},
        {3, {4}},
        {4, {3}}
    };
    int result1 = sol.connected_components_count(graph1);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 2: Single component
    Solution::Graph graph2 = {
        {0, {1}},
        {1, {0, 2}},
        {2, {1}}
    };
    int result2 = sol.connected_components_count(graph2);
    std::cout << "Test 2: " << (result2 == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 3: All isolated nodes
    Solution::Graph graph3 = {
        {0, {}},
        {1, {}},
        {2, {}}
    };
    int result3 = sol.connected_components_count(graph3);
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Empty graph
    Solution::Graph graph4 = {};
    int result4 = sol.connected_components_count(graph4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
