/* 
    Leetcode name: 713. Subarray Product Less Than K

    Problem Statement
    Given an array with positive numbers and a positive target number, find all of its contiguous subarrays whose product is less than the target number.

    Example 1:
    Input: [2, 5, 3, 10], target=30                                              
    Output: [2], [5], [2, 5], [3], [5, 3], [10]                           
    Explanation: There are six contiguous subarrays whose product is less than the target.
    
    Example 2:
    Input: [8, 2, 6, 5], target=50                                              
    Output: [8], [2], [8, 2], [6], [2, 6], [5], [6, 5]                         
    Explanation: There are seven contiguous subarrays whose product is less than the target.

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Two pointers + sliding window:
/* 
    Intuition:
        For each right, call opt(right) the smallest left so that the product of the subarray nums[left] * nums[left + 1] * ... * nums[right] is less than k.
        opt is a monotone increasing function, so we can use a sliding window.
        In summary, this algorithm slides a window across the array, expanding and contracting this window as necessary, to find all subarrays where the product of the numbers is less than a target value. For each window, it generates all valid subarrays ending at the right edge of the window.
    
    Algorithm:
        1. The algorithm uses a sliding window approach combined with a two-pointer method. A "window" of subarray is defined between the indices pointed to by two pointers, left and right.
        2. The window starts from the leftmost side of the array (l=r=0), slides to the right one at a time, expanding the window.
        3. As we add a new element into the window (the right element), we multiply our current product with this new element.
        4. Whenever "product" of the numbers within the window (from left to right) becomes >= target, we need to make the product smaller. This is achieved by:
            4.1. Incrementing left pointer to the right, effectively excluding the left element from our window.
            4.2. Dividing our product by this removed element. We keep doing this until our product is less than target again.

        5. **For each position of right, we create all possible subarrays that end at right, and that have a product less than the target. 
            We do this by starting with a subarray that only includes the right element, then progressively adding the element to its left, and so on, until we reach the left pointer. All of these subarrays are added to the result.

        6. This process is repeated for each element in the array (each position of right), with the left boundary being adjusted as necessary.

    Complexity Analysis:
        Time Complexity: O(n) or O(n^3) where "n" is the length of nums
            -> if using the formula: count += (r-l) + 1; it's O(n)

        Space Complexity: O(1)
            -> The space used by prod, left, and ans.
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) return 0;
        
        int product = 1, pairs_count = 0, left = 0;
        for (int right = 0; right < nums.size(); right++) 
        {
            product *= nums[right];
            while (product >= k) product /= nums[left++];
            pairs_count += right - left + 1; // +1 to count the element itself (inclusive)
        }
        return pairs_count;
    }
};



// --------------------------------------------------------------------------------------------------------------------------------------------------------------


// Approach #1 Exact Approach with slight variation of counting the pairs

/* 
    Time Complexity: 
        // O(n^3) Worst case scenario:
        A talk about Space Complexity:

    Space Complexity:
        // O(1) the space used by prod, left, and ans.
        Ignoring the space required for the output list, the algorithm runs in  space which is used for the temp list.

        Can you try estimating how much space will be required for the output list?
        n + (n-1) + (n-2) + ... 3 + 2 + 1
        The worst-case will happen when every subarray has a product less than the target!

        So the question will be, how many contiguous subarrays an array can have?
        It is definitely not all Permutations of the given array; is it all Combinations of the given array?
        It is not all the Combinations of all elements of the array!

        For an array with distinct elements, finding all of its contiguous subarrays is like finding the number of ways to choose two indices, i and j, in the array such that i <= j.

        If there are a total of n elements in the array, here is how we can count all the contiguous subarrays:

        When i = 0, j can have any value from 0 to n-1, giving a total of n choices.
        When i = 1, j can have any value from 1 to n-1, giving a total of n-1 choices.
        
        Similarly, when i = 2, j can have n-2 choices. … …
        When i = n-1, j can only have only 1 choice.
        
        Let’s combine all the choices:
        Which gives us a total of: n * (n+1)/2.

        So, at most, we need space for O(n^2) output lists. At worst, each subarray can take O(n) space, so overall, our algorithm's space complexity will be O(n^3).

*/


class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        vector<vector<int>> triplets;
        if (k <= 1) return 0;
        
        int product = 1, pairs_count = 0, left = 0;
        for (int right = 0; right < nums.size(); right++) 
        {
            product *= nums[right];
            while (product >= k) product /= nums[left++];

            // Intuitive or if one forget the formula .. 
            vector<int> current_triplets;
            for (size_t i = left; i <= right; i++)
            {
                current_triplets.insert(current_triplets.begin(), nums[i]);
                triplets.push_back(current_triplets);
            }
        }
        return pairs_count;
    }
};