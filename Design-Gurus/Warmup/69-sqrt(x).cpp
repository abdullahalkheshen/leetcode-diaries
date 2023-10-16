/* Problem Statement
Given a non-negative integer x, return the square root of x rounded down to the nearest integer. The returned integer should be non-negative as well.

You must not use any built-in exponent function or operator.

For example, do not use pow(x, 0.5) in c++ or x ** 0.5 in python.

Example 1:

Input: x = 8
Output: 2
Explanation: The square root of 8 is 2.8284, and since we need to return the floor of the square root (integer), hence we returned 2.
Example 2:

Input: x = 4
Output: 2
Explanation: The square root of 4 is 2.
Example 3:

Input: x = 2
Output: 1
Explanation: The square root of 2 is 1.414, and since we need to return the floor of the square root (integer), hence we returned 1. */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Binary Search

/* Intuition:
The floor of the square root of a number x lies between 0 and {x/2} for all x > 1, we can use binary search within this range to find the square root.
(The integer part (i.e., the floor) of the square root will be the final result)

Algorithm:
1. If x < 2, return x.
2. Set the left pointer to 2, and the right pointer to x / 2.
3. While left <= right:
    num = (left + right) / 2 as a guess.
    Compute num * num and compare it with x:
        If num * num > x, move the right pointer right = pivot -1
        Else, if num * num < x, move the left pointer left = pivot + 1
        Otherwise num * num == x,

3. The integer square root is here, let's return it

Big-O:
Time complexity : O(logN), where N is the input number because it uses binary search to find the square root.
Space complexity : O(1), because it only uses a few variables to store the pointers, and their size doesn't grow with the input size. */

class Solution
{
public:
    int mySqrt(int x)
    {
        long number;
        int pivot, left = 2, right = x / 2;
        while (left <= right)
        {
            pivot = left + (right - left) / 2;
            number = (long)pivot * pivot;

            if (number < x)
                left = pivot + 1;
            else if (number > x)
                right = pivot - 1;
            else
                return pivot;

            // number < x ? (left = pivot + 1) : (number > x ? (right = pivot - 1) : (pivot));
        }
        return right;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approcah #2 Pocket Calculator (a bit of cheating)

/* Intuition:
Usually a pocket calculator computes well exponential functions and natural logarithms by having logarithm tables hardcoded or by the other means.

Algorithm:
1. Pocket calculators typically implement good routines to compute the exponential function and the natural logarithm, and then compute the square root of "x" using the identity found using the properties of:
2. {logarithms: ln(x^n) = n.lnx and exponentials:e^(lnx) = x.}

Big-O:
Time-complexity: O(1)
Space-complexity: O(1)
 */

#include <math.h>
class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 2)
            return x;

        int left = pow(exp(0.5 * log(x)), 1);
        int right = left + 1;

        return (long long)right * right > x ? left : right;
    }
};
