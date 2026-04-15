/**
 * Problem: Largest Component
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, DFS, Connected Components, Undirected Graph
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Write a function that takes in the adjacency list of an undirected graph
    and returns the size of the largest connected component in the graph.

    Example 1:
    Input: graph = {
        0: [8, 1, 5],
        1: [0],
        5: [0, 8],
        8: [0, 5],
        2: [3, 4],
        3: [2, 4],
        4: [3, 2]
    }
    Output: 4
    Explanation: Largest component is {0, 1, 5, 8} with size 4

    Example 2:
    Input: graph = {
        1: [2],
        2: [1, 8],
        6: [7],
        9: [],
        7: [6, 8],
        8: [7, 2]
    }
    Output: 5
    Explanation: Component {1, 2, 6, 7, 8} has size 5

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

// Approach #1: DFS to Count Component Size

/*
    Intuition:
    Similar to counting connected components, but instead of just counting
    components, we calculate the size of each component. DFS returns the
    count of nodes it visits, and we track the maximum size seen.

    Algorithm:
    1. Initialize a visited set and largest = 0
    2. For each node in the graph:
       a. If node is not visited, perform DFS to get component size
       b. DFS returns 1 + sum of sizes from all unvisited neighbors
       c. Update largest if current size is greater
    3. Return largest

    Complexity Analysis:
    - Time: O(V + E) where V is vertices and E is edges
    - Space: O(V) for the visited set and recursion stack
*/

class Solution {
public:
    using Graph = std::unordered_map<int, std::vector<int>>;

    int dfs(const Graph& graph, int node, std::unordered_set<int>& visited) {
        if (visited.count(node) > 0) return 0;
        visited.insert(node);

        int size = 1;
        for (int neighbor : graph.at(node)) {
            size += dfs(graph, neighbor, visited);
        }

        return size;
    }

    int largest_component(const Graph& graph) {
        std::unordered_set<int> visited;
        int largest = 0;

        for (const auto& [node, _] : graph) {
            int size = dfs(graph, node, visited);
            if (size > largest) {
                largest = size;
            }
        }

        return largest;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Two components, sizes 4 and 3
    Solution::Graph graph1 = {
        {0, {8, 1, 5}},
        {1, {0}},
        {5, {0, 8}},
        {8, {0, 5}},
        {2, {3, 4}},
        {3, {2, 4}},
        {4, {3, 2}}
    };
    int result1 = sol.largest_component(graph1);
    std::cout << "Test 1: " << (result1 == 4 ? "PASS" : "FAIL") << std::endl;

    // Test 2: Single component
    Solution::Graph graph2 = {
        {0, {1}},
        {1, {0, 2}},
        {2, {1}}
    };
    int result2 = sol.largest_component(graph2);
    std::cout << "Test 2: " << (result2 == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 3: All isolated nodes
    Solution::Graph graph3 = {
        {0, {}},
        {1, {}},
        {2, {}}
    };
    int result3 = sol.largest_component(graph3);
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Empty graph
    Solution::Graph graph4 = {};
    int result4 = sol.largest_component(graph4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 5: Single node
    Solution::Graph graph5 = {
        {0, {}}
    };
    int result5 = sol.largest_component(graph5);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
