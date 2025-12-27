## Problem

https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/

Given an array of integers `preorder`, which represents the preorder traversal of a BST (binary search tree), construct the tree and return its root.

**Key Definitions:**
- **BST Property**: For every node, any descendant of `Node.left` has a value strictly less than `Node.val`, and any descendant of `Node.right` has a value strictly greater than `Node.val`
- **Preorder Traversal**: Visits the node first, then traverses left subtree, then right subtree

**Examples:**

Example 1:
```
Input: preorder = [8,5,1,7,10,12]
Output: [8,5,10,1,7,null,12]

Tree structure:
       8
      / \
     5   10
    / \    \
   1   7   12
```

Example 2:
```
Input: preorder = [1,3]
Output: [1,null,3]
```

**Constraints:**
- `1 <= preorder.length <= 100`
- `1 <= preorder[i] <= 1000`
- All values are unique

## Observations

1. **Preorder gives us root first**: The first element in preorder is always the root of the tree

2. **BST insertion property**: Since we have a BST, we can insert elements one by one following BST rules:
   - If value < current node → go left
   - If value > current node → go right
   - Insert when we reach a null position

3. **Simple but not optimal**: While inserting elements sequentially works, it has O(n²) worst case time complexity if the tree becomes skewed

4. **Preorder structure**: In preorder traversal `[root, left_subtree, right_subtree]`:
   - First element is root
   - Elements smaller than root belong to left subtree
   - Elements larger than root belong to right subtree

5. **Alternative approaches exist**: We can use the preorder structure more intelligently with bounds to achieve O(n) time complexity

## Solution

### Approach 1: Sequential BST Insertion (Provided Solution)

**Algorithm:**
1. Create root node with first element of preorder
2. For each remaining element in preorder:
   - Insert it into BST using standard BST insertion
3. Return the root

**Implementation Details:**
```python
def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
    def add_node(root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        # Base case: found insertion point
        if not root:
            return TreeNode(val)
        
        # BST property: smaller values go left
        if root.val > val:
            root.left = add_node(root.left, val)
        # BST property: larger values go right
        elif root.val < val:
            root.right = add_node(root.right, val)
        
        return root
    
    # Create root with first element
    root = TreeNode(preorder[0])
    
    # Insert remaining elements
    for i in range(1, len(preorder)):
        root = add_node(root, preorder[i])
    
    return root
```

**Complexity:**
- **Time**: O(n²) worst case (when tree is skewed), O(n log n) average case
  - We insert n elements
  - Each insertion takes O(h) where h is height
  - Worst case: h = n (skewed tree)
  - Average case: h = log n (balanced tree)
- **Space**: O(h) for recursion stack = O(n) worst case, O(log n) average case

**Pros:**
- Simple and intuitive
- Easy to understand and implement
- Uses standard BST insertion

**Cons:**
- Not optimal time complexity
- Can be slow for large inputs with skewed trees

---

### Approach 2: Optimal Recursive with Bounds (O(n) solution)

**Key Insight**: Use the bounds to determine where each element belongs without searching

**Algorithm:**
1. Use a pointer to track current position in preorder
2. For each recursive call, maintain valid range [min, max]
3. Current element is valid only if it's within the bounds
4. Build left subtree with upper bound = current value
5. Build right subtree with lower bound = current value

**Implementation:**
```python
def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
    self.idx = 0
    
    def build(min_val, max_val):
        # All elements processed or current element out of bounds
        if self.idx >= len(preorder) or not (min_val < preorder[self.idx] < max_val):
            return None
        
        # Current element is the root
        val = preorder[self.idx]
        root = TreeNode(val)
        self.idx += 1
        
        # Left subtree: values between min_val and val
        root.left = build(min_val, val)
        
        # Right subtree: values between val and max_val
        root.right = build(val, max_val)
        
        return root
    
    return build(float('-inf'), float('inf'))
```

**Complexity:**
- **Time**: O(n) - each element is visited exactly once
- **Space**: O(h) for recursion stack = O(n) worst case, O(log n) average case

**Why it's O(n)**: Each element in preorder is consumed exactly once by incrementing `idx`, and we never backtrack or revisit elements.

---

### Comparison

| Approach | Time | Space | Difficulty |
|----------|------|-------|------------|
| Sequential Insertion | O(n²) worst, O(n log n) avg | O(h) | Easy |
| Recursive with Bounds | O(n) | O(h) | Medium |

For interview purposes, both solutions are acceptable. The sequential insertion is easier to explain and code quickly, while the bounds approach shows optimization skills.

# Tags

