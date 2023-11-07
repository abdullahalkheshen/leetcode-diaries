/*
  Leetcode name: 202. Happy Number

  Problem Statement:
  Any number will be called a happy number if, after repeatedly replacing it with a number equal to the sum of the square of all of its digits, leads us to the number 1. All other (not-happy) numbers will never reach 1. Instead, they will be stuck in a cycle of numbers that does not include 1.

  Given a positive number n, return true if it is a happy number otherwise return false.

  Example 1:
  Input: 23
  Output: true (23 is a happy number)
  Explanations: Here are the steps to find out that 23 is a happy number:
  2^2 + 3^2 = 4 + 9 = 13
  1^2 + 3^2 = 1 + 9 = 10
  1^2 + 0^2 = 1 + 0 = 1
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Two Pointers (Fast and Slow)
// Floyd’s tortoise and hare cycle-finding algorithm

/*
  Intuition:  
    The algorithm uses a two-pointer approach to detect cycles while continuously applying this process. 
    If a cycle is detected, it implies that the number is not a Happy Number, and if the process converges to 1, it indicates that the number is indeed a Happy Number.

  Algorithm:  
    1. Define a helper function, `find(n)`, that takes a number `n`, and for each digit in `n`, it squares the digit and sums these squared values.
    2. Initialize two pointers, `slow` and `fast`, both initially set to the given number `n`.
    3. Use a do-while loop to continuously apply the `find` function to both `slow` and `fast`. The `slow` pointer advances one step at a time, while the `fast` pointer advances two steps at a time.
    4. If the `slow` and `fast` pointers meet (indicating a cycle), exit the loop.
    5. Check if the `slow` pointer equals 1. If it does, return `true`, indicating that the number is a Happy Number. If it's not 1, return `false`.

  Complexity Analysis:  
    • Time Complexity: O(log n),
      → where n is the given number. 
      The process of determining whether a number is a Happy Number involves repeatedly summing the squares of its digits, and the number of iterations required is logarithmic in the value of n.
    • Space Complexity: O(1),
      → as the algorithm uses only a constant amount of extra space for the `slow` and `fast` pointers, regardless of the input number.
*/

using namespace std;
#include <list>

class Solution
{
public:

  bool isHappy(int n)
  {
    int slow, fast;
    slow = fast = n;
    do
    {
      slow = find(slow);
      fast = find(find(fast));
    } while (slow != fast);
    return slow == 1;
  }

  int find(int n)
  {
    int sum = 0, digit;
    while (n > 0)
    {
      digit = n % 10;
      sum += digit * digit;
      n /= 10;
    }
    return sum;
  }
};