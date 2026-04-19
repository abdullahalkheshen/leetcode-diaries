/**
 * Problem: Island Count
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Graph, DFS, BFS, Grid, 2D Matrix
 *
 * Date Solved: 2026-04-19
 * Time Taken: 
 */

/*
    Problem Statement:
    Write a function that takes in a grid containing Ws and Ls. W represents
    water and L represents land. The function should return the number of islands
    on the grid. An island is a vertically or horizontally connected region of land.

    Example 1:
    Input: grid = [
        ['W', 'L', 'W', 'W', 'W'],
        ['W', 'L', 'W', 'W', 'W'],
        ['W', 'W', 'W', 'L', 'W'],
        ['W', 'W', 'L', 'L', 'W'],
        ['L', 'W', 'W', 'L', 'W'],
        ['L', 'L', 'W', 'W', 'W']
    ]
    Output: 3
    Explanation: There are 3 separate islands in the grid

    Example 2:
    Input: grid = [
        ['L', 'W', 'W', 'L', 'W'],
        ['L', 'W', 'W', 'L', 'L'],
        ['W', 'L', 'W', 'L', 'W'],
        ['W', 'W', 'W', 'W', 'W'],
        ['W', 'W', 'L', 'L', 'L']
    ]
    Output: 4

    Example 3:
    Input: grid = [
        ['L', 'L', 'L'],
        ['L', 'L', 'L'],
        ['L', 'L', 'L']
    ]
    Output: 1
    Explanation: All land is connected, forming one island

    Example 4:
    Input: grid = [
        ['W', 'W'],
        ['W', 'W'],
        ['W', 'W']
    ]
    Output: 0
    Explanation: No land, so no islands

    Constraints:
    - Grid contains only 'W' (water) and 'L' (land)
    - Islands are connected horizontally or vertically (not diagonally)
    - Grid dimensions can vary
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

// ---------------------------------------------------------------------------

// Approach #1: DFS

/*
    Intuition:
    

    Algorithm:
    

    Complexity Analysis:
    - Time: O(r * c) where r is rows and c is columns
    - Space: O(r * c) for the visited set
*/

class Solution {
public:
    bool explore_island(const std::vector<std::vector<char>>& grid, int r, int c, std::unordered_set<std::string> &visited) {
        int row_in_bound = 0 <= row && row <= grid.size();
        int col_in_bound = 0 <= col && col <= grid[0].size();
        if (!row_in_bound || !col_in_bound) return false;

        if (grid[row][col] == 'W') return -1;

        std::string pos = std::to_string(r) + ',' + std::to_string(c);
        if (visited.count(pos) > 0 ) return -1;
        visited.insert(pos);

        explore_island(grid, c-1, r, visited);
        explore_island(grid, c+1, r, visited);
        explore_island(grid, c, r-1, visited);
        explore_island(grid, c, r+1, visited);

        return true;

    }

    int island_count(const std::vector<std::vector<char>>& grid) {
        std::unordered_set<std::string> visited;
        for (int r=0; r<grid.size(); r++) {
            for (int c=0; r<grid.size(); c++) {
                if (explore_island(graph, r, c, visited)) {
                    count++;
                }
            }
        }
        return count;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: Multiple islands
    std::vector<std::vector<char>> grid1 = {
        {'W', 'L', 'W', 'W', 'W'},
        {'W', 'L', 'W', 'W', 'W'},
        {'W', 'W', 'W', 'L', 'W'},
        {'W', 'W', 'L', 'L', 'W'},
        {'L', 'W', 'W', 'L', 'W'},
        {'L', 'L', 'W', 'W', 'W'}
    };
    int result1 = sol.island_count(grid1);
    std::cout << "Test 1: " << (result1 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result1 << ")" << std::endl;

    // Test 2: Four islands
    std::vector<std::vector<char>> grid2 = {
        {'L', 'W', 'W', 'L', 'W'},
        {'L', 'W', 'W', 'L', 'L'},
        {'W', 'L', 'W', 'L', 'W'},
        {'W', 'W', 'W', 'W', 'W'},
        {'W', 'W', 'L', 'L', 'L'}
    };
    int result2 = sol.island_count(grid2);
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result2 << ")" << std::endl;

    // Test 3: Single island (all land)
    std::vector<std::vector<char>> grid3 = {
        {'L', 'L', 'L'},
        {'L', 'L', 'L'},
        {'L', 'L', 'L'}
    };
    int result3 = sol.island_count(grid3);
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result3 << ")" << std::endl;

    // Test 4: No islands (all water)
    std::vector<std::vector<char>> grid4 = {
        {'W', 'W'},
        {'W', 'W'},
        {'W', 'W'}
    };
    int result4 = sol.island_count(grid4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result4 << ")" << std::endl;

    // Test 5: Single cell island
    std::vector<std::vector<char>> grid5 = {
        {'W', 'W', 'W'},
        {'W', 'L', 'W'},
        {'W', 'W', 'W'}
    };
    int result5 = sol.island_count(grid5);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result5 << ")" << std::endl;

    return 0;
}
