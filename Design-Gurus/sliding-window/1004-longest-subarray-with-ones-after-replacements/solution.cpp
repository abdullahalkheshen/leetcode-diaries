/**
 * Problem: 1004. Max Consecutive Ones III
 * Link: https://leetcode.com/problems/max-consecutive-ones-iii/
 * Platform: Design-Gurus
 * Difficulty: Hard
 * Tags: Sliding Window, Array, Binary Search, Prefix Sum
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array containing 0s and 1s, if you are allowed to replace no more 
    than 'k' 0s with 1s, find the length of the longest contiguous subarray 
    having all 1s.

    Example 1:
    Input: Array=[0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1], k=2  
    Output: 6  
    Explanation: Replace the '0' at index 5 and 8 to have the longest contiguous 
    subarray of 1s having length 6.

    Example 2:
    Input: Array=[0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], k=3  
    Output: 9  
    Explanation: Replace the '0' at index 6, 9, and 10 to have the longest 
    contiguous subarray of 1s having length 9.

    Constraints:
    - 1 <= nums.length <= 10^5
    - nums[i] is either 0 or 1
    - 0 <= k <= nums.length
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Sliding Window

/*
    Intuition:
    This problem is similar to "Longest Substring with Same Letters after Replacement"
    but simpler because we only have two values (0 and 1) and we can only replace 
    0s with 1s.

    We use a sliding window and track the count of 1s in the current window.
    The window is valid if: window_size - ones_count <= k
    (meaning we have at most k zeros that need to be replaced)

    Algorithm:
    1. Initialize window_start = 0, max_ones = 0, max_length = 0
    2. Iterate window_end from 0 to n-1:
       - If arr[window_end] == 1, increment max_ones
       - While window has more than k zeros (window_size - max_ones > k):
         - If arr[window_start] == 1, decrement max_ones
         - Increment window_start
       - Update max_length with current window size
    3. Return max_length

    Complexity Analysis:
    - Time: O(n) - each element is visited at most twice (added and removed)
    - Space: O(1) - constant extra space
*/

class Solution {
public:
    int find_length(const std::vector<int>& arr, int k) {
        int max_length = 0;
        int window_start = 0;
        int max_ones = 0;
        
        for (int window_end = 0; window_end < (int)arr.size(); window_end++) {
            if (arr[window_end] == 1) {
                max_ones++;
            }
            
            while (window_end - window_start + 1 - max_ones > k) {
                if (arr[window_start++] == 1) {
                    max_ones--;
                }
            }
            
            max_length = std::max(max_length, window_end - window_start + 1);
        }
        return max_length;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1
    std::vector<int> arr1 = {0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1};
    int result1 = sol.find_length(arr1, 2);
    std::cout << "Test 1: " << (result1 == 6 ? "PASS" : "FAIL") 
              << " (got: " << result1 << ")" << std::endl;
    
    // Test 2
    std::vector<int> arr2 = {0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1};
    int result2 = sol.find_length(arr2, 3);
    std::cout << "Test 2: " << (result2 == 9 ? "PASS" : "FAIL") 
              << " (got: " << result2 << ")" << std::endl;
    
    // Test 3 - All ones
    std::vector<int> arr3 = {1, 1, 1, 1, 1};
    int result3 = sol.find_length(arr3, 2);
    std::cout << "Test 3: " << (result3 == 5 ? "PASS" : "FAIL") 
              << " (got: " << result3 << ")" << std::endl;
    
    // Test 4 - All zeros
    std::vector<int> arr4 = {0, 0, 0, 0, 0};
    int result4 = sol.find_length(arr4, 3);
    std::cout << "Test 4: " << (result4 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result4 << ")" << std::endl;
    
    // Test 5 - k = 0
    std::vector<int> arr5 = {1, 1, 0, 1, 1, 1};
    int result5 = sol.find_length(arr5, 0);
    std::cout << "Test 5: " << (result5 == 3 ? "PASS" : "FAIL") 
              << " (got: " << result5 << ")" << std::endl;
    
    // Test 6 - Large k (can flip all zeros)
    std::vector<int> arr6 = {0, 1, 0, 1, 0, 1};
    int result6 = sol.find_length(arr6, 10);
    std::cout << "Test 6: " << (result6 == 6 ? "PASS" : "FAIL") 
              << " (got: " << result6 << ")" << std::endl;
    
    return 0;
}
