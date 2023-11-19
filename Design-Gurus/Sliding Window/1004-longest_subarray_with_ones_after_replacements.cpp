/* 
    Leetcode name: 1004. Max Consecutive Ones III
    Longest Subarray with Ones after Replacement (hard)

    Problem Statement
    Given an array containing 0s and 1s, if you are allowed to replace no more than ‘k’ 0s with 1s, find the length of the longest contiguous subarray having all 1s.

    Example 1:
    Input: Array=[0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1], k=2  
    Output: 6  
    Explanation: Replace the '0' at index 5 and 8 to have the longest contiguous subarray of 1s having length 6.

    Example 2:
    Input: Array=[0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], k=3  
    Output: 9  
    Explanation: Replace the '0' at index 6, 9, and 10 to have the longest contiguous subarray of 1s having length 9.
*/

// ------------------------------------------------- Sliding Window Pattern -------------------------------------------------

/* 
    Intuition:
        The problem follows the Sliding Window pattern and is quite similar to Longest Substring with same Letters after Replacement.
        There is only one difference though: 
            In the problem statement of Longest Substring with same Letters after Replacement, we were asked to find the longest substring having the same letter which could be replaced with any letter (K);
            whereas in this problem, we can only replace 0s with 1s to get the longest contiguous subarray of 1s.
        Following a similar approach, we’ll iterate through the array to add one number at a time in the window. 
        We’ll also keep track of the maximum number of repeating 1s in the current window (let’s call it maxOnesCount). 
        So at any time, we know that we can have a window with 1s repeating maxOnesCount time, so we should try to replace the remaining 0s. 
        If we have more than ‘k’ remaining 0s, we should shrink the window as we are not allowed to replace more than ‘k’ 0s.

    Algorithm:
        -
    Complexity Analysis:
        where N is the number of elements in the array
        • Time Complexity: O(N)
            In worst case we might end up visiting every element of array twice, once by left pointer and once by right pointer.
        
        • Space Complexity: 0(1). We do not use any extra space.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution 
{
    public:
        static int findLength(const vector<int> &arr, int k)
        {
            int max_length = 0;
            int window_start = 0;
            int max_ones = 0;
            for(int window_end=0; window_end < arr.size(); window_end++)
            {
                if (arr[window_end] == 1) max_ones++;
                while(window_end - window_start + 1 - max_ones > k)
                {
                    if (arr[window_start++] == 1) max_ones--;
                }
                max_length = max(max_length, window_end - window_start + 1);
            }
            return max_length;
        }
};