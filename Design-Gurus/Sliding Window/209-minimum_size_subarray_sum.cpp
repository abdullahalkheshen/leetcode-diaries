/* 
    Leetcode name: 209. Minimum Size Subarray Sum
    Smallest Subarray With a Greater Sum (easy)

    Problem Statement:
    Given an array of positive integers and a number ‘S,’ find the length of the smallest contiguous subarray whose sum is greater than or equal to 'S'. Return 0 if no such subarray exists.

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
    Explanation: Smallest subarrays with a sum greater than or equal to '8' are [3, 4, 1] or [1, 1, 6].
*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute force [Time Limit Exceeded]

/* 
    Intuition:
        Do as directed in question. Find the sum for all the possible subarrays and update the {ans} as and when we get a better subarray that fulfill the requirements sum>=s  
    
    Algorithm:
        1. Initialize ans = INT_MAX
        2. Iterate the array from left to right using i:
            o Iterate from the current element to the end of vector using j:
                o Find the sum of elements from index i to j
                o If sum is greater then s:
                    o Update ans — i + 1))
                    o Start the next ith iteration, since, we got the smallest subarray with sum 2 s starting from the current index.
    
    Complexity Analysis:
        • Time complexity: O(n3).
            o For each element of array, we find all the subarrays starting from that index which is O(n2) .
            o Time complexity to find the sum of each subarray is O(n).
            o Thus, the total time complexity : O(n2 * n) = O(n3)

        • Space complexity: 0(1) extra space.
*/

using namespace std;
#include <vector>
#include <algorithm>

int minSubArrayLen(int s, vector<int>& nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += nums[k];
            }
            if (sum >= s) {
                ans = min(ans, (j - i + 1));
                break; //Found the smallest subarray with sum>=s starting with index i, hence move to next index
            }
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

