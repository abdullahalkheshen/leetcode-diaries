/* Contains Duplicate (easy)
Problem Statement
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

Example 1:
Input: nums= [1, 2, 3, 4]
Output: false
Explanation: There are no duplicates in the given array.

Example 2:
Input: nums= [1, 2, 3, 1]
Output: true
Explanation: '1' is repeating. */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 (Naive Linear Search) or Brute Force: [Time Limit Exceeded]
/*
Intuition:
we can use a brute force approach abd compare each element with all other elements in the vector/array.
If any two elements are the same, we'll return true, If we've gone through the entire vector/array and haven't found any duplicates, we'll return false.

Algorithm:
Nested for loop to compare each and every element in the vector.

Big-O:
Time complexity: O(n2) "n" is the number of elements in the vector/array. Here n2 because we're comparing each element with all other elements ..
Space complexity: O(1) we only need few variables to store the indicies, which takes constant space.
*/

#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    bool containsDuplicate_Brute(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++) // i+1 we only compare each element with the elements that come after it in the array,
                if (nums[i] == nums[j])
                    return true;
        }
        return false;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 (Sorting) [Accepted]
/*
Intuition:
If there are any duplicate integers, they will be consecutive after sorting.

Algorithm:
Sort the vector/array in ascending order using sort(arr.begin(),arr.end()), then check if adjacents are equal.

Big-O:
Time complexity: O(nlogn)
Space complexity: O(n) or O(1) depending on the sorting algorithm(in-place or creates new data-structure/array)
*/

#include <algorithm> // std::sort
class Solution
{
public:
    bool containDuplicatesSorting(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == nums[i + 1])
                return true;
        }
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Hash Set
/*
Intuition:
Utilizing a data structure with faster search time will speed up the entire algorithm on the back of space.

Algorithm:
Set only holds unique elements;
    1. first check if the element is existing in the set.
        1.a. if it's existing return true.
        1.b. if not insert() it to the set.
    2. If no unique elements, return false outside the loop.

Big-O:
Time complexity: O(n) where "n" is the number of elements in the vector/array, this's because we iterate through the whole array
Space complexity: O(n) The algorithm utalizes "n" spaces as it stores the elements/numbers in a set.
*/

#include <unordered_set>
class Solution
{
public:
    bool containsDuplicatesSet(vector<int> &nums)
    {
        unordered_set<int> unique_set;
        for (auto &&i : nums)
        {
            if (unique_set.count(i) > 0)
                return true;
            unique_set.insert(i);
        }
        return false;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #4: Hash Map
/*
Intuition: Like the hashset, but also keeps track of the occurences of each element.

Algorithm:
Elements in vector/array are stored as keys, while their indicies are stored as values.
In a Map: elements -> keys ; indicies -> values.
1. If duplicate is encoutered(counter already incremeneted by 1), return true.
    1.1. otherwise, increment the count of that element by 1.
3. If no duplicates exists/found return false.

Big-O:
Time complexity: O(n) n is the number of elements in the hash map.
Space complexity: O(n) n is the number of elements in the hash map.

*/

#include <unordered_map>
class Solution
{
public:
    bool containsDuplicatesMap(vector<int> &nums)
    {
        unordered_map<int, int> unordered_map;
        for (auto &&num : nums)
        {
            if (unordered_map[num] >= 1)
                return true;
            unordered_map[num]++;
        }
        return false;
    }
};