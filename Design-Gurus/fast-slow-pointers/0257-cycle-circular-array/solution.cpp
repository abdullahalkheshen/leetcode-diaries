/**
 * Problem: 457. Circular Array Loop
 * Link: https://leetcode.com/problems/circular-array-loop/
 * Platform: Design-Gurus
 * Difficulty: Hard
 * Tags: Array, Two Pointers, Hash Table, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    We are given an array containing positive and negative numbers. Suppose the 
    array contains a number 'M' at a particular index. Now, if 'M' is positive we 
    will move forward 'M' indices and if 'M' is negative move backwards 'M' indices.

    You should assume that the array is circular which means two things:
    - If, while moving forward, we reach the end of the array, we will jump to the 
      first element to continue the movement.
    - If, while moving backward, we reach the beginning of the array, we will jump 
      to the last element to continue the movement.

    Write a method to determine if the array has a cycle. The cycle should have more 
    than one element and should follow one direction which means the cycle should not 
    contain both forward and backward movements.

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

    Constraints:
    - 1 <= nums.length <= 5000
    - -1000 <= nums[i] <= 1000
    - nums[i] != 0
*/

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers (Fast & Slow)

/*
    Intuition:
    This problem involves finding a cycle in the array and, as we know, the Fast & 
    Slow pointer method is an efficient way to do that. We can start from each index 
    of the array to find the cycle.

    There are a couple of additional things we need to take care of:
    1. The cycle should have more than one element. This means that when we move a 
       pointer forward, if the pointer points to the same element after the move, 
       we have a one-element cycle.
    2. The cycle should not contain both forward and backward movements. We will 
       handle this by remembering the direction of each element while searching.

    Algorithm:
    1. Edge Case Handling: Check for empty or single-element arrays.
    2. Initialization: Initialize slow and fast pointers to the same index.
    3. Direction Determination: Set initial direction based on the first element's value.
    4. Cycle Detection Loop: Move slow by one step and fast by two steps.
    5. Return true if slow and fast meet, otherwise continue to next starting index.

    Complexity Analysis:
    - Time: O(n^2) - For each element, we may traverse the entire array.
    - Space: O(1) - Only constant memory for pointers and temporary variables.
*/

class Solution {
public:
    bool circular_array_loop(std::vector<int>& arr) {
        if (arr.size() <= 1) return false;

        for (size_t i = 0; i < arr.size(); i++) {
            int slow = i;
            int fast = i;
            bool is_forward = arr[i] > 0;

            while (true) {
                slow = get_next_position(arr, slow, is_forward);
                if (slow == -1) break;

                fast = get_next_position(arr, fast, is_forward);
                if (fast == -1) break;

                fast = get_next_position(arr, fast, is_forward);
                if (fast == -1) break;

                if (slow == fast) return true;
            }
        }
        return false;
    }

private:
    int get_next_position(const std::vector<int>& arr, int index, bool is_forward) {
        bool direction = arr[index] >= 0;

        if (direction != is_forward) return -1;

        int next_index = ((index + arr[index]) % static_cast<int>(arr.size()));

        if (next_index < 0) {
            next_index = next_index + static_cast<int>(arr.size());
        }

        if (next_index == index) return -1;

        return next_index;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: Has cycle
    std::vector<int> arr1 = {1, 2, -1, 2, 2};
    bool result1 = sol.circular_array_loop(arr1);
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Has cycle
    std::vector<int> arr2 = {2, 2, -1, 2};
    bool result2 = sol.circular_array_loop(arr2);
    std::cout << "Test 2: " << (result2 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: No cycle
    std::vector<int> arr3 = {2, 1, -1, -2};
    bool result3 = sol.circular_array_loop(arr3);
    std::cout << "Test 3: " << (result3 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Single element (no cycle possible)
    std::vector<int> arr4 = {1};
    bool result4 = sol.circular_array_loop(arr4);
    std::cout << "Test 4: " << (result4 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 5: All same direction forward
    std::vector<int> arr5 = {-1, -2, -3, -4, -5};
    bool result5 = sol.circular_array_loop(arr5);
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
