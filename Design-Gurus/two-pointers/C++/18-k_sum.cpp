/* 
    Introduction:
        • This problem is a follow-up of 3Sum, so take a look at that problem first if you haven't.
        • 4Sum and 3Sum are very similar; the difference is that we are looking for unique quadruplets instead of triplets.

        • As you see, 3Sum just wraps Two Sum in an outer loop. As it iterates through each value "v", it finds all pairs whose sum is equal to target - "v" using one of these approaches:
            1. Two Sum uses a hash set to check for a matching value.
            2. Two Sum II uses the two pointers pattern in a sorted array.

        Following a similar logic, we can implement 4Sum by wrapping 3Sum in another loop.
        
        But wait - there is a catch. If an interviewer asks you to solve 4Sum, they can follow-up with 5Sum, 6Sum, and so on.
        What they are really expecting at this point is a kSum solution. Therefore, we will focus on a generalized implementation here.
*/

// ----------------------------------------------------------------------------------------------------------------------------------------------------


// Approach 1: Two Pointers
/* 
    Intuition:
        The two pointers pattern requires the array to be sorted, so we do that first.
        Also, it's easier to deal with duplicates if the array is sorted: repeated values are next to each other and easy to skip.
        
        • For 3Sum, we enumerate each value in a single loop, and use the two pointers pattern for the rest of the array. 
        • For kSum, we will have k - 2 nested loops to enumerate all combinations of k - 2 values.

    Algorithm
        1. We can implement k - 2 loops using a "recursion". We will pass the starting point and k as the parameters. 
            * When k == 2, we will call twoSum, terminating the recursion.

        2. For the main four_sum function:
            2.1. Sort the input array nums.
            2.2. Call kSum with start = 0, k = 4, and target, and return the result.
        
        3. For k_Sum function:
            3.1 At the start of the kSum function, we will check three conditions:
                3.1.1 Have we run out of numbers to choose from?
                3.1.2 Is the smallest number remaining greater than target / k?
                        • If so, then any k numbers we choose will be too large.
                3.1.3 Is the largest number remaining smaller than target / k?
                        • If so, then any k numbers we choose will be too small.
                If any of these conditions is true, there is no need to continue as no combination of the remaining elements can sum to target.
            
            3.2 If k equals 2, call twoSum and return the result.
            
            3.3 Iterate i through the array from start:
                If the current value is the same as the one before, skip it.
                Recursively call kSum with start = i + 1, k = k - 1, and target - nums[i].
                For each returned subset of values:
                    Include the current value nums[i] into subset.
                    Add subset to the result res.
        
        4. For twoSum function:
                Set the low pointer l to start, and high pointer r to the last index.
                While low pointer is smaller than high:
                    If the sum of nums[l] and nums[r] is less than target, increment l.
                        Also increment l if the value is the same as for l - 1.
                    If the sum is greater than target, decrement r.
                        Also decrement r if the value is the same as for r + 1.
                    Otherwise, we found a pair:
                        Add it to the result res.
                        Decrement r and increment l.
        5. Return the result res.


    Complexity Analysis
        Time Complexity: O(n^{k - 1}) for K_sum, O(n^3) for 4Sum.
            -> We have k-2 loops, and twoSum is O(n).
            -> Note that for k>2, sorting the array does not change the overall time complexity.

        Space Complexity: O(n). We need O(k) space for the recursion. k can be the same as n in the worst case for the generalized algorithm.
            -> Note that, for the purpose of complexity analysis, we ignore the memory required for the output.
*/


using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>


