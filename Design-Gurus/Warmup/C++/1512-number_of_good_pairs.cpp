/* Problem Statement
Given an array of integers nums, return the number of good pairs.
A pair (i, j) is called good if nums[i] == nums[j] and i < j.

Example 1:
Input: nums = [1,2,3,1,1,3]
Output: 4
Explanation: There are 4 good pairs, here are the indices: (0,3), (0,4), (3,4), (2,5).

Example 2:
Input: nums = [1,1,1,1]
Output: 6
Explanation: Each pair in the array is a 'good pair'.

Example 3:
Input: words = nums = [1,2,3]
Output: 0
Explanation: No number is repeating. */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute Force (Two Pass)

/*
    Intuition:
    A pair (i, j) needs to have i < j. We can check all these pairs and count the number of pairs where nums[i] == nums[j].
    Iterate i over the indices of nums. For each i, iterate over all j greater than i. If the numbers at the indices match, increment the number_of_good_pairswer.

    Algorithm:
    1. Initialize number_of_good_pairs = 0.
    2. Iterate i from 0 until nums.length
    3. Iterate j from i + 1 until nums.length
    4. If nums[i] == nums[j], increment number_of_good_pairs.
    5. Return number_of_good_pairs.

    Big-O:
    Time complexity: O(n^2)
        -> We have a nested loop over the length of the input. The total iterations is 1 + 2 + 3 + 4 + ... + n, which is the partial sum of this series.

    Space complexity: O(1)
        -> We aren't using any extra space except for a few integers.

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int numIdenticalPairs(vector<int> &nums)
    {
        int number_of_good_pairs = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] == nums[j])
                {
                    number_of_good_pairs++;
                }
            }
        }
        return number_of_good_pairs;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Map
/*
    Intuition:
    We can improve our performance by using a hash map to count the frequency of the encountered numbers during the traversal.
    In general, whenever we encounter a number, it can form k good pairs with previously traversed numbers, where k is the number of times we have seen the number previously.

    Algorithm:
    1. Initialize number_of_good_pairs , = 0 and a hash map counts.
    2. Iterate over the input. For each num:
    3. Increment number_of_good_pairs by counts[num], then increment counts[num];
    4. Return number_of_good_pairs.


    Big-O:
    Time complexity: O(n)
        -> We iterate over the input once. At each iteration, we perform O(1)O(1)O(1) work since hash map operations run in constant time.

    Space complexity: O(n)
        -> In the worst case, the array contains at most nnn unique numbers, then counts will grow to a size of nnn.

*/

#include <unordered_map>

class Solution
{
public:
    int numIdenticalPairs(vector<int> &nums)
    {
        unordered_map<int, int> counts;
        int number_of_good_pairs = 0;

        for (int num : nums)
        {
            number_of_good_pairs += counts[num]++;
        }
        
        return number_of_good_pairs;
    }
};