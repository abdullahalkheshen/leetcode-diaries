/*
    Leetcode name: 26. Remove Duplicates from Sorted Array.

    Problem Statement
    Given an array of sorted numbers, move all non-duplicate number instances at the beginning of the array in-place. The relative order of the elements should be kept the same and you should not use any extra space so that the solution has constant space complexity i.e., .

    Move all the unique number instances at the beginning of the array and after moving return the length of the subarray that has no duplicate in it.

    Example 1:
    Input: [2, 3, 3, 3, 6, 9, 9]
    Output: 4
    Explanation: The first four elements after moving element will be [2, 3, 6, 9].

    Example 2:
    Input: [2, 2, 2, 11]
    Output: 2
    Explanation: The first two elements after moving elements will be [2, 11].

*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1  Two Pointers (Maybe Fast & Slow pointers)

/*
    Intuition:
        ***As the input array is sorted***
        whenever we encounter duplicates, we shift the elements left.
        In other words, we will keep one pointer for iterating the array and one pointer for placing the next non-duplicate number.
        So our algorithm will be to iterate the array and whenever we see a non-duplicate number we move it next to the last non-duplicate number we’ve seen.

    Algorithm:
        1. Create the fast pointer.
        2. Start a for loop from zero to end of array.
        3. "i" pointer (fast pointer) will keep incrementing/traversing.
        4. "j" pointer (slow pointer) will keep track of the last non duplicate element.
        4. if we encounter a new non duplicate at arr[i], update the original array with the new element.
        5. Increment/Update the non duplicate pointer by 1.
        6. After for loop end, return fast pointer.

    Complexity Analysis:
        Time Complexity: O(n)
            where ‘n’ is the total number of elements in the given array.
        Space Complexity: O(1)
            The algorithm runs in constant space (It's mandatory (a condition))
*/

#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    static int remove(vector<int> &arr)
    {
        int j = 1;
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[j - 1] != arr[i])
            {
                arr[j++] = arr[i];
            }
        }
        return j;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

/*
    Intuition:
        Use two pointers to maintain the next available position and the current element. If the current element is not equal to the previous element, copy the current element to the next available position and increment the next available position.


    Algorithm:
        1. The variable j is used to keep track of the next position to insert a unique element into the array.
            It is initialized to 0 because we assume that the first element of the array is unique.
        2. The for loop iterates over the array from index 0 to index nums.size() - 2.
            Inside the for loop, we compare the current element of the array to the next element.
            If the two elements are not equal, then we copy the current element to the position pointed to by j and increment j.
        3. After the for loop finishes iterating, j will point to the position of the last unique element in the array.
        4. The function returns j + 1.

    Complexity Analysis:
        Time complexity: O(n)
            where n is the length of the array, since we need to iterate over the array once.
        Space complexity: O(1)
            since we only need two pointers.
*/

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int j = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[j] != nums[i])
            {
                nums[++j] = nums[i];
            }
        }
        return j + 1;
    }
};
