/**
 * Problem: Max Path Sum
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Dynamic Programming, Recursion, Memoization, Grid
 *
 * Date Solved: 2026-05-16
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function maxPathSum that takes in a grid as an argument. The function
    should return the maximum sum possible by traveling a path from the top-left
    corner to the bottom-right corner. You may only travel through the grid by
    moving down or right.

    You can assume that all numbers are non-negative.

    Example 1:
    Input: grid = {
      {1, 3, 12},
      {5, 1, 1},
      {3, 6, 1}
    }
    Output: 18

    Example 2:
    Input: grid = {
      {1, 2, 8, 1},
      {3, 1, 12, 10},
      {4, 0, 6, 3}
    }
    Output: 36

    Example 3:
    Input: grid = {
      {1, 2, 8, 1},
      {3, 10, 12, 10},
      {4, 0, 6, 3}
    }
    Output: 39

    Constraints:
    - Grid dimensions: rows >= 1, cols >= 1
    - All numbers in the grid are non-negative
    - Start is always top-left (0,0), end is always bottom-right (r-1, c-1)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Recursive with Memoization

/*
    Intuition:
    From any cell (r, c) we can only move right to (r, c+1) or down to (r+1, c).

    The maximum path sum from (r, c) to the destination is the current cell's
    
    value plus the better of the two choices (down or right). Out-of-bounds
    positions return 0 — since all values are non-negative, this acts as a
    neutral base that never wins a max comparison against a valid path unless
    there is no valid path in that direction.

    Without memoization, overlapping subproblems cause exponential recomputation.
    Caching the result for each (r, c) ensures every cell is solved at most once.

    Algorithm:
    1. Base cases:
       - (r, c) is out of bounds       → return 0.
       - (r, c) is the bottom-right    → return grid[r][c] (goal cell).
    2. If (r, c) is in memo, return the cached value.
    3. Recurse: result = grid[r][c] + max(maxPathSum(r+1, c), maxPathSum(r, c+1)).
    4. Store result in memo for (r, c) and return it.

    Complexity Analysis:
    - Time: O(r * c) — each cell is computed at most once.
    - Space: O(r * c) — memo stores one entry per cell + recursion stack depth
      is at most O(r + c).
*/

class Solution {
public:
    int maxPathSum(std::vector<std::vector<int>>& grid,
                   int r, int c,
                   std::unordered_map<std::string, int>& memo) {
        // base cases
        if (!(0<=r && r<grid.size()) || !(0<=c && c<grid[0].size())) return 0;
        if (r == (int)grid.size() - 1 && c == (int)grid[0].size() - 1) return grid[r][c];

        // check memo
        std::string key = std::to_string(r) + "," + std::to_string(c);
        if (memo.count(key)) return memo[key];

        // recurse
        return memo[key] = grid[r][c] + std::max(maxPathSum(grid, r + 1, c, memo), maxPathSum(grid, r, c + 1, memo));
    }

    int maxPathSum(std::vector<std::vector<int>> grid) {
        std::unordered_map<std::string, int> memo;
        return maxPathSum(grid, 0, 0, memo);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: 3x3 grid
    std::vector<std::vector<int>> grid1 = {
        {1, 3, 12},
        {5, 1, 1},
        {3, 6, 1}
    };
    int result1 = sol.maxPathSum(grid1);
    std::cout << "Test 1: " << (result1 == 18 ? "PASS" : "FAIL")
              << " (expected 18, got " << result1 << ")" << std::endl;

    // Test 2: 3x4 grid
    std::vector<std::vector<int>> grid2 = {
        {1, 2, 8, 1},
        {3, 1, 12, 10},
        {4, 0, 6, 3}
    };
    int result2 = sol.maxPathSum(grid2);
    std::cout << "Test 2: " << (result2 == 36 ? "PASS" : "FAIL")
              << " (expected 36, got " << result2 << ")" << std::endl;

    // Test 3: 3x4 grid with larger middle value
    std::vector<std::vector<int>> grid3 = {
        {1, 2, 8, 1},
        {3, 10, 12, 10},
        {4, 0, 6, 3}
    };
    int result3 = sol.maxPathSum(grid3);
    std::cout << "Test 3: " << (result3 == 39 ? "PASS" : "FAIL")
              << " (expected 39, got " << result3 << ")" << std::endl;

    // Test 4: 1x1 grid (start == end)
    std::vector<std::vector<int>> grid4 = {
        {5}
    };
    int result4 = sol.maxPathSum(grid4);
    std::cout << "Test 4: " << (result4 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result4 << ")" << std::endl;

    // Test 5: single row
    std::vector<std::vector<int>> grid5 = {
        {1, 2, 3, 4}
    };
    int result5 = sol.maxPathSum(grid5);
    std::cout << "Test 5: " << (result5 == 10 ? "PASS" : "FAIL")
              << " (expected 10, got " << result5 << ")" << std::endl;

    // Test 6: single column
    std::vector<std::vector<int>> grid6 = {
        {1},
        {2},
        {3},
        {4}
    };
    int result6 = sol.maxPathSum(grid6);
    std::cout << "Test 6: " << (result6 == 10 ? "PASS" : "FAIL")
              << " (expected 10, got " << result6 << ")" << std::endl;

    return 0;
}
