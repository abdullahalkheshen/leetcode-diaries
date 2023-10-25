/*
    Leetcode: 977. Squares of a Sorted Array

    Problem Statement
    Given a sorted array, create a new array containing squares of all the numbers of the input array in the sorted order.

    Example 1:
    Input: [-2, -1, 0, 2, 3]
    Output: [0, 1, 4, 4, 9]

    Example 2:
    Input: [-3, -1, 0, 1, 2]
    Output: [0, 1, 1, 4, 9]

*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Sort

/*
    Intuition:
        We can use a brute-force approach to iterate the input array and calculate the square of each number. We can store these squares in a new array and then sort the resulting array using any sorting algorithm like Quicksort or Mergesort.

    ALgorithm:
        1. It depends if you want to return a new a array/vector or not.
            1.1. If yes Declare a new array and push/append to/in it.
            1.2. If not just arr[i]*=arr[i]
        2. Enter a for loop from 0 till arr.size();
        3. For each num in arr, square it then add/push/append it to the array/vector.
        4. sort the original or created vector.

    Complexity Analysis:
        Time Complexity: O(n*logn)
            This is because of sorting, where "n" is the length of the input array.

        Space Complexity: O(n) or O(1)
            If we create a new vector/array it's O(n) otherwise, O(1).
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static vector<int> makeSquares(const vector<int> &arr)
    {
        vector<int> squares;
        for (size_t i = 0; i < arr.size(); i++)
        {
            squares[i] = arr[i] * arr[i];
        }

        sort(begin(squares), end(squares));
        return squares;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Two Pointers

/*
    Intuition:
        we can utilize the Two Pointers technique to iterate over the array, with one pointer moving forward to scan positive numbers, and the other pointer moving backward to scan negative numbers. At each step, we can compare the squares of the numbers pointed by both pointers and append the smaller square to the output array.

    Algorithm:
        1. Declare a result vector to be returned.
        2. Reverse for loop (To append elements from last to first index)
        3. Compare absolute values or (square of elements at both pointers)
        4. Store the larger element 
        5.


    Complexity Analysis:
        -> Time Complexity: O(n)
            We are iterating the input array only once.

        -> Space Complexity: O(n)
            this space will be used for the output array.

 */

class Solution
{
public:
    static vector<int> makeSquares(const vector<int> &arr)
    {
        vector<int> result;
        int l = 0, r = arr.size() - 1;
        for (int i = arr.size(); i >= 0; i--)
        {
            if (abs(l) > abs(r))
                result[i] = arr[l] * arr[l++];
            else
                result[i] = arr[r] * arr[r--];
            
        }
        return result;
    }
};

// Using while loop + index to new array

class Solution
{
    public:
        static vector<int> makeSquare(const vector<int> &arr)
        {
            vector<int> result;
            int highest_index = arr.size()-1;
            int l=0, r=arr.size()-1;
            while (l<r)
            {
                if (abs(arr[l] > abs(arr[r])))
                {
                    result[highest_index--] = arr[l]*arr[l++];
                }
                else
                    result[highest_index--] = arr[r]*arr[r--];
            }
            return result;
            
        }
};