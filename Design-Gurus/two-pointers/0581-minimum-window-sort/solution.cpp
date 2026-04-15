/**
 * Problem: 581. Shortest Unsorted Continuous Subarray
 * Link: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Stack, Greedy, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array, find the length of the smallest subarray in it which when
    sorted will sort the whole array.

    Example 1:
    Input: [1, 2, 5, 3, 7, 10, 9, 12]
    Output: 5
    Explanation: We need to sort only the subarray [5, 3, 7, 10, 9] to make
    the whole array sorted.

    Example 2:
    Input: [1, 3, 2, 0, -1, 7, 10]
    Output: 5
    Explanation: We need to sort only the subarray [1, 3, 2, 0, -1] to make
    the whole array sorted.

    Example 3:
    Input: [1, 2, 3]
    Output: 0
    Explanation: The array is already sorted.

    Example 4:
    Input: [3, 2, 1]
    Output: 3
    Explanation: The whole array needs to be sorted.

    Constraints:
    - 1 <= nums.length <= 10^4
    - -10^5 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force [Time Limit Exceeded]

/*
    Intuition:
    Find the leftmost and rightmost elements of the unsorted subarray by
    comparing each element with all elements to its right.

    Algorithm:
    1. Initialize two pointers to track the unsorted subarray boundaries.
    2. For each pair of elements, if nums[j] < nums[i], update boundaries.
    3. Return the length of the unsorted subarray.

    Complexity Analysis:
    - Time: O(n^2), nested loops over all pairs
    - Space: O(1), only two pointers used
*/

class SolutionBruteForce {
public:
    int find_unsorted_subarray(std::vector<int>& nums) {
        int left = nums.size(), right = 0;

        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[j] < nums[i]) {
                    right = std::max(right, static_cast<int>(j));
                    left = std::min(left, static_cast<int>(i));
                }
            }
        }

        return (right - left < 0) ? 0 : (right - left + 1);
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Sort and Compare

/*
    Intuition:
    Sort a copy of the array and compare it with the original. The unsorted
    subarray is between the first and last positions where they differ.

    Algorithm:
    1. Create a sorted copy of the input array.
    2. Find the first index where they differ (left boundary).
    3. Find the last index where they differ (right boundary).
    4. Return the length of the subarray.

    Complexity Analysis:
    - Time: O(n log n), for sorting
    - Space: O(n), for the sorted copy
*/

class SolutionSort {
public:
    int find_unsorted_subarray(std::vector<int>& nums) {
        std::vector<int> sorted_nums(nums);
        std::sort(sorted_nums.begin(), sorted_nums.end());

        int left = nums.size(), right = 0;

        for (size_t i = 0; i < nums.size(); i++) {
            if (sorted_nums[i] != nums[i]) {
                left = std::min(left, static_cast<int>(i));
                right = std::max(right, static_cast<int>(i));
            }
        }

        return (right - left >= 0) ? (right - left + 1) : 0;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Two Pointers (Optimal)

/*
    Intuition:
    Find the minimum and maximum values in the unsorted subarray. Then extend
    the boundaries to include any elements that are out of order relative to
    these min/max values.

    Algorithm:
    1. Find the initial boundaries where the array stops being sorted.
    2. Find min and max values within this unsorted region.
    3. Extend left boundary while elements are greater than min.
    4. Extend right boundary while elements are less than max.
    5. Return the length.

    Complexity Analysis:
    - Time: O(n), three passes through the array
    - Space: O(1), constant space
*/

class Solution {
public:
    int find_unsorted_subarray(std::vector<int>& nums) {
        int n = nums.size();
        int low = 0, high = n - 1;

        while (low + 1 < n && nums[low] <= nums[low + 1]) low++;
        while (high - 1 >= 0 && nums[high - 1] <= nums[high]) high--;

        if (low == n - 1) return 0;

        int subarray_min = INT_MAX, subarray_max = INT_MIN;
        for (int i = low; i <= high; i++) {
            subarray_min = std::min(subarray_min, nums[i]);
            subarray_max = std::max(subarray_max, nums[i]);
        }

        while (low > 0 && nums[low - 1] > subarray_min) low--;
        while (high < n - 1 && nums[high + 1] < subarray_max) high++;

        return high - low + 1;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 2, 5, 3, 7, 10, 9, 12};
    int result1 = sol.find_unsorted_subarray(nums1);
    std::cout << "Test 1: " << (result1 == 5 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {1, 3, 2, 0, -1, 7, 10};
    int result2 = sol.find_unsorted_subarray(nums2);
    std::cout << "Test 2: " << (result2 == 5 ? "PASS" : "FAIL") << std::endl;

    // Test 3: Already sorted
    std::vector<int> nums3 = {1, 2, 3};
    int result3 = sol.find_unsorted_subarray(nums3);
    std::cout << "Test 3: " << (result3 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Reverse sorted
    std::vector<int> nums4 = {3, 2, 1};
    int result4 = sol.find_unsorted_subarray(nums4);
    std::cout << "Test 4: " << (result4 == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 5: Single element
    std::vector<int> nums5 = {1};
    int result5 = sol.find_unsorted_subarray(nums5);
    std::cout << "Test 5: " << (result5 == 0 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
