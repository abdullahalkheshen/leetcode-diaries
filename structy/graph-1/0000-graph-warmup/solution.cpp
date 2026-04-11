//
// Created by abdul on 2/28/2026.
//


#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

using namespace std;



    void depth_first_search_iterative(const std::unordered_map<std::string, std::vector<std::string>> &graph, const std::string &vertex) {
        std::stack<std::string> stack;
        stack.push(vertex);
        while (!stack.empty()) {
            std::string current_vertex = stack.top();
            std::cout << current_vertex << " ";
            stack.pop();
            for (const std::string &neighbor : graph.at(current_vertex)) {
                stack.push(neighbor);
            }
        }
    }



    void depth_first_search_recursive(const std::unordered_map<std::string, std::vector<std::string>> &graph, const std::string &vertex) {
        std::cout << vertex << " ";
        for (const std::string &neighbor : graph.at(vertex)) {
            depth_first_search_recursive(graph, neighbor);
        }
    }


    void breadth_first_search(const std::unordered_map<std::string, std::vector<std::string>> &graph, const std::string &vertex) {
        std::queue<std::string> queue;
        queue.push(vertex);
        while (!queue.empty()) {
            std::string current_vertex = queue.front();
            std::cout << current_vertex << " ";
            queue.pop();
            for (const std::string &neighbor : graph.at(current_vertex)) {
                queue.push(neighbor);
            }
        }
    }


int main () {
        std::unordered_map<std::string, std::vector<std::string>> graph {
                { "a", { "b", "c" } },
                { "b", { "d" } },
                { "c", { "e" } },
                { "d", { "f" } },
                { "e", { } },
                { "f", { } }
        };

        std::cout << "depth first search iterative " << std::endl;
        depth_first_search_iterative(graph, "a");
        std::cout << std::endl;



        std::cout << "depth first search recursive " << std::endl;
        depth_first_search_recursive(graph, "a");
        std::cout << std::endl;


        std::cout << "breadth first search " << std::endl;
        breadth_first_search(graph, "a");
        std::cout << std::endl;

        return 0;

    }

