/**
 * Problem: 1512. Number of Good Pairs
 * Link: https://leetcode.com/problems/number-of-good-pairs/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Array, Hash Table, Math, Counting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of integers nums, return the number of good pairs.
    A pair (i, j) is called good if nums[i] == nums[j] and i < j.

    Example 1:
    Input: nums = [1,2,3,1,1,3]
    Output: 4
    Explanation: There are 4 good pairs: (0,3), (0,4), (3,4), (2,5).

    Example 2:
    Input: nums = [1,1,1,1]
    Output: 6
    Explanation: Each pair in the array is a 'good pair'.

    Example 3:
    Input: nums = [1,2,3]
    Output: 0
    Explanation: No number is repeating.

    Constraints:
    - 1 <= nums.length <= 100
    - 1 <= nums[i] <= 100
*/

#include <iostream>
#include <vector>
#include <unordered_map>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force (Two Pass)

/*
    Intuition:
    A pair (i, j) needs to have i < j. We can check all these pairs and count
    the number of pairs where nums[i] == nums[j].

    Algorithm:
    1. Initialize number_of_good_pairs = 0.
    2. Iterate i from 0 until nums.length.
    3. Iterate j from i + 1 until nums.length.
    4. If nums[i] == nums[j], increment number_of_good_pairs.
    5. Return number_of_good_pairs.

    Complexity Analysis:
    - Time: O(n^2), we have a nested loop over the length of the input
    - Space: O(1), we aren't using any extra space except for a few integers
*/

class SolutionBruteForce {
public:
    int num_identical_pairs(std::vector<int>& nums) {
        int number_of_good_pairs = 0;

        for (size_t i = 0; i < nums.size(); i++) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] == nums[j]) {
                    number_of_good_pairs++;
                }
            }
        }

        return number_of_good_pairs;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Hash Map

/*
    Intuition:
    We can improve our performance by using a hash map to count the frequency
    of the encountered numbers during the traversal. Whenever we encounter a
    number, it can form k good pairs with previously traversed numbers, where
    k is the number of times we have seen the number previously.

    Algorithm:
    1. Initialize number_of_good_pairs = 0 and a hash map counts.
    2. Iterate over the input. For each num:
        - Increment number_of_good_pairs by counts[num].
        - Then increment counts[num].
    3. Return number_of_good_pairs.

    Complexity Analysis:
    - Time: O(n), we iterate over the input once with O(1) work per iteration
    - Space: O(n), in the worst case, the array contains n unique numbers
*/

class Solution {
public:
    int num_identical_pairs(std::vector<int>& nums) {
        std::unordered_map<int, int> counts;
        int number_of_good_pairs = 0;

        for (int num : nums) {
            number_of_good_pairs += counts[num]++;
        }

        return number_of_good_pairs;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 2, 3, 1, 1, 3};
    int result1 = sol.num_identical_pairs(nums1);
    std::cout << "Test 1: " << (result1 == 4 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {1, 1, 1, 1};
    int result2 = sol.num_identical_pairs(nums2);
    std::cout << "Test 2: " << (result2 == 6 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {1, 2, 3};
    int result3 = sol.num_identical_pairs(nums3);
    std::cout << "Test 3: " << (result3 == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 4: Single element
    std::vector<int> nums4 = {1};
    int result4 = sol.num_identical_pairs(nums4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
