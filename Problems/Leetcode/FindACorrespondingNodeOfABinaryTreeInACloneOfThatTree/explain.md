## Problem

https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/

```
Given two binary trees original and cloned and given a reference to a node target in the original tree.

The cloned tree is a copy of the original tree.

Return a reference to the same node in the cloned tree.

Note that you are not allowed to change any of the two trees or the target node and the answer must be a reference to a node in the cloned tree.

Example 1:

Input: tree = [7,4,3,null,null,6,19], target = 3
Output: 3
Explanation: In all examples the original and cloned trees are shown. The target node is a green node from the original tree. The answer is the yellow node from the cloned tree.

Example 2:

Input: tree = [7], target =  7
Output: 7

Example 3:

Input: tree = [8,null,6,null,5,null,4,null,3,null,2,null,1], target = 4

Output: 4

Constraints:

The number of nodes in the tree is in the range [1, 104].
The values of the nodes of the tree are unique.
target node is a node from the original tree and is not null.

Follow up: Could you solve the problem if repeated values on the tree are allowed?
```

## Observations

1. **Problem Understanding**: We have two identical binary trees - `original` and `cloned`. We're given a reference to a node `target` in the original tree and need to find the corresponding node in the cloned tree.

2. **Key Constraint**: The values of nodes are unique (in the basic version). This makes the problem straightforward since we can simply search for a node with the same value as the target.

3. **Tree Structure**: Both trees have identical structure and values, so the corresponding node will be at the same relative position in both trees.

4. **Search Strategy**: We can use any tree traversal (DFS or BFS) to find the node with the target value in the cloned tree.

5. **Follow-up Challenge**: If repeated values are allowed, we need to track the path/position of the target node in the original tree and follow the same path in the cloned tree.

## Solution

### Approach 1: Simple Value Search (When values are unique)

Since node values are unique, we can simply traverse the cloned tree and find the node with the same value as the target.

**Algorithm:**
1. Perform DFS/BFS on the cloned tree
2. For each node, check if its value equals target's value
3. Return the matching node

**Time Complexity:** O(n) where n is the number of nodes
**Space Complexity:** O(h) where h is the height of the tree (recursion stack)

```cpp
TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
    if (!cloned) return nullptr;
    if (cloned->val == target->val) return cloned;
    
    TreeNode* left = getTargetCopy(original, cloned->left, target);
    if (left) return left;
    
    return getTargetCopy(original, cloned->right, target);
}
```

### Approach 2: Path Tracking (For repeated values)

When values can be repeated, we need to track the path to the target in the original tree and follow the same path in the cloned tree.

**Algorithm:**
1. Find the path from root to target in the original tree
2. Follow the same path in the cloned tree to reach the corresponding node

**Time Complexity:** O(n)
**Space Complexity:** O(h)

```cpp
TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
    if (!original) return nullptr;
    if (original == target) return cloned;
    
    TreeNode* left = getTargetCopy(original->left, cloned->left, target);
    if (left) return left;
    
    return getTargetCopy(original->right, cloned->right, target);
}
```

### Approach 3: Iterative with Stack

```cpp
TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
    stack<pair<TreeNode*, TreeNode*>> st;
    st.push({original, cloned});
    
    while (!st.empty()) {
        auto [orig, clone] = st.top();
        st.pop();
        
        if (orig == target) return clone;
        
        if (orig->right) st.push({orig->right, clone->right});
        if (orig->left) st.push({orig->left, clone->left});
    }
    
    return nullptr;
}
```

### Key Insights

1. **Reference vs Value**: The problem asks for a reference to the node, not just the value. This is important when values can be repeated.

2. **Parallel Traversal**: We traverse both trees simultaneously, maintaining the correspondence between nodes at the same position.

3. **Early Termination**: Once we find the target, we can immediately return without exploring the rest of the tree.

## Tags

- Binary Tree
- Tree Traversal
- DFS
- BFS
- Recursion
- Reference Tracking

