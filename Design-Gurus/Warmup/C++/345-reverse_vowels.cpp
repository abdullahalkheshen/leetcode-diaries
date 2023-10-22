/* https://leetcode.com/problems/reverse-vowels-of-a-string/description/
Problem Statement
Given a string s, reverse only all the vowels in the string and return it.
The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:
Input: s= "hello"
Output: "holle"

Example 2:
Input: s= "AEIOU"
Output: "UOIEA"

Example 3:
Input: s= "DesignGUrus"
Output: "DusUgnGires" */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1  Two Pointers
/* Intuition:
We can use the two-pointer technique to traverse the string from both ends simultaneously.
Whenever a vowel is encountered at both ends, we will swap them. The process will continue until the two pointers meet in the middle.

Algorithm:
1. We first create a static string "vowels" that contains all lowercase and uppercase vowels.
    This is used for checking whether a character in the input string is a vowel.
2. The reverseVowels method accepts a string 's' as an argument. The i and j pointers are initialized to the start and end of the string, respectively.
3. We enter a while loop that continues while 'i' is less than 'j'.
6. Keep iterating untill we find a vowel at both edges (i and j), once we've found a vowel at both the 'i' and 'j' pointers, we swap these vowels.
7. After the swap, we increment the 'i' pointer and decrement the 'j' pointer, and continue to the next iteration of the outer while loop.
8. After exiting the while loop, we convert the character array back to a string and return it as the result.

Big-O:
-Time complexity: O(n), It might be tempting to say that there are two nested loops and hence the complexity would be O(n2).
However, if we observe closely the pointers start and end will only traverse the index once.
Each element of the string "s" will be iterated only once either by the left or right pointer and not both.
-Space complexity: O(1) In C++ we only need an extra temporary variable to perform the swap and hence the space complexity is O(1).*/

#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    string reverseVowels(string s)
    {
        int i = 0, j = s.length() - 1;
        unordered_set<char> st = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};

        while (i < j)
        {
            if (!st.count(s[i])) // or st.count(s[i] == 0)
                i++;
            else if (!st.count(s[j])) // or st.count(s[i] == 0)
                j--;
            else swap(s[i++], s[j--]);
        }
        return s;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------
// A variation/substition to the unordered_set is using a isVowel function for checking if a char is a vowel as follow:

class Solution
{
public:
    string reverseVowels(string s)
    {
        int i = 0, j = s.length() - 1;

        bool isVowel(char c)
        {
            return c == 'a' || c == 'i' || c == 'e' || c == 'o' || c == 'u' || c == 'A' || c == 'I' || c == 'E' || c == 'O' || c == 'U';
        }

        while (i < j)
        {
            if (!isVowel(s[i]))
                i++;
            else if (!isVowel(s[j]))
                j--;
            else
            {
                swap(s[i++], s[j--]);
            }
        }

        return s;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------