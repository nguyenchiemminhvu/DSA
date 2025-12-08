## Problem

https://leetcode.com/problems/merge-in-between-linked-lists/description/

You are given two linked lists: `list1` and `list2` of sizes `n` and `m` respectively.

Remove `list1`'s nodes from the `a`-th node to the `b`-th node, and put `list2` in their place.

**Example 1:**
```
Input: list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [10,1,13,1000000,1000001,1000002,5]
Explanation: We remove nodes at positions 3 and 4 (values 6 and 9) and insert list2 in their place.
```

**Example 2:**
```
Input: list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
Output: [0,1,1000000,1000001,1000002,1000003,1000004,6]
Explanation: Remove nodes at positions 2-5 (values 2,3,4,5) and insert list2.
```

**Constraints:**
- 3 <= list1.length <= 10^4
- 1 <= a <= b < list1.length - 1
- 1 <= list2.length <= 10^4

## Observations

1. **Index-based Node Removal**: We need to remove nodes from index `a` to index `b` (inclusive, 0-indexed).

2. **Four Key Pointers**:
   - Node before position `a` (to connect to `list2`)
   - Node at position `a` (first node to remove)
   - Node at position `b` (last node to remove)
   - Node after position `b` (to connect after `list2`)

3. **Connection Strategy**:
   - Connect node at `(a-1)` → head of `list2`
   - Connect tail of `list2` → node at `(b+1)`

4. **Edge Cases**:
   - The constraints guarantee `a >= 1` and `b < list1.length - 1`, so we always have nodes before and after the removed section
   - No need to handle empty lists or boundary cases

5. **Traversal Efficiency**: 
   - Use a single pass to find the node before position `a`
   - Continue from there to find the node after position `b`
   - Traverse `list2` to find its tail

## Solution

### Approach: Pointer Manipulation

**Algorithm:**

1. **Find Node Before Position `a`**:
   - Create a dummy node pointing to `list1` for easier manipulation
   - Move `a` steps to reach the node just before the removal section
   - This node's `next` will be connected to `list2`

2. **Find Node After Position `b`**:
   - From the node before position `a`, continue `(b - a + 2)` more steps
   - This brings us to the node after position `b`
   - Save this node to reconnect later

3. **Insert `list2`**:
   - Connect the node before position `a` to the head of `list2`
   - Traverse to the tail of `list2`
   - Connect the tail of `list2` to the node after position `b`

4. **Return Result**: Return the original `list1` head

**Visual Example (Example 1):**

```
Initial: list1 = [10,1,13,6,9,5], a=3, b=4, list2=[1000000,1000001,1000002]

Positions:    0   1   2   3  4  5
list1:      [10, 1, 13, 6, 9, 5]
                      ↑      ↑
                    a-1      b+1

After step 1: p points to node with value 13 (position 2)
After step 2: pp points to node with value 5 (position 5)
After step 3: 13 → 1000000 → 1000001 → 1000002
After step 5: 1000002 → 5

Result: [10, 1, 13, 1000000, 1000001, 1000002, 5]
```

**Complexity Analysis:**

- **Time Complexity**: O(n + m)
  - O(a) to find node before position `a`
  - O(b - a) to find node after position `b`
  - O(m) to traverse `list2` to its tail
  - Total: O(b + m) ≈ O(n + m) where n is length of list1

- **Space Complexity**: O(1)
  - Only using a constant number of pointers
  - No additional data structures

**Key Insights:**

1. **Dummy Node Trick**: Using a dummy node simplifies edge cases when manipulating the head
2. **Simultaneous Decrementation**: Decrementing both `a` and `b` together maintains the relative distance
3. **Pointer Reuse**: Reusing pointer `p` to traverse `list2` is memory efficient
4. **No Node Deletion**: We don't actually delete nodes; we just skip over them by changing pointers

# Tags

`Linked List` `Pointer Manipulation` `Two Pointers`