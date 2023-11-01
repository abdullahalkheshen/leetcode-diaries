/*
    Leetcode name: 844. Backspace String Compare
    Problem Challenge 2: Comparing Strings containing Backspaces (medium)

    Problem Statement
    Given two strings containing backspaces (identified by the character ‘#’), check if the two strings are equal.

    Example 1:
    Input: str1="xy#z", str2="xzz#"
    Output: true
    Explanation: After applying backspaces the strings become "xz" and "xz" respectively.

    Example 2:
    Input: str1="xy#z", str2="xyz#"
    Output: false
    Explanation: After applying backspaces the strings become "xz" and "xy" respectively.

    Example 3:
    Input: str1="xp#", str2="xyz##"
    Output: true
    Explanation: After applying backspaces the strings become "x" and "x" respectively.
    In "xyz##", the first '#' removes the character 'z' and the second '#' removes the character 'y'.

    Example 4:
    Input: str1="xywrrmp", str2="xywrrmu#p"
    Output: true
    Explanation: After applying backspaces the strings become "xywrrmp" and "xywrrmp" respectively.

*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------
// Approach #1: Build New String [Accepted]

/* 
    Intuition:
        Let's individually return the result -new string without spaces/hashtags- of each string, then compare if they are equal.
        To return the result of a string s, we'll use a stack based, simulating the result of each keystroke.
        Since we have to Data structures, here strings, we'll code two functions one "compare" function to comapre the new two resultant strings,
        and another function get_valid_charachter to return the new strings to be comapred.

    Algorithm:

    Complexity Analysis
        • Time Complexity: O(M + N).
        • Space Complexity: O(M + N).
        
        -> where M, N are the lengths of s and T respectively.
*/

using namespace std;
#include <iostream>
#include <string>

class Solution
{
public:
    bool backspaceCompare(string S, string T)
    {
        return build(S) == build(T);
    }

    string build(string S)
    {
        stack<char> ans;
        for (char c : S)
        {
            if (c != '#') ans.push(c);
            else if (!ans.empty()) ans.pop();
        }

        string result;
        while (!ans.empty())
        {
            result += ans.top();
            ans.pop();
        }

        reverse(result.begin(), result.end());
        return result;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2: Two Pointers

/*
    Intuition:
        To compare the given strings, first, we need to apply the backspaces. An efficient way to do this would be from the end of both the strings. We can have separate pointers, pointing to the last element of the given strings. We can start comparing the characters pointed out by both the pointers to see if the strings are equal. If, at any stage, the character pointed out by any of the pointers is a backspace (’#’), we will skip and apply the backspace until we have a valid character available for comparison.

    Algorithm:
        1. In the compare function, two pointers are initialized, pointer1 and pointer2, to the last index of str1 and str2, respectively.
        2. A while loop is started which continues until both pointers are less than zero, that is, both have traversed their strings completely in a reverse manner.
        3. Inside this loop, for each string, the get_next_valid_index function is called with the current pointer. This function returns the index of the next valid character in the string (traversing from back to front) by taking into account the backspace characters. i1 and i2 point to the index of the next valid character in the two strings.
        4. If both i1 and i2 are less than zero, it means the end of both strings has been reached, and the strings are considered equal.
        5. If only one of i1 or i2 is less than zero, it means the end of one string has been reached, but not the other, and the strings are not equal.
        6. If the characters at indices i1 and i2 are not the same, the strings are not equal.
        7. If none of the above conditions are met, the loop continues to the next valid characters in both strings.
        8. The get_next_valid_index function accepts a string and an index, and uses a backspace count to keep track of how many backspaces have been encountered. It then loops through the string backwards from the provided index until it encounters a valid character or reaches the beginning of the string.
        9. If a backspace character is found, the backspace count is incremented. If a non-backspace character is found and there are any counted backspaces, one backspace is subtracted from the count (to simulate the removal of the previous character), and the loop continues. If a non-backspace character is found and there are no backspaces left to account for, the loop breaks and the index of the valid character is returned.

    Complexity Analysis:
        Time Complexity: O(m+n)
            -> The time complexity of the above algorithm will be  where ‘M’ and ‘N’ are the lengths of the two input strings respectively.

        Space Complexity: O(1)
            -> The algorithm runs in constant space .
*/

class BackspaceCompare
{
public:
    static bool compare(const string &str1, const string &str2)
    {
        // use two pointer approach to compare the strings
        int pointer1 = str1.size() - 1, pointer2 = str2.size() - 1;
        while (pointer1 >= 0 || pointer2 >= 0)
        {
            int i1 = get_next_valid_index(str1, pointer1);
            int i2 = get_next_valid_index(str2, pointer2);

            if (i1 < 0 && i2 < 0) return true;
            if (i1 < 0 || i2 < 0) return false;
            if (str1[i1] != str2[i2]) return false;

            pointer1 = i1--;
            pointer2 = i2--;
        }

        return true;
    }

private:
    static int get_next_valid_index(const string &str, int index)
    {
        int backspace_count = 0;
        while (index >= 0)
        {
            if (str[index] == '#') backspace_count++;
            else if (backspace_count > 0) backspace_count--;
            else break;

            index--; // skip a backspace or a valid character
        }
        return index;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------------

