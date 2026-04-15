/**
 * Problem: 217. Contains Duplicate
 * Link: https://leetcode.com/problems/contains-duplicate/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Array, Hash Table, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an integer array nums, return true if any value appears at least twice
    in the array, and return false if every element is distinct.

    Example 1:
    Input: nums = [1, 2, 3, 4]
    Output: false
    Explanation: There are no duplicates in the given array.

    Example 2:
    Input: nums = [1, 2, 3, 1]
    Output: true
    Explanation: '1' is repeating.

    Constraints:
    - 1 <= nums.length <= 10^5
    - -10^9 <= nums[i] <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Naive Linear Search) [Time Limit Exceeded]

/*
    Intuition:
    We can use a brute force approach and compare each element with all other
    elements in the array. If any two elements are the same, we'll return true.
    If we've gone through the entire array and haven't found any duplicates,
    we'll return false.

    Algorithm:
    1. Nested for loop to compare each and every element in the vector.
    2. Return true if any two elements match.
    3. Return false if no duplicates found.

    Complexity Analysis:
    - Time: O(n^2), comparing each element with all other elements
    - Space: O(1), only need a few variables to store the indices
*/

class SolutionBruteForce {
public:
    bool contains_duplicate(std::vector<int>& nums) {
        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) return true;
            }
        }
        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Sorting

/*
    Intuition:
    If there are any duplicate integers, they will be consecutive after sorting.

    Algorithm:
    1. Sort the array in ascending order.
    2. Check if any adjacent elements are equal.
    3. Return true if duplicates found, false otherwise.

    Complexity Analysis:
    - Time: O(n log n), dominated by sorting
    - Space: O(1) or O(n), depending on the sorting algorithm
*/

class SolutionSorting {
public:
    bool contains_duplicate(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        for (size_t i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1]) return true;
        }

        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Hash Set

/*
    Intuition:
    Utilizing a data structure with faster search time will speed up the entire
    algorithm at the cost of space.

    Algorithm:
    1. Create an empty hash set.
    2. For each element, check if it exists in the set.
        - If it exists, return true (duplicate found).
        - If not, insert it into the set.
    3. If no duplicates found, return false.

    Complexity Analysis:
    - Time: O(n), we iterate through the array once
    - Space: O(n), the set stores up to n elements
*/

class Solution {
public:
    bool contains_duplicate(std::vector<int>& nums) {
        std::unordered_set<int> unique_set;

        for (int num : nums) {
            if (unique_set.count(num) > 0) return true;
            unique_set.insert(num);
        }

        return false;
    }
};

// ---------------------------------------------------------------------------

// Approach #4: Hash Map

/*
    Intuition:
    Like the hashset, but also keeps track of the occurrences of each element.

    Algorithm:
    1. Create an empty hash map.
    2. For each element, check if its count is already >= 1.
        - If yes, return true (duplicate found).
        - If not, increment its count.
    3. If no duplicates found, return false.

    Complexity Analysis:
    - Time: O(n), we iterate through the array once
    - Space: O(n), the map stores up to n elements
*/

class SolutionHashMap {
public:
    bool contains_duplicate(std::vector<int>& nums) {
        std::unordered_map<int, int> count_map;

        for (int num : nums) {
            if (count_map[num] >= 1) return true;
            count_map[num]++;
        }

        return false;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 2, 3, 4};
    bool result1 = sol.contains_duplicate(nums1);
    std::cout << "Test 1: " << (result1 == false ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {1, 2, 3, 1};
    bool result2 = sol.contains_duplicate(nums2);
    std::cout << "Test 2: " << (result2 == true ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    bool result3 = sol.contains_duplicate(nums3);
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;

    // Test 4: Single element
    std::vector<int> nums4 = {1};
    bool result4 = sol.contains_duplicate(nums4);
    std::cout << "Test 4: " << (result4 == false ? "PASS" : "FAIL") << std::endl;

    return 0;
}
