/**
 * Problem: Sum Possible
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy/Medium
 * Tags: Dynamic Programming, Recursion, Memoization
 *
 * Date Solved: 2026-05-03
 * Time Taken: 1 hour
 */

/*
    Problem Statement:
    Write a function sumPossible that takes in an amount and a vector of positive
    numbers. The function should return a boolean indicating whether or not it is
    possible to create the amount by summing numbers of the vector. You may reuse
    numbers of the vector as many times as necessary.

    You may assume that the target amount is non-negative.

    Example 1:
    Input: amount = 8, numbers = {5, 12, 4}
    Output: true (4 + 4 = 8)

    Example 2:
    Input: amount = 15, numbers = {6, 2, 10}
    Output: false

    Example 3:
    Input: amount = 0, numbers = {}
    Output: true

    Example 4:
    Input: amount = 12, numbers = {12, 4, 6}
    Output: true (12, or 4+4+4, or 6+6)

    Example 5:
    Input: amount = 271, numbers = {10, 8, 265, 24}
    Output: false

    Constraints:
    - amount >= 0
    - All numbers in the vector are positive
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Recursive with Memoization

/*
    Intuition:
    At each step, we ask: "what was the last number I used to reach this amount?"
    It must be one of the numbers in the vector. For each candidate, we subtract
    it from the current amount and recursively check if the remainder is achievable.
    If any path reaches 0, the answer is true.

    Memoization prevents recomputing the same sub-amount multiple times — without
    it, the recursion tree branches exponentially.

    Algorithm:
    1. Base cases:
       - amount == 0 → return true (we've exactly hit the target).
       - amount < 0  → return false (we've overshot).
    2. Check if the result for this amount is already in the memo map.
       - If yes, return the cached value.
    3. For each number in the vector:
       - Recursively call sumPossible(amount - number).
       - If any call returns true, store true in memo and return true.
    4. If no number leads to a solution, store false in memo and return false.

    Complexity Analysis:
    - Time: O(amount * n) — at most `amount` unique subproblems, each iterating
      through n numbers.
    - Space: O(amount) — memo map stores up to `amount` entries + recursion stack.
*/

class Solution {
public:
    bool sumPossible(int amount, std::vector<int>& numbers, std::unordered_map<int, bool>& memo) {
        if (memo.count(amount)) return memo[amount];
        if (amount == 0) return true;
        if (amount < 0) return false;

        for (int num : numbers) {
            if (sumPossible(amount - num, numbers, memo)) {
                memo[amount] = true;
                return true;
            }
        }

        memo[amount] = false;
        return false;
    }

    bool sumPossible(int amount, std::vector<int> numbers) {
        std::unordered_map<int, bool> memo;
        return sumPossible(amount, numbers, memo);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: basic true case
    std::vector<int> nums1 = {5, 12, 4};
    bool result1 = sol.sumPossible(8, nums1);
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL")
              << " (expected true, got " << result1 << ")" << std::endl;

    // Test 2: impossible case
    std::vector<int> nums2 = {6, 2, 10};
    bool result2 = sol.sumPossible(15, nums2);
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL")
              << " (expected false, got " << result2 << ")" << std::endl;

    // Test 3: amount is 0
    std::vector<int> nums3 = {};
    bool result3 = sol.sumPossible(0, nums3);
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL")
              << " (expected true, got " << result3 << ")" << std::endl;

    // Test 4: exact match with single number
    std::vector<int> nums4 = {12, 4, 6};
    bool result4 = sol.sumPossible(12, nums4);
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL")
              << " (expected true, got " << result4 << ")" << std::endl;

    // Test 5: large amount, impossible
    std::vector<int> nums5 = {10, 8, 265, 24};
    bool result5 = sol.sumPossible(271, nums5);
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL")
              << " (expected false, got " << result5 << ")" << std::endl;

    // Test 6: large amount, possible
    std::vector<int> nums6 = {3, 5};
    bool result6 = sol.sumPossible(103, nums6);
    std::cout << "Test 6: " << (result6 == true ? "PASS" : "FAIL")
              << " (expected true, got " << result6 << ")" << std::endl;

    return 0;
}
