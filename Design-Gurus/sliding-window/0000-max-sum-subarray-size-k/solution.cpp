/**
 * Problem: 2461. Maximum Sum of Distinct Subarrays With Length K
 * Link: https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Sliding Window, Array, Hash Table
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given an array of positive numbers and a positive number 'k,' find the maximum 
    sum of any contiguous subarray of size 'k'.

    Example 1:
    Input: [2, 1, 5, 1, 3, 2], k=3 
    Output: 9
    Explanation: Subarray with maximum sum is [5, 1, 3].
    
    Example 2:
    Input: [2, 3, 4, 1, 5], k=2 
    Output: 7
    Explanation: Subarray with maximum sum is [3, 4].

    Constraints:
    - 1 <= k <= nums.length
    - 1 <= nums[i] <= 10^5
*/

#include <iostream>
#include <vector>
#include <algorithm>

// ---------------------------------------------------------------------------

// Approach #1: Fixed Sliding Window (Two-Pass)

/*
    Intuition:
    If you observe closely, you will realize that to calculate the sum of a 
    contiguous subarray, we can utilize the sum of the previous subarray. 
    Consider each subarray as a Sliding Window of size 'k.' To calculate the 
    sum of the next subarray, we need to slide the window ahead by one element:
    1. Subtract the element going out of the sliding window (first element)
    2. Add the new element getting included in the sliding window (element after end)
    This approach saves us from re-calculating the sum of the overlapping part.

    Algorithm:
    1. Initialize sum with the first k elements
    2. Set maximum to this initial sum
    3. Slide the window: subtract outgoing element, add incoming element
    4. Update maximum at each step
    5. Return maximum

    Complexity Analysis:
    - Time: O(n) - we iterate through the array once
    - Space: O(1) - only constant memory for variables
*/

class Solution1 {
public:
    int find_max_sum_subarray(int k, const std::vector<int>& arr) {
        int maximum = 0;
        int sum = 0;
        
        for (int window_end = 0; window_end < k; window_end++) {
            sum += arr[window_end];
        }
        maximum = std::max(sum, maximum);

        for (int window_end = k; window_end < (int)arr.size(); window_end++) {
            sum -= arr[window_end - k];
            sum += arr[window_end];
            maximum = std::max(sum, maximum);
        }
        return maximum;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Fixed Sliding Window (Single-Pass)

/*
    Intuition:
    Same as Approach #1, but we handle window initialization and sliding in 
    a single loop by checking when the window has reached size k.

    Algorithm:
    1. Initialize window_start = 0, sum = 0, maximum_sum = 0
    2. Iterate window_end from 0 to n-1:
       - Add arr[window_end] to sum
       - If window size equals k:
         - Update maximum_sum
         - Subtract arr[window_start] and increment window_start
    3. Return maximum_sum

    Complexity Analysis:
    - Time: O(n) - single pass through the array
    - Space: O(1) - constant memory usage

    Note: Kth element is at index k-1, nth element is at index n-1.
*/

class Solution2 {
public:
    int find_max_sum_subarray(int k, const std::vector<int>& arr) {
        int sum = 0;
        int maximum_sum = 0;
        int window_start = 0;
        
        for (int window_end = 0; window_end < (int)arr.size(); window_end++) {
            sum += arr[window_end];
            if (window_end - window_start + 1 == k) {
                maximum_sum = std::max(sum, maximum_sum);
                sum -= arr[window_start++];
            }
        }
        return maximum_sum;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution1 sol1;
    Solution2 sol2;
    
    // Test 1
    std::vector<int> arr1 = {2, 1, 5, 1, 3, 2};
    int result1 = sol1.find_max_sum_subarray(3, arr1);
    std::cout << "Test 1 (Approach 1): " << (result1 == 9 ? "PASS" : "FAIL") << std::endl;
    
    // Test 2
    std::vector<int> arr2 = {2, 3, 4, 1, 5};
    int result2 = sol1.find_max_sum_subarray(2, arr2);
    std::cout << "Test 2 (Approach 1): " << (result2 == 7 ? "PASS" : "FAIL") << std::endl;
    
    // Test 3 - Using Approach 2
    int result3 = sol2.find_max_sum_subarray(3, arr1);
    std::cout << "Test 3 (Approach 2): " << (result3 == 9 ? "PASS" : "FAIL") << std::endl;
    
    // Test 4 - Using Approach 2
    int result4 = sol2.find_max_sum_subarray(2, arr2);
    std::cout << "Test 4 (Approach 2): " << (result4 == 7 ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
