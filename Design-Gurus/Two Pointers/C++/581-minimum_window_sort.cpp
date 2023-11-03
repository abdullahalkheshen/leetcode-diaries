/* 
    Leetcode name: 581. Shortest Unsorted Continuous Subarray

    Problem Challenge 3: Minimum Window Sort (medium)
        Problem Statement
        Given an array, find the length of the smallest subarray in it which when sorted will sort the whole array.

        Example 1:
        Input: [1, 2, 5, 3, 7, 10, 9, 12]
        Output: 5
        Explanation: We need to sort only the subarray [5, 3, 7, 10, 9] to make the whole array sorted
        
        Example 2:
        Input: [1, 3, 2, 0, -1, 7, 10]
        Output: 5
        Explanation: We need to sort only the subarray [1, 3, 2, 0, -1] to make the whole array sorted
        
        Example 3:
        Input: [1, 2, 3]
        Output: 0
        Explanation: The array is already sorted
        
        Example 4:
        Input: [3, 2, 1]
        Output: 3
        Explanation: The whole array needs to be sorted.
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force [Time Limit Exceeded]

/*

    Intuition
        The function works by finding the smallest unsorted subarray of the input array. 
        The intuition is that if we find the leftmost and rightmost elements of the unsorted subarray, we can simply return the length of the subarray between them.

    Algorithm
        1. Initialize two pointers, 1 and r , to the leftmost and rightmost indces of the array, respectively.
        2. Iterate through the array from left to right, comparing each element to its next element.
        3. If the current element is greater than its next element, update the pointers 1 and r to the indices of the current element and its next element,
        respectively.
        4. Continue iterating through the array until you reach the r of the array.
        5. Return the length of the unsorted subarray, which is r - 1 + 1 . If r - 1 < ø then the arrayis already sorted, so return O.
    
    Complexity Analysis
        Time Complexity: O(n^2)
            where n is the length of the input array. This is because the nested for loop iterates over all pairs of elernents in the array.
        Space Complexity: 0(1)
            since the algorithm only uses two pointers to track the indices of the unsorted subarray.
*/

using namespace std;
#include <vector>

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int l = nums.size(), r = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) 
            {
                if (nums[j] < nums[i]) 
                {
                    r = max(r, j);
                    l = min(l, i);
                }
            }
        }
        return (r - l < 0) ? 0 : (r - l + 1);
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Sort

/* 
    Intuition:
    The function findUnsortedSubarray() works by sorting a copy of the input array and then comparing the sorted array to the original array. 
    The intuition is that if the input array is already sorted, then the sorted and original arrays will be identical. 
    However, if the input array is not sorted, then the sorted and original arrays will differ at some point. 
    The unsorted subarray is then the subarray between the leftmost and rightmost elements of the sorted array that differ from the corresponding elements of the original array.

    Algorithm:
        1. Create a copy of the input array.
        2. Sort the copy of the input array.
        3. Initialize two pointers, start and end , to the leftmost and rightmost indices of the input array, respectively.
        4. Iterate through the input array, comparing each element to the corresponding element in the sorted array.
        5. If the current element of the input array is different from the corresponding element in the sorted array, update the pointers
        start and end to the indices of the current element and its next element, respectively.
        6. Continue iterating through the input array until you reach the end of the array.
        7. Return the length of the unsorted subarray, which is end - start + 1 . If end - start < ø , then the input array is already
        sorted, so retum O.

    Complexity Analysis
        • Time Complexity: O(n*logn)
            -> where n is the length of the input array. 
            -> This is because usually sorting algorithm takes (n*logn).
        
        • Space Complexity: O(n) 
            -> since the algorithm creates a copy of the original/input array.
*/

#include<algorithm>

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> snums(nums);
        sort(snums.begin(), snums.end());
        int l = snums.size(), r = 0;
        for (int i = 0; i < snums.size(); i++) 
        {
            if (snums[i] != nums[i]) 
            {
                l = min(l, i);
                r = max(r, i);
            }
        }
        return (r - l >= 0) ? (r - l + 1) : 0;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Stack + Two Pointers:

