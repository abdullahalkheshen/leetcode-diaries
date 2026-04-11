/* 
    Leetcode name: 457. Circular Array Loop
    Problem Challenge 3: Cycle in a Circular Array (hard)
    
    Problem Statement:
    We are given an array containing positive and negative numbers. 
    Suppose the array contains a number ‘M’ at a particular index. Now, if ‘M’ is positive we will move forward ‘M’ indices and if ‘M’ is negative move backwards ‘M’ indices. 
    
    You should assume that the array is circular which means two things:
    If, while moving forward, we reach the end of the array, we will jump to the first element to continue the movement.
    If, while moving backward, we reach the beginning of the array, we will jump to the last element to continue the movement.
    Write a method to determine if the array has a cycle. The cycle should have more than one element and should follow one direction which means the cycle should not contain both forward and backward movements.

    Example 1:
    Input: [1, 2, -1, 2, 2]
    Output: true
    Explanation: The array has a cycle among indices: 0 -> 1 -> 3 -> 0
    
    Example 2:
    Input: [2, 2, -1, 2]
    Output: true
    Explanation: The array has a cycle among indices: 1 -> 3 -> 1
    
    Example 3:
    Input: [2, 1, -1, -2]
    Output: false
    Explanation: The array does not have any cycle.

    
*/

/* 
    Intuition:
        This problem involves finding a cycle in the array and, as we know, the Fast & Slow pointer method is an efficient way to do that. 
        We can start from each index of the array to find the cycle. If a number does not have a cycle we will move forward to the next element. 
        
        There are a couple of additional things we need to take care of:
            1. As mentioned in the problem, the cycle should have more than one element. This means that when we move a pointer forward, if the pointer points to the same element after the move, we have a one-element cycle. Therefore, we can finish our cycle search for the current element.
            2. The other requirement mentioned in the problem is that the cycle should not contain both forward and backward movements. We will handle this by remembering the direction of each element while searching for the cycle. If the number is positive, the direction will be forward and if the number is negative, the direction will be backward. 
            So whenever we move a pointer forward, if there is a change in the direction, we will finish our cycle search right there for the current element.

    Algorithm:
        1. Edge Case Handling: The code checks for edge cases where the array is empty or has only one element. In these cases, no cycle exists, and the function returns `false`.
        2. Initialization: The `slow` and `fast` pointers are both initialized to the same index, typically the first element of the array.
        3. Direction Determination: The initial direction (`is_forward`) is set based on the value of the first element. If the value is positive, the pointers move forward; otherwise, they move backward.
        4. Cycle Detection Loop: The code enters an infinite loop that continues until the cycle is detected or the entire array has been traversed.
            a. Slow Pointer Movement: The `slow` pointer advances one step at a time, representing the standard traversal speed.
            b. Fast Pointer Movement: The `fast` pointer advances two steps at a time, representing a faster traversal speed.
            c. Next Position Calculation: For each pointer, the `getNextPosition` function is called to determine the next index based on the current index and the direction.
            d. Invalid Move Handling: If either pointer reaches the end of the array or encounters an invalid index (negative index after wrapping), it is set to `-1`, indicating that the pointer has reached the end or an invalid state.
            e. Cycle Detection Check: If both `slow` and `fast` pointers are pointing to the same element (both have the same value of `-1` or a valid index), it indicates the presence of a cycle. The function returns `true` in this case.
        5. Cycle Detection Failure: If the loop terminates without detecting a cycle, it means the array has been traversed without encountering a cycle. The function returns `false`, indicating the absence of a circular array loop.

    Complexity Analysis:
        Time Complexity: O(n^2)
            → The code iterates through the array in the worst case until the entire array has been traversed, which occurs when there is no cycle. 
            → Therefore, the time complexity is linear to the length of the array (n).

        Space Complexity: O(1)
            → The code only uses constant memory for the `slow` and `fast` pointers and temporary variables. Therefore, the space complexity is constant (O(1)).

*/

using namespace std;
#include <vector>

class Solution 
{
public:
    static bool circularArrayLoop(std::vector<int> arr) 
    {
        if (arr.size() <= 1)  return false;

        for (int i = 0; i < arr.size(); i++) {
            int slow, fast;
            slow = fast = i;
            bool is_forward = arr[i] > 0;

            while (true) 
            {
                slow = getNextPosition(arr, slow, is_forward);
                if (slow == -1)  break;

                fast = getNextPosition(arr, fast, is_forward);
                if (fast == -1) break;

                fast = getNextPosition(arr, fast, is_forward);
                if (fast == -1) break;

                if (slow == fast) return true;
            }
        }
        return false;
    }

private:
    static int getNextPosition(std::vector<int> arr, int index, bool is_forward) 
    {
        bool direction = arr[index] >= 0;

        if (direction != is_forward) return -1; 

        int nextIndex = (index + arr[index]) % arr.size();

        if (nextIndex < 0) nextIndex = nextIndex + arr.size();

        if (nextIndex == index) return -1;

        return nextIndex;
    }
};
