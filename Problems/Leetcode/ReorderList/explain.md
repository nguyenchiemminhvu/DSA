## Problem

https://leetcode.com/problems/reorder-list/description/

You are given the head of a singly linked-list. The list can be represented as:

```
L0 → L1 → … → Ln - 1 → Ln
```

Reorder the list to be on the following form:

```
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
```

You may not modify the values in the list's nodes. Only nodes themselves may be changed.

**Example 1:**
```
Input: head = [1,2,3,4]
Output: [1,4,2,3]
```

**Example 2:**
```
Input: head = [1,2,3,4,5]
Output: [1,5,2,4,3]
```

**Constraints:**
- The number of nodes in the list is in the range `[1, 5 * 10^4]`
- `1 <= Node.val <= 1000`

## Observations

1. **Pattern Recognition**: The reordering pattern interleaves nodes from the beginning and end of the list, working towards the middle.

2. **In-place Requirement**: We cannot modify node values, only rearrange the pointers. This means we need to manipulate the `next` pointers.

3. **Three-Step Approach**:
   - Find the middle of the linked list
   - Reverse the second half of the list
   - Merge the two halves by alternating nodes

4. **Finding the Middle**: Using the slow/fast pointer technique (Floyd's algorithm), when fast reaches the end, slow will be at the middle.

5. **Edge Cases**: 
   - Empty list or single node → no reordering needed
   - Even vs odd length lists → handled by the merging logic

## Solution

**Algorithm:**

1. **Find Middle (Slow-Fast Pointers)**:
   - Use two pointers: `slow` and `fast`, both starting at `head`
   - Move `slow` one step and `fast` two steps at a time
   - When `fast` reaches the end, `slow` is at the middle
   - This splits the list into two halves

2. **Reverse Second Half**:
   - Starting from `slow`, reverse the second half of the list
   - Use three pointers: `prev`, `cur`, and `nxt`
   - Standard linked list reversal technique

3. **Merge Two Halves**:
   - Use two pointers: `p1` (first half) and `p2` (reversed second half)
   - Alternate connections: `p1 → p2 → p1.next → p2.next → ...`
   - Continue until `p2.next` is `None`

**Visualization:**

Original: `1 → 2 → 3 → 4 → 5`

Step 1 - Find middle:
```
1 → 2 → 3 → 4 → 5
        ↑
      slow
```

Step 2 - Reverse second half:
```
First half:  1 → 2 → 3
Second half: 5 → 4 → 3 (reversed from 3 → 4 → 5)
```

Step 3 - Merge:
```
1 → 5 → 2 → 4 → 3
```

- **Time Complexity**: O(n)
  - Finding middle: O(n/2)
  - Reversing second half: O(n/2)
  - Merging: O(n/2)
  - Total: O(n)

- **Space Complexity**: O(1)
  - Only using a constant number of pointers
  - No extra data structures

**Key Points:**

1. The condition `while p2.next:` in the merge step is crucial:
   - For even-length lists: both halves have equal nodes, stops when second half is exhausted
   - For odd-length lists: first half has one extra node (the middle), which naturally stays at the end

2. We don't need to worry about the last node of the first half pointing to the middle node of the original list, because:
   - For even lists: the connection is properly updated
   - For odd lists: the middle node ends up at the correct position

3. This is a classic example of combining multiple linked list techniques in one problem.

# Tags

`Linked List` `Two Pointers` `Fast-Slow Pointers` `Reverse Linked List` `In-place`

