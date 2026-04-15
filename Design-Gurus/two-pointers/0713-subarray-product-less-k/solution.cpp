/**
 * Problem: 713. Subarray Product Less Than K
 * Link: https://leetcode.com/problems/subarray-product-less-than-k/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Sliding Window, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array with positive numbers and a positive target number, find all
    of its contiguous subarrays whose product is less than the target number.

    Example 1:
    Input: [2, 5, 3, 10], target=30
    Output: 6
    Explanation: There are six contiguous subarrays whose product is less than
    the target: [2], [5], [2, 5], [3], [5, 3], [10]

    Example 2:
    Input: [8, 2, 6, 5], target=50
    Output: 7
    Explanation: There are seven contiguous subarrays whose product is less than
    the target: [8], [2], [8, 2], [6], [2, 6], [5], [6, 5]

    Constraints:
    - 1 <= nums.length <= 3 * 10^4
    - 1 <= nums[i] <= 1000
    - 0 <= k <= 10^6
*/

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers + Sliding Window

/*
    Intuition:
    For each right pointer position, find the smallest left pointer such that
    the product of the subarray is less than k. Since the array has positive
    numbers, the product is monotonically increasing as we expand the window.

    Algorithm:
    1. Initialize product = 1, count = 0, left = 0.
    2. For each right position:
        - Multiply product by nums[right].
        - While product >= k, divide by nums[left] and increment left.
        - Add (right - left + 1) to count (number of valid subarrays ending at right).
    3. Return count.

    Complexity Analysis:
    - Time: O(n), each element is visited at most twice
    - Space: O(1), constant space
*/

class Solution {
public:
    int num_subarray_product_less_than_k(std::vector<int>& nums, int k) {
        if (k <= 1) return 0;

        int product = 1;
        int count = 0;
        int left = 0;

        for (int right = 0; right < static_cast<int>(nums.size()); right++) {
            product *= nums[right];

            while (product >= k) {
                product /= nums[left++];
            }

            count += right - left + 1;
        }

        return count;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {2, 5, 3, 10};
    int result1 = sol.num_subarray_product_less_than_k(nums1, 30);
    std::cout << "Test 1: " << (result1 == 6 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {8, 2, 6, 5};
    int result2 = sol.num_subarray_product_less_than_k(nums2, 50);
    std::cout << "Test 2: " << (result2 == 7 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {10, 5, 2, 6};
    int result3 = sol.num_subarray_product_less_than_k(nums3, 100);
    std::cout << "Test 3: " << (result3 == 8 ? "PASS" : "FAIL") << std::endl;

    // Test 4: k = 0
    std::vector<int> nums4 = {1, 2, 3};
    int result4 = sol.num_subarray_product_less_than_k(nums4, 0);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
