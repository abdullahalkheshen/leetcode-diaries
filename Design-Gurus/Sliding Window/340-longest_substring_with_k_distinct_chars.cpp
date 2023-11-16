/* 
    Leetcode name: 340. Longest Substring with At Most K Distinct Characters
    Longest Substring with K Distinct Characters

    Problem Statement
    Given a string, find the length of the longest substring in it with no more than K distinct characters.
    You can assume that K is less than or equal to the length of the given string.

    Example 1:
    Input: String="araaci", K=2  
    Output: 4  
    Explanation: The longest substring with no more than '2' distinct characters is "araa".

    Example 2:
    Input: String="araaci", K=1  
    Output: 2  
    Explanation: The longest substring with no more than '1' distinct characters is "aa".

    Example 3:
    Input: String="cbbebi", K=3  
    Output: 5  
    Explanation: The longest substrings with no more than '3' distinct characters are "cbbeb" & "bbebi".

*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Fixed Sliding Window + Binary Search
/* 
    Intuition:
        Since we are asked to find the longest substring of identical characters, we could first set up a target length max_size.
        To check if a valid substring with this length exists, we iterate over "s" and check each substring of length max_size.
            If we find a substring that contains "k" or fewer unique characters, then this substring is considered valid.
            The method described in this solution is also known as the fixed sliding window algorithm. 
            As we traverse the sequence from left_bound to windows_end, we maintain a fixed length max_size for the subarray, which can be visualized as moving a window of that length over the input. 
            if we set the window length to max_size = 3 , we can find some valid windows that only contain 2 or fewer unique characters. 
            However, if we set the length to max_size = 7 , we will not find any valid windows, since the only 3 windows of size 7 contain more than 2 distinct characters.
            During the iteration, when we move the windows_end boundary of the window from windows_end - 1 to windows_end, we don't need to recalculate the count of each character over again, note that two adjacent windows only differ by two characters s[windows_end - max_size]. 
            We only need to increment the count of s[windows_end] by 1 and decrement the count of s[windows_end] s[windows_end - max_size] by 1 , based on the result of the previous window.
        To quickly find the maximum valid window length, we can use binary search. 
            To begin, we need to define a search space that ensures the maximum window length we are looking for is in this range.
            We can set the left_bound boundary of the search space to left_bound = k (a window of size k always contains no more than k unique characters) and the windows_end boundary to = n.
            We will now perform a binary search on the interval [left_bound, windows_end] . 
            → In each iteration, we compute the midpoint of the interval, which we denote as mid.
            Then, we slide a window of length mid using the previous approach to check whether there exists at least one valid window. 
            If we find a valid window, we then continue to search for a larger window length in [mid, windows_end], the windows_end half of the interval.
            Otherwise, if mid is still too large, we continue our search in [left_bound, mid - 1] , the left_bound half of the search space.
    
    Algorithm:
        1. If k >= n , we don't need to perform the binary search, just return n .
        2. Initialize the search space as left_bound = k , windows_end = n
        3. Define a function isVa1id to help verify if there exists a valid subarray of length size :
            • Count the number of each characterin in a hash map map , return true if len(map) k
            • Iterate the index of the windows_end boundary of the window from size - 1 to n . At each step i , increment
            byl and decrement - size]] by 1, if - o , we delete this item maps[s[i - size]] ¯ from map .
            • Return true if len(map) k at any point in this iteration
            • Return false if we finish iterating without finding a valid window.
        4. While left_bound < windows_end
           • Compute the middle value as mid = windows_end — (windows_end — left_bound) / 2
           • Check if the window of size mid is valid using the helper method.
           • If isVa1id(mid) is true, let left_bound = mid and repeat.
           • If isVa1id(mid) is false, let windows_end = mid - 1 and repeat.
        5. Return left_bound once the binary search ends.
    
    Complexity Analysis:
        Time complexity: • logn)
            o Let n be the length of the input string s
            o We set the search space as [k, n], it takes at most O(logn) binary search steps.
            o At each step, we iterate over s which takes time.
        
        Space complexity: O(n)
            o We need to update the boundary indices left_bound and windows_end .
            o During the iteration, we use a hash map map which could contain at most O(n) distinct characters.
*/
using namespace std;
#include <iostream>
#include <string>
#include <unordered_map>

