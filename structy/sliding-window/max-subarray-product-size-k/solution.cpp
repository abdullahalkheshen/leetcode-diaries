/**
 * Problem: Max Subarray Product Size K
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Sliding Window, Array
 *
 * Date Solved: 2026-04-24
 * Time Taken: 40 mins
 */

/*
    Problem Statement:
    Given an array of positive numbers and a positive number 'k', find the
    maximum product of any contiguous subarray of size 'k'.

    Example 1:
    Input: nums = [2, 1, 5, 1, 3, 2], k = 3
    Output: 15
    Explanation: Subarray with maximum product is [5, 1, 3].

    Example 2:
    Input: nums = [2, 3, 4, 1, 5], k = 2
    Output: 12
    Explanation: Subarray with maximum product is [3, 4].

    Constraints:
    - 1 <= k <= nums.length
    - 1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window (Single-Pass)

/*
    Intuition:
    We can use a sliding window to find the maximum product of any contiguous
    subarray of size 'k'. We will use a window of size 'k' and slide it through
    the array. We will keep track of the product of the current window and update
    the maximum product if the current product is greater than the maximum product.

    Algorithm:
    1. Initialize a variable to keep track of the maximum product.
    2. Initialize a variable to keep track of the current product.
    3. Initialize a variable to keep track of the start index of the window.
    4. Initialize a variable to keep track of the end index of the window.
    5. Iterate through the array and add the current element to the current product.
    6. If the current product is greater than the maximum product, update the maximum product.
    7. If the window size is greater than 'k', subtract the element at the start index from the current product and increment the start index.
    8. Return the maximum product.

    Complexity Analysis:
    - Time: O(n) - single pass through the array
    - Space: O(1) - only constant memory for variables
*/

class Solution {
public:
    int maxSubarrayProductSizeK(std::vector<int> nums, int k) {
        int i = 0, j = 0;
        int current_product = 1, max_product = -std::numeric_limits<int>::infinity();

        while (j < (int)nums.size()) {
            current_product *= nums[j];

            if (j - i + 1 == k) {
                max_product = std::max(max_product, current_product);
                current_product /= nums[i];
                i++;
            }

            j++;
        }

        return max_product;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {2, 1, 5, 1, 3, 2};
    int result1 = sol.maxSubarrayProductSizeK(nums1, 3);
    std::cout << "Test 1: " << (result1 == 15 ? "PASS" : "FAIL")
              << " (expected 15, got " << result1 << ")" << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 3, 4, 1, 5};
    int result2 = sol.maxSubarrayProductSizeK(nums2, 2);
    std::cout << "Test 2: " << (result2 == 12 ? "PASS" : "FAIL")
              << " (expected 12, got " << result2 << ")" << std::endl;

    // Test 3: Single-element window
    std::vector<int> nums3 = {4, 2, 7};
    int result3 = sol.maxSubarrayProductSizeK(nums3, 1);
    std::cout << "Test 3: " << (result3 == 7 ? "PASS" : "FAIL")
              << " (expected 7, got " << result3 << ")" << std::endl;

    return 0;
}
