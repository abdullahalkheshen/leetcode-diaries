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
#include <vector>

class Solution {
    public:
        int characterReplacement(string s, int k) 
        {
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

        bool isValidSubstring(const string& s, int substringLength, int k) 
        {
            vector<int> counter(26, 0);
            int max_frequency = 0;
            int window_start = 0;
            
            for (int window_end = 0; window_end < s.length(); window_end++) 
            {
                counter[s[window_end] - 'a'] += 1;
                if (window_end + 1 - window_start > substringLength) 
                {
                    counter[s[window_start++] - 'a']--;
                }
                max_frequency = max(max_frequency, counter[s[window_end] - 'a']);
                
                if (substringLength - max_frequency <= k) return true;
            }
            return false;
        }
};

// -------------------------------------------------- Dynamic Sliding Window (Slow) --------------------------------------------------

/* 
    Intuition:
        In the previous approach, our implementation of binary search makes use of a sliding window to check the validity condition. 
        We explore the idea of sliding window from another angle in the current approach.
        What if the question was about a specific character? Let's understand this with an example: s = "AABEAFACAAEAA" k = 1
        Here, we are allowed to do a 1 operation. i.e., 1 replacement of a character with any other character. 
        After the operation, we need to return the longest substring where all the letters are "A".
        We are going to use a sliding window here as well, but this time the window's size (the number of characters in the window) isn't fixed.
        Create two pointers that point to the start and end of the window. We also use a variable count to record the number of As in the current window. 
        We call a window valid only if the difference between the size of the window and count is <= to k. (end—start+1)— count <= k
        The window expands when the pointer end moves forward, and it shrinks when start moves ahead.
        The variable count increases when the window grows, and the new character entering the window is "A" or "a" for some problem given/inputs.
        On the opposite side,  we decrease count when the window shrinks and the outgoing character is A.
        In the beginning, start and end points to -1. Thereby creating a sliding window of size 0 (end-start+1 = —1+0+1 = 0). which's valid window as per the condition.
        While the window is valid, we expand the window by moving the end pointer forward. As we do so, we also note the maximum length of the window seen so far, max_size. 
        When the window becomes invalid, we shrink the size by moving the start pointer forward. start pointer moves until the window becomes valid again. 
        The process continues until the window reaches the right edge of the string and can't move any further.
        In the end, max_size contains our answer.
    
    Algorithm:
        1. Loop over the string to collect all the unique characters. Store them in a set allLetters .
        2. Initialize max_size to 0. This variable would contain the final answer.
        3. For each letter letter present in allLetters, do the following.
            a. Declare three variables, start, end, and count, and initialize them to O.
            b. Iterate end from index 0 to the end of the given string.
                a. If end points at the same letter as the character stored in letter, then increase count by 1.
                b. If end points to a different letter
                    • Check if the current window is valid, if it is valid, then move end to the next index.
                    • Ifthe window is not valid, we move start in steps of 1 until the window becomes valid again. 
                        Before every step, if start is pointing at a character same as letter, then decrease count by 1.
            c. Compare max_size with the current length of the window. If the current length is bigger, then update mar Length.
        4. Return max_size back to the caller.
    
    Complexity Analysis:
        Let n be the number of characters in the string and m be the number of unique characters.
        • Time complexity: O(nm). 
            We iterate over each unique character once, which requires O(k) time. 
            We move a sliding window for each unique character from left to right of the string. As the window moves, each character of the string is visited at most two times. 
            Once when it enters the window and again when it leaves the window. This adds O(n) time complexity for each iteration. So the final time complexity is O(nm). For all uppercase English letters, the maximum value of rn would be 26.
        
        • Space complexity: O(m). 
            We use an auxiliary set to store all unique characters.
            Since there are only uppercase English letters in the string, m = 26.
*/

#include <unordered_set>

int characterReplacement(string s, int k) {
    unordered_set<char> allLetters;

    for (int i = 0; i < s.length(); i++) 
    {
        allLetters.insert(s[i]);
    }

    int max_size = 0;
    for (char letter : allLetters) 
    {
        int max_char_count = 0;
        
        int start = 0;
        for (int end = 0; end < s.length(); end += 1) 
        {
            if (s[end] == letter) max_char_count++;
            while (!((end-start+1) - max_char_count <= k)) 
            {
                if (s[start++] == letter) 
                {
                    max_char_count--;
                }
            }
            max_size = max(max_size, (end-start+1));
        }
    }
    return max_size;
}

// -------------------------------------------------- Dynamic Sliding Window (Fast) --------------------------------------------------

/* 
    Intuition:
        In the first approach, where we apply binary search to different lengths of substrings. 
        Depending on whether a substring meets the specified conditions or not, we increase or decrease the length of the substring. 
        We use a sliding window-based approach to test the validity condition.
        Note that the size of the sliding window does not change while it moves across the string. 
        If it does, we try again from the beginning, increasing the window size (or decreasing it if it remains invalid). 
        In this way, we try to find the longest valid window. But do we need to start at the beginning of the string again?
        Recall that when a string of length 1 is valid, all its substrings form a valid string. 
        
        Let's try looking at it from the other side. 
        Suppose we have identified a valid substring/window of length l—1. To find an even longer valid window, we should try adding the next alphabet. 
        This temporarily increases the size of the window to l. We check whether it forms a valid window or not. 
        If not, we move the beginning of the window to the right, which resets the window size back to l—1 and effectively moves the window to the right.
        We keep moving it until we reach a point where we find a valid window of size l. Now, we don't need to stop there. 
        We can continue looking for a valid window Of size l+1. We continue this process until the window hits the right edge Of the string. 
        The size of the window at the end would be our answer.
        The key takeaway here is that once we have found a valid window, we don't need to decrease the size of it. 
        The window keeps moving toward the right. At each step, even if the window becomes invalid, we never decrease its size. 
        We increase the size only when we find a valid window of larger size.
        
        Now let's look at it a bit more formally We begin with a sliding window of size O positioned at the left edge of the string. We consider an empty window as valid.
        start points at the first character of the window initially positioned at index 0. end points at the last character of the window initially positioned at index —1. 
        We can see that the window's size is O (end—start+1 —  we also consult our old friend, the frequency map. It stores a map of characters to their frequencies in the window; 
        Our objective is to find the longest valid window. So, whenever we see a valid window, we try to expand its size by moving the end pointer forward. 
        As we move the pointer forward, we update the frequencyMap as well. The frequency map helps us keep track of the character that appears most frequently in the window. 
        We compare the frequency of the newly added character with the maximum frequency of any character seen so far - maxFrequency. We update maxFrequency when we find a new maximum.
        The window size increases only when maxFrequency finds a new maximum. For this, we always want the following condition to hold true -windowSize — ma;rFrequency k
        We stop moving the end pointer forward, or in other words, stop expanding the window when it becomes invalid. 
        Say the size of the window when it becomes invalid is l. We know the previous window with the size l — 1 was valid. 
        So, we move the prior window of length l — 1 toward the right To do so, the start pointer moves one step further. 
        Remember that the end pointer had already moved, so we don't need to move the end pointer again.
        At this point, the last valid window has moved one step to the right, but it might still be invalid. 
        As explained earlier, we are only interested in larger windows, so we don't need to decrease the window size. 
        We move the window of size i — 1 further and further to the right until it becomes valid again.
        If we come across a valid window, we try to expand it as much as possible, and the process continues until the end pointer reaches the rightmost alphabet of the string. 
        At this point, the size of the window indicates the longest valid substring seen yet.

    Algorithm
        1. Initialize start = 0 and end = 0. They represent the indexes of the window's left most and the most characters resepectively.
        2. Initialize a hash map frequencyMap to contain characters and their frequencies.
        3. Initially the size of the window is 0, which we consider as valid. Expand the window by moving end pointer forward. We do so until the window becomes invalid.
        4. Every time end moves forward, we update the frquency map of the newly added element. We update maxFrequency if its frequency is the maximum we have seen so far.
            We check for validity using the following formula: (end + 1 — start) — maxFrequency < k
        5. If the window is invalid, move the start pointer ahead by one step. Every time start moves forward, we update the frequency of the outgoing element in the map. 
            At this point the size of the window is equal to the longest valid window we have seen so far. We make a note of the window size in a variable longestSubstringLength.
        6. We repeat the last two steps until the window reaches the right edge of the string.
        7. longestSubstringLength contains the answer.
    
    Complexity Analysis
        If there are n characters in the given string-
        • Time complexity: O(n). 
            In this approach, we access each index of the string at most two times. When it is added to the sliding window, and when it is removed from the sliding window. 
            The sliding window always moves forward. In each step, we update the frequency map, maxFrequency, and check for validity, they are all constant-time operations. 
            To sum up, the time complexity is proportional to the number of characters in the string - O(n).
        
        • Space complexity: O(m). 
            Similar to the previous approaches, this approach requires an auxiliary frequency map.
            The maximum number of keys in the map equals the number of unique characters in the string. 
            If there are m unique characters, then the memory required is proportional to m. So the space complexity is O(m). 
            Considering uppercase English letters only, m 26.
*/

#include <unordered_map>
class Solution {
public:
    int characterReplacement(string s, int k) 
    {
        int max_size = 0;
        int max_char_count = 0;
        int window_start = 0;
        int window_end = 0;
        unordered_map<char, int> map;
        while(window_end < s.size())
        {
            map[s[window_end]]++;
            max_char_count = max(max_char_count, map[s[window_end]]);
            if((window_end - window_start + 1) - max_char_count > k )
            {
                map[s[window_start++]]--;
            }
            max_size = max(max_size, window_end-window_start+1);
            window_end++;
        }
        return max_size;
    }
};


// Or inside while loop we can use a while loop instead of if condition because we need to move window_start until the window becomes valid again. 
// here while loop and if condition are same because we are moving window_start by 1 in both cases. 

class Solution {
public:
    int characterReplacement(string s, int k) 
    {
        int max_size = 0;
        int max_char_count = 0;
        int window_start = 0;
        int window_end = 0;
        unordered_map<char, int> map;
        while(window_end < s.size())
        {
            map[s[window_end]]++;
            max_char_count = max(max_char_count, map[s[window_end]]);
            while((window_end - window_start + 1) - max_char_count > k)
            {
                map[s[window_start++]]--;
            }
            max_size = max(max_size, window_end-window_start+1);
            window_end++;
        }
        return max_size;
    }
};