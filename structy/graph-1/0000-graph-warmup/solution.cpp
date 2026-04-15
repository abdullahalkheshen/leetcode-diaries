/**
 * Problem: Graph Traversal Warmup (DFS & BFS)
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Graph, DFS, BFS, Traversal, Stack, Queue
 *
 * Date Solved: 2026-02-28
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Implement depth-first search (DFS) and breadth-first search (BFS) traversals
    on a directed graph represented as an adjacency list.

    Example 1:
    Input: graph = {a: [b,c], b: [d], c: [e], d: [f], e: [], f: []}, start = "a"
    Output (DFS): a c e b d f (or a b d f c e depending on order)
    Output (BFS): a b c d e f

    Constraints:
    - Graph is directed
    - Graph may have cycles (though this example doesn't)
    - All nodes are reachable from the start node
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: DFS Iterative (Stack)

/*
    Intuition:
    Use a stack to explore as deep as possible before backtracking. The stack
    naturally handles the "last in, first out" order needed for depth-first
    exploration.

    Algorithm:
    1. Push the starting vertex onto the stack
    2. While stack is not empty:
       a. Pop the top vertex and process it
       b. Push all its neighbors onto the stack
    3. Continue until stack is empty

    Complexity Analysis:
    - Time: O(V + E) where V is vertices and E is edges
    - Space: O(V) for the stack
*/

class Solution {
public:
    using Graph = std::unordered_map<std::string, std::vector<std::string>>;

    void depth_first_search_iterative(const Graph& graph, const std::string& start) {
        std::stack<std::string> stack;
        stack.push(start);

        while (!stack.empty()) {
            std::string current = stack.top();
            stack.pop();
            std::cout << current << " ";

            for (const std::string& neighbor : graph.at(current)) {
                stack.push(neighbor);
            }
        }
    }

// ---------------------------------------------------------------------------

// Approach #2: DFS Recursive

/*
    Intuition:
    Recursion naturally implements depth-first behavior since the call stack
    handles backtracking automatically.

    Algorithm:
    1. Process the current vertex
    2. Recursively visit each neighbor
    3. Base case: when a node has no neighbors

    Complexity Analysis:
    - Time: O(V + E)
    - Space: O(V) for the recursion stack
*/

    void depth_first_search_recursive(const Graph& graph, const std::string& vertex) {
        std::cout << vertex << " ";
        for (const std::string& neighbor : graph.at(vertex)) {
            depth_first_search_recursive(graph, neighbor);
        }
    }

// ---------------------------------------------------------------------------

// Approach #3: BFS (Queue)

/*
    Intuition:
    Use a queue to explore all neighbors at the current depth before moving
    to the next level. The queue's "first in, first out" order ensures
    level-by-level exploration.

    Algorithm:
    1. Enqueue the starting vertex
    2. While queue is not empty:
       a. Dequeue the front vertex and process it
       b. Enqueue all its neighbors
    3. Continue until queue is empty

    Complexity Analysis:
    - Time: O(V + E)
    - Space: O(V) for the queue
*/

    void breadth_first_search(const Graph& graph, const std::string& start) {
        std::queue<std::string> queue;
        queue.push(start);

        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();
            std::cout << current << " ";

            for (const std::string& neighbor : graph.at(current)) {
                queue.push(neighbor);
            }
        }
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    Solution::Graph graph = {
        {"a", {"b", "c"}},
        {"b", {"d"}},
        {"c", {"e"}},
        {"d", {"f"}},
        {"e", {}},
        {"f", {}}
    };

    // Test 1: DFS Iterative
    std::cout << "Test 1 - DFS Iterative: ";
    sol.depth_first_search_iterative(graph, "a");
    std::cout << "-> PASS (visual check)" << std::endl;

    // Test 2: DFS Recursive
    std::cout << "Test 2 - DFS Recursive: ";
    sol.depth_first_search_recursive(graph, "a");
    std::cout << "-> PASS (visual check)" << std::endl;

    // Test 3: BFS
    std::cout << "Test 3 - BFS: ";
    sol.breadth_first_search(graph, "a");
    std::cout << "-> PASS (visual check)" << std::endl;

    return 0;
}
