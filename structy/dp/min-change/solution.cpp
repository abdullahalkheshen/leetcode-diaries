/**
 * Problem: Min Change
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Dynamic Programming, Recursion, Memoization
 *
 * Date Solved: 2026-05-04
 * Time Taken:
 */

/*
    Problem Statement:
    Write a function minChange that takes in an amount and a vector of coins.
    The function should return the minimum number of coins required to create
    the amount. You may use each coin as many times as necessary.

    If it is not possible to create the amount, then return -1.

    Example 1:
    Input: amount = 8, coins = {5, 4, 12}
    Output: 2 (4 + 4 = 8)

    Example 2:
    Input: amount = 13, coins = {1, 9, 5, 14, 30}
    Output: 5 (9 + 1 + 1 + 1 + 1 = 13)

    Example 3:
    Input: amount = 23, coins = {2, 5, 7}
    Output: 4 (7 + 7 + 7 + 2 = 23)

    Example 4:
    Input: amount = 0, coins = {1, 2, 3}
    Output: 0

    Example 5:
    Input: amount = 11, coins = {5, 7}
    Output: -1

    Constraints:
    - amount >= 0
    - All coin values are positive
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

// ---------------------------------------------------------------------------

// Approach #1: Recursive with Memoization

/*
    Intuition:
    This is the same tree structure as sumPossible, but instead of asking "can I
    reach 0?" we ask "what's the fewest coins to reach 0?" At each node we try
    every coin, subtract it, and recurse. Among all paths that reach 0 we pick
    the shortest one (minimum coins). If no path reaches 0 we return -1.

    Memoization caches the answer for each sub-amount so each unique amount is
    only solved once.

    Algorithm:
    1. Base cases:
       - amount == 0 → return 0 (no coins needed).
       - amount < 0  → return -1 (overshot, invalid path).
    2. If amount is in memo, return cached result.
    3. Set minCoins = -1 (tracks best answer found so far).
    4. For each coin:
       - Recurse on (amount - coin).
       - If the recursive result is not -1 (valid path), compute
         numCoins = 1 + subResult.
       - Update minCoins if this is the first valid answer or fewer coins.
    5. Store minCoins in memo and return it.

    Complexity Analysis:
    - Time: O(amount * n) — at most `amount` unique subproblems, each iterating
      through n coins.
    - Space: O(amount) — memo map stores up to `amount` entries + recursion stack.
*/

using namespace std;
class Solution {
public:
    int minChange(int amount, std::vector<int>& coins, std::unordered_map<int, int>& memo) {
        if (memo.count(amount)) return memo[amount];
        if (amount == 0) return 0;
        if (amount < 0) return -1;

        int minCoins = -1;
        for (int coin : coins) {
            int sub = minChange(amount - coin, coins, memo);
            if (sub != -1) {
                int numCoins = 1 + sub;
                if (minCoins == -1 || numCoins < minCoins) {
                    minCoins = numCoins;
                }
            }
        }

        memo[amount] = minCoins;
        return minCoins;
    }

    int minChange(int amount, std::vector<int> coins) {
        std::unordered_map<int, int> memo;
        return minChange(amount, coins, memo);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: basic case
    std::vector<int> coins1 = {5, 4, 12};
    int result1 = sol.minChange(8, coins1);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result1 << ")" << std::endl;

    // Test 2: multiple coins needed
    std::vector<int> coins2 = {1, 9, 5, 14, 30};
    int result2 = sol.minChange(13, coins2);
    std::cout << "Test 2: " << (result2 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result2 << ")" << std::endl;

    // Test 3: combination of coins
    std::vector<int> coins3 = {2, 5, 7};
    int result3 = sol.minChange(23, coins3);
    std::cout << "Test 3: " << (result3 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result3 << ")" << std::endl;

    // Test 4: amount is 0
    std::vector<int> coins4 = {1, 2, 3};
    int result4 = sol.minChange(0, coins4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result4 << ")" << std::endl;

    // Test 5: impossible case
    std::vector<int> coins5 = {5, 7};
    int result5 = sol.minChange(11, coins5);
    std::cout << "Test 5: " << (result5 == -1 ? "PASS" : "FAIL")
              << " (expected -1, got " << result5 << ")" << std::endl;

    // Test 6: large amount
    std::vector<int> coins6 = {2, 3};
    int result6 = sol.minChange(102, coins6);
    std::cout << "Test 6: " << (result6 == 34 ? "PASS" : "FAIL")
              << " (expected 34, got " << result6 << ")" << std::endl;

    return 0;
}
