## Problem

https://leetcode.com/problems/partition-list/description/

```
Given the head of a linked list and a value x, partition it such that all nodes 
less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

Example 1:
Input: head = [1,4,3,2,5,2], x = 3
Output: [1,2,2,4,3,5]
Explanation: Nodes with values less than 3 (1,2,2) come before nodes >= 3 (4,3,5)

Example 2:
Input: head = [2,1], x = 2
Output: [1,2]

Constraints:
- The number of nodes in the list is in the range [0, 200]
- -100 <= Node.val <= 100
- -200 <= x <= 200
```

## Observations

1. **Two-Partition Problem**: We need to split the linked list into two groups:
   - Nodes with values **less than** x
   - Nodes with values **greater than or equal to** x

2. **Order Preservation**: The relative order within each partition must be maintained. This means we can't use sorting or rearranging - we must keep nodes in their original sequence within each group.

3. **Single Pass Solution**: We can solve this in one traversal by maintaining two separate linked lists and then connecting them.

4. **Edge Cases to Consider**:
   - Empty list (head = null)
   - All nodes less than x
   - All nodes greater than or equal to x
   - Single node list
   - All nodes equal to x

5. **Key Insight**: Use dummy nodes to simplify the creation of two separate lists, avoiding null checks when building the lists.

## Solution

### Approach: Two-Pointer with Dummy Nodes

The solution uses a **two-list approach** where we maintain separate linked lists for nodes less than x and nodes greater than or equal to x.

#### Algorithm Steps:

1. **Create Two Dummy Nodes**:
   - `left`: dummy head for nodes with values < x
   - `right`: dummy head for nodes with values >= x
   - Use pointers `pleft` and `pright` to track the tail of each list

2. **Traverse Original List**:
   - For each node, compare its value with x
   - If `node.val < x`: append to the left list (move `pleft`)
   - If `node.val >= x`: append to the right list (move `pright`)

3. **Handle List Termination**:
   - Set `pleft.next = None` to terminate the left list
   - Set `pright.next = None` to terminate the right list
   - This prevents cycles in the final linked list

4. **Merge Two Lists**:
   - If left list is empty, return the right list
   - Otherwise, connect the tail of the left list to the head of the right list

#### Implementation:

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        # Create dummy nodes for two partitions
        left = ListNode(float('inf'))   # Dummy for nodes < x
        right = ListNode(float('inf'))  # Dummy for nodes >= x
        
        # Pointers to build the two lists
        pleft = left
        pright = right
        
        # Traverse the original list and partition nodes
        while head:
            if head.val < x:
                pleft.next = head
                pleft = pleft.next
            else:
                pright.next = head
                pright = pright.next
            head = head.next
        
        # Terminate both lists to prevent cycles
        pleft.next = None
        pright.next = None
        
        # Merge the two lists
        head = left.next  # Start with the left partition
        if not head:
            # If left partition is empty, use right partition
            head = right.next
        else:
            # Find the tail of left partition and connect to right partition
            while left.next:
                left = left.next
            left.next = right.next
        
        return head
```

#### Complexity Analysis:

- **Time Complexity**: O(n)
  - Single traversal of the linked list
  - Additional traversal to find the tail of the left list (worst case: all nodes < x)
  - Overall: O(n) + O(n) = O(n)

- **Space Complexity**: O(1)
  - Only using a constant number of pointers (left, right, pleft, pright)
  - No additional data structures needed
  - Rearranging existing nodes in-place

#### Example Walkthrough:

**Input**: `head = [1,4,3,2,5,2], x = 3`

1. **Initial State**:
   ```
   left: [inf] → null
   right: [inf] → null
   ```

2. **After Processing Each Node**:
   ```
   Node 1 (< 3): left: [inf] → 1 → null
   Node 4 (≥ 3): right: [inf] → 4 → null
   Node 3 (≥ 3): right: [inf] → 4 → 3 → null
   Node 2 (< 3): left: [inf] → 1 → 2 → null
   Node 5 (≥ 3): right: [inf] → 4 → 3 → 5 → null
   Node 2 (< 3): left: [inf] → 1 → 2 → 2 → null
   ```

3. **After Merging**:
   ```
   Connect: [1 → 2 → 2] → [4 → 3 → 5]
   Output: [1,2,2,4,3,5]
   ```

#### Optimization Note:

The current implementation has a minor inefficiency in the merging step. We can optimize by keeping track of the tail of the left list during the partitioning phase, avoiding the extra traversal:

```python
class Solution:
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        left = ListNode(0)
        right = ListNode(0)
        pleft = left
        pright = right
        
        while head:
            if head.val < x:
                pleft.next = head
                pleft = pleft.next
            else:
                pright.next = head
                pright = pright.next
            head = head.next
        
        # Terminate and merge in one step
        pright.next = None
        pleft.next = right.next
        
        return left.next
```

This optimized version eliminates the need to traverse the left list again to find its tail.

# Tags

`Linked List` `Two Pointers` `Partition` `Medium`

