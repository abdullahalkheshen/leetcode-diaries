/* 
    This's the hardest problem I've passen through so far.
    
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

// ----------------------------- Sliding Window  -------------------------------- //

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
        int minimum_window_size = s.size()+1; // Maximum possible value for minimum window
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
                if(minimum_window_size > window_end - window_start + 1)
                {
                    min_window_start = window_start;
                    minimum_window_size = window_end - window_start + 1;
                }

                if(map.find(s[window_start]) != map.end())
                {
                    if(map[s[window_start]] == 0) matched--;
                    map[s[window_start]]++;
                }
                
                window_start++;
            }
        }
        return (minimum_window_size > s.size()) ? "" : s.substr(min_window_start, minimum_window_size);
    }
};


// ----------------------------- Sliding Window 1 -------------------------------- //

class Solution {
public:
    std::string minWindow(std::string s, std::string t) 
    {
        if (s.length() == 0 || t.length() == 0) 
        {
            return "";
        }

        std::unordered_map<char, int> dictT;
        for (char c : t) 
        {
            dictT[c]++;
        }

        int required = dictT.size();
        int l = 0, r = 0;
        int formed = 0;
        int ans[3] = { -1, 0, 0 };
        std::unordered_map<char, int> windowCounts;

        while (r < s.length()) 
        {
            char c = s[r];
            windowCounts[c]++;

            if (dictT.find(c) != dictT.end() && windowCounts[c] == dictT[c]) 
            {
                formed++;
            }

            while (l <= r && formed == required) 
            {
                c = s[l];
                if (ans[0] == -1 || r - l + 1 < ans[0]) 
                {
                    ans[0] = r - l + 1;
                    ans[1] = l;
                    ans[2] = r;
                }

                windowCounts[c]--;

                if (dictT.find(c) != dictT.end() && windowCounts[c] < dictT[c]) 
                {
                    formed--;
                }

                l++;
            }

            r++;
        }

        return ans[0] == -1 ? "" : s.substr(ans[1], ans[2] - ans[1] + 1);
    }
};

// ----------------------------- Sliding Window 2 -------------------------------- //
