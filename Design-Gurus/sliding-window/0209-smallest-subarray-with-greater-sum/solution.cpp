/**
 * Problem: 209. Minimum Size Subarray Sum
 * Link: https://leetcode.com/problems/minimum-size-subarray-sum/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Sliding Window, Array, Binary Search, Prefix Sum
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of positive integers and a number 'S,' find the length of the 
    smallest contiguous subarray whose sum is greater than or equal to 'S'. 
    Return 0 if no such subarray exists.

    Example 1:
    Input: [2, 1, 5, 2, 3, 2], S=7
    Output: 2
    Explanation: The smallest subarray with a sum greater than or equal to '7' is [5, 2].

    Example 2:
    Input: [2, 1, 5, 2, 8], S=7
    Output: 1 
    Explanation: The smallest subarray with a sum greater than or equal to '7' is [8].

    Example 3:
    Input: [3, 4, 1, 1, 6], S=8
    Output: 3
    Explanation: Smallest subarrays with a sum >= '8' are [3, 4, 1] or [1, 1, 6].

    Constraints:
    - 1 <= target <= 10^9
    - 1 <= nums.length <= 10^5
    - 1 <= nums[i] <= 10^4
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// ---------------------------------------------------------------------------

// Approach #1: Brute Force [Time Limit Exceeded]

/*
    Intuition:
    Find the sum for all possible subarrays and update the answer when we get 
    a better subarray that fulfills the requirement sum >= s.

    Algorithm:
    1. Initialize ans = INT_MAX
    2. Iterate the array from left to right using i
    3. For each i, iterate from i to end using j
    4. Calculate sum from index i to j
    5. If sum >= s, update ans and break (found smallest for this i)
    6. Return ans (or 0 if no valid subarray found)

    Complexity Analysis:
    - Time: O(n^3) - three nested loops
    - Space: O(1) - constant extra space
*/

class Solution1 {
public:
    int min_subarray_len(int s, std::vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int sum = 0;
                for (int k = i; k <= j; k++) {
                    sum += nums[k];
                }
                if (sum >= s) {
                    ans = std::min(ans, (j - i + 1));
                    break;
                }
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Enhanced Brute Force with Prefix Sum

/*
    Intuition:
    Instead of calculating sum for every subarray in O(n), store cumulative sum 
    from the beginning (memoization). Sum of subarray from i to j can be found 
    in O(1) using: sum = sums[j] - sums[i] + nums[i].

    Algorithm:
    1. Create prefix sum array: sums[i] = sums[i-1] + nums[i-1]
    2. For each starting index i, iterate through ending indices j
    3. Calculate sum using prefix sums in O(1)
    4. Update ans when sum >= target

    Complexity Analysis:
    - Time: O(n^2) - two nested loops, O(1) sum calculation
    - Space: O(n) - for prefix sum array
*/

class Solution2 {
public:
    int min_subarray_len(int target, std::vector<int>& nums) {
        int ans = INT_MAX;
        std::vector<int> sums(nums.size(), 0);
        sums[0] = nums[0];
        
        for (size_t i = 1; i < nums.size(); i++) {
            sums[i] = sums[i - 1] + nums[i];
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            for (int j = i; j < (int)nums.size(); j++) {
                int sum = sums[j] - (i > 0 ? sums[i - 1] : 0);
                if (sum >= target) {
                    ans = std::min(ans, j - i + 1);
                    break;
                }
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Binary Search

/*
    Intuition:
    Using prefix sums, we can use binary search to find the smallest j such that 
    sums[j] - sums[i-1] >= s. Since prefix sums are monotonically increasing 
    (all positive numbers), we can use lower_bound.

    Algorithm:
    1. Create prefix sum array with sums[0] = 0 for easier calculation
    2. For each starting index i, find target sum: to_find = s + sums[i-1]
    3. Use binary search (lower_bound) to find smallest j where sums[j] >= to_find
    4. Update ans with the subarray length

    Complexity Analysis:
    - Time: O(n * log(n)) - n iterations with binary search
    - Space: O(n) - for prefix sum array
*/

class Solution3 {
public:
    int min_subarray_len(int s, std::vector<int>& nums) {
        if (nums.size() == 0) return 0;

        int ans = INT_MAX;
        std::vector<int> sums(nums.size() + 1, 0);

        for (int i = 1; i <= (int)nums.size(); i++) {
            sums[i] = sums[i - 1] + nums[i - 1];
        }
            
        for (int i = 1; i <= (int)nums.size(); i++) {
            int to_find = s + sums[i - 1];
            auto bound = std::lower_bound(sums.begin(), sums.end(), to_find);
            if (bound != sums.end()) {
                ans = std::min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }
};

// ---------------------------------------------------------------------------

// Approach #4: Dynamic Sliding Window

/*
    Intuition:
    Use a sliding window that expands when sum < s and shrinks when sum >= s.
    This follows the Sliding Window pattern similar to Maximum Sum Subarray of Size K,
    but with variable window size.

    Algorithm:
    1. Add elements from the beginning until sum >= s
    2. Record the window length as smallest so far
    3. Try to shrink the window from the left while sum >= s
    4. At each shrink step, update the minimum length
    5. Continue sliding until the end of array

    Complexity Analysis:
    - Time: O(n) - each element is visited at most twice (added and removed)
    - Space: O(1) - constant space
*/

class Solution4 {
public:
    int min_subarray_len(int s, std::vector<int>& nums) {
        int ans = INT_MAX;
        int sum = 0;
        int window_start = 0;
        
        for (int window_end = 0; window_end < (int)nums.size(); window_end++) {
            sum += nums[window_end];
            while (sum >= s) {
                ans = std::min(ans, window_end + 1 - window_start);
                sum -= nums[window_start++];
            }
        }
        return (ans != INT_MAX) ? ans : 0;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution4 sol;
    
    // Test 1
    std::vector<int> arr1 = {2, 1, 5, 2, 3, 2};
    int result1 = sol.min_subarray_len(7, arr1);
    std::cout << "Test 1: " << (result1 == 2 ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    std::vector<int> arr2 = {2, 1, 5, 2, 8};
    int result2 = sol.min_subarray_len(7, arr2);
    std::cout << "Test 2: " << (result2 == 1 ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3
    std::vector<int> arr3 = {3, 4, 1, 1, 6};
    int result3 = sol.min_subarray_len(8, arr3);
    std::cout << "Test 3: " << (result3 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - No valid subarray
    std::vector<int> arr4 = {1, 1, 1, 1, 1};
    int result4 = sol.min_subarray_len(100, arr4);
    std::cout << "Test 4: " << (result4 == 0 ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - Entire array needed
    std::vector<int> arr5 = {1, 2, 3, 4, 5};
    int result5 = sol.min_subarray_len(15, arr5);
    std::cout << "Test 5: " << (result5 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    return 0;
}