class Solution {
public:
    int length_of_longest_substring_K_distinct(string &s, int k) 
    {
        if (s.length() <= k) return s.length();
        
        int left_bound = k, right_bound = s.length();
        while (left_bound < right_bound)
        {
            int mid = (left_bound + right_bound + 1) / 2;
            if (is_valid_window(s, mid, k)) left_bound = mid;
            else right_bound = mid - 1;
        }
        return left_bound;
    }

private:
    bool is_valid_window(string s, int window_size, int k) 
    {
        unordered_map<char, int> map;

        for (int window_index = 0; window_index < window_size; window_index++) map[s[window_index]]++;
        if (map.size() <= k) return true;

        for (int window_index = window_size; window_index < s.length(); window_index++)
        {
            map[s[window_index]]++;
            map[s[window_index - window_size]]--;
            if (map[s[window_index - window_size]] == 0) 
                map.erase(s[window_index - window_size]);
            
            if (map.size() <= k) return true;
        }

        return false;
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach#2 Dynamic Sliding Window

/* 
    Intuition:
        This problem follows the Sliding Window pattern, and we can use a similar dynamic sliding window strategy as discussed in Smallest Subarray with a Greater Sum. 
        We can use a HashMap to remember the frequency of each character we have processed.
        
        We can also find the longest valid window with fewer traversals. Unlike the previous fixed-length sliding window solution, this time we can adjust the window length based on the situation. 
        We will still use the map map to record the map of each type of character within the window.
        Specifically, if the current window is valid, we can try to expand the window by moving the windows_end boundary one position
        to the windows_end, windows_end = windows_end + 1 . 
        On the other hand, if the current window is invalid, we keep moving the left_bound boundary to the windows_end (equivalent to removing the left_boundmost character from the window) until the window becomes valid, that is left_bound = left_bound + 1 . 
        During this process, we constantly record the longest valid window seen so far.
        As shown in the following figure, we keep adjusting the size of the window and recording the maximum size of the valid window.

    Algorithm:
        1. First, we will insert characters from the beginning of the string until we have K distinct characters in the HashMap.
        2. These characters will constitute our sliding window. We are asked to find the longest such window having no more than K distinct characters. 
            We will remember the length of this window as the longest window so far.
        3. After this, we will keep adding one character in the sliding window (i.e., slide the window ahead) in a stepwise fashion.
        4. In each step, we will try to shrink the window from the beginning if the count of distinct characters in the HashMap is larger than K. We will shrink the window until
        we have no more than K distinct characters in the HashMap. This is needed as we intend to find the longest window.
        5. While shrinking, we'll decrement the character's frequency going out of the window and remove it from the HashMap if its frequency becomes zero.
        6. At the end of each step, we'll check if the current window length is the longest so far, and if so, remember its length.

    Complexity Analysis:
        Time Complexity: O(n)
            → where "n" is the number of characters in the input string. 
            → The outer fom loop runs for all characters, and the inner while loop processes each character only once.
                the time complexity of the algorithm will be O(n + n), which is asymptotically equivalent to O(n).
        Space Complexity: O(k)
            → as we will be storing a maximum of K + 1 characters in the HashMap.  
*/

class Solution
{
    public:
        static int length_of_longest_substring_K_distinct(const string &str, int k)
        {
            int max_size = 0;
            int window_start = 0;
            int window_end = 0;
            unordered_map<char, int> map;

            while(window_end < str.length()) // or for(int window_end=0; window_end<str.length(); window_end++)
            {
                map[str[window_end]]++;
                
                while ((int)map.size() > k)
                {
                    map[str[window_start]]--;
                    if (map[str[window_start]] == 0) map.erase(str[window_start]);
                    window_start++;
                }
                // remember the maximum length so far
                max_size = max(max_size, (window_end - window_start + 1));
                window_end++;
            }
            return max_size;
        }
};


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach#2 Fixed Sliding Window

/* 
    Intuition:
        In the previous solution, we need to ensure that the current window is always valid. 
        If the window contains more than k distinct characters, we need to continuously remove the left_boundmost character in the window. 
        During this process, the size of the window may decrease, even smaller than the previous valid window. 
        Taking the figure below as an example, the window on the left_bound is valid, but the window' on the windows_end is not valid, and we need to remove the left_bound characters from it to make it valid.
        However, we don't need to decrease the size of the window.
        If we have already found a window of length max_size , then what we need to do next is to search for a larger valid window, for example, a window with length max_size + 1 . 
        Therefore, in the following sliding window process, even if the current window with size max_size is not valid, there is no problem, because we have already found a window of length max_size before, so we may as well continue looking for a larger window.
        Understanding this, we can simplify the solution in approach 2:
        Again, we use a hash map map to keep track of the frequency of each letter in the current window. When we increase the window length by 1, we need to increase the count of the character at the current windows_end boundary map[s[windows_end]] by 1.
        If the expanded window is still valid, it means that we geta larger valid window with length max_size + 1 (from 2 to 3 ). We can continue to move the boundary windows_end.
        However, if the expanded window is invalid, we only need to remove the left_boundmost character in the window to keep the window length still at max_size (from 4 to 3 ), that is, decrease - by 1.
        Since the expanded window of length 4 was invalid, we removed a character from the left_boundmost side of the window to make its length 3 again. 
        Although the current window is still invalid, we don't need to keep shrinking it because we have previously found a valid window of length 3 . 
        We can continue to shift the boundary windows_end to try the next window of size 4 .
        Once this iteration is over, max_size represents the maximum size of the valid window.

    Algorithm:
        1. Use a hash map "map" to keep track of the number of each character in the current window.
        2. Set max_size = 0, iterate windows_end from ø to n - 1 , at each step windows_end, increment s[windows_end] by 1, and increment map[s[windows_end]] by 1.
            • If len(map) > k , decrement map[s[windows_end — max_size]] by l.
            • Delete map [s [windows_end — max_sizel] if its value equals O.
            • Otherwise, increment max_size by 1.
        3. Return max_size when the iteration ends which's the maximum distinct characters substring size.
    
    Complexity Analysis:
        Let n be the length of the input string s and k be the maximum number of distinct characters.
        Time complexity: O(n)
            → In the iteration of the windows_end boundary windows_end , we shift it from to n - 1
            → At each step, we update the number of s[windows_end] and/or the number of s[windows_end - max_size] in the hash map map , which takes constant time.
            → To sum up, the overall time complexity is O(n).
        Space complexity: O(n)
            → We need to record the occurrence of each distinct character in the window. During the iteration, there might be at most O(n) unique characters in the window, which takes O(n) space.
*/

class Solution {
public:

    int length_of_longest_substring_K_distinct(string s, int k) {
        int window_start = 0;
        unordered_map<char, int> map;

        for (int windows_end = 0; windows_end < s.length(); windows_end++) 
        {
            map[s[windows_end]]++;


            // we used if instead of while because we want to keep the window size same as max_size even if the window is invalid 
            // because we have already found a valid window of length max_size before, so we may as well continue looking for a larger window.

            if (map.size() <= k) window_start++;
            else 
            {
                // note that windows_end - window_start is the size of the window
                // but map[s[windows_end - window_start]] is the left_boundmost character of the window to be removed from the map 
                /* 
                    If you're wondering how str[windows_end - window_start] is accessing the left_boundmost character of the maximum window,
                    it's because we're dealing with indicies here, not the characters/numbers.  
                    for example: if windows_end = 4 and window_start = 2, then windows_end - window_start = 2, and s[2] is the left_boundmost character of the window
                
                */

                map[s[windows_end - window_start]]--; 
                if (map[s[windows_end - window_start]] == 0) 
                    map.erase(s[windows_end - window_start]);
            }
        }

        return window_start;
    }
};

