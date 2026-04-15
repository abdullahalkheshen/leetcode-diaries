/**
 * Problem: Graph Representation
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Graph, Data Structure, Adjacency List
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Understand and implement basic graph representations using adjacency lists.
    A graph is a collection of nodes (vertices) connected by edges.

    Example 1:
    Input: Graph with nodes a, b, c and edges a->b, b->c
    Output: Adjacency list representation

    Constraints:
    - Graphs can be directed or undirected
    - Graphs can have cycles
    - Nodes can have any number of neighbors
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Adjacency List Representation

/*
    Intuition:
    An adjacency list represents a graph as a map where each node maps to a
    list of its neighbors. This is efficient for sparse graphs and allows
    O(1) access to a node's neighbors.

    Algorithm:
    1. Use an unordered_map with node as key and vector of neighbors as value
    2. For directed graphs: add edge from source to destination
    3. For undirected graphs: add edges in both directions

    Complexity Analysis:
    - Time: O(1) to add an edge, O(degree) to iterate neighbors
    - Space: O(V + E) where V is vertices and E is edges
*/

class Solution {
public:
    using Graph = std::unordered_map<std::string, std::vector<std::string>>;

    Graph create_directed_graph() {
        Graph graph = {
            {"a", {"b", "c"}},
            {"b", {"d"}},
            {"c", {"e"}},
            {"d", {"f"}},
            {"e", {}},
            {"f", {}}
        };
        return graph;
    }

    void print_graph(const Graph& graph) {
        for (const auto& [node, neighbors] : graph) {
            std::cout << node << " -> ";
            for (const auto& neighbor : neighbors) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Create and print a directed graph
    auto graph = sol.create_directed_graph();
    
    bool pass1 = (graph.size() == 6 && 
                  graph["a"].size() == 2 && 
                  graph["f"].size() == 0);
    std::cout << "Test 1 (Graph creation): " << (pass1 ? "PASS" : "FAIL") << std::endl;

    // Test 2: Verify adjacency list structure
    bool pass2 = (graph["a"][0] == "b" && graph["a"][1] == "c");
    std::cout << "Test 2 (Adjacency list): " << (pass2 ? "PASS" : "FAIL") << std::endl;

    // Print the graph for visualization
    std::cout << "\nGraph structure:" << std::endl;
    sol.print_graph(graph);

    return 0;
}