/* 
    Intuition:
        The function findUnsortedSubarray() works by using a stack to maintain the indices of the elements in the input array that are greater than or equal to the current element. 
        The intuition is that the unsorted subarray is the subarray between the leftmost and rightmost elements in the stack that are less than the current element.
    
    Algorithm:
        1. Initialize a stack.
        2. Initialize two pointers, 1 and r , to the leftmost and rightmost indices of the input array, respectively.
        3. Iterate through the input array from left to right.
            o While the stack is not empty and the element at the top of the stack is greater than the current element, pop the element from the stack and update the pointer 1 to the index of the popped element.
            o Push the index of the current element onto the stack.
        4. Clear the stack.
        5. Iterate through the input array from right to left.
            o While the stack is not empty and the element at the top of the stack is less than the current element, pop the element from the stack and update the pointer r to the index of the popped element.
            o Push the index of the current element onto the stack.
        6. Return the length of the unsorted subarray, which is r - 1 + 1 .
    
    Complexity Analysis
        • Time Complexity: O(n), 
            -> where n is the length of the input array. This is because the algorithm iterates through the input array twice, and the stack operations are constant time.
        • Space Complexity: O(n), 
            -> since the algorithm uses a stack to store the indices of the elements in the input array.
*/

#include <stack>

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        stack<int> stack;
        int n = nums.size();
        int l = n, r = 0;

        for (int i = 0; i < n; i++) 
        {
            while (!stack.empty() && nums[stack.top()] > nums[i]) 
            {
                l = min(l, stack.top());
                stack.pop();
            }
            stack.push(i);
        }

        while (!stack.empty()) 
        {
            stack.pop();
        }

        for (int i = n - 1; i >= 0; i--) 
        {
            while (!stack.empty() && nums[stack.top()] < nums[i]) 
            {
                r = max(r, stack.top());
                stack.pop();
            }
            stack.push(i);
        }

        return (r - l > 0) ? (r - l + 1) : 0;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #4: Pure Two Pointers
/* 
    Intuition:
        The function findUnsortedSubarray() works by finding the minimum and maximum values in the unsorted subarray. 
        Once these values are found, the algorithm then finds the leftmost element that is greater than the minimum value and the rightmost element that is less than the maximum value. 
        The unsorted subarray is then the subarray between these two elements.

    Algorithm:
        1. Initialize two pointers, low and high , to the leftmost and rightmost indices of the input array, respectively.
        2. While Iow + I < nums.size() and nums[10wJ nums[low + II , increment Iow .
        3. While high - I Ø and nums[high
        - I] nums [high] , decrement high .
        4. If low nums.size()
        - 1 , then the array is already sorted and the function retums O.
        5. Initialize two variables, min1nUnsortedSubarray and max1nUnsortedSubarray , to INT MAX and INT MIN, respectively.
        6. Iterate over the unsorted subarray (i.e., from low to high , inclusive) and update min1nUnsortedSubarray and
        max1nUnsortedSubar ray to the minimum and maximum values in the subarray, respectively.
        Increment Iow while Iow - I Ø and nums[low - I] > minInUnsortedSubarray .
        7.
        8. Decrement high while high + 1 nums . size() - 1 and nums[high + 1] < maxInUnsortedSubarray .
        9. Return the length of the unsorted subarray, which is high - low + 1 .

    Complexity Analysis
        • Time Complexity: O(n), 
            -> where n is the length of the input array. 
            -> This is because the algorithm iterates through the input array three times.
        • Space Complexity: 0(1), 
            -> since the algorithm only uses four variables.
*/

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        while (low+1 < nums.size() && nums[low] <= nums[low+1]) low++;
        while (high-1 >= 0 && nums[high-1] <= nums[high]) high--;

        if (low == nums.size()-1) return 0;

        int unsortedSubarrayLeftIndex = INT_MAX, unsortedSubarrayRightIndex = INT_MIN;
        for (int i = low; i <= high; i++) 
        {
            unsortedSubarrayLeftIndex = min(unsortedSubarrayLeftIndex, nums[i]);
            unsortedSubarrayRightIndex = max(unsortedSubarrayRightIndex, nums[i]);
        }

        while (low-1 >= 0 && nums[low-1] > unsortedSubarrayLeftIndex) low--;
        while (high+1 <= nums.size()-1 && nums[high+1] < unsortedSubarrayRightIndex) high++;

        return high - low + 1;
    }
};