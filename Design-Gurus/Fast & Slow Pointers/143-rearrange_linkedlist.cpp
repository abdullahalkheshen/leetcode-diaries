/* 
    Leetcode name: 143. Reorder List
    Problem Challenge 2: Rearrange a LinkedList

    Problem Statement
    Given the head of a Singly LinkedList, write a method to modify the LinkedList such that the nodes from the second half of the LinkedList are inserted alternately to the nodes from the first half in reverse order. So if the LinkedList has nodes 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null, your method should return 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> null.

    Your algorithm should use only constant space the input LinkedList should be modified in-place.

    Example 1:
    Input: 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> null
    Output: 2 -> 12 -> 4 -> 10 -> 6 -> 8 -> null 
    
    Example 2:
    Input: 2 -> 4 -> 6 -> 8 -> 10 -> null
    Output: 2 -> 10 -> 4 -> 8 -> 6 -> null
*/

// -------------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #1 Iterative with Fast and Slow Pointers

/*
    Intuition:
        The iterative approach utilizes the two-pointer technique to efficiently reorder the linked list into an alternating pattern. 
        It finds the middle node of the list, reverses the second half, and then merges the reversed second half with the first half, resulting in an alternating pattern.
    
    Algorithm:
        1. `reorderList(head)`: This function rearranges the linked list into an alternating pattern.
            a. Base case: If the list has only one node, no rearrangement is needed.
            b. Finding the middle node: It employs the two-pointer approach to find the middle node of the linked list. 
                One pointer (`slow`) advances one step at a time, while the other pointer (`fast`) advances two steps at a time. 
                When `fast` reaches the end or the second to last node, `slow` will be at the middle node.
            c. Reversing the second half: Once the middle node is found, the second half of the list is reversed using the `reverse` function. 
                This involves iteratively swapping the current node's `next` pointer to point to the previous node, effectively reversing the order of the nodes.
            d. Merging the reversed second half with the first half: The `merge` function interweaves the reversed second half with the unmodified first half. 
                It alternates between connecting nodes from the first half and the second half, creating the desired alternating pattern.
        
        2. `reverse(head)`: This function reverses the given linked list iteratively.
            a. It maintains two pointers: `prev` pointing to the previous node and `curr` pointing to the current node. Initially, `prev` is `nullptr` and `curr` is the head node.
            b. It iteratively swaps the `next` pointer of the current node to point to the previous node and advances `prev` and `curr` pointers. This effectively reverses the order of the nodes.
            c. After the loop terminates, the `prev` pointer, which now points to the last node, is returned as the new head of the reversed list.
        
        3. `merge(l1, l2)`: This function merges two linked lists into an alternating pattern.
            a. It iteratively alternates between connecting nodes from the first list (`l1`) and the second list (`l2`).
            b. It stores the next node of the current node from `l1` and the next node of the current node from `l2`.
            c. It connects the current node from `l1` to the current node from `l2`.
            d. If the stored next node from `l1` is not `nullptr`, it connects the current node from `l2` to the stored next node from `l1`.
            e. It advances the current nodes (`l1` and `l2`) to the stored next nodes, effectively interleaving nodes from the two lists.
            f. The loop terminates when `l1` is `nullptr`, indicating the end of the first list.

    Complexity Analysis:
        • Time Complexity: O(n)
            → The `reorderList` function involves finding the middle node, reversing the second half, and merging the reversed half with the first half. 
            → The `reverse` function iterates over the second half of the list, and the `merge` function iterates over the entire merged list. 
            → Therefore, the overall time complexity is linear to the number of nodes (n).
        • Space Complexity: O(1)
            → The provided code does not allocate any additional memory during execution. It only uses constant space for pointers and temporary variables. 
            → Therefore, the space complexity is constant (O(1)).
*/

class Solution {
public:
    struct ListNode {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    void reorderList(ListNode* head) 
    {
        if (head->next == nullptr) return;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) 
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(fast) slow->next = nullptr;

        ListNode *middle = slow;
        
        ListNode* l1 = head;
        ListNode* l2 = reverse(middle);
        
        merge(l1, l2);
    }
private:
    ListNode* reverse(ListNode* head) 
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* next = curr->next;
        
        while (curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        return prev;
    }

