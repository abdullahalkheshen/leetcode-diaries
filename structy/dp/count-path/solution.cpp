/**
 * Problem: Count Paths
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Dynamic Programming, Recursion, Memoization, Grid
 *
 * Date Solved: 2026-05-13
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function countPaths that takes in a grid as input. The grid contains
    only "O" (open) and "X" (wall) characters. You may only move down or right
    and cannot pass through walls. The function should return the number of ways
    to travel from the top-left corner to the bottom-right corner.

    Example 1:
    Input: grid = {
      {"O", "O"},
      {"O", "O"}
    }
    Output: 2

    Example 2:
    Input: grid = {
      {"O", "O", "X"},
      {"O", "O", "O"},
      {"O", "O", "O"}
    }
    Output: 5

    Example 3:
    Input: grid = {
      {"O", "O", "O"},
      {"O", "O", "X"},
      {"O", "X", "O"}
    }
    Output: 1

    Example 4:
    Input: grid = {
      {"O", "O", "X", "O", "O", "O"},
      {"O", "O", "X", "O", "O", "O"},
      {"X", "O", "X", "O", "O", "O"},
      {"X", "X", "X", "O", "O", "O"},
      {"O", "O", "O", "O", "O", "O"}
    }
    Output: 0

    Constraints:
    - Grid dimensions: rows >= 1, cols >= 1
    - Grid cells are either "O" or "X"
    - Start is always top-left (0,0), end is always bottom-right (r-1, c-1)
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Recursive with Memoization

/*
    Intuition:
    From any cell (r, c) we can only move right to (r, c+1) or down to (r+1, c).
    The number of paths from (r, c) to the destination is the sum of paths from
    those two neighbors. Walls ("X") and out-of-bounds positions contribute 0
    paths. The destination itself contributes exactly 1 path (the empty path).

    Without memoization, many cells are visited via different routes, causing
    exponential recomputation. Caching the count for each (r, c) ensures every
    cell is solved at most once.

    Algorithm:
    1. Base cases:
       - (r, c) is out of bounds       → return 0.
       - grid[r][c] == "X" (wall)      → return 0.
       - (r, c) is the bottom-right    → return 1 (reached the destination).
    2. If (r, c) is in memo, return the cached value.
    3. Recurse: count = countPaths(r+1, c) + countPaths(r, c+1).
    4. Store count in memo for (r, c) and return it.

    Complexity Analysis:
    - Time: O(r * c) — each cell is computed at most once.
    - Space: O(r * c) — memo stores one entry per cell + recursion stack depth
      is at most O(r + c).
*/

class Solution {
public:
    int countPaths(std::vector<std::vector<std::string>>& grid,
                   int r, int c,
                   std::unordered_map<std::string, int>& memo) {
        if (r >= (int)grid.size() || c >= (int)grid[0].size()) return 0;
        if (grid[r][c] == "X") return 0;
        if (r == (int)grid.size() - 1 && c == (int)grid[0].size() - 1) return 1;

        std::string key = std::to_string(r) + "," + std::to_string(c);
        if (memo.count(key)) return memo[key];

        int count = countPaths(grid, r + 1, c, memo) + countPaths(grid, r, c + 1, memo);
        memo[key] = count;
        return count;
    }

    int countPaths(std::vector<std::vector<std::string>> grid) {
        std::unordered_map<std::string, int> memo;
        return countPaths(grid, 0, 0, memo);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: 2x2 open grid
    std::vector<std::vector<std::string>> grid1 = {
        {"O", "O"},
        {"O", "O"}
    };
    int result1 = sol.countPaths(grid1);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result1 << ")" << std::endl;

    // Test 2: 3x3 with one wall
    std::vector<std::vector<std::string>> grid2 = {
        {"O", "O", "X"},
        {"O", "O", "O"},
        {"O", "O", "O"}
    };
    int result2 = sol.countPaths(grid2);
    std::cout << "Test 2: " << (result2 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result2 << ")" << std::endl;

    // Test 3: only one path available
    std::vector<std::vector<std::string>> grid3 = {
        {"O", "O", "O"},
        {"O", "O", "X"},
        {"O", "X", "O"}
    };
    int result3 = sol.countPaths(grid3);
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result3 << ")" << std::endl;

    // Test 4: completely blocked
    std::vector<std::vector<std::string>> grid4 = {
        {"O", "O", "X", "O", "O", "O"},
        {"O", "O", "X", "O", "O", "O"},
        {"X", "O", "X", "O", "O", "O"},
        {"X", "X", "X", "O", "O", "O"},
        {"O", "O", "O", "O", "O", "O"}
    };
    int result4 = sol.countPaths(grid4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result4 << ")" << std::endl;

    // Test 5: 1x1 grid (start == end)
    std::vector<std::vector<std::string>> grid5 = {
        {"O"}
    };
    int result5 = sol.countPaths(grid5);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result5 << ")" << std::endl;

    // Test 6: larger open grid (4x4)
    std::vector<std::vector<std::string>> grid6 = {
        {"O", "O", "O", "O"},
        {"O", "O", "O", "O"},
        {"O", "O", "O", "O"},
        {"O", "O", "O", "O"}
    };
    int result6 = sol.countPaths(grid6);
    std::cout << "Test 6: " << (result6 == 20 ? "PASS" : "FAIL")
              << " (expected 20, got " << result6 << ")" << std::endl;

    return 0;
}
