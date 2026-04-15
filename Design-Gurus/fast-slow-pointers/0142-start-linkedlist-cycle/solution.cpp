/**
 * Problem: 142. Linked List Cycle II
 * Link: https://leetcode.com/problems/linked-list-cycle-ii/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Linked List, Two Pointers, Hash Table, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the head of a Singly LinkedList that contains a cycle, write a function 
    to find the starting node of the cycle.

    Example 1:
    Input: head = [3,2,0,-4], pos = 1
    Output: Node with value 2
    Explanation: There is a cycle in the linked list, where tail connects to the 
    second node.

    Example 2:
    Input: head = [1,2], pos = 0
    Output: Node with value 1

    Example 3:
    Input: head = [1], pos = -1
    Output: null

    Constraints:
    - The number of nodes in the list is in the range [0, 10^4].
    - -10^5 <= Node.val <= 10^5
    - pos is -1 or a valid index in the linked-list.
*/

#include <iostream>
#include <unordered_set>

// ---------------------------------------------------------------------------

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
};

// ---------------------------------------------------------------------------

// Approach #1: HashSet

/*
    Intuition:
    The hash table stores the memory addresses of the nodes visited during the 
    traversal of the linked list. If a node is encountered that has already been 
    visited, it indicates the presence of a cycle, as the node is part of a 
    repeating loop in the linked list.

    Algorithm:
    1. Initialize an unordered_set to store visited nodes.
    2. Set a pointer current_pointer to the head of the linked list.
    3. Iterate while current_pointer is not null:
        a. Check if the memory address of current_pointer is already present in the set:
            i. If yes, return current_pointer (start of cycle).
            ii. If no, insert the memory address into the set.
        b. Advance current_pointer to current_pointer->next.
    4. If the loop terminates without detecting a cycle, return nullptr.

    Complexity Analysis:
    - Time: O(n) - where n is the number of nodes in the linked list.
    - Space: O(n) - for the hash table to store visited nodes.
*/

class Solution_HashSet {
public:
    ListNode* find_cycle_start(ListNode* head) {
        std::unordered_set<ListNode*> visited;
        ListNode* current_pointer = head;
        
        while (current_pointer != nullptr) {
            if (visited.count(current_pointer) > 0) {
                return current_pointer;
            }
            visited.insert(current_pointer);
            current_pointer = current_pointer->next;
        }
        return nullptr;
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Two Pointers (Fast & Slow) - Floyd's Algorithm
// Reference: https://medium.com/@zephyr.ventum/floyds-tortoise-and-hare-cycle-finding-algorithm-my-over-explanation-5631c5ce71d7

/*
    Intuition:
    The algorithm employs the concept of two pointers, a slow pointer and a fast 
    pointer, to detect the presence of a cycle in a linked list. The key idea is 
    that in a cycle, if you have two runners (the slow pointer and fast pointer), 
    they will eventually meet. This is because the fast pointer moves faster and 
    will "lap" the slow pointer.

    Algorithm:
    1. Start with two pointers, slow_pointer and fast_pointer, both initialized at 
       the head of the linked list.
    2. Use a loop to iterate through the list, with the loop continuing as long as 
       both fast_pointer and fast_pointer->next are not null.
    3. In each iteration, advance slow_pointer by one step and fast_pointer by two steps.
    4. If the two pointers meet at some point, it indicates the presence of a cycle. 
       To find the node where the cycle begins, reset slow_pointer to the head and 
       move both pointers one step at a time until they meet again.
    5. Return the node where slow_pointer and fast_pointer converge.

    Complexity Analysis:
    - Time: O(n) - In the worst case, both pointers traverse the entire list.
    - Space: O(1) - Only constant amount of extra space for the two pointers.
*/

class Solution {
public:
    ListNode* find_cycle_start(ListNode* head) {
        ListNode* slow_pointer = head;
        ListNode* fast_pointer = head;
        
        while (fast_pointer != nullptr && fast_pointer->next != nullptr) {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next->next;
            
            if (slow_pointer == fast_pointer) {
                slow_pointer = head;
                while (slow_pointer != fast_pointer) {
                    slow_pointer = slow_pointer->next;
                    fast_pointer = fast_pointer->next;
                }
                return slow_pointer;
            }
        }
        return nullptr;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: List with cycle starting at second node
    ListNode* head1 = new ListNode(3);
    ListNode* cycle_start1 = new ListNode(2);
    head1->next = cycle_start1;
    head1->next->next = new ListNode(0);
    head1->next->next->next = new ListNode(-4);
    head1->next->next->next->next = cycle_start1; // Create cycle
    
    ListNode* result1 = sol.find_cycle_start(head1);
    std::cout << "Test 1: " << (result1 == cycle_start1 ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: List with cycle at head
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = head2; // Cycle back to head
    
    ListNode* result2 = sol.find_cycle_start(head2);
    std::cout << "Test 2: " << (result2 == head2 ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: List without cycle
    ListNode* head3 = new ListNode(1);
    head3->next = new ListNode(2);
    head3->next->next = new ListNode(3);
    
    ListNode* result3 = sol.find_cycle_start(head3);
    std::cout << "Test 3: " << (result3 == nullptr ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Empty list
    ListNode* result4 = sol.find_cycle_start(nullptr);
    std::cout << "Test 4: " << (result4 == nullptr ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
