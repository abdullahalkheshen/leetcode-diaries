/* 
    Leetcode name: 75. Sort Colors

    Problem Statement
    Given an array containing 0s, 1s and 2s, sort the array in-place. You should treat numbers of the array as objects, hence, we can’t count 0s, 1s, and 2s to recreate the array.
    
    OR
    
    The flag of the Netherlands consists of three colors: red, white and blue; and since our input array also consists of three different numbers that is why it is called Dutch National Flag problem.
    We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
    
    Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

    You must solve this problem without using the library's sort function.

    Example 1:
    Input: [1, 0, 2, 1, 0]
    Output: [0 0 1 1 2]

    Example 2:
    Input: [2, 2, 0, 1, 2, 0]
    Output: [0 0 1 2 2 2 ]

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1: Brute Force | Time limit Exceeded.

/* 
    Intuition:
        he intuition behind the algorithm is to partition the vector into three parts: one part for the 0s, one part for the 1s, and one part for the 2s.
        To do this, the algorithm first counts the number of 0s, 1s, and 2s in the vector. Then, it iterates through the vector again, and for each element, it replaces it with the corresponding number of 0s, 1s, or 2s, depending on the counters.
        In other words, the algorithm works by first counting the number of each type of element in the vector, and then sorting the vector by overwriting the elements with the corresponding number of elements of the same type.

    Complexity Analysis:
        Time Complexity: O(n)
        Space Complexity: O(1)
*/
#include <vector>

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
        int z=0,o=0,t=0;
        for(int i=0;i<nums.size();i++)
        {
            if(nums[i]==0)z++;
            else if(nums[i]==1) o++;
            else t++;
        }

        for(int i=0;i<nums.size();i++)
        {
            while(z>0) 
                nums[i++]=0; 
                z--;
            while(o>0) 
                nums[i++]=1; 
                o--;
            while(t>0) 
                nums[i++]=2; 
                t--;
        }
    }
};



// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Two pointers

/* 
    Intuition:
        Let's use here three pointers to track the rightmost boundary of zeros, the leftmost boundary of twos and the current element under the consideration.
        The idea of solution is to move curr pointer along the array, if nums[curr] = 0 - swap it with nums[p0], if nums[curr] = 2 - swap it with nums[p2].
        In the end, all 0s are on the left, all 1s are in the middle, and all 2s are on the right.
    
    Algorithm:
        1. p0 is meant to keep track of the latest position where a 0 should be placed, p2 is meant to keep track of the latest position where a 2 should be placed. i is the current index.
            initializing three variables: i and p0 to 0, p2 to the last index of the array.
        
        2. We then start a loop that continues as long as i is less than or equal to p2. In each iteration of the loop, we check the value of the array at the current index "i".
        
        3. If the value is 0, we swap the "values/elements" at the indices i and p0. 
         We then increment both i and p0, since we know that the new element at p0 is 0 (sorted in its correct place) and we can move to the next index.
        
        4.If the value is 2, we swap the values at i and p2.
         However, after the swap, we only decrement p2 without incrementing i. 
         This is because the new value at index i (after the swap) could be 0, 1 or 2, and we need to check this value again in the next iteration.
        
        5. If the value is 1, we do nothing other than increment i. This is because we want 1s to be in the middle of the array.
        
        6. The swap function simply switches the values at two given indices in the array.
        
        7. The process continues until i is greater than p2, at which point every element in the array has been checked and placed in its correct position. Hence, the array is now sorted.

    Complexity Analysis:
        Time Complexity: O(n)
            We are iterating the input array only once.

        Space Complexity: O(1)
            The algorithm runs in constant space O(1).
*/

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
        int l=0;int r=nums.size()-1;
        for(int i=0;i<=r;i++)
        {
            if(nums[i]==0){std::swap(nums[i], nums[l++]);}
            else if(nums[i]==2){std::swap(nums[i--], nums[r--]);}
        }
    }
};