/**
 * Problem: 167. Two Sum II - Input Array Is Sorted
 * Link: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Binary Search
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of numbers sorted in ascending order and a target sum, find
    a pair in the array whose sum is equal to the given target.

    Write a function to return the indices of the two numbers (i.e. the pair)
    such that they add up to the given target.

    Example 1:
    Input: [1, 2, 3, 4, 6], target=6
    Output: [1, 3]
    Explanation: The numbers at index 1 and 3 add up to 6: 2+4=6

    Example 2:
    Input: [2, 5, 9, 11], target=11
    Output: [0, 2]
    Explanation: The numbers at index 0 and 2 add up to 11: 2+9=11

    Constraints:
    - 2 <= numbers.length <= 3 * 10^4
    - -1000 <= numbers[i] <= 1000
    - numbers is sorted in non-decreasing order
    - -1000 <= target <= 1000
    - Only one valid answer exists
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Two Passes)

/*
    Intuition:
    Use nested for loops to compare each and every element in the array.

    Algorithm:
    1. Traverse outer for loop from element of index 0 till the last element.
    2. Traverse inner for loop from second element till the last element.
    3. If sum of any two elements equals target, return their indices.
    4. Return empty vector if no pair found.

    Complexity Analysis:
    - Time: O(n^2), nested loops
    - Space: O(1), only a few variables used
*/

class SolutionBruteForce {
public:
    std::vector<int> pair_with_target_sum(std::vector<int>& nums, int target) {
        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return {static_cast<int>(i), static_cast<int>(j)};
                }
            }
        }
        return {};
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Optimal)

/*
    Intuition:
    Since the array is sorted, use two pointers: one at the beginning and one
    at the end. If the sum is too large, move the right pointer left. If the
    sum is too small, move the left pointer right.

    Algorithm:
    1. Initialize left = 0, right = n - 1.
    2. While left < right:
        - Calculate sum = nums[left] + nums[right].
        - If sum == target, return indices.
        - If sum < target, increment left.
        - If sum > target, decrement right.
    3. Return empty vector if no pair found.

    Complexity Analysis:
    - Time: O(n), single pass through the array
    - Space: O(1), constant space
*/

class Solution {
public:
    std::vector<int> pair_with_target_sum(const std::vector<int>& arr, int target_sum) {
        int left = 0;
        int right = arr.size() - 1;

        while (left < right) {
            int sum = arr[left] + arr[right];

            if (sum == target_sum) {
                return {left, right};
            } else if (sum < target_sum) {
                left++;
            } else {
                right--;
            }
        }

        return {};
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Hash Map

/*
    Intuition:
    Use a hash map to store each number and its index. For each number, check
    if its complement (target - number) exists in the map.

    Algorithm:
    1. Create a hash map to store number -> index.
    2. For each element, calculate complement = target - arr[i].
    3. If complement exists in map, return the indices.
    4. Otherwise, add current element to map.

    Complexity Analysis:
    - Time: O(n), single pass through the array
    - Space: O(n), for the hash map
*/

class SolutionHashMap {
public:
    std::vector<int> pair_with_target_sum(const std::vector<int>& arr, int target_sum) {
        std::unordered_map<int, int> nums;

        for (size_t i = 0; i < arr.size(); i++) {
            int complement = target_sum - arr[i];

            if (nums.find(complement) != nums.end()) {
                return {nums[complement], static_cast<int>(i)};
            }

            nums[arr[i]] = i;
        }

        return {};
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> arr1 = {1, 2, 3, 4, 6};
    auto result1 = sol.pair_with_target_sum(arr1, 6);
    std::cout << "Test 1: " << ((result1[0] == 1 && result1[1] == 3) ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> arr2 = {2, 5, 9, 11};
    auto result2 = sol.pair_with_target_sum(arr2, 11);
    std::cout << "Test 2: " << ((result2[0] == 0 && result2[1] == 2) ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> arr3 = {2, 7, 11, 15};
    auto result3 = sol.pair_with_target_sum(arr3, 9);
    std::cout << "Test 3: " << ((result3[0] == 0 && result3[1] == 1) ? "PASS" : "FAIL") << std::endl;

    // Test 4
    std::vector<int> arr4 = {-1, 0};
    auto result4 = sol.pair_with_target_sum(arr4, -1);
    std::cout << "Test 4: " << ((result4[0] == 0 && result4[1] == 1) ? "PASS" : "FAIL") << std::endl;

    return 0;
}
