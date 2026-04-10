/*
    Leetcode name: 259. 3Sum Smaller premium
    Problem Statement
    Given an vector arr of unsorted numbers and a target sum, count all triplets in it such that arr[i] + arr[j] + arr[k] < target where i, j, and k are three different indices. 
    Write a function to return the count of such triplets.

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
        Find every possible set of triplets (i,j,k) such that i<j<k and test for the condition.

    Algorithm:
        1. Triple for loops
        2. if(nums[i] + nums[j] + nums[k] < target) add/insert into triplet.

    Complexity analysis
        • Time complexity: O(n^3).
        • Space complexity: 0(1).
*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach: #2 Binary Search

/*
    Intuition
        Before we solve the threeSum problem, solve this simpler twoSum version:
        Given a nums vector, find the number of index pairs i, j with 0 i < j < n that satisfy the condition: nums[i] + nums[j] < target
        If we sort the vector first then we can apply binary search to find the largest index j such that nums[il +
        nums[j) < target for each i. Once we have found that largest index j, we know there must be j — i pairs that satisfy the above condition with i •s value fixed.
        Finally. we can now apply the twoSum solution to threeSum directly by wrapping an outer for-loop around it.

        *Note:
        In this binary search we choose the upper middle element (left+right+1)/2 instead of the lower middle element (left+right)/2.
        The reason is due to the terminating condition when there are two elements left:
         -> If we chose the lower middle element and the condition nums[mid] < target evaluates to true, then the loop would never terminate. 
         ->Choosing the upper middle element will guarantee termination.
    
    Algorithm:

    Complexity analysis
        • Time complexity: O(n2*logn).
            -> The binarySearch function takes O(logn) time, therefore the twoSumSmaller takes O(n^2 * logn) time.

        • Space complexity. 0(1) because no additional data structures are used.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        sort(begin(nums), end(nums));
        int count = 0;
        for (int i = 0; i < nums.size() - 2; i++)
        {
            count += twoSumSmaller(nums, i + 1, target - nums[i]);
        }
        return count;
    }

private:
    int twoSumSmaller(vector<int> &nums, int startIndex, int target)
    {
        int count = 0;
        for (int i = startIndex; i < nums.size() - 1; i++)
        {
            int j = binarySearch(nums, i, target - nums[i]);
            count += j - i;
        }
        return count;
    }

    int binarySearch(vector<int> &nums, int startIndex, int target)
    {
        int left = startIndex;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = (left + right + 1) / 2;
            if (nums[mid] < target) left = mid;
            else right = mid - 1;
        }
        return left;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach 3: Two Pointers

/*
    Intuition:
        Let us try sorting the vector first. For example. nums = (3, 5, 2, 8, 1] becomes [1, 2, 3, 5, 8).
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
        1. The method searchTriplets starts by sorting the input vector arr in ascending order.
         Sorting is important as it allows us to move our pointers based on the sum we are getting and how close we are to the target sum.
        
        2. The variable count is initialized to keep track of the total number of triplets found.
        
        3. The function then iterates through arr using a for loop, stopping when it is two positions from the end of arr (arr.size() - 2).
             This is because we are always looking for triplets and thus don't need to consider the last two positions in this loop.
        
        4. Inside the for loop, we call the searchPair function with the vector, the target value minus the current element, and the current index.
         This function will find all pairs within the vector from index first+1 to the end of the vector whose sum with arr[i] is less than target. 
         The return value, which is the count of such pairs, is added to count.
        
        5.The searchPair function initializes two pointers: left to first+1 and right to the last element in the vector.
         It then enters a while loop that continues as long as left is less than right.
        
        6. In the loop, if the sum of the elements at the left and right indices is less than targetSum, this means we have found a valid pair, because adding arr[first] would still result in a sum less than target.
         Since the vector is sorted, all the elements between left and right with arr[first] will also form valid triplets. So, we add all these pairs to our count by adding right - left to count.
        
        7. We then increment left to move towards higher numbers in the vector.
        
        8. If the sum of the elements at left and right is not less than targetSum, we need a smaller sum.
         Since the vector is sorted, to achieve a smaller sum, we need to reduce the value of the larger number. Hence, we decrement right.
        
        9. This process repeats until left and right cross, at which point we have examined all possible pairs for our current value of first.
        
        10. Once searchPair has processed all possible pairs for the given first index, it returns the count of valid pairs.
        
        11. The loop in searchTriplets continues until we have tried every possible starting point for our triplet.
        
        12. Once all possible triplets have been considered, the searchTriplets function returns count, the total number of triplets whose sum is less than target.

    Complexity analysis
        • Time complexity: O(n2).
            -> twoSumSmaller takes O(n) at most since it touches each element in the vector once. 
                It's parent function threeSumSmaller takes O(n*logn) to sort the vector, then runs a loop that touches (n — 2) elements, invoking twoSumSmaller at each iteration. 
            -> Therefore, the overall time complexity is O(nlogn + n2), which boils down to O(n2).

        • Space complexity: 0(1) because no additional data structures are used.

*/

class Solution
{
public:
    int threeSumSmaller(vector<int>& nums, int target)
    {
        sort(nums.begin(), nums.end());
        int count = 0;
        for (int i = 0; i < nums.size() - 2; i++)
        {
            count += twoSumSmaller(nums, i + 1, target - nums[i]);
        }
        return count;
    }

private:
    int twoSumSmaller(vector<int>& nums, int startIndex, int target)
    {
        int count = 0;
        int left = startIndex;
        int right = nums.size() - 1;
        while (left < right)
        {
            if (nums[left] + nums[right] < target)
            {
                count += right - left;
                left++;
            }
            else right--;                
        }
        return count;
    }
};

// Or with single function:

class Solution
{
public:
    int threeSumSmaller(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        if (nums.size() < 3) return 0;
    
        int count = 0;
        for (size_t i = 0; i < nums.size(); i++)
        {
            int l = i + 1, r = nums.size() - 1;
            while (l < r)
            {
                if (nums[i] + nums[l] + nums[r] >= target) r--;
                else if (nums[i] + nums[l] + nums[r] < target)
                {
                    count = count + r - l;
                    l++;
                }
            }
            l++;
        }
        return count;
    }
};