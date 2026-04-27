/**
 * Problem: Longest Subarray Sum
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
    length of the longest contiguous subarray whose sum is less than or equal
    to the target.

    Example 1:
    Input: nums = [4, 2, 2, 1, 3], target = 6
    Output: 3
    Explanation: Longest subarray with sum <= 6 is [2, 2, 1] (length 3, sum 5).

    Example 2:
    Input: nums = [2, 1, 1, 1, 5], target = 5
    Output: 4
    Explanation: Longest subarray with sum <= 5 is [2, 1, 1, 1] (length 4, sum 5).

    Example 3:
    Input: nums = [3, 1, 2, 1, 1], target = 4
    Output: 3
    Explanation: Longest subarray with sum <= 4 is [1, 2, 1] or [2, 1, 1] (length 3).

    Constraints:
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^4
    - 1 <= target <= 10^9
    - All numbers are positive
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Variable-Size Sliding Window

/*
    Intuition:
    Because all elements are positive, adding an element always increases the
    window sum and removing one always decreases it. This monotonicity lets us
    greedily expand the window to the right, and only shrink from the left
    when the sum exceeds the target. At every valid window we check if its
    length is the longest seen so far.

    Algorithm:
    1. Initialize two pointers i = 0, j = 0, a running sum = 0, and maxLen = 0.
    2. Add nums[j] to sum (expand window).
    3. While sum > target, subtract nums[i] and increment i (shrink window).
    4. The window [i..j] is now valid. Update maxLen = max(maxLen, j - i + 1).
    5. Increment j and repeat.
    6. Return maxLen.

    Complexity Analysis:
    - Time: O(n) — each element is added and removed from the window at most once
    - Space: O(1) — only constant memory for pointers, sum, and maxLen
*/

class Solution {
public:
    int longestSubarraySum(std::vector<int> nums, int target) {
        int i=0, j=0;
        int sum = 0;
        
        int longest = -1;
        while (j<nums.size()) {
            // increase the window
            sum += nums[j];

            // as long as current_sum > target_sum
            if (sum > targetSum) {
                sum -= nums[i++];
            }
            
            // whenever sum == target_sum get the longest sum 
            if (sum == targetSum) longest = std::max(j-i+1, longest);
            
            j++;
        }
        return longest;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {4, 2, 2, 1, 3};
    int result1 = sol.longestSubarraySum(nums1, 6);
    std::cout << "Test 1: " << (result1 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result1 << ")" << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 1, 1, 1, 5};
    int result2 = sol.longestSubarraySum(nums2, 5);
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result2 << ")" << std::endl;

    // Test 3
    std::vector<int> nums3 = {3, 1, 2, 1, 1};
    int result3 = sol.longestSubarraySum(nums3, 4);
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL")
              << " (expected 3, got " << result3 << ")" << std::endl;

    // Test 4: Single element equals target
    std::vector<int> nums4 = {5};
    int result4 = sol.longestSubarraySum(nums4, 5);
    std::cout << "Test 4: " << (result4 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result4 << ")" << std::endl;

    // Test 5: Entire array fits
    std::vector<int> nums5 = {1, 1, 1, 1};
    int result5 = sol.longestSubarraySum(nums5, 10);
    std::cout << "Test 5: " << (result5 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result5 << ")" << std::endl;

    // Test 6: Every element exceeds target
    std::vector<int> nums6 = {10, 20, 30};
    int result6 = sol.longestSubarraySum(nums6, 5);
    std::cout << "Test 6: " << (result6 == 0 ? "PASS" : "FAIL")
              << " (expected 0, got " << result6 << ")" << std::endl;

    return 0;
}
