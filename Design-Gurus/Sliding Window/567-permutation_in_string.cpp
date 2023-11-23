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
        Note: this approach is included because it is a logical first step towards building an efficient solution. However, it is a brute-force approach and is not expected to pass all test cases. Readers are still recommended to read it because it helps to understand the next following approaches.
        The simplest method is to generate all the permutations of the short string and to check if the generated permutation is a substring of the longer string.

        In order to generate all the possible pairings, we make use of a function permute(string_1, string_2, current_index). This function creates all the possible permutations of the short string s1s1s1.

        To do so, permute takes the index of the current element current_indexcurrent\_indexcurrent_index as one of the arguments. Then, it swaps the current element with every other element in the array, lying towards its right, so as to generate a new ordering of the array elements. After the swapping has been done, it makes another call to permute but this time with the index of the next element in the array. While returning back, we reverse the swapping done in the current function call.

        Thus, when we reach the end of the array, a new ordering of the array's elements is generated. The following animation depicts the process of generating the permutations.


    Algorithm:
        Three functions are used in this approach:
        1. swap(string, index_1, index_2) - This function swaps the elements of the string at index_1 and index_2.
        2. permute(string_1, string_2, current_index) - This function generates all the permutations of string_1 and checks if any of the permutations is a substring of string_2.
        3. checkInclusion(string_1, string_2) - This function is the main function which checks if any of the permutations of string_1 is a substring of string_2.

    Complexity Analysis:
        Let n be the length of sl
        • Time complexity: O(n!).
        • Space complexity: O(n2). The depth of the recursion tree is refers to the length of
        the short string sl). Every node of the recursion tree contains a string of max. length n.
*/

using namespace std;
#include <iostream>
#include <string>

class Solution 
{
public:
    bool checkInclusion(string s1, string s2) 
    {
        permute(s1, s2, 0);
        return flag;
    }

    bool flag = false;

    string swap(string s, int i0, int i1) 
    {
        if (i0 == i1) return s;
            
        string s1 = s.substr(0, i0);
        string s2 = s.substr(i0 + 1, i1 - i0 - 1);
        string s3 = s.substr(i1 + 1);

        return s1 + s[i1] + s2 + s[i0] + s3;
    }

    void permute(string s1, string s2, int current_index) 
    {
        if (current_index == s1.length()) 
        {
            if (s2.find(s1) != string::npos) flag = true;
        }
        else 
        {
            for (int i = current_index; i < s1.length(); i++) 
            {
                s1 = swap(s1, current_index, i);
                permute(s1, s2, current_index+1);
                s1 = swap(s1, current_index, i);
            }
        }
    }
};


// ------------------------------------------------ Solution 2: Using sorting ------------------------------------------------
/* 
    Intuition:
        If we sort both the strings, the permutations of the short string will be a substring of the long string. 
        This is because when we sort the strings, the relative order of the characters within the string doesn't change. 
        Thus, the relative order of the characters of the short string will be preserved as a substring in the long string.

    Algorithm:
        1. Sort the short string s1s1s1.
        2. For every substring of the long string s2s2s2 having length equal to the length of s1s1s1, sort this substring as well.
        3. If the two sorted strings obtained in the above steps are equal, then s1s1s1 and its permutation are present as a substring in s2s2s2.
    
    Complexity Analysis:
        Let n be the length of sl
        • Time complexity: O(nlogn). We traverse over the string s2s2s2 of length n once. Apart from this, we sort the short string s1s1s1 of length l and every substring of s2s2s2 having length l.
            Sorting a string of length l costs O(llogl) time. Thus, the overall time complexity is O(nlogn + l(l + logl)).
        • Space complexity: O(l). Sorting a string of length l costs O(l) space.
*/

#include <algorithm>
class Solution {
public:
    bool checkInclusion(std::string s1, std::string s2) {
        s1 = sort_string(s1);
        for (int i = 0; i <= static_cast<int>(s2.length()) - static_cast<int>(s1.length()); ++i) 
        {
            if (s1 == sort_string(s2.substr(i, s1.length()))) return true;
        }
        return false;
    }

private:
    std::string sort_string(std::string str) 
    {
        std::sort(str.begin(), str.end());
        return str;
    }
};