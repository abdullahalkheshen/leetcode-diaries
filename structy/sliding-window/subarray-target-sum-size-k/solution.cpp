/**
 * Problem: Subarray Target Sum Size K
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Easy
 * Tags: Sliding Window, Array
 *
 * Date Solved: 2026-04-25
 * Time Taken: 10 mins (Solved on first attempt)
 */

/*
    Problem Statement:
    Given an array of positive numbers and a positive number 'k', find if
    there exists a contiguous subarray of size 'k' whose elements sum up
    to the given target.

    Example 1:
    Input: nums = [2, 1, 5, 1, 3, 2], k = 3, target = 9
    Output: true
    Explanation: Subarray [5, 1, 3] sums to 9.

    Example 2:
    Input: nums = [2, 3, 4, 1, 5], k = 2, target = 10
    Output: false
    Explanation: No subarray of size 2 sums to 10.

    Constraints:
    - 1 <= k <= nums.length
    - 1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window (Single-Pass)

/*
    Intuition:
    A brute-force approach would check every subarray of size k by
    recomputing the sum from scratch, costing O(n * k). But consecutive
    windows of size k share k-1 elements — so sliding the window one
    step right only requires adding the new element and subtracting the
    departing one. At each valid window we simply compare the running
    sum against the target and increment a counter on match.

    Algorithm:
    1. Initialize two pointers i = 0, j = 0, a running sum = 0, and a count = 0.
    2. Expand the window by adding nums[j] to sum.
    3. Once the window reaches size k (j - i + 1 == k):
       a. If sum == target, increment count.
       b. Shrink from the left: subtract nums[i] and increment i.
    4. Increment j to continue sliding.
    5. Return count.

    Complexity Analysis:
    - Time: O(n) - single pass through the array
    - Space: O(1) - only constant memory for variables
*/

class Solution {
public:
    int subarrayTargetSumSizeK(std::vector<int> nums, int k, int target) {
        int i = 0, j = 0;
        int sum = 0;
        int count = 0;

        while (j < (int)nums.size()) {
            // Expand the window from the right
            sum += nums[j];

            if (j - i + 1 == k) {
                if (sum == target) {
                    count++;
                }
                // Shrink the window from the left
                sum -= nums[i];
                
                i++;
            }

            j++;
        }

        return count;   
    }
};
    std::vector<int> nums2 = {2, 3, 4, 1, 5};
    bool result2 = sol.subarrayTargetSumSizeK(nums2, 2, 10);
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL")
              << " (expected false, got " << (result2 ? "true" : "false") << ")" << std::endl;

    // Test 3: Single-element window
    std::vector<int> nums3 = {4, 2, 7};
    bool result3 = sol.subarrayTargetSumSizeK(nums3, 1, 7);
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result3 ? "true" : "false") << ")" << std::endl;

    // Test 4: Target found at the beginning
    std::vector<int> nums4 = {3, 4, 1, 2, 5};
    bool result4 = sol.subarrayTargetSumSizeK(nums4, 2, 7);
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL")
              << " (expected true, got " << (result4 ? "true" : "false") << ")" << std::endl;

    return 0;
}
