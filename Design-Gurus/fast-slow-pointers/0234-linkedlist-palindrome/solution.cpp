/**
 * Problem: 234. Palindrome Linked List
 * Link: https://leetcode.com/problems/palindrome-linked-list/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Linked List, Two Pointers, Stack, Recursion, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the head of a Singly LinkedList, write a method to check if the LinkedList 
    is a palindrome or not.

    Your algorithm should use constant space and the input LinkedList should be in 
    the original form once the algorithm is finished. The algorithm should have O(N) 
    time complexity where 'N' is the number of nodes in the LinkedList.

    Example 1:
    Input: 2 -> 4 -> 6 -> 4 -> 2 -> null
    Output: true

    Example 2:
    Input: 2 -> 4 -> 6 -> 4 -> 2 -> 2 -> null
    Output: false

    Constraints:
    - The number of nodes in the list is in the range [1, 10^5].
    - 0 <= Node.val <= 9
*/

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// ---------------------------------------------------------------------------

// Approach #1: Iterative with Fast and Slow Pointers

/*
    Intuition:
    We can solve this problem by reversing the second half of the linked list and 
    comparing it with the first half. If both halves are identical, the linked list 
    is a palindrome.

    Algorithm:
    1. Check if the given linked list is empty or contains only one element.
    2. Initialize two pointers, slow_pointer and fast_pointer, both starting at head.
    3. Once fast_pointer reaches the end, slow_pointer will be at the middle node.
    4. Reverse the second half of the linked list starting from slow_pointer.
    5. Compare the values of each node in the first half with the reversed second half.
    6. If all comparisons are equal, return true.

    Complexity Analysis:
    - Time: O(n) - Finding middle, reversing, and comparing are all O(n).
    - Space: O(1) - We are changing pointers in-place.
*/

class Solution {
public:
    bool is_palindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;

        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;

        while (fast_pointer != nullptr && fast_pointer->next != nullptr) {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }

        if (fast_pointer != nullptr) {
            slow_pointer = slow_pointer->next;
        }

        ListNode* second_half = reverse_linkedlist(slow_pointer);
        ListNode* first_half = head;

        while (second_half != nullptr) {
            if (second_half->val != first_half->val) {
                return false;
            }
            second_half = second_half->next;
            first_half = first_half->next;
        }
        return true;
    }

private:
    ListNode* reverse_linkedlist(ListNode* head) {
        ListNode* previous = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        return previous;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Recursive with One Pointer

/*
    Intuition:
    The recursive approach utilizes the divide-and-conquer strategy to efficiently 
    check whether a linked list is a palindrome. It divides the list into two halves 
    and recursively checks each half for palindromicity.

    Algorithm:
    1. check_palindrome(head, target, is_even): Recursive function that compares nodes.
    2. is_palindrome(head): Initiates the recursive check for the entire linked list.

    Complexity Analysis:
    - Time: O(n) - The recursive function traverses the entire linked list once.
    - Space: O(n) - In the worst case, the recursion stack can grow up to the size of the list.
*/

class Solution_Recursive {
public:
    bool is_palindrome(ListNode* head) {
        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;

        while (fast_pointer != nullptr && fast_pointer->next != nullptr) {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }

        if (fast_pointer != nullptr) {
            slow_pointer = slow_pointer->next;
        }

        ListNode* middle = slow_pointer;
        bool is_even = (fast_pointer != nullptr);

        return check_palindrome(head, middle, is_even);
    }

private:
    bool check_palindrome(ListNode* head, ListNode*& target, bool is_even) {
        if (head == target) {
            if (!is_even) {
                target = target->next;
            }
            return true;
        }

        if (!check_palindrome(head->next, target, is_even)) {
            return false;
        }

        if (head != nullptr && target == nullptr) {
            return false;
        }

        if (head->val == target->val) {
            target = target->next;
            return true;
        }

        return false;
    }
};

// ---------------------------------------------------------------------------

// Helper function to create linked list from vector
ListNode* create_list(const std::vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: Palindrome (odd length)
    ListNode* head1 = create_list({2, 4, 6, 4, 2});
    bool result1 = sol.is_palindrome(head1);
    std::cout << "Test 1: " << (result1 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Not a palindrome
    ListNode* head2 = create_list({2, 4, 6, 4, 2, 2});
    bool result2 = sol.is_palindrome(head2);
    std::cout << "Test 2: " << (result2 == false ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Palindrome (even length)
    ListNode* head3 = create_list({1, 2, 2, 1});
    bool result3 = sol.is_palindrome(head3);
    std::cout << "Test 3: " << (result3 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Single node
    ListNode* head4 = create_list({1});
    bool result4 = sol.is_palindrome(head4);
    std::cout << "Test 4: " << (result4 == true ? "PASS" : "FAIL") << std::endl;
    
    // Test 5: Two nodes - not palindrome
    ListNode* head5 = create_list({1, 2});
    bool result5 = sol.is_palindrome(head5);
    std::cout << "Test 5: " << (result5 == false ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
