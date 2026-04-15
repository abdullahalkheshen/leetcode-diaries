/**
 * Problem: 977. Squares of a Sorted Array
 * Link: https://leetcode.com/problems/squares-of-a-sorted-array/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Array, Two Pointers, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given a sorted array, create a new array containing squares of all the
    numbers of the input array in the sorted order.

    Example 1:
    Input: [-2, -1, 0, 2, 3]
    Output: [0, 1, 4, 4, 9]

    Example 2:
    Input: [-3, -1, 0, 1, 2]
    Output: [0, 1, 1, 4, 9]

    Constraints:
    - 1 <= nums.length <= 10^4
    - -10^4 <= nums[i] <= 10^4
    - nums is sorted in non-decreasing order
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// ---------------------------------------------------------------------------

// Approach #1: Sort

/*
    Intuition:
    We can use a brute-force approach to iterate the input array and calculate
    the square of each number. We can store these squares in a new array and
    then sort the resulting array.

    Algorithm:
    1. Create a new array and push squared values.
    2. Sort the resulting array.
    3. Return the sorted array.

    Complexity Analysis:
    - Time: O(n log n), because of sorting
    - Space: O(n), for the result array
*/

class SolutionSort {
public:
    std::vector<int> sorted_squares(const std::vector<int>& arr) {
        std::vector<int> squares(arr.size());

        for (size_t i = 0; i < arr.size(); i++) {
            squares[i] = arr[i] * arr[i];
        }

        std::sort(squares.begin(), squares.end());
        return squares;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers

/*
    Intuition:
    We can utilize the Two Pointers technique to iterate over the array, with
    one pointer moving forward to scan positive numbers, and the other pointer
    moving backward to scan negative numbers. At each step, we compare the
    squares of the numbers pointed by both pointers and append the larger
    square to the output array (filling from the end).

    Algorithm:
    1. Declare a result vector of the same size.
    2. Use two pointers: left at start, right at end.
    3. Iterate from the last index to the first.
    4. Compare absolute values at both pointers.
    5. Store the larger square at the current index.
    6. Move the appropriate pointer.

    Complexity Analysis:
    - Time: O(n), we iterate the input array only once
    - Space: O(n), for the output array
*/

class Solution {
public:
    std::vector<int> sorted_squares(const std::vector<int>& arr) {
        int n = arr.size();
        std::vector<int> result(n);
        int left = 0, right = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (std::abs(arr[left]) > std::abs(arr[right])) {
                result[i] = arr[left] * arr[left];
                left++;
            } else {
                result[i] = arr[right] * arr[right];
                right--;
            }
        }

        return result;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> arr1 = {-2, -1, 0, 2, 3};
    std::vector<int> result1 = sol.sorted_squares(arr1);
    std::vector<int> expected1 = {0, 1, 4, 4, 9};
    std::cout << "Test 1: " << (result1 == expected1 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> arr2 = {-3, -1, 0, 1, 2};
    std::vector<int> result2 = sol.sorted_squares(arr2);
    std::vector<int> expected2 = {0, 1, 1, 4, 9};
    std::cout << "Test 2: " << (result2 == expected2 ? "PASS" : "FAIL") << std::endl;

    // Test 3: All negative
    std::vector<int> arr3 = {-4, -3, -2, -1};
    std::vector<int> result3 = sol.sorted_squares(arr3);
    std::vector<int> expected3 = {1, 4, 9, 16};
    std::cout << "Test 3: " << (result3 == expected3 ? "PASS" : "FAIL") << std::endl;

    // Test 4: All positive
    std::vector<int> arr4 = {1, 2, 3, 4};
    std::vector<int> result4 = sol.sorted_squares(arr4);
    std::vector<int> expected4 = {1, 4, 9, 16};
    std::cout << "Test 4: " << (result4 == expected4 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
