/* 
    Leetcode name: 567. Permutation in String
    Problem Challenge 1: Permutation in a String (hard)

    Problem Statement
    Given a string and a pattern, find out if the string contains any permutation of the pattern.
    Permutation is defined as the re-arranging of the characters of the string. For example, “abc” has the following six permutations:
    abc
    acb
    bac
    bca
    cab
    cba
    If a string has ‘n’ distinct characters, it will have n! permutations.

    Example 1:
    Input: String="oidbcaf", Pattern="ABC"   
    Output: true   
    Explanation: The string contains "bca" which is a permutation of the given pattern.
    
    Example 2:
    Input: String="odicf", Pattern="dc"   
    Output: false  
    Explanation: No permutation of the pattern is present in the given string as a substring.
    
    Example 3:
    Input: String="bcdxabcdy", Pattern="bcdyabcdx"  
    Output: true  
    Explanation: Both the string and the pattern are a permutation of each other.
    
    Example 4:
    Input: String="aaacb", Pattern="abc"  
    Output: true  
    Explanation: The string contains "acb" which is a permutation of the given pattern.
*/

// ------------------------------------------------ Solution 1: Brute Force ------------------------------------------------

/* 
    Intuition:
    Algorithm:
    Complexity Analysis:
*/

using namespace std;
#include <iostream>
#include <string>

class Solution {
    bool flag = false;

    string swap(string s, int i0, int i1) 
    {
        if (i0 == i1) return s;
            
        string s1 = s.substr(0, i0);
        string s2 = s.substr(i0 + 1, i1 - i0 - 1);
        string s3 = s.substr(i1 + 1);

        return s1 + s[i1] + s2 + s[i0] + s3;
    }

    void permute(string s1, string s2, int l) 
    {
        if (l == s1.length()) 
        {
            if (s2.find(s1) != string::npos) flag = true;
                
        }
        else 
        {
            for (int i = l; i < s1.length(); i++) 
            {
                s1 = swap(s1, l, i);
                permute(s1, s2, l + 1);
                s1 = swap(s1, l, i);
            }
        }
    }

public:
    bool checkInclusion(string s1, string s2) 
    {
        permute(s1, s2, 0);
        return flag;
    }
};
