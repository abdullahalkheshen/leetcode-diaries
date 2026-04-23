/**
 * Problem: Max Subarray Sum Size K
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Sliding Window, Array
 *
 * Date Solved: 2026-04-23
 * Time Taken: 1 hour
 */

/*
    Problem Statement:
    Given an array of positive numbers and a positive number 'k', find the
    maximum sum of any contiguous subarray of size 'k'.

    Example 1:
    Input: nums = [2, 1, 5, 1, 3, 2], k = 3
    Output: 9
    Explanation: Subarray with maximum sum is [5, 1, 3].

    Example 2:
    Input: nums = [2, 3, 4, 1, 5], k = 2
    Output: 7
    Explanation: Subarray with maximum sum is [3, 4].

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
    A brute-force approach would recompute the sum from scratch for every
    window position, costing O(n * k). The key insight is that consecutive
    windows of size k overlap in k-1 elements — so when we slide the window
    one step right, we only need to add the new element entering the window
    and subtract the element leaving it. This turns an O(n * k) problem
    into O(n).

    Algorithm:
    1. Initialize two pointers i = 0, j = 0, a running sum = 0, and
       maxSum = -infinity.
    2. Expand the window by adding nums[j] to sum.
    3. Once the window reaches size k (j - i + 1 == k):
       - Update maxSum = max(maxSum, sum).
       - Shrink from the left: subtract nums[i] and increment i.
    4. Increment j to continue sliding.
    5. Return maxSum.

    Complexity Analysis:
    - Time: O(n) - single pass through the array
    - Space: O(1) - only constant memory for variables
*/

class Solution {
public:
    int maxSubarraySumSizeK(std::vector<int> nums, int k) {
        int i = 0, j = 0;
        double sum = 0, maxSum = -std::numeric_limits<double>::infinity();

        while (j < (int)nums.size()) {
            sum += nums[j];

            if (j - i + 1 == k) {
                maxSum = std::max(maxSum, sum);
                sum -= nums[i];
                i++;
            }

            j++;
        }
        
        return (int)maxSum;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {2, 1, 5, 1, 3, 2};
    int result1 = sol.maxSubarraySumSizeK(nums1, 3);
    std::cout << "Test 1: " << (result1 == 9 ? "PASS" : "FAIL")
              << " (expected 9, got " << result1 << ")" << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 3, 4, 1, 5};
    int result2 = sol.maxSubarraySumSizeK(nums2, 2);
    std::cout << "Test 2: " << (result2 == 7 ? "PASS" : "FAIL")
              << " (expected 7, got " << result2 << ")" << std::endl;

    // Test 3: Single-element window
    std::vector<int> nums3 = {4, 2, 7};
    int result3 = sol.maxSubarraySumSizeK(nums3, 1);
    std::cout << "Test 3: " << (result3 == 7 ? "PASS" : "FAIL")
              << " (expected 7, got " << result3 << ")" << std::endl;

    return 0;
}
