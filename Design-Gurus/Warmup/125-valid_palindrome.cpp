/* A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string s, return true if it is a palindrome, or false otherwise.

Example 1:
Input: sentence = "A man, a plan, a canal, Panama!"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Example 2:
Input: sentence = "Was it a car or a cat I saw?"
Output: true
Explanation: Explanation: "wasitacaroracatisaw" is a palindrome. */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

//  Approach #1 Reverse then Compare
/*
Intuition:
A palindrome is a sequence that reads the same backwards as forwards. A palindrome, and its reverse, are identical to each other.

Algorithm:
1. Create (declare & initialize) filtered and reversed strings.
2. Fill alphanumeric chars in the filtered string
3. Reverse filtered string
4. Compare reversed (filtered) string with original string


Big-O:
Time complexity: O(n), in length n of the string.
    -> Each iteration runs linear in time (since each character operation completes in constant time). Thus, the effective run-time complexity is linear.

Space complexity: O(n), in length n of the string.
    -> O(n) as additional space to stored the filtered string and the reversed string.
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        string filtered_string, reversed_string;

        for (auto ch : s)
        {
            if (isalnum(ch))
                filtered_string += tolower(ch);
        }

        reversed_string.resize(filtered_string.size());
        reverse_copy(filtered_string.begin(), filtered_string.end(),
                     reversed_string.begin());

        return filtered_string == reversed_string;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

//  Approach #2 Two pointers
/*
Intuition: Our algorithm can leverage the two-pointer technique where one pointer starts at the beginning of the string, and the other one starts at the end. The two pointers move towards each other, checking if the characters they point to are the same.

Algorithm:
1. The isPalindrome function starts by setting two pointers: 'i' at the start of the string and 'j' at the end.
2. Then it enters a while loop which continues until the two pointers cross each other.
3. Keep iterating until we encounter "un"equal chars at both pointers, return false
4. Whatever else return true. (No different chars exist at both pointers).

Complexity Analysis || Big-O:
Time complexity : O(n), "n" is length of the string. We traverse over each character at-most once, until the two pointers meet in the middle, or when we break and return early.
Space complexity : O(1), No extra space required, at all. */

class Solution
{
public:
    bool checkIfPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;
    
    while (left < right) {
        if (s[left++] != s[right++]) return false;        
    }
    return true;
}

}
