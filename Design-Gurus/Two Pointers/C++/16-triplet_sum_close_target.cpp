/* 
    Leetcode name: 16. 3Sum Closest

    Problem Statement
    Given an array of unsorted numbers and a target number, find a triplet in the array whose sum is as close to the target number as possible, return the sum of the triplet. If there are more than one such triplet, return the sum of the triplet with the smallest sum.

    Example 1:
    Input: [-1, 0, 2, 3], target=3 
    Output: 2
    Explanation: There are two triplets whose sum is less than the target: [-1, 0, 3], [-1, 0, 2]

    Example 2:
    Input: [-3, -1, 1, 2], target=1
    Output: 0
    Explanation: The triplet [-3, 1, 2] has the closest sum to the target.

    Example 3:
    Input: [1, 0, 1, 1], target=100
    Output: 3
    Explanation: The triplet [1, 1, 1] has the closest sum to the target.

    Example 4:
    Input: [0, 0, 1, 1, 2, 6], target=5
    Output: 4
    Explanation: There are two triplets with distance '1' from target: [1, 1, 2] & [0,0, 6]. 
    Between these two triplets, the correct answer will be [1, 1, 2] as it has a sum '4' which is less than the sum of the other triplet which is '6'. 
    
    ***This is because of the following requirement: 'If there are more than one such triplet, return the sum of the triplet with the smallest sum.'***

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1: Sort + Two pointers
// **SO many failed submissions because of integer overflow.**
// Refer to this article to know what's Integer overflow, why it's happening and how to fix it.
// https://g.co/bard/share/f016bba8802c

/* 
    Intuition:
        In this problem, we need to find the triplets whose sum is less than the given target.
         To meet the condition i != j != k we need to make sure that each number is not used more than once.
        Following a similar approach, first, we can sort the array and then iterate through it, taking one number at a time.
         Let’s say during our iteration we are at number ‘X’, so we need to find ‘Y’ and ‘Z’ such that X+Y+Z = target.
         At this stage, our problem translates into finding a pair whose sum is less than “target < X” (as from the above equation "Y+Z < target-X").

    Algorithm:
        1. Initialize the minimum difference diff with a large value.
        2. Sort the input array nums.
        3. Iterate through the array, for the current position i, set lo to i + 1, and hi to the last index.
        4. While the lo pointer is smaller than hi:
        5. Set sum to nums[i] + nums[lo] + nums[hi].
        6. If the absolute difference between sum and target is smaller than the absolute value of diff:
            6.1. Set diff to "target - sum". !!! Don't set diff to sum directly or it's integer overflow. !!!
        7. If sum is less than target, increment lo, else, decrement hi.
        9. If diff is zero, break from the loop.
        10. Return the value of the closest triplet, which is "target - diff" which's basically.
            Note that mathematically as diff = target - sum    target - (target - sum) = "sum"

    Complexity Analysis:
        Time Complexity: O(n^2)
            -> We have outer and inner loops, each going through "n" elements.
            -> Sorting the array takes O(nlog⁡n), so overall complexity is O(nlog⁡n+n2). This is asymptotically equivalent to O(n^2).

        Space Complexity: from O(log⁡n) to O(n).
            -> depending on the implementation of the sorting algorithm.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int diff = INT_MAX;
        int sz = nums.size();
        sort(begin(nums), end(nums));
        for (int i = 0; i < sz && diff != 0; ++i) {
            int lo = i + 1;
            int hi = sz - 1;
            while (lo < hi) {
                int sum = nums[i] + nums[lo] + nums[hi];
                if (abs(target - sum) < abs(diff)) {
                    diff = target - sum;
                }
                if (sum < target) {
                    ++lo;
                } else {
                    --hi;
                }
            }
        }
        return target - diff;
    }
};


// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2: Binary Search

/* 
    Intuition:
        * In the two pointers approach, we fix one number and use two pointers to enumerate pairs.
            Here, we fix two numbers, and use a binary search to find the third complement number.
            This is less efficient than the two pointers approach, however, it could be more intuitive to come up with.

        * Note that we may not find the exact complement number, so we check the difference between the complement and two numbers: the next higher and the previous lower.
            For example, if the complement is 42, and our array is [-10, -4, 15, 30, 60], the next higher is 60 (so the difference is -18), and the previous lower is 30 (and the difference is 12).

    Algorithm:
        1. Initialize the minimum difference diff with a large value.
        2. Sort the input array nums.
        3. Iterate through the array (outer loop):
            For the current position i, iterate through the array starting from j = i + 1 (inner loop):
                Binary-search for complement (target - nums[i] - nums[j]) in the rest of the array.
                For the next higher value, check its absolute difference with complement against diff.
                For the previous lower value, check its absolute difference with complement against diff.
                    Update diff based on the smallest absolute difference.
            If diff is zero, break from the loop.
        4. Return the value of the closest triplet, which is target - diff.
        
    Complexity Analysis:
        Time Complexity: O(n^2 * logn).
            -> Binary search takes O(logn), and we do it n times in the inner loop. 
            -> Since we are going through n elements in the outer loop, the overall complexity is O(n2 log n) .
        
        Space Complexity. from O(logn) to O(n), 
            -> depending on the implementation of the sorting algorithm.
*/


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int diff = INT_MAX;
        int sz = nums.size();
        sort(begin(nums), end(nums));
        for (int i = 0; i < sz && diff != 0; ++i) {
            for (int j = i + 1; j < sz - 1; ++j) {
                int complement = target - nums[i] - nums[j];
                auto it = upper_bound(begin(nums) + j + 1, end(nums), complement);
                int hi = it - begin(nums), lo = hi - 1;
                if (hi < sz && abs(complement - nums[hi]) < abs(diff)) {
                    diff = complement - nums[hi];
                }
                if (lo > j && abs(complement - nums[lo]) < abs(diff)) {
                    diff = complement - nums[lo];
                }
            }
        }
        return target - diff;
    }
};