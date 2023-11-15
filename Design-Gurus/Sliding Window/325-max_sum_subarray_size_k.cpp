/* 
    Leetcode name: 2461. Maximum Sum of Distinct Subarrays With Length K

    Maximum Sum Subarray of Size K (easy)
    Problem Statement
    Given an array of positive numbers and a positive number 'k,' find the maximum sum of any contiguous subarray of size 'k'.

    Example 1:
    Input: [2, 1, 5, 1, 3, 2], k=3 
    Output: 9
    Explanation: Subarray with maximum sum is [5, 1, 3].
    
    Example 2:
    Input: [2, 3, 4, 1, 5], k=2 
    Output: 7
    Explanation: Subarray with maximum sum is [3, 4].
*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Fixed Sliding Window

/* 
  Intuition:
    If you observe closely, you will realize that to calculate the sum of a contiguous subarray, we can utilize the sum of the previous subarray. For this, consider each subarray as a Sliding Window of size 'k.' To calculate the sum of the next subarray, we need to slide the window ahead by one element. So to slide the window forward and calculate the sum of the new position of the sliding window, we need to do two things:
    1. Subtract the element going out of the sliding window, i.e., subtract the first element of the window.
    2. Add the new element getting included in the sliding window, i.e., the element coming right after the end of the window.
    This approach will save us from re-calculating the sum of the overlapping part of the sliding window.

  Algorithm:
    The `findMaxSumSubArray()` function calculates the maximum sum of a subarray of size `k` in a given array `arr`. It works by maintaining a sliding window of size `k` and calculating the sum of the elements in the window. At each step, it slides the window forward by one element and updates the maximum sum accordingly.
    1. Initialize two variables: `window_sum` to store the sum of the elements in the sliding window and `max_sum` to store the maximum sum of a subarray of size `k` found so far.
    2. Initialize the `window_start` pointer to the beginning of the array.
    3. Iterate through the array, starting at index `k - 1`:
        * Add the next element in the array to `window_sum`.
        * If `window_end >= k - 1`:
            * Compare `window_sum` to `max_sum` and update `max_sum` if necessary.
            * Subtract the element at index `window_start` from `window_sum`.
            * Increment `window_start` by one.
    4. Return `max_sum`.

  Complexity Analysis:
    Time Complexity: O(n)
      → we iterates through the array once, so the time complexity is linear to the length of the array (n).
    Space Complexity: O(1)
      → we only uses constant memory for the `window_sum`, `max_sum`, and `window_start` variables.

*/

using namespace std;

#include <iostream>
#include <vector>

class Solution {
  public:
    static int findMaxSumSubArray(int k, const vector<int>& arr) 
    {
      int max_sum = 0;
      int window_sum = 0;
      int window_start = 0;

      for (size_t window_end = 0; window_end < arr.size(); window_end++)
      {
        window_sum += arr[window_end];
        if (window_end >= k-1)
        {
          max_sum = max(max_sum, window_sum);
          window_sum -= arr[window_start];
          window_start++;
        }
        return max_sum;
      }
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------