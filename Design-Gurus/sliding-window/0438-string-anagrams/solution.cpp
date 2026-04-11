/* 
    Leetcode name: 438. Find All Anagrams in a String
    Problem Challenge 2: String Anagrams (hard)

    Problem Statement
    Given a string and a pattern, find all anagrams of the pattern in the given string.

    Every anagram is a permutation of a string.
    As we know, when we are not allowed to repeat characters while finding permutations of a string, we get N! permutations (or anagrams) of a string having N characters. 
    For example, here are the six anagrams of the string “abc”:
    abc
    acb
    bac
    bca
    cab
    cba

    Write a function to return a list of starting indices of the anagrams of the pattern in the given string.

    Example 1:
    Input: String="ppqp", Pattern="pq"  
    Output: [1, 2]  
    Explanation: The two anagrams of the pattern in the given string are "pq" and "qp".

    Example 2:
    Input: String="abbcabc", Pattern="abc"  
    Output: [2, 3, 4]  
    Explanation: The three anagrams of the pattern in the given string are "bca", "cab", and "abc".
*/

using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution 
{
    public:
    vector<int> findAnagrams(string s, string p) 
    {
        int matched = 0;
        int window_start = 0;
        
        unordered_map<char, int> map;
        for(auto chr : p) map[chr]++;

        vector<int> v;

        for(int window_end = 0; window_end < s.size(); window_end++)
        {
            if(map.find(s[window_end]) != map.end())
            {
                map[s[window_end]]--;
                if(map[s[window_end]] == 0) matched++;
            }

            if(matched == (int)map.size()) v.push_back(window_start);

            if(window_end >= p.length()-1)
            {
                if(map.find(s[window_start]) != map.end())
                {
                    if(map[s[window_start]] == 0) matched--;
                    map[s[window_start]]++;
                }
                window_start++;
            }
        }
        return v;
    }
};