/* 
    Leetcode name: 259. 3Sum Smaller premium
    Problem Statement
    Given an array arr of unsorted numbers and a target sum, count all triplets in it such that arr[i] + arr[j] + arr[k] < target where i, j, and k are three different indices. Write a function to return the count of such triplets.

    Example 1:
    Input: [-1, 0, 2, 3], target=3 
    Output: 2
    Explanation: There are two triplets whose sum is less than the target: [-1, 0, 3], [-1, 0, 2]
    
    Example 2:
    Input: [-1, 4, 2, 1, 3], target=5 
    Output: 4
    Explanation: There are four triplets whose sum is less than the target: 
    [-1, 1, 4], [-1, 1, 3], [-1, 1, 2], [-1, 2, 3]
    
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1: Brute Force

/* 

    Intuition:
        Find every possible set of triplets (i,j,k)(i, j, k)(i,j,k) such that i<j<ki < j < ki<j<k and test for the condition.
    
    Complexity analysis
        • Time complexity: O(n^3).
        • Space complexity: 0(1).
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach: #2 Binary Search

/* 
    Intuition
        Before we solve the threeSum problem, solve this simpler twoSum version:
        Given a nums array, find the number of index pairs i, j with 0 i < j < n that satisfy the condition: nums[i] + nums[j] < target
        If we sort the array first then we can apply binary search to find the largest index j such that nums[il +
        nums[j) < target for each i. Once we have found that largest index j, we know there must be j — i pairs that satisfy the above condition with i •s value fixed.
        Finally. we can now apply the twoSum solution to threeSum directly by wrapping an outer for-loop around it.
    
    Algorithm:
        Note that in the above binary search we choose the upper middle element e t t *right +1) instead of the lower
        middle element ( lett+right
        The reason is due to the terminating condition when there are two elements left. If we
        chose the lower middle element and the condition nums[mid] < target evaluates to true, then the loop would
        never terminate. Choosing the upper middle element will guarantee termination.
        
        
    Complexity analysis
        • Time complexity: O(n2*logn).
            The binarySearch function takes O(logn) time, therefore the twoSumSmaller takes logn) time. The
            threeSumSmaller wraps with another for-loop, and therefore is O(n2 log n) time.
        
        • Space complexity. 0(1) because no additional data structures are used.

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach 3: Two Pointers

/*
    Intuition:
        Let us try sorting the array first. For example. nums = (3, 5, 2, 8, 1] becomes [1, 2, 3, 5, 8).
        Let us look at an example nums = [1, 2, 3, 5, 81, and target = 7.
        [1, 2, 3, 5, 8]
         ↑           ↑
         left       right
        Let us initialize two indices, left and right pointing to the first and last element respectively.
        When we look at the sum of first and last element. it is 1 + 8 = 9, which is 2 target. That tells us no index pair will
        ever contain the index right. So the next logical step is to move the right pointer one step to its left.
        [1, 2, 3, 5, 8]
         ↑        ↑
         left    right
        Now the pair sum is 1 -+- 5 6, which is less than target. How many pairs with one of the index left that satisfy
        the condition? You can tell by the difference between right and left which is 3, namely (1, 2), (1, 3), and (1, 5).
        Therefore, we move left one step to its right. 

    Algorithm:
    
    Complexity analysis
        • Time complexity: O(n2).
        twoSumSmaller takes O(n) at most since it touches each element in the array once. It's parent function,
        threeSumSmaller takes O(n log n) to sort the array, then runs a loop that touches (n — 2) elements, invoking
        twoSumSmaller at each iteration. Therefore, the overall time complexity is O(nlogn + n2), which boils down
        to O(n2).
        • Space complexity: 0(1) because no additional data structures are used.
    
*/