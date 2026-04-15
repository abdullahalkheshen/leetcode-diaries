/**
 * Problem: 202. Happy Number
 * Link: https://leetcode.com/problems/happy-number/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Math, Two Pointers, Hash Table, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Any number will be called a happy number if, after repeatedly replacing it with 
    a number equal to the sum of the square of all of its digits, leads us to the 
    number 1. All other (not-happy) numbers will never reach 1. Instead, they will 
    be stuck in a cycle of numbers that does not include 1.

    Given a positive number n, return true if it is a happy number otherwise return false.

    Example 1:
    Input: 23
    Output: true (23 is a happy number)
    Explanation: Here are the steps to find out that 23 is a happy number:
    2^2 + 3^2 = 4 + 9 = 13
    1^2 + 3^2 = 1 + 9 = 10
    1^2 + 0^2 = 1 + 0 = 1

    Example 2:
    Input: 2
    Output: false

    Constraints:
    - 1 <= n <= 2^31 - 1
*/

#include <iostream>

// ---------------------------------------------------------------------------

// Approach #1: Two Pointers (Fast and Slow) - Floyd's Cycle Detection

/*
    Intuition:
    The algorithm uses a two-pointer approach to detect cycles while continuously 
    applying the sum of squares process. If a cycle is detected, it implies that 
    the number is not a Happy Number, and if the process converges to 1, it 
    indicates that the number is indeed a Happy Number.

    Algorithm:
    1. Define a helper function, sum_of_squares(n), that takes a number n, and for 
       each digit in n, it squares the digit and sums these squared values.
    2. Initialize two pointers, slow and fast, both initially set to the given number n.
    3. Use a do-while loop to continuously apply the sum_of_squares function to both 
       slow and fast. The slow pointer advances one step at a time, while the fast 
       pointer advances two steps at a time.
    4. If the slow and fast pointers meet (indicating a cycle), exit the loop.
    5. Check if the slow pointer equals 1. If it does, return true.

    Complexity Analysis:
    - Time: O(log n) - The number of iterations required is logarithmic in the value of n.
    - Space: O(1) - Only constant amount of extra space for the slow and fast pointers.
*/

class Solution {
public:
    bool is_happy(int n) {
        int slow = n;
        int fast = n;
        
        do {
            slow = sum_of_squares(slow);
            fast = sum_of_squares(sum_of_squares(fast));
        } while (slow != fast);
        
        return slow == 1;
    }

private:
    int sum_of_squares(int n) {
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        return sum;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: Happy number
    bool result1 = sol.is_happy(23);
    std::cout << "Test 1 (n=23): " << (result1 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Happy number
    bool result2 = sol.is_happy(19);
    std::cout << "Test 2 (n=19): " << (result2 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Not a happy number
    bool result3 = sol.is_happy(2);
    std::cout << "Test 3 (n=2): " << (result3 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Happy number (1 itself)
    bool result4 = sol.is_happy(1);
    std::cout << "Test 4 (n=1): " << (result4 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 5: Not a happy number
    bool result5 = sol.is_happy(4);
    std::cout << "Test 5 (n=4): " << (result5 == false ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
