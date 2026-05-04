## Problem

https://leetcode.com/problems/path-sum-iii/description

Given the root of a binary tree and an integer `targetSum`, return the number of paths where the sum of the values along the path equals `targetSum`.

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).

### Example 1:

```
Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.
```

Tree visualization:
```
        10
       /  \
      5   -3
     / \    \
    3   2   11

Paths with sum 8:
1. 5 -> 3 = 8
2. 5 -> 2 -> 1 (but 1 is not shown, finding: 5 -> 3 = 8)
3. Actually: 10 -> 5 -> 3 = 18 (no), 5 + 3 = 8 (yes), 5 + 2 + 1 (need path), -3 + 11 = 8 (yes)
```

### Example 2:

```
Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: 3
```

### Constraints:

- The number of nodes in the tree is in the range `[0, 1000]`
- $-10^9 \leq \text{Node.val} \leq 10^9$
- $-1000 \leq \text{targetSum} \leq 1000$

## Observations

1. **Path Must Go Downwards**: Paths only travel from parent to child, eliminating backtracking complexity.

2. **Path Can Start Anywhere**: Unlike typical problems, paths don't need to start at the root or end at a leaf - they can start at any node and end at any descendant.

3. **Brute Force Limitation**: A naive DFS approach counting all paths would be $O(n^2)$ - for each node, exploring all downward paths.

4. **Prefix Sum Insight**: We can use the prefix sum technique:
   - If we have a cumulative sum from root to current node: `cur_sum`
   - And we want to find paths ending at current node with sum = `target`
   - Then we need: `cur_sum - prefix_sum = target`
   - Which means: `prefix_sum = cur_sum - target`
   
5. **Key Optimization**: Store a frequency map of all prefix sums encountered on the current path. When we reach a node, check how many times `(cur_sum - target)` appears in the map.

6. **Backtracking Required**: When returning from recursion, we must decrement the prefix sum count to avoid counting paths from other branches.

## Solution

### Approach: Prefix Sum with DFS and Backtracking

The algorithm uses a prefix sum map to track all cumulative sums from the root to each node on the current path.

#### Algorithm:

```python
from collections import defaultdict

class Solution:
    def pathSum(self, root: Optional[TreeNode], target: int) -> int:
        prefix_sum_count = defaultdict(int)
        prefix_sum_count[0] = 1  # Base case: empty path has sum 0
        res = [0]

        def dfs(root: Optional[TreeNode], cur_sum: int):
            if not root:
                return
            
            # Add current node's value to cumulative sum
            cur_sum += root.val
            
            # Check if there's a path ending at current node with target sum
            # If cur_sum - target exists in map, we found valid paths
            res[0] += prefix_sum_count[cur_sum - target]
            
            # Add current sum to the map for future nodes
            prefix_sum_count[cur_sum] += 1
            
            # Explore left and right subtrees
            dfs(root.left, cur_sum)
            dfs(root.right, cur_sum)
            
            # Backtrack: remove current sum from map
            prefix_sum_count[cur_sum] -= 1
        
        dfs(root, 0)
        return res[0]
```

#### Step-by-Step Walkthrough (Example 1):

Given `root = [10,5,-3,3,2,null,11,3,-2,null,1]`, `targetSum = 8`

```
Tree:
        10
       /  \
      5   -3
     / \    \
    3   2   11

1. Start at 10: cur_sum = 10
   - Check if (10-8)=2 exists in map: No
   - Add 10 to map: {0:1, 10:1}

2. Go to 5: cur_sum = 15
   - Check if (15-8)=7 exists: No
   - Add 15: {0:1, 10:1, 15:1}

3. Go to 3: cur_sum = 18
   - Check if (18-8)=10 exists: Yes! Count += 1 ✓
   - Add 18: {0:1, 10:1, 15:1, 18:1}
   - Backtrack: {0:1, 10:1, 15:1}

4. Go to 2: cur_sum = 17
   - Check if (17-8)=9 exists: No
   - Add 17: {0:1, 10:1, 15:1, 17:1}
   - Backtrack: {0:1, 10:1, 15:1}

5. Back to 10, go to -3: cur_sum = 7
   - Check if (7-8)=-1 exists: No
   - Add 7: {0:1, 10:1, 7:1}

6. Go to 11: cur_sum = 18
   - Check if (18-8)=10 exists: Yes! Count += 1 ✓
   - Backtrack

Result: 3 paths found
```

#### Time Complexity:

- **Best/Average Case**: $O(n)$ - Visit each node once, map operations are $O(1)$ on average
- **Space Complexity**: $O(h)$ where $h$ is the height of the tree (recursion stack + map size bounded by path length)

#### Why Backtracking is Essential:

Without decrementing the count on backtrack, prefix sums from one branch would incorrectly count as valid paths in other branches.

# Tags

- **Type**: Binary Tree Traversal, DFS
- **Difficulty**: Medium
- **Key Concept**: Prefix Sum, Hash Map
- **Related Topics**: Tree DP, Path Problems
- **Similar Problems**: Path Sum I & II, Subarray Sum Equals K

