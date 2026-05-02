/**
 * Problem: Max Ones With Flips
 * Link: https://structy.net/
 * Platform: Structy
 * Difficulty: Medium
 * Tags: Sliding Window, Array, Variable-Size Window
 *
 * Date Solved: 2026-05-01
 * Time Taken: 30 mins
 */

/*
    Problem Statement:
    Given a binary array (containing only 0s and 1s) and a positive integer k,
    find the length of the longest contiguous subarray of 1s you can obtain by
    flipping at most k 0s to 1s.

    Example 1:
    Input: nums = [1, 1, 0, 0, 1, 1, 1, 0, 1], k = 2
    Output: 7
    Explanation: Flip the two 0s at indices 2 and 3 (or 2 and 7) to get a
    subarray of 7 consecutive 1s.

    Example 2:
    Input: nums = [0, 0, 1, 1, 0, 1, 1, 0, 0], k = 1
    Output: 4
    Explanation: Flip one 0 to get [1, 1, 0, 1, 1, 1, 0, 0] → subarray of
    length 4.

    Example 3:
    Input: nums = [1, 1, 1, 1], k = 0
    Output: 4
    Explanation: All elements are already 1, no flips needed.

    Example 4:
    Input: nums = [0, 0, 0, 0], k = 2
    Output: 2
    Explanation: Flip any two 0s to get at most 2 consecutive 1s.

    Constraints:
    - 1 <= nums.length <= 10^5
    - nums[i] is either 0 or 1
    - 0 <= k <= nums.length
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Variable-Size Sliding Window

/*
    Intuition:


    Algorithm:


    Complexity Analysis:
    - Time:
    - Space:
*/

class Solution {
public:
    int maxOnesWithFlips(std::vector<int> nums, int k) {
        int i=0, j=0;
        std::unordered_map<char, int> m;

        while (j<nums.size()) {
            m[nums[j]]++;
            
            while (m['0'] == 1) {
                m[nums[i]]--;
                if (m[nums[i]] == 0) m.erase(nums[i]);
                i++;
            }
            j++;
        }
        int longest = std::max (j-i+1, longest);

        return longest;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 1, 0, 0, 1, 1, 1, 0, 1};
    int result1 = sol.maxOnesWithFlips(nums1, 2);
    std::cout << "Test 1: " << (result1 == 7 ? "PASS" : "FAIL")
              << " (expected 7, got " << result1 << ")" << std::endl;

    // Test 2
    std::vector<int> nums2 = {0, 0, 1, 1, 0, 1, 1, 0, 0};
    int result2 = sol.maxOnesWithFlips(nums2, 1);
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result2 << ")" << std::endl;

    // Test 3: All ones, no flips needed
    std::vector<int> nums3 = {1, 1, 1, 1};
    int result3 = sol.maxOnesWithFlips(nums3, 0);
    std::cout << "Test 3: " << (result3 == 4 ? "PASS" : "FAIL")
              << " (expected 4, got " << result3 << ")" << std::endl;

    // Test 4: All zeros
    std::vector<int> nums4 = {0, 0, 0, 0};
    int result4 = sol.maxOnesWithFlips(nums4, 2);
    std::cout << "Test 4: " << (result4 == 2 ? "PASS" : "FAIL")
              << " (expected 2, got " << result4 << ")" << std::endl;

    // Test 5: k equals array length
    std::vector<int> nums5 = {0, 1, 0, 1, 0};
    int result5 = sol.maxOnesWithFlips(nums5, 5);
    std::cout << "Test 5: " << (result5 == 5 ? "PASS" : "FAIL")
              << " (expected 5, got " << result5 << ")" << std::endl;

    // Test 6: Single element
    std::vector<int> nums6 = {0};
    int result6 = sol.maxOnesWithFlips(nums6, 1);
    std::cout << "Test 6: " << (result6 == 1 ? "PASS" : "FAIL")
              << " (expected 1, got " << result6 << ")" << std::endl;

    return 0;
}
