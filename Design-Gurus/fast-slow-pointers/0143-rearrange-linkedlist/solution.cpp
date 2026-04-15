/**
 * Problem: 143. Reorder List
 * Link: https://leetcode.com/problems/reorder-list/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Linked List, Two Pointers, Stack, Recursion, Fast-Slow Pointers
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the head of a Singly LinkedList, write a method to modify the LinkedList 
    such that the nodes from the second half of the LinkedList are inserted 
    alternately to the nodes from the first half in reverse order.
    
    So if the LinkedList has nodes 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null, your method 
    should return 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> null.

    Your algorithm should use only constant space and the input LinkedList should 
    be modified in-place.

    Example 1:
    Input: 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> null
    Output: 2 -> 12 -> 4 -> 10 -> 6 -> 8 -> null

    Example 2:
    Input: 2 -> 4 -> 6 -> 8 -> 10 -> null
    Output: 2 -> 10 -> 4 -> 8 -> 6 -> null

    Constraints:
    - The number of nodes in the list is in the range [1, 5 * 10^4].
    - 1 <= Node.val <= 1000
*/

#include <iostream>
#include <stack>
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
    The iterative approach utilizes the two-pointer technique to efficiently reorder 
    the linked list into an alternating pattern. It finds the middle node of the list, 
    reverses the second half, and then merges the reversed second half with the first 
    half, resulting in an alternating pattern.

    Algorithm:
    1. reorder_list(head): This function rearranges the linked list into an alternating pattern.
        a. Base case: If the list has only one node, no rearrangement is needed.
        b. Finding the middle node: Use two-pointer approach to find the middle node.
        c. Reversing the second half: Reverse the second half using the reverse function.
        d. Merging: Interweave the reversed second half with the first half.

    2. reverse(head): Reverses the given linked list iteratively.

    3. merge(l1, l2): Merges two linked lists into an alternating pattern.

    Complexity Analysis:
    - Time: O(n) - Finding middle, reversing, and merging are all O(n).
    - Space: O(1) - Only constant space for pointers and temporary variables.
*/

class Solution {
public:
    void reorder_list(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        ListNode* second_half = reverse(slow->next);
        slow->next = nullptr;
        
        merge(head, second_half);
    }

private:
    ListNode* reverse(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        return prev;
    }

    void merge(ListNode* l1, ListNode* l2) {
        while (l1 != nullptr && l2 != nullptr) {
            ListNode* p1 = l1->next;
            ListNode* p2 = l2->next;
            
            l1->next = l2;
            l2->next = p1;
            
            l1 = p1;
            l2 = p2;
        }
    }
};

// ---------------------------------------------------------------------------

// Approach #2: Using Stack

/*
    Intuition:
    The stack approach pushes all the nodes of the linked list onto a stack, 
    effectively reversing the second half of the list. Then, it interleaves the 
    nodes from the original first half with the nodes from the reversed second half.

    Algorithm:
    1. Edge Case Handling: Check for empty, single-node, or two-node lists.
    2. Stack Initialization: Create an empty stack to store the nodes.
    3. Push Nodes onto Stack: Traverse the linked list, pushing each node onto the stack.
    4. Rearrangement: Pop nodes from the stack and insert them between every two nodes.
    5. Terminate Rearranged List: Set the next pointer of the last inserted node to nullptr.

    Complexity Analysis:
    - Time: O(n) - Linear to the number of nodes.
    - Space: O(n) - Stack can potentially hold all the nodes.
*/

class Solution_Stack {
public:
    void reorder_list(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return;
        }
        
        std::stack<ListNode*> node_stack;
        ListNode* current_node = head;
        int list_size = 0;
        
        while (current_node != nullptr) {
            node_stack.push(current_node);
            list_size++;
            current_node = current_node->next;
        }

        ListNode* previous_node = head;
        for (int i = 0; i < list_size / 2; i++) {
            ListNode* top_node = node_stack.top();
            node_stack.pop();
            
            top_node->next = previous_node->next;
            previous_node->next = top_node;
            previous_node = previous_node->next->next;
        }
        previous_node->next = nullptr;
    }
};

// ---------------------------------------------------------------------------

// Approach #3: Recursion

/*
    Intuition:
    The recursive approach divides the list into smaller sublists and recursively 
    reorders them. By doing so, we can achieve the desired ordering of the entire list.
    
    Note: The penultimate node in a linked list is the second-to-last node.

    Algorithm:
    1. Base Case: If the linked list has zero, one, or two elements, return.
    2. Find Penultimate Node: Identify the second-to-last node in the linked list.
    3. Link Penultimate Node with Second Element: Connect the last node to the second element.
    4. Detach Last Element: Set the next pointer of the penultimate node to nullptr.
    5. Recursive Reordering: Recursively call on the remaining portion.

    Complexity Analysis:
    - Time: O(n^2) - Each recursive call involves traversing to find penultimate node.
    - Space: O(n) - Recursion stack depth.
*/

class Solution_Recursive {
public:
    void reorder_list(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return;
        }
        
        ListNode* penultimate = head;
        while (penultimate->next->next != nullptr) {
            penultimate = penultimate->next;
        }
        
        penultimate->next->next = head->next;
        head->next = penultimate->next;
        penultimate->next = nullptr;
        
        reorder_list(head->next->next);
    }
};

// ---------------------------------------------------------------------------

// Helper function to print linked list
void print_list(ListNode* head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

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

// Helper function to convert list to vector
std::vector<int> list_to_vector(ListNode* head) {
    std::vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Test Cases
int main() {
    Solution sol;
    
    // Test 1: Even number of nodes
    ListNode* head1 = create_list({2, 4, 6, 8, 10, 12});
    sol.reorder_list(head1);
    std::vector<int> expected1 = {2, 12, 4, 10, 6, 8};
    std::vector<int> result1 = list_to_vector(head1);
    std::cout << "Test 1: " << (result1 == expected1 ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Odd number of nodes
    ListNode* head2 = create_list({2, 4, 6, 8, 10});
    sol.reorder_list(head2);
    std::vector<int> expected2 = {2, 10, 4, 8, 6};
    std::vector<int> result2 = list_to_vector(head2);
    std::cout << "Test 2: " << (result2 == expected2 ? "PASS" : "FAIL") << std::endl;
    
    // Test 3: Single node
    ListNode* head3 = create_list({1});
    sol.reorder_list(head3);
    std::vector<int> expected3 = {1};
    std::vector<int> result3 = list_to_vector(head3);
    std::cout << "Test 3: " << (result3 == expected3 ? "PASS" : "FAIL") << std::endl;
    
    // Test 4: Two nodes
    ListNode* head4 = create_list({1, 2});
    sol.reorder_list(head4);
    std::vector<int> expected4 = {1, 2};
    std::vector<int> result4 = list_to_vector(head4);
    std::cout << "Test 4: " << (result4 == expected4 ? "PASS" : "FAIL") << std::endl;
    
    return 0;
}
