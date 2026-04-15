/**
 * Problem: 844. Backspace String Compare
 * Link: https://leetcode.com/problems/backspace-string-compare/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: String, Two Pointers, Stack, Simulation
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given two strings containing backspaces (identified by the character '#'),
    check if the two strings are equal.

    Example 1:
    Input: str1="xy#z", str2="xzz#"
    Output: true
    Explanation: After applying backspaces the strings become "xz" and "xz".

    Example 2:
    Input: str1="xy#z", str2="xyz#"
    Output: false
    Explanation: After applying backspaces the strings become "xz" and "xy".

    Example 3:
    Input: str1="xp#", str2="xyz##"
    Output: true
    Explanation: After applying backspaces the strings become "x" and "x".

    Example 4:
    Input: str1="xywrrmp", str2="xywrrmu#p"
    Output: true
    Explanation: After applying backspaces the strings become "xywrrmp" and "xywrrmp".

    Constraints:
    - 1 <= s.length, t.length <= 200
    - s and t only contain lowercase letters and '#' characters
*/

#include <iostream>
#include <string>
#include <stack>

// ---------------------------------------------------------------------------

// Approach #1: Stack + Build New String

/*
    Intuition:
    Let's individually build the result of each string by simulating the
    keystrokes using a stack, then compare if they are equal.

    Algorithm:
    1. For each string, use a stack to simulate typing.
    2. If character is not '#', push it to stack.
    3. If character is '#' and stack is not empty, pop from stack.
    4. Build the resulting string from the stack.
    5. Compare both resulting strings.

    Complexity Analysis:
    - Time: O(m + n), where m, n are the lengths of str1 and str2
    - Space: O(m + n), for the stacks
*/

class SolutionStack {
public:
    bool backspace_compare(std::string str1, std::string str2) {
        return build(str1) == build(str2);
    }

private:
    std::string build(const std::string& str) {
        std::stack<char> stk;

        for (char c : str) {
            if (c != '#') {
                stk.push(c);
            } else if (!stk.empty()) {
                stk.pop();
            }
        }

        std::string result;
        while (!stk.empty()) {
            result = stk.top() + result;
            stk.pop();
        }
        return result;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Optimal)

/*
    Intuition:
    To compare the given strings, we can process them from the end. We use
    separate pointers pointing to the last element of each string. We skip
    characters that would be deleted by backspaces and compare valid characters.

    Algorithm:
    1. Initialize two pointers at the end of each string.
    2. For each string, find the next valid character by skipping backspaces.
    3. Compare the valid characters from both strings.
    4. If they don't match, return false.
    5. If we reach the end of both strings, return true.

    Complexity Analysis:
    - Time: O(m + n), where m and n are the lengths of the two strings
    - Space: O(1), constant space
*/

class Solution {
public:
    bool backspace_compare(const std::string& str1, const std::string& str2) {
        int ptr1 = str1.size() - 1;
        int ptr2 = str2.size() - 1;

        while (ptr1 >= 0 || ptr2 >= 0) {
            int j1 = get_next_valid_char_index(str1, ptr1);
            int j2 = get_next_valid_char_index(str2, ptr2);

            if (j1 < 0 && j2 < 0) return true;
            if (j1 < 0 || j2 < 0) return false;
            if (str1[j1] != str2[j2]) return false;

            ptr1 = j1 - 1;
            ptr2 = j2 - 1;
        }

        return true;
    }

private:
    int get_next_valid_char_index(const std::string& str, int index) {
        int backspace_count = 0;

        while (index >= 0) {
            if (str[index] == '#') {
                backspace_count++;
            } else if (backspace_count > 0) {
                backspace_count--;
            } else {
                break;
            }
            index--;
        }

        return index;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1
    bool result1 = sol.backspace_compare("xy#z", "xzz#");
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;

    // Test 2
    bool result2 = sol.backspace_compare("xy#z", "xyz#");
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;

    // Test 3
    bool result3 = sol.backspace_compare("xp#", "xyz##");
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;

    // Test 4
    bool result4 = sol.backspace_compare("xywrrmp", "xywrrmu#p");
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;

    // Test 5: Empty after backspaces
    bool result5 = sol.backspace_compare("ab##", "c#d#");
    std::cout << "Test 5: " << (result5 == true ? "PASS" : "FAIL") << std::endl;

    return 0;
}
