/**
 * Problem: Fibonacci
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Dynamic Programming, Recursion, Memoization
 *
 * Date Solved: 2026-05-02
 * Time Taken: 
 */

/*
    Problem Statement:
    Write a function fib that takes in a number argument, n, and returns the
    n-th number of the Fibonacci sequence.

    The 0-th number of the sequence is 0.
    The 1-st number of the sequence is 1.

    To generate further numbers of the sequence, calculate the sum of the
    previous two numbers.

    Solve this recursively.

    Example 1:
    Input: n = 0
    Output: 0

    Example 2:
    Input: n = 1
    Output: 1

    Example 3:
    Input: n = 8
    Output: 21

    Example 4:
    Input: n = 46
    Output: 1836311903

    Constraints:
    - 0 <= n <= 46
*/

#include <iostream>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Recursive with Memoization

/*
    Intuition:
    The naive recursive approach recalculates the same subproblems exponentially.
    By storing already-computed results in a hash map (memoization), each fib(k)
    is solved only once, turning the overlapping-subproblem tree into a linear
    chain of lookups.

    Algorithm:
    1. Base cases: fib(0) = 0, fib(1) = 1.
    2. Before computing fib(n), check if n is already in the memo map.
       - If yes, return the cached value immediately.
       - If no, compute fib(n-1) + fib(n-2), store the result in memo, and return.
    3. Each unique subproblem is computed exactly once and retrieved in O(1) after.

    Complexity Analysis:
    - Time: O(n) — each of the n subproblems is computed once.
    - Space: O(n) — memo map stores n entries + O(n) recursion stack depth.
*/

#include <unordered_map>

class Solution {
public:
    int fib(int n, std::unordered_map<int, int>& memo) {
        if (memo.count(n)) return memo[n];
        if (n > 2) return n;

        memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
        return memo[n];
    }

    int fib(int n) {
        std::unordered_map<int, int> memo;
        return fib(n, memo);
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    int result1 = sol.fib(0);
    std::cout << "Test 1: " << (result1 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result1 << ")" << std::endl;

    // Test 2
    int result2 = sol.fib(1);
    std::cout << "Test 2: " << (result2 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result2 << ")" << std::endl;

    // Test 3
    int result3 = sol.fib(8);
    std::cout << "Test 3: " << (result3 == 21 ? "PASS" : "FAIL")
              << " (expected 21, got " << result3 << ")" << std::endl;

    // Test 4
    int result4 = sol.fib(5);
    std::cout << "Test 4: " << (result4 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result4 << ")" << std::endl;

    // Test 5
    int result5 = sol.fib(10);
    std::cout << "Test 5: " << (result5 == 55 ? "PASS" : "FAIL")
              << " (expected 55, got " << result5 << ")" << std::endl;

    // Test 6: Large n
    int result6 = sol.fib(46);
    std::cout << "Test 6: " << (result6 == 1836311903 ? "PASS" : "FAIL")
              << " (expected 1836311903, got " << result6 << ")" << std::endl;

    return 0;
}
