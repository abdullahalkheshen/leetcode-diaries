/**
 * Problem: 75. Sort Colors (Dutch National Flag)
 * Link: https://leetcode.com/problems/sort-colors/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array containing 0s, 1s and 2s, sort the array in-place. You should
    treat numbers of the array as objects, hence, we can't count 0s, 1s, and 2s
    to recreate the array.

    The flag of the Netherlands consists of three colors: red, white and blue;
    and since our input array also consists of three different numbers that is
    why it is called Dutch National Flag problem.

    Example 1:
    Input: [1, 0, 2, 1, 0]
    Output: [0, 0, 1, 1, 2]

    Example 2:
    Input: [2, 2, 0, 1, 2, 0]
    Output: [0, 0, 1, 2, 2, 2]

    Constraints:
    - n == nums.length
    - 1 <= n <= 300
    - nums[i] is either 0, 1, or 2
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Counting Sort

/*
    Intuition:
    Count the number of 0s, 1s, and 2s, then overwrite the array with the
    correct number of each value.

    Algorithm:
    1. Count occurrences of 0, 1, and 2.
    2. Overwrite the array with the counted values.

    Complexity Analysis:
    - Time: O(n), two passes through the array
    - Space: O(1), only three counters
*/

class SolutionCounting {
public:
    void sort_colors(std::vector<int>& nums) {
        int zeros = 0, ones = 0, twos = 0;

        for (int num : nums) {
            if (num == 0) zeros++;
            else if (num == 1) ones++;
            else twos++;
        }

        int i = 0;
        while (zeros-- > 0) nums[i++] = 0;
        while (ones-- > 0) nums[i++] = 1;
        while (twos-- > 0) nums[i++] = 2;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Dutch National Flag Algorithm)

/*
    Intuition:
    Use three pointers to track the rightmost boundary of zeros, the leftmost
    boundary of twos, and the current element under consideration. Move
    elements to their correct positions in a single pass.

    Algorithm:
    1. Initialize: left = 0 (boundary for 0s), right = n-1 (boundary for 2s),
       i = 0 (current element).
    2. While i <= right:
        - If nums[i] == 0: swap with nums[left], increment both left and i.
        - If nums[i] == 2: swap with nums[right], decrement right only.
        - If nums[i] == 1: just increment i.
    3. The array is now sorted.

    Complexity Analysis:
    - Time: O(n), single pass through the array
    - Space: O(1), constant space
*/

class Solution {
public:
    void sort_colors(std::vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        for (int i = 0; i <= right; ) {
            if (nums[i] == 0) {
                std::swap(nums[i], nums[left]);
                left++;
                i++;
            } else if (nums[i] == 2) {
                std::swap(nums[i], nums[right]);
                right--;
            } else {
                i++;
            }
        }
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 0, 2, 1, 0};
    sol.sort_colors(nums1);
    std::vector<int> expected1 = {0, 0, 1, 1, 2};
    std::cout << "Test 1: " << (nums1 == expected1 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 2, 0, 1, 2, 0};
    sol.sort_colors(nums2);
    std::vector<int> expected2 = {0, 0, 1, 2, 2, 2};
    std::cout << "Test 2: " << (nums2 == expected2 ? "PASS" : "FAIL") << std::endl;

    // Test 3: All same
    std::vector<int> nums3 = {1, 1, 1};
    sol.sort_colors(nums3);
    std::vector<int> expected3 = {1, 1, 1};
    std::cout << "Test 3: " << (nums3 == expected3 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Already sorted
    std::vector<int> nums4 = {0, 1, 2};
    sol.sort_colors(nums4);
    std::vector<int> expected4 = {0, 1, 2};
    std::cout << "Test 4: " << (nums4 == expected4 ? "PASS" : "FAIL") << std::endl;

    // Test 5: Reverse sorted
    std::vector<int> nums5 = {2, 1, 0};
    sol.sort_colors(nums5);
    std::vector<int> expected5 = {0, 1, 2};
    std::cout << "Test 5: " << (nums5 == expected5 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
