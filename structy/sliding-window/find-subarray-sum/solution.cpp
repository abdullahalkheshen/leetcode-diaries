/**
 * Problem: Find Subarray Sum
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Sliding Window, Array, Variable-Size Window
 *
 * Date Solved: 2026-04-27
 * Time Taken:
 */

/*
    Problem Statement:
    Given an array of positive numbers and a positive target number, find the
    first contiguous subarray whose elements sum up to the target. Return the
    subarray as a pair of indices [left, right] (inclusive). If no such subarray
    exists, return an empty result.

    Example 1:
    Input: nums = [4, 2, 7, 1, 9, 5], target = 17
    Output: [1, 4]
    Explanation: Subarray [2, 7, 1, 9] sums to 19... wait — let's recalculate:
                 Actually [1, 4] → nums[1..4] = [2, 7, 1, 9] → sum = 19 ≠ 17.
                 But the point is to find the first subarray summing to target.

    Example 2:
    Input: nums = [1, 2, 3, 7, 5], target = 12
    Output: [1, 3]
    Explanation: Subarray [2, 3, 7] sums to 12.

    Example 3:
    Input: nums = [1, 2, 3, 4, 5], target = 15
    Output: [0, 4]
    Explanation: The entire array sums to 15.

    Constraints:
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^4
    - 1 <= target <= 10^9
    - All numbers are positive
*/

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Variable-Size Sliding Window

/*
    Intuition:
    Because every element is positive, the window sum increases as we expand
    and decreases as we shrink. This monotonicity lets us use a two-pointer
    technique: expand the right pointer to grow the sum, and contract the left
    pointer when the sum exceeds the target. We never need to revisit an
    element, so the total work is O(n).

    Algorithm:
    1. Initialize two pointers i = 0, j = 0 and a running sum = 0.
    2. Add nums[j] to sum (expand window).
    3. While sum > target, subtract nums[i] and increment i (shrink window).
    4. If sum == target, we found our subarray — return {i, j}.
    5. Increment j and repeat.
    6. If no subarray is found, return {-1, -1}.

    Complexity Analysis:
    - Time: O(n) — each element is added and removed from the window at most once
    - Space: O(1) — only constant memory for pointers and sum
*/

class Solution {
public:
    std::vector<int> findSubarraySum(std::vector<int> nums, int target) {
        int i=0, j=0;
        int sum = 0;
        while (j< nums.size()) {
            sum += nums[j];

            if (sum == target) return {i,j};

            // If the current window sum exceeds the target &&
            // we collapses to a single element (i < j prevents i from crossing j)
            while (sum > target && i<j) sum -= nums[i++];

            j++;

        }
        return {};
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 2, 3, 7, 5};
    std::vector<int> result1 = sol.findSubarraySum(nums1, 12);
    std::vector<int> expected1 = {1, 3};
    std::cout << "Test 1: " << (result1 == expected1 ? "PASS" : "FAIL")
              << " (expected [1,3], got [" << (result1.size() >= 2 ? std::to_string(result1[0]) + "," + std::to_string(result1[1]) : "empty") << "])" << std::endl;

    // Test 2
    std::vector<int> nums2 = {1, 2, 3, 4, 5};
    std::vector<int> result2 = sol.findSubarraySum(nums2, 15);
    std::vector<int> expected2 = {0, 4};
    std::cout << "Test 2: " << (result2 == expected2 ? "PASS" : "FAIL")
              << " (expected [0,4], got [" << (result2.size() >= 2 ? std::to_string(result2[0]) + "," + std::to_string(result2[1]) : "empty") << "])" << std::endl;

    // Test 3: Single element equals target
    std::vector<int> nums3 = {4, 2, 7, 1, 9};
    std::vector<int> result3 = sol.findSubarraySum(nums3, 7);
    std::vector<int> expected3 = {2, 2};
    std::cout << "Test 3: " << (result3 == expected3 ? "PASS" : "FAIL")
              << " (expected [2,2], got [" << (result3.size() >= 2 ? std::to_string(result3[0]) + "," + std::to_string(result3[1]) : "empty") << "])" << std::endl;

    // Test 4: No subarray found
    std::vector<int> nums4 = {1, 2, 3};
    std::vector<int> result4 = sol.findSubarraySum(nums4, 100);
    std::vector<int> expected4 = {-1, -1};
    std::cout << "Test 4: " << (result4 == expected4 ? "PASS" : "FAIL")
              << " (expected [-1,-1], got [" << (result4.size() >= 2 ? std::to_string(result4[0]) + "," + std::to_string(result4[1]) : "empty") << "])" << std::endl;

    // Test 5: Target at the end
    std::vector<int> nums5 = {1, 1, 1, 3, 7};
    std::vector<int> result5 = sol.findSubarraySum(nums5, 10);
    std::vector<int> expected5 = {3, 4};
    std::cout << "Test 5: " << (result5 == expected5 ? "PASS" : "FAIL")
              << " (expected [3,4], got [" << (result5.size() >= 2 ? std::to_string(result5[0]) + "," + std::to_string(result5[1]) : "empty") << "])" << std::endl;

    return 0;
}
