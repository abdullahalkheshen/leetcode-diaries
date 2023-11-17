/* 
    Leetcode name: 904. Fruit Into Baskets
    Fruits into Baskets (medium)

    Problem Statement
    You are visiting a farm to collect fruits. The farm has a single row of fruit trees. You will be given two baskets, and your goal is to pick as many fruits as possible to be placed in the given baskets.

    You will be given an array of characters where each character represents a fruit tree. The farm has following restrictions:

    Each basket can have only one type of fruit. There is no limit to how many fruit a basket can hold.
    You can start with any tree, but you can’t skip a tree once you have started.
    You will pick exactly one fruit from every tree until you cannot, i.e., you will stop when you have to pick from a third fruit type.
    Write a function to return the maximum number of fruits in both baskets.

    Example 1:
    Input: Fruit=['A', 'B', 'C', 'A', 'C']  
    Output: 3  
    Explanation: We can put 2 'C' in one basket and one 'A' in the other from the subarray ['C', 'A', 'C']
    
    Example 2:
    Input: Fruit = ['A', 'B', 'C', 'B', 'B', 'C']  
    Output: 5  
    Explanation: We can put 3 'B' in one basket and two 'C' in the other basket. This can be done if we start with the second letter: ['B', 'C', 'B', 'B', 'C']

*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1: Brute Force

/* 
    Overview
    In this problem, we are given an input array representing different types of fruits and two baskets.
    We want to collect some fruits from a subarray. However, each basket can only hold one type of fruit. 
    In other words, we can collect at most 2 es of fruits.
    The task is to find out the maximum number of fruits we can collect under this premise.
    To start with, we focus on the mathematical part of the problem, this question equals:
    Given an array of integers, find the longest subarray that contains at most 2 unique integers. 
    (We will call such subarray a valid subarray for convenience)
    
    Intuition:
    Let's start with the most straightforward method, brute force! That is. to check every subarray and find out the longest valid one.
    The steps are simple:
    I. Iterate over all subarrays.
    2. For each subarray, we count the types of fruits it contains. If the subarray has no more than 2 types of fruits, meaning it is valid, we take its length to update the maximum length.

    Algorithm
        1. Initialize nax_picked = 0 to track the maximum number of fruits we can collect.
        2. Iterate over the left index left of subarrays.
        3. For every subarray start at index left , iterate over every index right to fix the end of subarray.
        4. For each subarray (left, right) , count the types of fruits it contains.
        • If there are no more than 2 types, this subarray is valid, we take its length to update max_picked .
        Otherwise, if the current subarray is invalid, we move on to the next subarray.
        5. Once we finish the iteration, return nax_picked as the maximum number of fruits we can collect

    Complexity Analysis
        Let n be the length of the input array fruits .
        Time complexity: O(n3)
            o We have three nested loops, the first loop for the left index left, the second loop for the right index "right", and the third loop for the index currentlndex between left and nght .
            o In each step, we need to add the current fruit to the set basket , which takes constant time.
            o For each subarray, we need to calculate the size of the basket after the iteration, which also takes constant time.
        Space complexity: O(n)
            o During the iteration, we need to count the types of fruits in every subarray and store them in a hash set. 
            o In the worst-case scenario, there could be O(n) different types in some subarrays, thus it requires O(n) space complexity.
*/

using namespace std;

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>

