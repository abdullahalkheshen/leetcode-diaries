/**
 * Problem: 18. 4Sum (K-Sum Generalization)
 * Link: https://leetcode.com/problems/4sum/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Array, Two Pointers, Sorting, Recursion
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    This is a generalized k-Sum solution. Given an array of unsorted numbers
    and a target number, find all unique k-tuplets whose sum equals the target.

    The 4Sum problem is a specific case where k=4.

    Example 1:
    Input: nums = [1, 0, -1, 0, -2, 2], target = 0, k = 4
    Output: [[-2, -1, 1, 2], [-2, 0, 0, 2], [-1, 0, 0, 1]]

    Constraints:
    - 1 <= nums.length <= 200
    - -10^9 <= nums[i] <= 10^9
    - -10^9 <= target <= 10^9
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

// ---------------------------------------------------------------------------

// Approach #1: Recursive K-Sum with Two Pointers

/*
    Intuition:
    The two pointers pattern requires the array to be sorted. For kSum, we have
    k-2 nested loops to enumerate all combinations of k-2 values, then use two
    pointers for the remaining two values. We implement this recursively.

    Algorithm:
    1. Sort the input array.
    2. Call kSum recursively with start=0, k=4, and target.
    3. Base case: when k==2, use two pointers to find pairs.
    4. Recursive case: fix one element and call kSum with k-1.
    5. Skip duplicates and prune impossible cases.

    Complexity Analysis:
    - Time: O(n^(k-1)), for k-Sum. O(n^3) for 4Sum.
    - Space: O(n), for recursion stack
*/

class Solution {
public:
    std::vector<std::vector<int>> four_sum(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        return k_sum(nums, target, 0, 4);
    }

    std::vector<std::vector<int>> k_sum(std::vector<int>& nums, long long target, int start, int k) {
        std::vector<std::vector<int>> res;

        if (start == static_cast<int>(nums.size())) {
            return res;
        }

        long long average_value = target / k;

        if (nums[start] > average_value || average_value > nums.back()) {
            return res;
        }

        if (k == 2) {
            return two_sum(nums, target, start);
        }

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            if (i == start || nums[i - 1] != nums[i]) {
                for (auto& subset : k_sum(nums, target - nums[i], i + 1, k - 1)) {
                    res.push_back({nums[i]});
                    res.back().insert(res.back().end(), subset.begin(), subset.end());
                }
            }
        }

        return res;
    }

    std::vector<std::vector<int>> two_sum(std::vector<int>& nums, long long target, int start) {
        std::vector<std::vector<int>> res;
        int left = start;
        int right = nums.size() - 1;

        while (left < right) {
            int curr_sum = nums[left] + nums[right];

            if (curr_sum < target || (left > start && nums[left] == nums[left - 1])) {
                ++left;
            } else if (curr_sum > target || (right < static_cast<int>(nums.size()) - 1 && nums[right] == nums[right + 1])) {
                --right;
            } else {
                res.push_back({nums[left++], nums[right--]});
            }
        }

        return res;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: K-Sum with Hash Set

/*
    Intuition:
    Similar to Approach #1, but use a hash set for the two-sum base case
    instead of two pointers.

    Algorithm:
    1. Sort the array and skip duplicates.
    2. Recursively reduce k-sum to 2-sum.
    3. For 2-sum, use a hash set to find complements.

    Complexity Analysis:
    - Time: O(n^(k-1)), for k-Sum
    - Space: O(n), for the hash set
*/

class SolutionHashSet {
public:
    std::vector<std::vector<int>> four_sum(std::vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());
        return k_sum(nums, target, 0, 4);
    }

    std::vector<std::vector<int>> k_sum(std::vector<int>& nums, long long target, int start, int k) {
        std::vector<std::vector<int>> res;

        if (start == static_cast<int>(nums.size())) {
            return res;
        }

        long long average_value = target / k;

        if (nums[start] > average_value || average_value > nums.back()) {
            return res;
        }

        if (k == 2) {
            return two_sum_hash(nums, target, start);
        }

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            if (i == start || nums[i - 1] != nums[i]) {
                for (auto& subset : k_sum(nums, target - nums[i], i + 1, k - 1)) {
                    res.push_back({nums[i]});
                    res.back().insert(res.back().end(), subset.begin(), subset.end());
                }
            }
        }

        return res;
    }

    std::vector<std::vector<int>> two_sum_hash(std::vector<int>& nums, long long target, int start) {
        std::vector<std::vector<int>> res;
        std::unordered_set<long long> seen;

        for (int i = start; i < static_cast<int>(nums.size()); ++i) {
            if (res.empty() || res.back()[1] != nums[i]) {
                if (seen.count(target - nums[i])) {
                    res.push_back({static_cast<int>(target - nums[i]), nums[i]});
                }
            }
            seen.insert(nums[i]);
        }

        return res;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    std::vector<int> nums1 = {1, 0, -1, 0, -2, 2};
    auto result1 = sol.four_sum(nums1, 0);
    std::cout << "Test 1: " << (result1.size() == 3 ? "PASS" : "FAIL") << std::endl;

    // Test 2
    std::vector<int> nums2 = {2, 2, 2, 2, 2};
    auto result2 = sol.four_sum(nums2, 8);
    std::cout << "Test 2: " << (result2.size() == 1 ? "PASS" : "FAIL") << std::endl;

    // Test 3: No solution
    std::vector<int> nums3 = {1, 2, 3, 4};
    auto result3 = sol.four_sum(nums3, 100);
    std::cout << "Test 3: " << (result3.size() == 0 ? "PASS" : "FAIL") << std::endl;

    // Test 4
    std::vector<int> nums4 = {-3, -2, -1, 0, 0, 1, 2, 3};
    auto result4 = sol.four_sum(nums4, 0);
    std::cout << "Test 4: " << (result4.size() == 8 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
