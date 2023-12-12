/* 
    Leetcode: 76. Minimum Window Substring
    Problem Challenge 3: Smallest Window containing Substring (hard)

    Problem Statement:
    Given a string and a pattern, find the smallest substring in the given string which has all the characters of the given pattern.

    Example 1:
    Input: String="aabdec", Pattern="abc"
    Output: "abdec"
    Explanation: The smallest substring having all characters of the pattern is "abdec"

    Example 2:
    Input: String="aabdec", Pattern="abac"  
    Output: "aabdec"  
    Explanation: The smallest substring having all characters occurrences of the pattern is "aabdec"
    
    Example 3:
    Input: String="abdbca", Pattern="abc"  
    Output: "bca"  
    Explanation: The smallest substring having all characters of the pattern is "bca".
    
    Example 4:
    Input: String="adcad", Pattern="abc"  
    Output: ""  
    Explanation: No substring in the given string has all characters of the pattern
*/

using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>

class Solution 
{
    public:
    string findSubstring(string s, string p) 
    {
        int matched = 0;
        int window_start = 0;
        int minimum_window = s.size()+1; // Maximum possible value for minimum window
        int min_window_start = 0;
        
        unordered_map<char, int> map;
        for(auto chr : p) map[chr]++;

        for(int window_end = 0; window_end < s.size(); window_end++)
        {
            if(map.find(s[window_end]) != map.end())
            {
                map[s[window_end]]--;
                // If it is, matched is incremented. 
                // This means that this character is one of the characters we are looking for, because its original count in the map was positive.
                if(map[s[window_end]] >= 0) matched++;
            }

            while(matched == (int)p.size())
            {   
                // If it is, that means the current window is smaller than the smallest window found so far.
                if(minimum_window > window_end - window_start + 1)
                {
                    min_window_start = window_start;
                    minimum_window = window_end - window_start + 1;
                }

                if(map.find(s[window_start]) != map.end())
                {
                    if(map[s[window_start]] == 0) matched--;
                    map[s[window_start]]++;
                }
                window_start++;
            }
        }
        return (minimum_window > s.size()) ? "" : s.substr(min_window_start, minimum_window);
    }
};