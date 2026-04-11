/* Valid Anagram (easy)
Problem Statement
Given two strings s and t, return true if t is an anagram of s, and false otherwise.
An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

Example 1:
Input: s = "listen", t = "silent"
Output: true

Example 2:
Input: s = "rat", t = "car"
Output: false

Example 3:
Input: s = "hello", t = "world"
Output: false */

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Sorting

/*
Intuition:
An anagram is produced by rearranging the letters of sss into ttt. Therefore, if ttt is an anagram of sss, sorting both strings will result in two identical strings. Furthermore, if sss and ttt have different lengths, ttt must not be an anagram of sss and we can return early.

Algorithm:
1. if the size of both strings aren't equal directly return false.
2. Sort both strings.
3. return the boolean of the comparison.

Big-O:
Time complexity: O(nlogn).
    -> Assume that "n" is the length of "s", sorting costs O(nlogn) and comparing two strings costs O(n).
    -> Sorting time dominates and the overall time complexity is O(nlog⁡n)O(n \log n)O(nlogn).

Space complexity: O(1).
    -> Space depends on the sorting implementation which, usually, costs O(1) auxiliary space if heapsort is used.
    -> Note that in Java, toCharArray() makes a copy of the string so it costs O(n) extra space, but we ignore this for complexity analysis because:
        It is a language dependent detail (depends on how the sort function is designed).
  */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.size() != t.size())
            return false;
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Frequency counter (Vector or Hashmap)
// Approach #2.1 Frequency counter (Vector)

/*
Intuition:
To solve the anagram problem, we can count the frequency of each letter in both strings and compare them. If the frequencies of all letters are the same in both strings, then the two strings are anagrams of each other.

Algorithm:
1. Create an integer array freq of length 26 to track the frequency of each letter in the two strings.
2. Loop through each character in both strings and increment the frequency of the corresponding letter in s and decrement the frequency of the corresponding letter in t.
3. Finally, we loop through the freq array and check if all requencies are zero.
    3.1. If not, we return false.
    3.2. If all frequencies are zero, we return true because both strings are anagrams of each other.

Big-O:
Time complexity: O(n).
    -> where n is the length of the strings.
    -> We need to loop through each character in both strings once to count the frequency of each letter,
        and then loop through the freq array once to check if all frequencies are zero.

Space complexity: O(1).
    -> Size of freq array is const and fixed = 26.
    -> Space required to store the freq array does not depend on the length of the strings.
*/

#include <vector>
class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
        {
            return false;
        }

        vector<int> freq(26, 0);
        for (int i = 0; i < s.length(); i++)
        {
            freq[s[i] - 'a']++;
            freq[t[i] - 'a']--;
        }

        for (int i = 0; i < freq.size(); i++)
        {
            if (freq[i] != 0)
            {
                return false;
            }
        }

        return true;
    }
};

// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2.1 Frequency counter (Map)

#include <unordered_map>

class Solution
{
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.size() != t.size())
            return false;

        unordered_map<char, int> counter;
        for (int i = 0; i < s.length(); i++)
        {
            counter[s[i]]++;
            counter[t[i]]--;
        }

        for (auto count : counter)
        {
            if (count.second != 0)
                return false;
        }
        return true;
    }
};