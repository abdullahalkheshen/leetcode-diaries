/* 
    Leetcode name: 209. Minimum Size Subarray Sum
    Smallest Subarray With a Greater Sum (easy)

    Problem Statement:
    Given an array of positive integers and a number ‘S,’ find the length of the smallest contiguous subarray whose sum is greater than or equal to 'S'. Return 0 if no such subarray exists.

    Example 1:
    Input: [2, 1, 5, 2, 3, 2], S=7
    Output: 2
    Explanation: The smallest subarray with a sum greater than or equal to '7' is [5, 2].

    Example 2:
    Input: [2, 1, 5, 2, 8], S=7
    Output: 1 
    Explanation: The smallest subarray with a sum greater than or equal to '7' is [8].

    Example 3:
    Input: [3, 4, 1, 1, 6], S=8
    Output: 3
    Explanation: Smallest subarrays with a sum greater than or equal to '8' are [3, 4, 1] or [1, 1, 6].
*/

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Brute force [Time Limit Exceeded]

/* 
    Intuition:
        Do as directed in question. Find the sum for all the possible subarrays and update the {ans} as and when we get a better subarray that fulfill the requirements sum>=s  
    
    Algorithm:
        1. Initialize ans = INT_MAX
        2. Iterate the array from left to right using i:
            o Iterate from the current element to the end of vector using j:
                o Find the sum of elements from index i to j
                o If sum is greater then s:
                    o Update ans — i + 1))
                    o Start the next ith iteration, since, we got the smallest subarray with sum 2 s starting from the current index.
    
    Complexity Analysis:
        • Time complexity: O(n3).
            o For each element of array, we find all the subarrays starting from that index which is O(n2) .
            o Time complexity to find the sum of each subarray is O(n).
            o Thus, the total time complexity : O(n2 * n) = O(n3)

        • Space complexity: 0(1) extra space.
*/

using namespace std;
#include <vector>
#include <algorithm>

int minSubArrayLen(int s, vector<int>& nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += nums[k];
            }
            if (sum >= s) {
                ans = max(ans, (j - i + 1));
                break; //Found the smallest subarray with sum>=s starting with index i, hence move to next index
            }
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Enhanced Brute Force (Formula) [Accepted]

/*
    Intuition:
        In Approach #1, you may notice that the sum is calculated for every surarray in O(n) time. But, we could easily find the sum in 0(1) time by
        storing the cumulative sum from the beginning(Memoization). After we have stored the cumulative sum in sums, we could easily find the sum of any subarray from i to j .

    Algorithm
        • The algorithm is similar to Approach #1.
        • The only difference is in the way of finding the sum of subarrays:
            o Create a vector sums of size of nums
            o Initialize sums[O] = nums[()]
            o Iterate over the sums vector:
                o Update sums[i] = sums[i — 1] + nums[i]
            o Sum of subarray from i to j is calculated as:
                sum = sums[j] — sums[i] + nums[i], , wherein sums[j] — sums[i] is the sum from (i + l)th element to the jth element.

    Complexity analyis
        • Time complexity. O(n2).
            o Time complexity to find all the subarrays is O(n2).
            o Sum of the subarrays is calculated in 0(1) time.
            o Thus, the total time complexity: O(n2 * 1) O(n2)
        • Space complexity. O(n) extra space
            o Additional O(n) space for sums vector than in Approach #1.
*/

using namespace std;
#include <vector>
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = std::numeric_limits<int>::max();
        vector<int> sums;
        sums[0] = nums[0];
        for (size_t i = 1; i < nums.size(); i++) sums[i] = sums[i-1] + nums[i];
        for (int i = 0; i < nums.size(); i++)
        {
            int sum;
            for (int j = 0; j < nums.size(); j++)
            {
                sum = sums[j] - sums[i] + nums[i];
                if (sum > target) ans = min(ans, j-i+1);
            }
            
        }
        return ans == numeric_limits<int>::max() ? 0 : ans;
    }
};

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Binary Search

