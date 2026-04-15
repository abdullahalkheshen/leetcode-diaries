/**
 * Problem: 16. 3Sum Closest
 * Link: https://leetcode.com/problems/3sum-closest/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of unsorted numbers and a target number, find a triplet in
    the array whose sum is as close to the target number as possible, return
    the sum of the triplet.

    Example 1:
    Input: [-1, 0, 2, 3], target=3
    Output: 2
    Explanation: The triplet [-1, 0, 3] has sum 2, closest to target 3.

    Example 2:
    Input: [-3, -1, 1, 2], target=1
    Output: 0
    Explanation: The triplet [-3, 1, 2] has the closest sum to the target.

    Example 3:
    Input: [1, 0, 1, 1], target=100
    Output: 3
    Explanation: The triplet [1, 1, 1] has the closest sum to the target.

    Constraints:
    - 3 <= nums.length <= 500
    - -1000 <= nums[i] <= 1000
    - -10^4 <= target <= 10^4
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// ---------------------------------------------------------------------------

// Approach #1: Sort + Two Pointers

/*
    Intuition:
    Sort the array and use two pointers to find the triplet closest to target.
    Track the difference between current sum and target, updating when we find
    a closer sum.

    Algorithm:
    1. Initialize diff with a large value.
    2. Sort the input array.
    3. For each element, use two pointers on the remaining array.
    4. Calculate sum and update diff if closer to target.
    5. Move pointers based on whether sum is less or greater than target.
    6. Return target - diff (which equals the closest sum).

    Complexity Analysis:
    - Time: O(n^2), sorting + two pointers for each element
    - Space: O(log n) to O(n), depending on sorting implementation
*/

class Solution {
public:
    int three_sum_closest(std::vector<int>& nums, int target) {
        int diff = INT_MAX;
        int n = nums.size();

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < n && diff != 0; ++i) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (std::abs(target - sum) < std::abs(diff)) {
                    diff = target - sum;
                }

                if (sum < target) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return target - diff;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Binary Search

/*
    Intuition:
    Fix two elements and use binary search to find the third element that
    makes the sum closest to target.

    Algorithm:
    1. Sort the array.
    2. For each pair (i, j), binary search for complement.
    3. Check both the found position and adjacent positions.
    4. Update diff when a closer sum is found.

    Complexity Analysis:
    - Time: O(n^2 log n), binary search for each pair
    - Space: O(log n) to O(n), depending on sorting implementation
*/

class SolutionBinarySearch {
public:
    int three_sum_closest(std::vector<int>& nums, int target) {
        int diff = INT_MAX;
        int n = nums.size();

        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < n && diff != 0; ++i) {
            for (int j = i + 1; j < n - 1; ++j) {
                int complement = target - nums[i] - nums[j];

                auto it = std::upper_bound(nums.begin() + j + 1, nums.end(), complement);
                int hi = it - nums.begin();
                int lo = hi - 1;

                if (hi < n && std::abs(complement - nums[hi]) < std::abs(diff)) {
                    diff = complement - nums[hi];
                }

                if (lo > j && std::abs(complement - nums[lo]) < std::abs(diff)) {
                    diff = complement - nums[lo];
                }
            }
        }

        return target - diff;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {-1, 0, 2, 3};
    int result1 = sol.three_sum_closest(nums1, 3);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {-3, -1, 1, 2};
    int result2 = sol.three_sum_closest(nums2, 1);
    std::cout << "Test 2: " << (result2 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {1, 0, 1, 1};
    int result3 = sol.three_sum_closest(nums3, 100);
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 4
    std::vector<int> nums4 = {-1, 2, 1, -4};
    int result4 = sol.three_sum_closest(nums4, 1);
    std::cout << "Test 4: " << (result4 == 2 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
