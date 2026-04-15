/**
 * Problem: 69. Sqrt(x)
 * Link: https://leetcode.com/problems/sqrtx/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Math, Binary Search
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a non-negative integer x, return the square root of x rounded down to
    the nearest integer. The returned integer should be non-negative as well.

    You must not use any built-in exponent function or operator.

    Example 1:
    Input: x = 8
    Output: 2
    Explanation: The square root of 8 is 2.8284, and since we need to return
    the floor of the square root (integer), hence we returned 2.

    Example 2:
    Input: x = 4
    Output: 2
    Explanation: The square root of 4 is 2.

    Example 3:
    Input: x = 2
    Output: 1
    Explanation: The square root of 2 is 1.414, and since we need to return
    the floor of the square root (integer), hence we returned 1.

    Constraints:
    - 0 <= x <= 2^31 - 1
*/

#include <iostream>
#include <cmath>

// ---------------------------------------------------------------------------

// Approach #1: Binary Search

/*
    Intuition:
    The floor of the square root of a number x lies between 0 and x/2 for all
    x > 1, we can use binary search within this range to find the square root.
    (The integer part (i.e., the floor) of the square root will be the final result)

    Algorithm:
    1. If x < 2, return x.
    2. Set the left pointer to 2, and the right pointer to x / 2.
    3. While left <= right:
        - num = (left + right) / 2 as a guess.
        - Compute num * num and compare it with x:
            - If num * num > x, move the right pointer right = pivot - 1
            - Else, if num * num < x, move the left pointer left = pivot + 1
            - Otherwise num * num == x, the integer square root is found

    Complexity Analysis:
    - Time: O(log n), where n is the input number because it uses binary search
    - Space: O(1), because it only uses a few variables
*/

class Solution {
public:
    int my_sqrt(int x) {
        if (x < 2) return x;

        long number;
        int pivot, left = 2, right = x / 2;

        while (left <= right) {
            pivot = left + (right - left) / 2;
            number = (long)pivot * pivot;

            if (number < x)
                left = pivot + 1;
            else if (number > x)
                right = pivot - 1;
            else
                return pivot;
        }
        return right;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Pocket Calculator (Mathematical)

/*
    Intuition:
    Usually a pocket calculator computes well exponential functions and natural
    logarithms by having logarithm tables hardcoded or by the other means.

    Algorithm:
    1. Use the identity: sqrt(x) = e^(0.5 * ln(x))
    2. Compute using logarithms and exponentials
    3. Handle edge case where result might be off by 1 due to floating point

    Complexity Analysis:
    - Time: O(1)
    - Space: O(1)
*/

class SolutionPocketCalc {
public:
    int my_sqrt(int x) {
        if (x < 2) return x;

        int left = std::pow(std::exp(0.5 * std::log(x)), 1);
        int right = left + 1;

        return (long long)right * right > x ? left : right;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    int result1 = sol.my_sqrt(8);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    int result2 = sol.my_sqrt(4);
    std::cout << "Test 2: " << (result2 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    int result3 = sol.my_sqrt(2);
    std::cout << "Test 3: " << (result3 == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Edge case x = 0
    int result4 = sol.my_sqrt(0);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 5: Edge case x = 1
    int result5 = sol.my_sqrt(1);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