class Solution
{
public:
    int findLength(vector<char> &arr)
    {
        int max_length = 0;
        
        for (int left = 0; left < arr.size(); left++)
        {
            for (int right = 0; right < arr.size(); right++)
            {
                set<char> basket;
                for (int window_index = left; window_index <= right; window_index++) 
                {
                    basket.insert(arr[window_index]);
                }

                if (basket.size() <= 2)
                {
                    max_length = max(max_length, (right-left+1));
                }
            }
        }
        return max_length;
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Optimized Brute Force

/* 
    Intuition
        There are 3 nested loops in approach 1, so as tons of duplicated calculations. Let's try a better method to reduce the
        workload!
        So:
        No inner loop
        Let's look at the subarrays generated in every iteration.
        For every consecutive subarray, the only difference is that the second subarray has one added fruit, while the rest fruits are the same! 
        Therefore, to get the types of fruits in the second subarray, we just need to add the new fruit to the basket of the first subarray, rather than initializing an empty set and recounting all the fruits again!

    Algorithm
        l. Initialize max_picked as O.
        2. Iterate over left , the left index of the subarray.
        3. For every subarray start at index left we iterate over every index right to fix the end of subarray, and calculate the types of fruits in this subarray.
            • If there are no more than 2 types, this subarray is valid, we update max_ptcked with the length of this subarray.
            • Otherwise. the current subarray, as well as all the longer subarrays (with the same left index left ) are invalid.
                Move on to the next left index left + 1 .
        4. Once we finish the iteration, return nax_picked as the maximum number of fruits we can collect
    
    Complexity Analysis
        Let n be the length of the input array fruits .
        Time complexity: O(n2)
            o Compared with approach 1, we only have two nested loops now.
            o In each iteration step, we need to add the current fruit to the hash set basket, which takes constant time.
        Space complexity: 0(1)
            o During the iteration, we need to count the number of types in every possible subarray and update the maximum length. 
            o Since we used the early stop method, thus the types will never exceed 3.
*/

class Solution
{
    public:
        int findLength(vector<char> &arr)
        {
            int max_length = 0;

            for (int left = 0; left < arr.size(); left++)
            {
                set<char> basket;
                int right = left;
                while (right < arr.size())
                {
                    if(basket.find(arr[right]) == basket.end() && basket.size() == 2) break;
                    basket.insert(arr[right++]);
                }
                max_length = max(max_length, (right-left));
            }
            return max_length;
        }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Fixed Sliding Window!


/* 
    Intuition:
        Can we further reduce the time complexity? The answer is Yes!
        Recall how we restart the iteration in approach 2:
        If the current fruit at index right makes our window ( left, right) have 3 types of fruit, we need to break the
        iteration over rtght and start over from index left 1
        
        The question is. is this step necessary? Do we need to recalculate the types of fruits from left 1 again???
        If we have found a valid window of size k starting at index left , even though we want to restart at left + 1 , there is no need to recalculate the fruit type from left 1 all to way to right , which represent windows of size no larger than
        k . We only need to look for windows larger than k !
        Thus the logic becomes very clear: we let indexes left and right represent the size of the longest valid window we have encountered so far. In further iterations, instead of looking for smaller windows, we just check if the newly added fruit expands the window.
        More specifically: we always add fruits from the right side to temporarily increase the window size by I (Let's say from k to k + 1 ), and if the new window is valid, it means that we have managed to find a larger window of size k + 1 , great! 
        Otherwise, this means that we haven't encountered a valid window of size k 1 yet, so we should go back to the previous window size, by removing one fruit from the left side of the window.

    Algorithm:
        1. Initialize max_picked as O.
        2. Iterate over left , the left index of the subarray.
        3. For every subarray start at index left we iterate over every index right to fix the end of subarray, and calculate the types of fruits in this subarray.
            • If there are no more than 2 types, this subarray is valid, we update max_ptcked with the length of this subarray.
            • Otherwise. the current subarray, as well as all the longer subarrays (with the same left index left ) are invalid.
                Move on to the next left index left + 1 .
        4. Once we finish the iteration, return nax_picked as the maximum number of fruits we can collect
    
    Complexity Analysis
        Let n be the length of the input array fruits .
        Time complexity: O(n)
            o Compared with approach 2, we only have two nested loops now.
            o In each iteration step, we need to add the current fruit to the hash set basket, which takes constant time.
        Space complexity: 0(1)
            o During the iteration, we need to count the number of types in every possible subarray and update the maximum length. 
            o Since we used the early stop method, thus the types will never exceed 3.

*/

// The code of the above approach:
class Solution
{
public:
    int find_length(vector<char> &arr)
    {
        int left, right;
        unordered_map<char, int> basket;

        for (left = 0, right = 0; right < arr.size(); right++)
        {
            basket[arr[right]]++;
            if (basket.size() > 2)
            {
                basket[arr[left]]--;
                if (basket[arr[left]] == 0)
                    basket.erase(arr[left]);
                left++;
            }
        }
        return right - left;
    }
};