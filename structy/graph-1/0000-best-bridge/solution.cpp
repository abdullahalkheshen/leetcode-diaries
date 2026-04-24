/**
 * Problem: Best Bridge
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, DFS, BFS, Grid, 2D Matrix
 *
 * Date Solved: 2026-04-21
 * Time Taken: 
 */

/*
    Problem Statement:
    Write a function that takes in a grid containing Ws and Ls. W represents
    water and L represents land. The grid contains exactly two islands. An island
    is a vertically or horizontally connected region of land. Return the minimum
    length bridge needed to connect the two islands. A bridge is a path of water
    cells that connects the two islands.

    Example 1:
    Input: grid = [
        ['W', 'W', 'W', 'L', 'L'],
        ['L', 'L', 'W', 'W', 'L'],
        ['L', 'L', 'L', 'W', 'L'],
        ['W', 'L', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'W', 'W']
    ]
    Output: 1
    Explanation: The minimum bridge connects the two islands with 1 water cell

    Example 2:
    Input: grid = [
        ['W', 'W', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'W', 'W'],
        ['L', 'L', 'W', 'W', 'L'],
        ['W', 'L', 'W', 'W', 'L'],
        ['W', 'W', 'W', 'L', 'L'],
        ['W', 'W', 'W', 'W', 'W']
    ]
    Output: 2
    Explanation: The minimum bridge requires 2 water cells to connect the islands

    Example 3:
    Input: grid = [
        ['W', 'W', 'W', 'L', 'L'],
        ['L', 'L', 'L', 'L', 'L'],
        ['L', 'L', 'L', 'W', 'L'],
        ['W', 'L', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'W', 'W']
    ]
    Output: 0
    Explanation: The two islands are already connected (adjacent), no bridge needed

    Example 4:
    Input: grid = [
        ['W', 'L', 'W'],
        ['W', 'W', 'W'],
        ['W', 'W', 'L']
    ]
    Output: 2
    Explanation: Diagonal path requires 2 water cells

    Constraints:
    - Grid contains only 'W' (water) and 'L' (land)
    - There are exactly two islands in the grid
    - Islands are connected horizontally or vertically (not diagonally)
    - Grid dimensions can vary
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <string>

// ---------------------------------------------------------------------------

// Approach #1: DFS + BFS

/*
    Intuition:
    

    Algorithm:
    

    Complexity Analysis:
    - Time: O(r * c) where r is rows and c is columns
    - Space: O(r * c) for the visited set and queue
*/

class Solution {
public:
    int best_bridge(const std::vector<std::vector<char>>& grid) {
        // TODO: Implement solution
        return -1;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Basic two islands with 1-cell bridge
    std::vector<std::vector<char>> grid1 = {
        {'W', 'W', 'W', 'L', 'L'},
        {'L', 'L', 'W', 'W', 'L'},
        {'L', 'L', 'L', 'W', 'L'},
        {'W', 'L', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W'}
    };
    int result1 = sol.best_bridge(grid1);
    std::cout << "Test 1: " << (result1 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result1 << ")" << std::endl;

    // Test 2: Two islands requiring 2-cell bridge
    std::vector<std::vector<char>> grid2 = {
        {'W', 'W', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W'},
        {'L', 'L', 'W', 'W', 'L'},
        {'W', 'L', 'W', 'W', 'L'},
        {'W', 'W', 'W', 'L', 'L'},
        {'W', 'W', 'W', 'W', 'W'}
    };
    int result2 = sol.best_bridge(grid2);
    std::cout << "Test 2: " << (result2 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result2 << ")" << std::endl;

    // Test 3: Adjacent islands (bridge = 0)
    std::vector<std::vector<char>> grid3 = {
        {'W', 'W', 'W', 'L', 'L'},
        {'L', 'L', 'L', 'L', 'L'},
        {'L', 'L', 'L', 'W', 'L'},
        {'W', 'L', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'W', 'W'}
    };
    int result3 = sol.best_bridge(grid3);
    std::cout << "Test 3: " << (result3 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result3 << ")" << std::endl;

    // Test 4: Diagonal separation
    std::vector<std::vector<char>> grid4 = {
        {'W', 'L', 'W'},
        {'W', 'W', 'W'},
        {'W', 'W', 'L'}
    };
    int result4 = sol.best_bridge(grid4);
    std::cout << "Test 4: " << (result4 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result4 << ")" << std::endl;

    // Test 5: Single cell islands
    std::vector<std::vector<char>> grid5 = {
        {'L', 'W', 'L'}
    };
    int result5 = sol.best_bridge(grid5);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result5 << ")" << std::endl;

    return 0;
}
