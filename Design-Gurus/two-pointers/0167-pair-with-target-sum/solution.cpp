/* Problem Statement
    Two Sum II - Input Array Is Sorted - LeetCode
    Given an array of numbers sorted in ascending order and a target sum, find a pair in the array whose sum is equal to the given target.

    Write a function to return the indices of the two numbers (i.e. the pair) such that they add up to the given target.

    Example 1:
    Input: [1, 2, 3, 4, 6], target=6
    Output: [1, 3]
    Explanation: The numbers at index 1 and 3 add up to 6: 2+4=6

    Example 2:
    Input: [2, 5, 9, 11], target=11
    Output: [0, 2]
    Explanation: The numbers at index 0 and 2 add up to 11: 2+9=11

*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force (Two Passes)

/*
    Intuition:
        Use Nested for loop to compare each and every element in the array.

    Algorithm:
        1. Traverse outer for loop from element of index 0 till the last element.
        2. Traverse outer for loop from second element till the last element.
        3. if sum of any two elements equals to target return their indicies.
            (indicies incremented by 1, because that's a condition in the problem's statement).
        4. return empty vector of ints if no sum of any two elements equals to target exists.

    Big-O:
        Time Complexity: O(n^2).
            -> n is the length of the vector nums. We're iterating through this "n" twice.
        Space Complexity: O(1).
            -> We did only use space of two pointers and sum variables.

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> pair_with_target_sum(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target) return {i + 1, j + 1};
            }
        }
        return {};
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Two Pointers (One Pass)

/*
    Intuition:
        ***Since the given array is sorted***:
        Use two pointers l: left pointing to the beginning and r:right pointing to the end of the 1D array once.
        At every step, we will see if the numbers pointed by the two pointers add up to the target sum.
            If they do, we have found our pair; otherwise, we will do one of two things:
                1. If the sum of the two numbers pointed by the two pointers is greater than the target sum, this means that we need a pair with a smaller sum.  z zSo, to try more pairs, we can decrement the end-pointer.
                2. If the sum of the two numbers pointed by the two pointers is smaller than the target sum, this means that we need a pair with a larger sum. So, to try more pairs, we can increment the start-pointer.

    Algorithm:
        1. Create (declare and initialize) the two pointers.
        2. Enter a while loop as long as left is less than right.
        3. Compute the sum of the left and right pointer's elements (INSIDE WHILE LOOP).
        4. Manipulate and then return the vector/pair of ints of the indicies of the pointers if sum = target.
            4.1.
                vector<int> v(2,-1);
                v[0] = left;
                v[1] = right;
                return v;

            4.2.
                vector<int> v;
                v.push_back(i+1)
                v.push_back(j+1)
                return v;

            4.3.
                vector<int> v = {i + 1, j + 1};
                return v;

            4.4. Directly without vector at all:
                return {i+1, j+1};

        5. If no sum = target exists/found return empty vector {}.

    Big-O:
        Time complexity: O(n).
            The input array is traversed at most once.

        Space complexity: 0(1).
            Algoritm is of constant space, we did only use space to store two indices and the sum.

*/

class Solution
{
public:
    vector<int> pair_with_target_sum(const vector<int> &arr, int targetSum)
    {
        int l = 0, r = arr.size() - 1;
        while (l < r)
        {
            int sum = arr[l] + arr[r];
            if (sum == arr[l] + arr[r]) return {l + 1, r + 1};
            else if (sum < arr[l] + arr[r]) {l++;}
            else r--;
        }
        return {};
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Map

/* 
    Intuition:
        Instead of using a two-pointer, we can utilize a HashTable to search for the required pair. 
        Let's say during our iteration we are at number 'X', so we need to find 'Y' such that "X + Y Target". 
        We will do two things here:
            Search for 'Y' (which is equivalent to "Target—X") in the HashTable. If it is there, we have
            found the required pair. Otherwise, insert "X" in the HashTable, so that we can search it for the later numbers.
    
    Algorithm:
        1. Declare a map to store a number + it's index.
        2. Iterate a for loop from 0 to arr.size();
        3. find y (compliment of x) such: X + Y = Target where x = arr[i] and Target = sum.
        4. if a complimentary nb to arr[i] that adds up to targetSum exists, return {map[compliment], i}
        5. if not, store the number (arr[i]) and its index ("i") in the map.
        6. If till the end, no compliment "y" is found, return empty vector {}.

    Complexity Analysis:
        Time Complexity:
            O(N), where 'N' is the total number of elements in the given array.
        Space Complexity
            O(N), as, in the worst case, we will be pushing 'N' numbers in the HashTable.

*/

#include <unordered_map>

class Solution
{
    public:
        vector<int> pair_with_target_sum(const vector<int>& arr, int targetSum)
        {
            unordered_map<int, int> nums;  // to store number and its index
            for (int i = 0; i < arr.size(); i++) {
                int compliment = targetSum - arr[i];
                if (nums.find(compliment) != nums.end()) {
                    return {++nums[compliment], ++i};
                } else {
                    nums[arr[i]] = i;  // put the number and its index in the map
                }
            }
            return {};
        }
};