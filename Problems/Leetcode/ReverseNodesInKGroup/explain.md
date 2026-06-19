## Problem

https://leetcode.com/problems/reverse-nodes-in-k-group/description

```
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of
nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [2,1,4,3,5]

Example 2:
Input: head = [1,2,3,4,5], k = 3
Output: [3,2,1,4,5]

Constraints:
- The number of nodes in the list is n.
- 1 <= k <= n <= 5000
- 0 <= Node.val <= 1000

Follow-up: Can you solve the problem in O(1) extra memory space?
```

## Observations

1. **Group-by-Group Processing**: The list must be processed in windows of exactly `k` nodes. Each window is reversed independently before being linked to the next.

2. **Remainder Rule**: If fewer than `k` nodes remain at the tail, they must be left in their original order. This means we must verify that at least `k` nodes exist before committing to a reversal.

3. **Recursive Decomposition**: The problem has a natural recursive structure:  
   *Reverse the first k nodes, then append the result of recursively reversing the rest.*  
   This cleanly separates each group without needing to manage complex pointer bookkeeping across groups.

4. **Connecting Groups via Reversal**: A clever trick is to initialize the `left` pointer of the reversal loop to `next_head` (the head returned by the recursive call). Because we prepend each node of the current group to `left`, the reversed group is automatically stitched onto the already-processed tail — no extra connection step needed.

5. **Pointer Advancement Check**: Advancing a pointer exactly `k` steps from a dummy node (which sits before `head`) lands on the `k`-th node of the current group. If the pointer becomes `None` before all `k` steps are completed, we know the remaining nodes are fewer than `k` and must be returned unchanged.

6. **Space Complexity Trade-off**: The recursive approach uses O(n/k) stack space for the call frames. The follow-up asks for O(1) extra space, which requires an iterative solution.

## Solution

### Approach: Recursive Group Reversal

**Algorithm:**

1. **Base case**: if `k == 1`, no reversal is needed — return `head` immediately.

2. **Advance `k` steps**: starting from a dummy node placed before `head`, move pointer `p` exactly `k` times. If `p` becomes `None` before completing all `k` steps, fewer than `k` nodes remain, so return `head` as-is.

3. **Recurse on the rest**: call `reverseKGroup(p.next, k)`. This returns `next_head`, the correctly processed head of everything after the current `k`-node group.

4. **Isolate the current group**: set `p.next = None` to sever the current group from the rest of the list.

5. **Reverse the current group**: use a standard prepend-reversal loop. Initialize `left = next_head` so that after reversing, the tail of the current group is already pointing to the processed remainder of the list.

6. **Return the new head**: after the loop, `left` points to the last node we prepended, which is the original `k`-th node — the new head of this reversed group.

**Walkthrough** — `head = [1,2,3,4,5]`, `k = 2`:

```
reverseKGroup([1,2,3,4,5], k=2)
  └─ advance p 2 steps → p = node(2)
  └─ recurse: reverseKGroup([3,4,5], k=2)
       └─ advance p 2 steps → p = node(4)
       └─ recurse: reverseKGroup([5], k=2)
            └─ advance p: p becomes None (only 1 node) → return [5]
       └─ next_head = [5], isolate group [3→4]
       └─ reverse [3→4] prepending onto [5]:
            left=5, cur=3 → 3→5, left=3→5, cur=4
            left=3→5, cur=4 → 4→3→5, left=4→3→5, cur=None
       └─ return [4→3→5]
  └─ next_head = [4→3→5], isolate group [1→2]
  └─ reverse [1→2] prepending onto [4→3→5]:
       left=4→3→5, cur=1 → 1→4→3→5, left=1→4→3→5, cur=2
       left=1→4→3→5, cur=2 → 2→1→4→3→5, left=2→1→4→3→5, cur=None
  └─ return [2→1→4→3→5]  ✓
```

**Code:**
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        if k == 1:
            return head
        
        dummy = ListNode(0, head)
        p = dummy
        temp_k = k
        while temp_k > 0 and p:
            p = p.next
            temp_k -= 1
        
        if not p or temp_k > 0:
            return head
        
        next_head = self.reverseKGroup(p.next, k)
        p.next = None
        
        # reverse from head to p, prepending onto next_head
        left, cur, right = next_head, head, None
        while cur:
            right = cur.next
            cur.next = left
            left = cur
            cur = right
        
        return left
```

## Complexity

**Time Complexity**: `O(n)` — every node is visited exactly once across all recursive calls.

**Space Complexity**: `O(n/k)` — the recursion depth equals the number of groups. For the O(1) space follow-up, an iterative solution is required.

## Tags

`Linked List`, `Recursion`, `Two Pointers`
