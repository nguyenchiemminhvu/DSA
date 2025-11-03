## Problem

https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

```
Given the root of a binary search tree and an integer k, return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

Example 1:

Input: root = [5,3,6,2,4,null,7], k = 9
Output: true

Example 2:

Input: root = [5,3,6,2,4,null,7], k = 28
Output: false

Constraints:

The number of nodes in the tree is in the range [1, 104].
-104 <= Node.val <= 104
root is guaranteed to be a valid binary search tree.
-105 <= k <= 105
```

## Observations

1. **Two Sum Pattern**: This is a variation of the classic Two Sum problem, but applied to a Binary Search Tree instead of an array.

2. **BST Property**: While we have a BST, the solution doesn't leverage the BST property for optimization. Instead, it uses a hash set approach similar to the classic Two Sum problem.

3. **Hash Set Approach**: We can traverse the tree and for each node, check if `k - node.val` exists in our previously seen values. If yes, we found our pair.

4. **Early Termination**: The recursive approach allows for early termination - as soon as we find a valid pair, we can return `True` without exploring the rest of the tree.

5. **Traversal Order**: The algorithm uses a modified in-order traversal where:
   - We check if complement exists before adding current value to set
   - We process current node, then recursively check left and right subtrees
   - We propagate `True` immediately when found

6. **Time vs Space Trade-off**: This approach prioritizes simplicity and early termination over the potential BST-specific optimizations (like two-pointer technique on in-order traversal).

## Solution

1. **Base Case**: If current node is `None`, return `False` (no pair found in this path).

2. **Complement Check**: Before processing the current node, check if `k - root.val` exists in our set `d`. If it does, we found a valid pair, return `True`.

3. **Add Current Value**: Add the current node's value to our set for future complement checks.

4. **Recursive Search**: Recursively search left and right subtrees. If either returns `True`, propagate it immediately.

5. **Return False**: If no pair is found in current subtree, return `False`.

**Key Insights:**

- **Order Independence**: Unlike pure in-order traversal, this approach checks for complement before adding to set, allowing it to find pairs regardless of which node is visited first.

- **Early Return**: The `if inorder(root.left, d): return True` pattern ensures we stop as soon as a pair is found.

- **Set Persistence**: The same set `d` is passed throughout the recursion, accumulating all visited values.

**Complexity Analysis:**
- **Time Complexity**: O(n) where n is the number of nodes. We visit each node at most once.
- **Space Complexity**: O(n) for the hash set storing node values + O(h) for recursion stack where h is tree height.

**Alternative BST-Specific Approach:**
While this solution works efficiently, we could also:
1. Perform in-order traversal to get sorted array: O(n)
2. Use two pointers on sorted array: O(n)
This would also be O(n) time but might be slightly more complex to implement.

## Tags

binary search tree, hash set, two sum, tree traversal, recursion

