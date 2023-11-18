/* 
    Leetcode name: 424. Longest Repeating Character Replacement
    Longest Substring with Same Letters after Replacement

    Problem Statement
    Given a string with lowercase letters only, if you are allowed to replace no more than ‘k’ letters with any letter, find the length of the longest substring having the same letters after replacement.

    Example 1:
    Input: String="aabccbb", k=2  
    Output: 5  
    Explanation: Replace the two 'c' with 'b' to have a longest repeating substring "bbbbb".

    Example 2:
    Input: String="abbcb", k=1  
    Output: 4  
    Explanation: Replace the 'c' with 'b' to have a longest repeating substring "bbbb".

    Example 3:
    Input: String="abccde", k=1  
    Output: 3  
    Explanation: Replace the 'b' or 'd' with 'c' to have the longest repeating substring "ccc".
*/


// -------------------------------------------------- Fixed Sliding window + Binary Search --------------------------------------------------
/* 
    Intuition:
        The question asks us to find the longest substring length that satisfies the given conditions, we can window_start with generating all possible substrings.
        Now, given a substring, we want figure out if it can be converted into a string with the same letters.
        Because we are allowed only k operations to do so, we would want to minimize the number of operations.
        We can divide all the characters of the string "str" into two groups - fixed letters and the letters that will be changed. Fixed letters remain unchanged.
        To keep the number of substitutions minimum, the number of fixed letters must be maximum. So, we find the character target, which occurs with the maximum frequency in the string.
        All other characters can now be replaced with target. If the count of other characters is less than or equal to k, then this substring fulfills the condition given in the question. 
        
        We can try it over every substring and filter out all the valid substrings. The length of the longest valid substring would be our answer. 
        However, this is a time-consuming process, for it involves nested for loops which take O(n2) time only for generating substring ranges and the additional verhead of calculating the maximum frequency element.
        While this might not be a good solution, we learn an important idea here:
        We observe that if a valid substring of length i exists, then we can indeed say that a valid substring of length i - 1 would also exist.
        
        Let's understand this with an example.
        s = "ABCCDC", k - 1
        Let's revisit the condition of validity - a substring is valid if, after at most k character replacements, all the letters in the substring become the same.
        In this case, "CCDC" is the longest substring that satisfies the given condition. 
        We can take any substring of "CCDC" and it would still be valid. 
        That's because any substring of a valid string can never contain more than k instances of other characters (any character other than c in this example). 

        Using induction, we can say that if there exists a valid string of length "i", then all of its substrings of lengths i — 1, i — 2, i — 2 and I would also be valid.
        We can observe that it's making a monotonic function over the length of a valid substring. We want to find the longest valid substring. 
        
        Binary Search:
        Because of the presence of monotonic values, we should be able to use binary search over the length of substrings.
        We try to find out if a valid substring with a certain length exists or not.
        How to check whether a valid substring of a given length exists or not?

        A valid substring of a given length could exist anywhere in the string. Think of a window of the given size which slides over the string from left to right.
        
        If a valid substring of the given length does exist, one of the sliding window positions will provide it to us.
        As discussed earlier, we would need the element that appears the maximum number of times. A frequency map can be helpful here.
        A frequency map stores a list of characters with the frequency they appear in a particular window.
        
        Starting from the left edge of the string, we build a frequency map of the window. 
        As we move the window of fixed length toward the right, the frequency of the new character added to the window increases, and the frequency of the departing character decreases.
        As we move the sliding window from left to right, we also keep track of the maximum frequency we have seen so far of any character in the sliding window. 
        
        When we subtract the frequency from the size of the window, we get the count of all other characters which would be replaced. 
        For a valid substring, the number of other characters should be less than or equal to k.

        While working on binary search related problems, our first step is usually finding the search range.
        Let's focus on the same.
        Because a single character would always make a valid substring, we can confidently say that the minimum length of a valid substring is l; let's call it min.
        The complete string could also be a valid string, so the maximum length can be the length of the given string; let's call it max. 
        Our answer will lie in the range of [min,max] (inclusive).
        
        In this implementation of binary search, we use two variables, "low" and "high":
            1. "low" always points to the length of a valid string. At the beginning of the program, the length of a known valid string is min which is equal to 1. So we initialize to to 1.
                "low" is the minimum length of a valid substring (satisfies the condition), it's initialized to 1 because the substring can't be empty.
                we add 1 to s.length() because we want to include the case where the whole string is a valid substring
        
            2. "high" is the maximum length of the substring (satisfies the condition), it's initialized to s.length() + 1 because the substring can't be longer than the string itself.

        The range of "low" is the same as the search space defined above [min, max] (both inclusive).
        Here our task is to find the largest of "low", which stands for the longest valid substring.
        "high" stays just above the search space and always points to an invalid length. In this case, we initialize "high" to max+1. 
        As we proceed, "low" and "high" converge toward the answer.
        In the end, "low" contains the answer, and "high" points to one higher number than "low".

    Algorithm:
        1. Initialize "low" to 1 (min) and "high" to 1 more than the length of string (max + 1).
        2. Do the following until "low" and "high" are right next to each other.
            • Find the middle value mid of "low" and "high". Check if a valid string of length mid is possible or not. 
            For this we use another function, isValidSubstring, which uses a sliding window of length mid.
            • If we find a valid substring, we move the binary search to the right half of the range. So "low" becomes mid.
            • If we don't find a valid substring of length mid, then a valid string must exist on the left half of the range. "high" becomes mid.
        3. In the end, "low" contains the maximum length of the string that satisfies our condition. We return "low".
        
        Function to check if a valid substring of the given length windowLength exists or not. We call it canMakeVaIidSubstring.
        1. Create a frequency map to track the maximum frequency of a character in the sliding window.
        2. Initialize start to 0.
        3. Create an end pointer that iterates over each character of the given string s.
            • As it moves toward the right, add the character pointed by end to the frequency map. 
            If the size of the window exceeds windowLength, then it is time to move start one step further. Before start moves, decrease the
            frequency of the character pointed by it.
            • Store the maximum frequency seen so far of any character in a variable marFrequency.
            • If maxFrequency fulfills the condition for a valid substring, return true.
        4. If we cannot find a valid substring by the end of the loop, there is no valid range substring possible of the length windowLength. so we return false.
    
    Complexity Analysis
        If there are n characters in the given string.
        • Time complexity: O(n * logn).
            Binary search divides the search space in half in each iteration until one element is left.
            So from n elements to reach I element it takes O(logn) iterations. 
            We go through the full length of the string using a sliding window in every iteration. So it takes O(n) additional time per iteration. 
            So the final time complexity is O(log n) * O(n) = O (n log n) .
        • Space complexity: O(m) 
            where m is the number of distinct characters in the string. 
            The core logic of binary search doesn't involve any auxiliary data structure but checking for valid string involves creating a hash map.
            The number of keys could be as many as the number of distinct characters. For uppercase English alphabets, m = 26.
*/

using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
    public:
        bool isValidSubstring(const string& s, int substringLength, int k) {
            vector<int> counter(26, 0);
            int max_frequency = 0;
            int window_start = 0;
            
            for (int window_end = 0; window_end < s.length(); window_end++) 
            {
                counter[s[window_end]] += 1;
                if (window_end + 1 - window_start > substringLength) 
                {
                    counter[s[window_start++]]--;
                }
                max_frequency = max(max_frequency, counter[s[window_end]]);
                
                if (substringLength - max_frequency <= k) return true;
            }
            return false;
        }

        int characterReplacement(string s, int k) {
            int low = 1;
            int high = s.length() + 1;

            while (low + 1 < high) 
            {
                int mid = low + (high - low) / 2;
                if (isValidSubstring(s, mid, k)) low = mid;
                else high = mid;
            }
            
            return low;
        }
};

// -------------------------------------------------- Dynamic Sliding Window (Slow) --------------------------------------------------


