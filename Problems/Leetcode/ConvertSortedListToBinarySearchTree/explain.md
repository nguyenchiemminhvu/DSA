## Problem

https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/description/

```
Given the head of a singly linked list where elements are sorted in ascending order, 
convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree in which the depth of the two subtrees 
of every node never differs by more than one.

Example 1:
Input: head = [-10,-3,0,5,9]
Output: [0,-3,9,-10,null,5]
Explanation: One possible answer is [0,-3,9,-10,null,5], which represents a height-balanced BST.
       0
      / \
    -3   9
    /   /
  -10  5

Example 2:
Input: head = []
Output: []

Constraints:
- The number of nodes in head is in the range [0, 2 * 10^4]
- -10^5 <= Node.val <= 10^5
```

## Observations

1. **Sorted Input Property**: The linked list is already sorted in ascending order, which is perfect for BST construction since an in-order traversal of a BST yields sorted values.

2. **Height-Balanced Requirement**: We need to ensure the tree is balanced, meaning we should choose the middle element as the root to minimize height differences between left and right subtrees.

3. **Finding Middle Element**: Unlike arrays where we can access the middle element in O(1), finding the middle of a linked list requires traversal. We can use the **slow-fast pointer technique**.

4. **Recursive Structure**: The problem has a natural recursive structure:
   - Find the middle node → make it the root
   - Recursively build left subtree from left half
   - Recursively build right subtree from right half

5. **List Partitioning**: We need to split the list into three parts: left half, middle node, and right half.

6. **Base Cases**:
   - Empty list → return None
   - Single node → return TreeNode with that value

## Solution

### Approach: Divide and Conquer with Slow-Fast Pointers

**Algorithm:**

1. **Find Middle Node** using slow-fast pointer technique:
   - `slow` pointer moves one step at a time
   - `fast` pointer moves two steps at a time
   - Keep track of `prev` (node before `slow`)
   - When `fast` reaches the end, `slow` is at the middle

2. **Split the List**:
   - Set `prev.next = None` to disconnect left half from middle
   - Left half: from `head` to `prev`
   - Middle: `slow`
   - Right half: from `slow.next` onwards

3. **Build Tree Recursively**:
   - Create root node with middle value
   - Recursively build left subtree from left half
   - Recursively build right subtree from right half

**Implementation:**

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:
        # Base case: empty list
        if not head:
            return None
        
        # Base case: single node
        if not head.next:
            return TreeNode(head.val)
        
        # Find middle node using slow-fast pointers
        slow = fast = head
        prev = None
        
        while fast and fast.next:
            prev = slow           # Track node before slow
            slow = slow.next      # Move slow one step
            fast = fast.next.next # Move fast two steps
        
        # slow is now at middle
        mid = slow
        
        # Disconnect left half from middle
        prev.next = None
        
        # Create root with middle value
        root = TreeNode(mid.val)
        
        # Recursively build left and right subtrees
        root.left = self.sortedListToBST(head)      # Left half
        root.right = self.sortedListToBST(mid.next) # Right half
        
        return root
```

**How It Works - Example Walkthrough:**

```
Linked List: -10 → -3 → 0 → 5 → 9

Step 1: Find middle (0)
  slow starts at -10, fast at -10
  Iteration 1: prev=None, slow=-10, fast=-3
  Iteration 2: prev=-10, slow=-3, fast=0
  Iteration 3: prev=-3, slow=0, fast=5
  Iteration 4: prev=0, slow=5, fast=9
  Iteration 5: prev=5, slow=9, fast=None (end)
  Wait, let me trace again...
  
Actually with the loop condition:
  Initial: slow=-10, fast=-10, prev=None
  Loop 1: prev=-10, slow=-3, fast=0
  Loop 2: prev=-3, slow=0, fast=5
  Loop 3: fast.next is 9.next=None, so loop continues
          prev=0, slow=5, fast=None
  Loop ends (fast.next is None)
  
Actually the middle finding works like this for [-10,-3,0,5,9]:
  Initial: slow=-10, fast=-10, prev=None
  Iteration 1: prev=-10, slow=-3, fast=0
  Iteration 2: prev=-3, slow=0, fast=5
  Iteration 3: fast.next exists (9), so: prev=0, slow=5, fast.next.next=None
  Loop ends
  
So mid=0 (which is correct for balanced BST)

After split:
  Left: -10 → -3 (prev.next = None disconnects)
  Middle: 0
  Right: 5 → 9

       0
      / \
   [?]   [?]

Step 2: Recursively process left half [-10, -3]
  Middle: -3
  Left: -10
  Right: None
  
      -3
     /
   -10

Step 3: Recursively process right half [5, 9]
  Middle: 9
  Left: 5
  Right: None
  
      9
     /
    5

Final Result:
       0
      / \
    -3   9
    /   /
  -10  5
```

**Complexity Analysis:**

- **Time Complexity**: O(n log n)
  - Finding middle takes O(n) for each recursive call
  - Tree has O(log n) levels (balanced tree)
  - Each level processes all n nodes in total
  - Total: O(n log n)

- **Space Complexity**: O(log n)
  - Recursion stack depth for a balanced tree
  - Not counting the output tree itself

**Alternative Approach: Convert to Array First (O(n) time)**

```python
class Solution:
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:
        # Convert linked list to array - O(n)
        values = []
        current = head
        while current:
            values.append(current.val)
            current = current.next
        
        # Build BST from array - O(n)
        def buildBST(left, right):
            if left > right:
                return None
            
            mid = (left + right) // 2
            root = TreeNode(values[mid])
            root.left = buildBST(left, mid - 1)
            root.right = buildBST(mid + 1, right)
            return root
        
        return buildBST(0, len(values) - 1)
```

Time: O(n), Space: O(n) - trades space for better time complexity.

**Key Insights:**

1. **Slow-Fast Pointer Technique**: Essential for finding the middle of a linked list in one pass
2. **Why middle element as root**: Ensures balanced tree by having equal (or nearly equal) nodes on both sides
3. **List disconnection**: Setting `prev.next = None` is crucial to properly split the list
4. **For even-length lists**: The algorithm picks the second middle element, which is fine for balance

# Tags

`Linked List` `Binary Search Tree` `Divide and Conquer` `Two Pointers` `Recursion` `Tree Construction`

