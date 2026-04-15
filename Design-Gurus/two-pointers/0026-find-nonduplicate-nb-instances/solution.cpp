/**
 * Problem: 26. Remove Duplicates from Sorted Array
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Array, Two Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of sorted numbers, move all non-duplicate number instances
    at the beginning of the array in-place. The relative order of the elements
    should be kept the same and you should not use any extra space so that the
    solution has constant space complexity.

    Move all the unique number instances at the beginning of the array and after
    moving return the length of the subarray that has no duplicate in it.

    Example 1:
    Input: [2, 3, 3, 3, 6, 9, 9]
    Output: 4
    Explanation: The first four elements after moving will be [2, 3, 6, 9].

    Example 2:
    Input: [2, 2, 2, 11]
    Output: 2
    Explanation: The first two elements after moving will be [2, 11].

    Constraints:
    - 1 <= nums.length <= 3 * 10^4
    - -100 <= nums[i] <= 100
    - nums is sorted in non-decreasing order
*/

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers (Fast & Slow)

/*
    Intuition:
    Since the input array is sorted, whenever we encounter duplicates, we can
    shift the elements left. We keep one pointer for iterating the array and
    one pointer for placing the next non-duplicate number.

    Algorithm:
    1. Initialize a slow pointer j = 1 (position for next unique element).
    2. Iterate through the array with fast pointer i.
    3. If nums[i] != nums[j-1], it's a new unique element.
    4. Copy it to position j and increment j.
    5. Return j as the count of unique elements.

    Complexity Analysis:
    - Time: O(n), single pass through the array
    - Space: O(1), constant space (in-place modification)
*/

class Solution {
public:
    int remove_duplicates(std::vector<int>& nums) {
        if (nums.empty()) return 0;

        int j = 1;

        for (size_t i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[j - 1]) {
                nums[j++] = nums[i];
            }
        }

        return j;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {2, 3, 3, 3, 6, 9, 9};
    int result1 = sol.remove_duplicates(nums1);
    std::cout << "Test 1: " << (result1 == 4 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 2, 2, 11};
    int result2 = sol.remove_duplicates(nums2);
    std::cout << "Test 2: " << (result2 == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 3: No duplicates
    std::vector<int> nums3 = {1, 2, 3, 4, 5};
    int result3 = sol.remove_duplicates(nums3);
    std::cout << "Test 3: " << (result3 == 5 ? "PASS" : "FAIL") << std::endl;

    // Test 4: All same
    std::vector<int> nums4 = {1, 1, 1, 1};
    int result4 = sol.remove_duplicates(nums4);
    std::cout << "Test 4: " << (result4 == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 5: Single element
    std::vector<int> nums5 = {1};
    int result5 = sol.remove_duplicates(nums5);
    std::cout << "Test 5: " << (result5 == 1 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
