/**
 * Problem: 102. Binary Tree Level Order Traversal
 * Link: https://leetcode.com/problems/binary-tree-level-order-traversal/
 * Platform: Design-Gurus
 * Difficulty: Medium
 * Tags: Tree, BFS, Binary Tree, Level Order
 *
 * Date Solved: YYYY-MM-DD
 * Time Taken: XX min
 */

/*
    Problem Statement:
    Given the root of a binary tree, return the level order traversal of its
    nodes' values (i.e., from left to right, level by level).

    Example 1:
    Input: root = [12,7,1,9,null,10,5]
    Output: [[12],[7,1],[9,10,5]]

    Example 2:
    Input: root = [3,9,20,null,null,15,7]
    Output: [[3],[9,20],[15,7]]

    Constraints:
    - The number of nodes in the tree is in the range [0, 2000]
    - -1000 <= Node.val <= 1000
*/

#include <iostream>
#include <vector>
#include <queue>

// ---------------------------------------------------------------------------

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ---------------------------------------------------------------------------

// Approach #1: BFS with Queue

/*
    Intuition:
    Use a queue to process nodes level by level. At each level, we know exactly
    how many nodes belong to that level (the current queue size), so we process
    all of them before moving to the next level.

    Algorithm:
    1. Initialize a queue with the root node
    2. While queue is not empty:
       a. Get the current level size (number of nodes at this level)
       b. Process all nodes at this level, adding their children to the queue
       c. Add the current level's values to the result
    3. Return the result

    Complexity Analysis:
    - Time: O(n) where n is the number of nodes
    - Space: O(n) for the queue (worst case: complete binary tree's last level)
*/

class Solution {
public:
    std::vector<std::vector<int>> level_order_traversal(TreeNode* root) {
        std::vector<std::vector<int>> result;
        if (root == nullptr) {
            return result;
        }

        std::queue<TreeNode*> queue;
        queue.push(root);

        while (!queue.empty()) {
            int level_size = queue.size();
            std::vector<int> current_level;

            for (int i = 0; i < level_size; i++) {
                TreeNode* current_node = queue.front();
                queue.pop();

                current_level.push_back(current_node->val);

                if (current_node->left != nullptr) {
                    queue.push(current_node->left);
                }
                if (current_node->right != nullptr) {
                    queue.push(current_node->right);
                }
            }
            result.push_back(current_level);
        }

        return result;
    }
};

// ---------------------------------------------------------------------------

// Test Cases
int main() {
    Solution sol;

    // Test 1: [12,7,1,9,null,10,5]
    TreeNode* root1 = new TreeNode(12);
    root1->left = new TreeNode(7);
    root1->right = new TreeNode(1);
    root1->left->left = new TreeNode(9);
    root1->right->left = new TreeNode(10);
    root1->right->right = new TreeNode(5);

    std::vector<std::vector<int>> result1 = sol.level_order_traversal(root1);
    std::vector<std::vector<int>> expected1 = {{12}, {7, 1}, {9, 10, 5}};
    bool pass1 = (result1 == expected1);
    std::cout << "Test 1: " << (pass1 ? "PASS" : "FAIL") << std::endl;

    // Test 2: Empty tree
    std::vector<std::vector<int>> result2 = sol.level_order_traversal(nullptr);
    std::vector<std::vector<int>> expected2 = {};
    bool pass2 = (result2 == expected2);
    std::cout << "Test 2: " << (pass2 ? "PASS" : "FAIL") << std::endl;

    // Test 3: Single node
    TreeNode* root3 = new TreeNode(1);
    std::vector<std::vector<int>> result3 = sol.level_order_traversal(root3);
    std::vector<std::vector<int>> expected3 = {{1}};
    bool pass3 = (result3 == expected3);
    std::cout << "Test 3: " << (pass3 ? "PASS" : "FAIL") << std::endl;

    return 0;
}
