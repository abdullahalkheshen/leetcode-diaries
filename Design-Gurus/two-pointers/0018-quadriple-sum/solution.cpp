/**
 * Problem: 18. 4Sum
 * Link: https://leetcode.com/problems/4sum/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of unsorted numbers and a target number, find all unique
    quadruplets in it, whose sum is equal to the target number.

    Example 1:
    Input: [4, 1, 2, -1, 1, -3], target=1
    Output: [[-3, -1, 1, 4], [-3, 1, 1, 2]]
    Explanation: Both the quadruplets add up to the target.

    Example 2:
    Input: [2, 0, -1, 1, -2, 2], target=2
    Output: [[-2, 0, 2, 2], [-1, 0, 1, 2]]
    Explanation: Both the quadruplets add up to the target.

    Constraints:
    - 1 <= nums.length <= 200
    - -10^9 <= nums[i] <= 10^9
    - -10^9 <= target <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force

/*
    Intuition:
    Find unique quadruplets by iterating through four nested loops and checking
    if their sum equals the target.

    Algorithm:
    1. Sort the input array.
    2. Use four nested loops to generate all combinations.
    3. Store unique quadruplets in a set.
    4. Return the result.

    Complexity Analysis:
    - Time: O(n^4), four nested loops
    - Space: O(n^4), for storing unique quadruplets in worst case
*/

class SolutionBruteForce {
public:
    std::vector<std::vector<int>> four_sum(std::vector<int>& nums, int target) {
        int n = nums.size();
        std::sort(nums.begin(), nums.end());
        std::set<std::vector<int>> unique_set;

        for (int i = 0; i < n - 3; i++) {
            for (int j = i + 1; j < n - 2; j++) {
                for (int k = j + 1; k < n - 1; k++) {
                    for (int l = k + 1; l < n; l++) {
                        long long sum = static_cast<long long>(nums[i]) + nums[j] + nums[k] + nums[l];
                        if (sum == target) {
                            unique_set.insert({nums[i], nums[j], nums[k], nums[l]});
                        }
                    }
                }
            }
        }

        return std::vector<std::vector<int>>(unique_set.begin(), unique_set.end());
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Sort + Two Pointers

/*
    Intuition:
    Sort the array and use two nested loops to fix the first two elements.
    Then use two pointers to find the remaining two elements.

    Algorithm:
    1. Sort the input array.
    2. Use two nested loops for the first two elements.
    3. Use two pointers for the remaining two elements.
    4. Skip duplicates to ensure unique quadruplets.

    Complexity Analysis:
    - Time: O(n^3), two nested loops + two pointers
    - Space: O(1), excluding output space
*/

class Solution {
public:
    std::vector<std::vector<int>> four_sum(std::vector<int>& nums, int target) {
        int n = nums.size();
        if (n < 4) return {};

        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> quadruplets;

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                long long complement = static_cast<long long>(target) - nums[i] - nums[j];
                int left = j + 1, right = n - 1;

                while (left < right) {
                    int sum = nums[left] + nums[right];

                    if (sum < complement) {
                        left++;
                    } else if (sum > complement) {
                        right--;
                    } else {
                        quadruplets.push_back({nums[i], nums[j], nums[left], nums[right]});

                        do { left++; } while (left < right && nums[left] == nums[left - 1]);
                        do { right--; } while (left < right && nums[right] == nums[right + 1]);
                    }
                }
            }
        }

        return quadruplets;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {4, 1, 2, -1, 1, -3};
    auto result1 = sol.four_sum(nums1, 1);
    std::cout << "Test 1: " << (result1.size() == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 0, -1, 1, -2, 2};
    auto result2 = sol.four_sum(nums2, 2);
    std::cout << "Test 2: " << (result2.size() == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {1, 0, -1, 0, -2, 2};
    auto result3 = sol.four_sum(nums3, 0);
    std::cout << "Test 3: " << (result3.size() == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 4: No solution
    std::vector<int> nums4 = {1, 2, 3, 4};
    auto result4 = sol.four_sum(nums4, 100);
    std::cout << "Test 4: " << (result4.size() == 0 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