/* 
    Intuition
        We could further improve the Approach #2 using the binary search. Notice that we find the subarray with sum s starting with an index i in O(n) time. But, we
        could reduce the time to O(log(n)) using binary search. Note that in Approach #2, we search for subarray starting with index i, until we find sum sums[J]
        sums[i] + nums[i] that is greater than s. So, instead of iterating linearly to find the sum, we could use binary search to find the index that is not lower than s —
        sums(i] in the sums, which can be done using lower_bound function in C++ STL or could be implemented manually.

    Algorithm
        • Create vector sums of size n + 1 with :
            sums[0]=0, sums[i] = sums[i — 1] + nums[i — 1].
        • Iterate from i = 1 to n:
            o Find the value to_find in sum required for minimum subarray starting from index i to have sum greater than s, that is: to_find s + sums[i — 1].
            o Find the index in sums such that value at that index is not lower than the to_find value, say bound.
            o If we find the to_find in sums, then:
                o Size of current subarray is given by:
                bound — (sums.begin() + i — 1)
                o Compare ans with the current subarray size and store minimum in ans
    
    Complexity analysis
        • Time complexity: O(n * log(n)).
            o For each element in the vector, find the subarray starting from that index, and having sum greater than s using binary search. 
                Hence, the time required is O(n) for iteration over the vector and O(log(n)) for finding the subarray for each index using binary search.
            o Therefore, total time complexity = O(n * log(n))
        
        • Space complexity: O(n). Additional O(n) space for sums vector
*/
int minSubArrayLen(int s, vector<int>& nums)
{
    if (nums.size() == 0) return 0;

    int ans = INT_MAX;
    vector<int> sums(nums.size() + 1, 0); //size = n+1 for easier calculations

    //sums[0]=0 : Meaning that it is the sum of first 0 elements
    //sums[1]=A[0] : Sum of first 1 elements
    //ans so on...

    for (int i = 1; i <= nums.size(); i++) sums[i] = sums[i - 1] + nums[i - 1];
        
    for (int i = 1; i <= nums.size(); i++) 
    {
        int to_find = s + sums[i - 1];
        auto bound = lower_bound(sums.begin(), sums.end(), to_find);
        if (bound != sums.end()) ans = min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
    }
    return (ans != INT_MAX) ? ans : 0;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Approach #3 Dynamic Sliding Window 

/* 
    Intuition:
        This problem follows the Sliding Window pattern, and we can use a similar strategy as discussed in the Maximum Sum Subarray of Size K. There is one difference though: in this problem, the sliding window size is not fixed. Here is how we will solve this problem:
    
    Algorithm:
        1. First, we will add up elements from the beginning of the array until their sum
        becomes greater than or equal to
        2. These elements will constitute our sliding window. We are asked to find the smallest such window having a sum greater than or equal to 'S.' 
            We will remember the length of this window as the smallest window so far.
        3. After this, we will keep adding one element in the sliding window (i.e., slide the window ahead) in a stepwise fashion.
        4. In each step, we will also try to shrink the window from the beginning. We will shrink the window until the window's sum is smaller than 'St again. This is needed as we intend to find the smallest window. This shrinking will also happen in multiple
        steps; in each step, we will do two things:
            o Check if the current window length is the smallest so far, and if so, remember its
            length.
            o Subtract the first element of the window from the running sum to shrink the
            sliding window.
    
    Complexity Analysis:
        • Time Complexity: O(n)
            → The time complexity of the above algorithm will be O(N). The outer for loop runs for all elements, and the inner whilé loop processes each element only once.
            therefore, the time complexity of the algorithm will be O(N + N), which is asymptotically equivalent to O(n).
        
        • Space Complexity: O(1)
            → The algorithm runs in constant space 0(1).
*/

int minSubArrayLen(int s, vector<int>& nums)
{
    
    int ans = INT_MAX;
    int sum = 0;
    int window_start = 0;
    for (int window_end = 0; window_end < nums.size(); window_end++) {
        sum += nums[window_end];
        while (sum >= s) {
            ans = min(ans, window_end + 1 - window_start);
            sum -= nums[window_start++];
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}