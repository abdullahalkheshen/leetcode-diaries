/**
 * Problem: 876. Middle of the Linked List
 * Link: https://leetcode.com/problems/middle-of-the-linked-list/
 * Platform: Design-Gurus
 * Difficulty: Easy
 * Tags: Linked List, Two Pointers, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the head of a Singly LinkedList, write a method to return the middle node 
    of the LinkedList. If the total number of nodes in the LinkedList is even, return 
    the second middle node.

    Example 1:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> null
    Output: 3

    Example 2:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null
    Output: 4

    Example 3:
    Input: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> null
    Output: 4

    Constraints:
    - The number of nodes in the list is in the range [1, 100].
    - 1 <= Node.val <= 100
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

// Approach #1: Brute Force / Most Intuitive

/*
    Intuition:
    Count the total number of nodes first, then traverse again to find the middle.

    Algorithm:
    1. Initialize a pointer p to the head and a counter count to 0.
    2. Traverse the linked list, incrementing count for each node visited.
    3. Calculate the middle index mid = count / 2.
    4. Reinitialize the pointer to head and traverse to the node at index mid.
    5. Return the pointer pointing to the middle node.

    Complexity Analysis:
    - Time: O(n) - We traverse the linked list twice.
    - Space: O(1) - Only constant memory for pointers and counter.
*/

class Solution_BruteForce {
public:
    ListNode* middle_node(ListNode* head) {
        ListNode* p = head;
        int count = 0;

        while (p != nullptr) {
            count++;
            p = p->next;
        }

        ListNode* q = head;
        for (int i = 0; i < count / 2; i++) {
            q = q->next;
        }
        return q;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Fast & Slow)

/*
    Intuition:
    Imagine two runners racing along a linked list track. One runner, the "slow 
    pointer," takes one step at a time, while the other runner, the "fast pointer," 
    takes two steps at a time. When the fast pointer reaches the end of the track, 
    the slow pointer will be at the middle node of the linked list.

    Algorithm:
    1. Initialize two pointers, slow_pointer and fast_pointer, both pointing to head.
    2. While fast_pointer and its next node both exist:
        a. Advance slow_pointer by one node.
        b. Advance fast_pointer by two nodes.
    3. slow_pointer will be pointing to the middle node.

    Complexity Analysis:
    - Time: O(n) - We traverse the linked list once.
    - Space: O(1) - Only constant memory for the two pointers.
*/

class Solution {
public:
    ListNode* middle_node(ListNode* head) {
        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;
        
        while (fast_pointer != nullptr && fast_pointer->next != nullptr) {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
        }
        return slow_pointer;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Output to Array/Vector

/*
    Intuition:
    Store all nodes in a vector, then return the node at the middle index.

    Algorithm:
    1. Create an empty vector v.
    2. Add all nodes of the linked list to the vector v.
    3. The middle node is located at index v.size() / 2.
    4. Return the node at that index.

    Complexity Analysis:
    - Time: O(n) - We traverse the linked list once to populate the vector.
    - Space: O(n) - We create and store a vector that holds all nodes.
*/

class Solution_Array {
public:
    ListNode* middle_node(ListNode* head) {
        std::vector<ListNode*> v = {head};
        while (v.back()->next != nullptr) {
            v.push_back(v.back()->next);
        }
        return v[v.size() / 2];
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
    
    // Test 1: Odd number of nodes
    ListNode* head1 = create_list({1, 2, 3, 4, 5});
    ListNode* result1 = sol.middle_node(head1);
    std::cout << "Test 1: " << (result1->val == 3 ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Even number of nodes (return second middle)
    ListNode* head2 = create_list({1, 2, 3, 4, 5, 6});
    ListNode* result2 = sol.middle_node(head2);
    std::cout << "Test 2: " << (result2->val == 4 ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Seven nodes
    ListNode* head3 = create_list({1, 2, 3, 4, 5, 6, 7});
    ListNode* result3 = sol.middle_node(head3);
    std::cout << "Test 3: " << (result3->val == 4 ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Single node
    ListNode* head4 = create_list({1});
    ListNode* result4 = sol.middle_node(head4);
    std::cout << "Test 4: " << (result4->val == 1 ? "PASS" : "FAIL") << std::endl;
    
    // Test 5: Two nodes
    ListNode* head5 = create_list({1, 2});
    ListNode* result5 = sol.middle_node(head5);
    std::cout << "Test 5: " << (result5->val == 2 ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