class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        return kSum(nums, target, 0, 4);
    }
	
    vector<vector<int>> kSum(vector<int>& nums, long long target, int start, int k) {
        vector<vector<int>> res;
        
        // If we have run out of numbers to add, return res.
        if (start == nums.size()) {
            return res;
        }
        
        // There are k remaining values to add to the sum. The average of these values is at least target / k.
        long long average_value = target / k;
        
        // We cannot obtain a sum of target if the smallest value in nums is greater than target / k,
        //      or if the largest value in nums is smaller than target / k.
        if  (nums[start] > average_value || average_value > nums.back()) {
            return res;
        }

        if (k == 2) {
            return twoSum(nums, target, start);
        }

        // if k > 2 go for recursion:
        for (int i = start; i < nums.size(); ++i) {
            if (i == start || nums[i - 1] != nums[i]) {
                for (vector<int>& subset : kSum(nums, static_cast<long long>(target) - nums[i], i + 1, k - 1)) {
                    res.push_back({nums[i]});
                    res.back().insert(end(res.back()), begin(subset), end(subset));
                }
            }
        }
                                            
        return res;
    }
	
    vector<vector<int>> twoSum(vector<int>& nums, long long target, int start) {
        vector<vector<int>> res;
        int l = start, r = int(nums.size()) - 1;
    
        while (l < r) {
            int curr_sum = nums[l] + nums[r];
            if (curr_sum < target || (l > start && nums[l] == nums[l - 1])) {
                ++l;
            } else if (curr_sum > target || (r < nums.size() - 1 && nums[r] == nums[r + 1])) {
                --r;
            } else {
                res.push_back({ nums[l++], nums[r--] });
            }
        }
                                                           
        return res;
    }
};


// ----------------------------------------------------------------------------------------------------------------------------------------------------

// Approach 2: Hash Set

/* 
    Intuition
        Since elements must sum up to the exact target value, we can also use the Two Sum: One-pass Hash Table approach.
        In 3Sum: Hash Set, we solved the problem without sorting the array. To do that, we needed to sort values within triplets, and track them in a hash set. 
        Doing the same for k values could be impractical.
        So, for this approach, we will also sort the array and skip duplicates the same way as in the Two Pointers approach above. 
        Thus, the code will only differ in the twoSum implementation.
    
    Algorithm
        to avoid duplicates. Since the array is sorted, we can just compare the found pair with the last one in the result res.

    
        Complexity Analysis
            Time Complexity: k_sum O(n^{k - 1}) or O(n^3) for 4Sum.
                -> We have k−2k - 2k−2 loops iterating over nnn elements, and twoSum is O(n)O(n)O(n).
                -> Note that for k>2, sorting the array does not change the overall time complexity.

            Space Complexity: O(n) for the hash set. 
                -> The space needed for the recursion will not exceed O(n)
*/

#include <unordered_set>
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));
        return kSum(nums, target, 0, 4);
    }
	
    vector<vector<int>> kSum(vector<int>& nums, long long target, int start, int k) {
        vector<vector<int>> res;

        // If we have run out of numbers to add, return res.
        if (start == nums.size()) {
            return res;
        }
        
        // There are k remaining values to add to the sum. The average of these values is at least target / k.
        long long average_value = target / k;
        
        // We cannot obtain a sum of target if the smallest value in nums is greater than target / k or if the largest value in nums is smaller than target / k.
        if  (nums[start] > average_value || average_value > nums.back()) return res;
        
        if (k == 2) {
            return twoSum(nums, target, start);
        }
    
        for (int i = start; i < nums.size(); ++i) {
            if (i == start || nums[i - 1] != nums[i]) 
            {
                for (vector<int>& subset : kSum(nums, static_cast<long>(target) - nums[i], i + 1, k - 1)) 
                {
                    res.push_back({nums[i]});
                    res.back().insert(end(res.back()), begin(subset), end(subset));
                }
            }
        }
                                            
        return res;
    }
	
    vector<vector<int>> twoSum(vector<int>& nums, long long target, int start) 
    {
        vector<vector<int>> res;
        unordered_set<long long> s;
    
        for (int i = start; i < nums.size(); ++i) 
        {
            if (res.empty() || res.back()[1] != nums[i]) 
            {
                if (s.count(target - nums[i])) 
                {
                    res.push_back({int(target - nums[i]), nums[i]});
                }
            }
            s.insert(nums[i]);
        }
        return res;
    }  
};