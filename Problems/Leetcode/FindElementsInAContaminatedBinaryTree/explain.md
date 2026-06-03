# Problem Description

You are given a binary tree that has been "contaminated," meaning the values of all its nodes have been changed to `-1`. 

The original tree followed these specific rules:
1. `root.val == 0`
2. If a node has a value `x` and a left child, then `node.left.val == 2 * x + 1`
3. If a node has a value `x` and a right child, then `node.right.val == 2 * x + 2`

You need to implement the `FindElements` class:
* `FindElements(TreeNode* root)`: Initializes the object with the contaminated binary tree and recovers the original values of all nodes.
* `bool find(int target)`: Returns `true` if the `target` value exists in the recovered binary tree, and `false` otherwise.

---

# Observations

1. **Deterministic Values**: The value of any node is completely determined by its position in the tree relative to the root. If we know a parent's value is `x`, we can always calculate its children's values directly.
2. **Value Uniqueness**: Every position in this specific binary tree structure generates a unique integer. There are no duplicate values in the tree.
3. **Search Efficiency**: The `find` function will be called up to \(10^4\) times. If we search the tree structure manually for every `find` call, it could result in \(O(N)\) time per query, leading to a Time Limit Exceeded (TLE) error.
4. **Hash Set Optimization**: To achieve \(O(1)\) lookups for the `find` function, we can traverse the tree once during initialization, calculate the correct value for each node, and store these values in a hash set.

---

# Solution Explanation

### 1. Initialization (`__init__`)
* We define a hash set named `self.s` to store all the recovered node values.
* We use a Depth-First Search (DFS) traversal starting from the root node to reconstruct the values.
* The root starts with a value of `0`. 
* When moving to a left child, we pass down the value `val * 2 + 1`.
* When moving to a right child, we pass down the value `val * 2 + 2`.
* As we visit each node, we add its calculated value to our hash set. We must also make sure to pass the updated values correctly down to the children.

### 2. Search (`find`)
* Since all valid recovered values are saved in `self.s`, checking if a target exists simply requires a hash set lookup: `target in self.s`.
* This operation runs in \(O(1)\) average time complexity.

---

# Python 3 Code

```python
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class FindElements:

    def __init__(self, root: Optional[TreeNode]):
        # Hash set to store all recovered values for O(1) lookups
        self.s = set()
        
        # Helper function to perform DFS and recover node values
        def dfs(node: Optional[TreeNode], val: int):
            if not node:
                return
            
            # Store the current recovered value in the set
            self.s.add(val)
            
            # Recursively recover left and right subtrees with their calculated values
            dfs(node.left, val * 2 + 1)
            dfs(node.right, val * 2 + 2)
            
        # Start recovery from the root with an initial value of 0
        dfs(root, 0)

    def find(self, target: int) -> bool:
        # Check if the target exists in our set of recovered values
        return target in self.s

# Your FindElements object will be instantiated and called as such:
# obj = FindElements(root)
# param_1 = obj.find(target)
```

---

# Complexity Analysis

* **Time Complexity**:
  * **Constructor (`__init__`)**: $\mathcal{O}(N)$, where $N$ is the total number of nodes in the binary tree. We visit each node exactly once to recover its value.
  * **`find` function**: $\mathcal{O}(1)$ average time complexity because checking membership in a hash set takes constant time.

* **Space Complexity**: $\mathcal{O}(N)$ to store the recovered node values in the hash set, plus $\mathcal{O}(H)$ for the recursive call stack during DFS, where $H$ is the height of the tree (given as $H \le 20$). Thus, the overall space complexity is dominated by the hash set, which is $\mathcal{O}(N)$.
