/**
 * Problem: 15. 3Sum
 * Link: https://leetcode.com/problems/3sum/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Sorting
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of unsorted numbers, find all unique triplets in it that
    add up to zero.

    Example 1:
    Input: [-3, 0, 1, 2, -1, 1, -2]
    Output: [[-3, 1, 2], [-2, 0, 2], [-2, 1, 1], [-1, 0, 1]]
    Explanation: There are four unique triplets whose sum is equal to zero.

    Example 2:
    Input: [-5, 2, -1, -2, 3]
    Output: [[-5, 2, 3], [-2, -1, 3]]
    Explanation: There are two unique triplets whose sum is equal to zero.

    Constraints:
    - 3 <= nums.length <= 3000
    - -10^5 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <set>

// ---------------------------------------------------------------------------

// Approach #1: Sort + Two Pointers

/*
    Intuition:
    Sort the array first. For each element, find pairs in the remaining array
    that sum to the negative of that element using two pointers.

    Algorithm:
    1. Sort the input array.
    2. Iterate through the array. For each element nums[i]:
        - Skip if it's a duplicate of the previous element.
        - Use two pointers to find pairs that sum to -nums[i].
        - Skip duplicates when a valid triplet is found.

    Complexity Analysis:
    - Time: O(n^2), sorting is O(n log n), two pointers for each element is O(n)
    - Space: O(n), for sorting (depends on implementation)
*/

class Solution {
public:
    std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> triplets;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    left++;
                } else if (sum > 0) {
                    right--;
                } else {
                    triplets.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                }
            }
        }

        return triplets;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Sort + Hash Set

/*
    Intuition:
    Sort the array to skip duplicates easily. For each element, use a hash set
    to find pairs that sum to the negative of that element.

    Algorithm:
    1. Sort the input array.
    2. For each element nums[i], use a hash set to find complements.
    3. For each nums[j], check if complement = -nums[i] - nums[j] exists in set.
    4. Skip duplicates appropriately.

    Complexity Analysis:
    - Time: O(n^2), for each element we scan the remaining array
    - Space: O(n), for the hash set
*/

class SolutionHashSet {
public:
    std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> res;

        for (size_t i = 0; i < nums.size() && nums[i] <= 0; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            std::unordered_set<int> seen;

            for (size_t j = i + 1; j < nums.size(); j++) {
                int complement = -nums[i] - nums[j];

                if (seen.count(complement)) {
                    res.push_back({nums[i], complement, nums[j]});

                    while (j + 1 < nums.size() && nums[j] == nums[j + 1]) j++;
                }

                seen.insert(nums[j]);
            }
        }

        return res;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: No Sorting (Set + Map)

/*
    Intuition:
    For unsorted arrays where modification is not allowed, use a combination
    of sets and maps to track duplicates and find triplets.

    Algorithm:
    1. Use a set to skip duplicate first elements.
    2. Use a map to track seen elements and their iteration index.
    3. Sort each triplet before adding to result set to ensure uniqueness.

    Complexity Analysis:
    - Time: O(n^2), nested loops
    - Space: O(n), for the sets and maps
*/

class SolutionNoSort {
public:
    std::vector<std::vector<int>> three_sum(std::vector<int>& nums) {
        std::set<std::vector<int>> res;
        std::unordered_set<int> dups;
        std::unordered_map<int, int> seen;

        for (size_t i = 0; i < nums.size(); ++i) {
            if (dups.insert(nums[i]).second) {
                for (size_t j = i + 1; j < nums.size(); ++j) {
                    int complement = -nums[i] - nums[j];
                    auto it = seen.find(complement);

                    if (it != seen.end() && it->second == static_cast<int>(i)) {
                        std::vector<int> triplet = {nums[i], nums[j], complement};
                        std::sort(triplet.begin(), triplet.end());
                        res.insert(triplet);
                    }

                    seen[nums[j]] = i;
                }
            }
        }

        return std::vector<std::vector<int>>(res.begin(), res.end());
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {-3, 0, 1, 2, -1, 1, -2};
    auto result1 = sol.three_sum(nums1);
    std::cout << "Test 1: " << (result1.size() == 4 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {-5, 2, -1, -2, 3};
    auto result2 = sol.three_sum(nums2);
    std::cout << "Test 2: " << (result2.size() == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 3
    std::vector<int> nums3 = {-1, 0, 1, 2, -1, -4};
    auto result3 = sol.three_sum(nums3);
    std::cout << "Test 3: " << (result3.size() == 2 ? "PASS" : "FAIL") << std::endl;

    // Test 4: No solution
    std::vector<int> nums4 = {1, 2, 3};
    auto result4 = sol.three_sum(nums4);
    std::cout << "Test 4: " << (result4.size() == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 5: All zeros
    std::vector<int> nums5 = {0, 0, 0, 0};
    auto result5 = sol.three_sum(nums5);
    std::cout << "Test 5: " << (result5.size() == 1 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
