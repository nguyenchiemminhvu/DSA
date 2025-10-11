## Problem

https://leetcode.com/problems/binary-tree-tilt/

```
Given the root of a binary tree, return the sum of every tree node's tilt.

The tilt of a tree node is the absolute difference between the sum of all left subtree node values and all right subtree node values. If a node does not have a left child, then the sum of the left subtree node values is treated as 0. The rule is similar if the node does not have a right child.

Example 1:

Input: root = [1,2,3]
Output: 1
Explanation: 
Tilt of node 2 : |0-0| = 0 (no children)
Tilt of node 3 : |0-0| = 0 (no children)
Tilt of node 1 : |2-3| = 1 (left subtree is just left child, so sum is 2; right subtree is just right child, so sum is 3)
Sum of every tilt : 0 + 0 + 1 = 1

Example 2:

Input: root = [4,2,9,3,5,null,7]
Output: 15
Explanation: 
Tilt of node 3 : |0-0| = 0 (no children)
Tilt of node 5 : |0-0| = 0 (no children)
Tilt of node 7 : |0-0| = 0 (no children)
Tilt of node 2 : |3-5| = 2 (left subtree is just left child, so sum is 3; right subtree is just right child, so sum is 5)
Tilt of node 9 : |0-7| = 7 (no left child, so sum is 0; right subtree is just right child, so sum is 7)
Tilt of node 4 : |(3+5+2)-(9+7)| = |10-16| = 6 (left subtree values are 3, 5, and 2, which sums to 10; right subtree values are 9 and 7, which sums to 16)
Sum of every tilt : 0 + 0 + 0 + 2 + 7 + 6 = 15

Example 3:

Input: root = [21,7,14,1,1,2,2,3,3]
Output: 9

Constraints:

The number of nodes in the tree is in the range [0, 104].
-1000 <= Node.val <= 1000
```

## Observations

1. **Problem Understanding**: We need to find the sum of all node tilts in a binary tree, where tilt is the absolute difference between the sum of left subtree values and right subtree values.

2. **Key Insight**: The solution transforms the tree twice:
   - First: Convert each node's value to the sum of its entire subtree
   - Second: Convert each node's value to its tilt value
   - Third: Sum all tilts by converting the tilt tree back to sum tree

3. **Tree Transformations**:
   - `build_sum_tree()`: Recursively updates each node to contain the sum of all nodes in its subtree
   - `build_tilt_tree()`: Uses the sum tree to calculate tilt for each node (absolute difference between left and right subtree sums)
   - Final `build_sum_tree()`: Converts the tilt tree to get the total sum of all tilts

4. **Example Walkthrough** for `[1,2,3]`:
   - Original: `1(left:2, right:3)`
   - After first sum_tree: `6(left:2, right:3)` (1+2+3=6 at root)
   - After tilt_tree: `1(left:0, right:0)` (|2-3|=1 at root, leaves have no children so tilt=0)
   - After final sum_tree: `1` (sum of all tilts: 0+0+1=1)

5. **Time Complexity**: O(3n) = O(n) - three tree traversals
6. **Space Complexity**: O(h) where h is tree height due to recursion stack
7. **Edge Cases**: Empty tree returns 0, single node has tilt 0

## Solution

The solution uses a three-phase approach:

### Phase 1: Build Sum Tree

- **Purpose**: Transform each node to contain the sum of all values in its subtree
- **Process**: Post-order traversal, adding left and right subtree sums to current node's value

### Phase 2: Build Tilt Tree

- **Purpose**: Convert sum tree to tilt tree where each node contains its tilt value
- **Process**: Pre-order traversal, calculating absolute difference between left and right subtree sums

### Phase 3: Sum All Tilts
- Apply `build_sum_tree()` again to the tilt tree
- Root now contains the sum of all tilt values

**Alternative Approach**: A more efficient single-pass solution would calculate tilts during one traversal and accumulate the sum using a global variable, avoiding multiple tree modifications.

## Tags

binary tree