    void merge(ListNode* l1, ListNode* l2) 
    {
        while (l1) {
            ListNode* p1 = l1->next;
            ListNode* p2 = l2->next;
            
            l1->next = l2;
            if (p1 == nullptr) break;
            l2->next = p1;
            
            l1 = p1;
            l2 = p2;
        }
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #2 Using Stack

/* 
    Intuition:
        The provided code utilizes a stack to efficiently reorder a linked list into an alternating pattern. 
        It pushes all the nodes of the linked list onto a stack, effectively reversing the second half of the list. 
        Then, it interleaves the nodes from the original first half with the nodes from the reversed second half, creating the desired alternating pattern.

    Algorithm:
        1. Edge Case Handling: The code checks for basic edge cases where the linked list is empty, has only one node, or has only two nodes. 
            In these cases, no rearrangement is needed, and the function returns.
        2. Stack Initialization: An empty stack is created to store the nodes of the linked list.
        3. Push Nodes onto Stack: The code traverses the linked list from the beginning, pushing each node onto the stack. 
            This effectively reverses the second half of the list, as the nodes are pushed in reverse order.
        4. Rearrangement: The code iterates while there are still nodes on the stack and updates the `previous_node` pointer to keep track of the node before the insertion point.
            a. Pop Top Node from Stack: The top node from the stack (representing the reversed second half) is retrieved.
            b. Insert Extracted Node: The extracted node is inserted between the current `previous_node` and its next node, effectively interleaving the first and second halves.
            c. Update `previous_node`: The `previous_node` pointer is advanced to the next node after the inserted node, maintaining the insertion point.
        5. Terminate Rearranged List: The `next` pointer of the last inserted node is set to `nullptr` to terminate the rearranged list.

    Complexity Analysis:
        Time Complexity: O(n)
            → overall time complexity is linear to the number of nodes (n).
            → The code iterates over the entire linked list once to push nodes onto the stack and once more to interleave the nodes for rearrangement. 

        Space Complexity: O(n)
            → Space complexity is also linear to the number of nodes (n).
            → The stack can potentially hold all the nodes of the linked list, especially for unbalanced lists. 
*/

using namespace std;
#include <stack>

class Solution
{
public:
    struct ListNode
    {
        int value;
        ListNode *next;
        ListNode() : value(0), next(nullptr) {}
        ListNode(int x) : value(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : value(x), next(next) {}
    };
    
    void reorderList(ListNode *head)
    {
        if ((!head) || (!head->next) || (!head->next->next)) return; // Edge cases
            
        std::stack<ListNode *> node_stack;
        ListNode *current_node = head;
        int list_size = 0;
        
        while (current_node != nullptr) // Push all nodes into the stack
        {
            node_stack.push(current_node);
            list_size++;
            current_node = current_node->next;
        }

        ListNode *top_node;
        ListNode *previous_node = head;
        for (int i = 0; i < list_size / 2; i++) // Insert the top node from the stack between every two nodes
        {
            top_node = node_stack.top();
            node_stack.pop();
            
            top_node->next = previous_node->next;
            previous_node->next = top_node;
            previous_node = previous_node->next->next;
        }
        previous_node->next = nullptr;
    }
};

// --------------------------------------------------------------------------------------------------------------------------------------------------------

// Approach #3 Recrusion

/* 
    Intuition:
        ***The penultimate node in a linked list is the second-to-last node. In other words, it is the node that comes before the last node. The term "penultimate" is derived from the Latin words "paene" meaning "almost" and "ultimus" meaning "last".***
        
        The idea behind the recursive approach to reordering the linked list is to divide the list into smaller sublists and recursively reorder them. 
        By doing so, we can achieve the desired ordering of the entire list.

    Algorithm:
        1. Base Case: If the linked list has zero, one, or two elements, it is already in the desired order, so simply return.
        2. Find Penultimate Node: Identify the second-to-last node in the linked list. This node will be the pivot point for reordering the remaining elements.
        3. Link Penultimate Node with Second Element: Connect the second-to-last node to the second element in the linked list, effectively reversing the order of the remaining elements.
        4. Detach Last Element: Set the 'next' pointer of the second-to-last node to NULL, effectively detaching the last element from the linked list.
        5. Recursive Reordering: Recursively call the `reorderList` function on the remaining portion of the linked list, starting from the newly connected second element.

    Complexity Analysis:
        Time complexity: O(n) 
            → where n is the number of nodes in the linked list. 
            → This is because each recursive call involves traversing a portion of the linked list, and there are a total of O(n) nodes to traverse.
        Space complexity: O(1)
            → as it only requires constant memory for storing local variables. 
            → The recursion does not create additional copies of the linked list, and the memory usage remains constant throughout the execution. 
*/

class Solution {
public:
    struct ListNode
    {
        int value;
        ListNode *next;
        ListNode() : value(0), next(nullptr) {}
        ListNode(int x) : value(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : value(x), next(next) {}
    };

    void reorderList(ListNode* head) {
        //base case i.e if the linked list has zero,one or two elments just return it
        if(!head || !head->next || !head->next->next) return;
        
        //Find the penultimate node i.e second last node of the linkedlist
        ListNode* penultimate = head;
        while (penultimate->next->next) penultimate = penultimate->next;
        
        // Link the penultimate with the second element
        penultimate->next->next = head->next;
        head->next = penultimate->next;
        
        //Again set the penultimate to the the last element
        penultimate->next = NULL;
        
        // Do the above steps reursively
        reorderList(head->next->next);
    }
};