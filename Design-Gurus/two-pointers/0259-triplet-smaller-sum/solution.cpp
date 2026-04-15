/**
 * Problem: 259. 3Sum Smaller
 * Link: https://leetcode.com/problems/3sum-smaller/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Binary Search, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of unsorted numbers and a target sum, count all triplets in
    it such that arr[i] + arr[j] + arr[k] < target where i, j, and k are three
    different indices. Write a function to return the count of such triplets.

    Example 1:
    Input: [-1, 0, 2, 3], target=3
    Output: 2
    Explanation: There are two triplets whose sum is less than the target:
    [-1, 0, 3], [-1, 0, 2]

    Example 2:
    Input: [-1, 4, 2, 1, 3], target=5
    Output: 4
    Explanation: There are four triplets whose sum is less than the target:
    [-1, 1, 4], [-1, 1, 3], [-1, 1, 2], [-1, 2, 3]

    Constraints:
    - n == nums.length
    - 0 <= n <= 3500
    - -100 <= nums[i] <= 100
    - -100 <= target <= 100
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Binary Search

/*
    Intuition:
    Sort the array first. For each pair (i, j), use binary search to find the
    largest index k such that nums[i] + nums[j] + nums[k] < target.

    Algorithm:
    1. Sort the array.
    2. For each i, call twoSumSmaller for the remaining array.
    3. In twoSumSmaller, for each j, binary search for the largest valid k.
    4. Count all valid triplets.

    Complexity Analysis:
    - Time: O(n^2 log n), binary search for each pair
    - Space: O(1), excluding sorting space
*/

class SolutionBinarySearch {
public:
    int three_sum_smaller(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        int count = 0;

        for (size_t i = 0; i < nums.size(); i++) {
            count += two_sum_smaller(nums, i + 1, target - nums[i]);
        }

        return count;
    }

private:
    int two_sum_smaller(std::vector<int>& nums, int start_index, int target) {
        int count = 0;

        for (size_t i = start_index; i < nums.size() - 1; i++) {
            int j = binary_search(nums, i, target - nums[i]);
            count += j - i;
        }

        return count;
    }

    int binary_search(std::vector<int>& nums, int start_index, int target) {
        int left = start_index;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (nums[mid] < target) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return left;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Optimal)

/*
    Intuition:
    Sort the array. For each element, use two pointers to find all pairs that
    form a valid triplet. When we find a valid pair, all elements between left
    and right also form valid triplets.

    Algorithm:
    1. Sort the array.
    2. For each i, use two pointers (left, right) for the remaining array.
    3. If sum < target, all pairs from left to right-1 are valid.
    4. Add (right - left) to count and increment left.
    5. If sum >= target, decrement right.

    Complexity Analysis:
    - Time: O(n^2), sorting + two pointers for each element
    - Space: O(1), excluding sorting space
*/

class Solution {
public:
    int three_sum_smaller(std::vector<int>& nums, int target) {
        if (nums.size() < 3) return 0;

        std::sort(nums.begin(), nums.end());
        int count = 0;

        for (size_t i = 0; i < nums.size() - 2; i++) {
            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < target) {
                    count += right - left;
                    left++;
                } else {
                    right--;
                }
            }
        }

        return count;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {-1, 0, 2, 3};
    int result1 = sol.three_sum_smaller(nums1, 3);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {-1, 4, 2, 1, 3};
    int result2 = sol.three_sum_smaller(nums2, 5);
    std::cout << "Test 2: " << (result2 == 4 ? "PASS" : "FAIL") << std::endl;

    // Test 3: Empty array
    std::vector<int> nums3 = {};
    int result3 = sol.three_sum_smaller(nums3, 0);
    std::cout << "Test 3: " << (result3 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 4
    std::vector<int> nums4 = {-2, 0, 1, 3};
    int result4 = sol.three_sum_smaller(nums4, 2);
    std::cout << "Test 4: " << (result4 == 2 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
