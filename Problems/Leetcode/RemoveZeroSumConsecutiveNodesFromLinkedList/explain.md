## Problem

https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/description/

```
Given the head of a linked list, we repeatedly delete consecutive sequences of nodes that sum to 0 until there are no such sequences.

After doing so, return the head of the final linked list. You may return any such answer.

(Note that in the examples below, all sequences are serializations of ListNode objects.)

Example 1:
Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.

Example 2:
Input: head = [1,2,3,-3,4]
Output: [1,2,4]

Example 3:
Input: head = [1,2,3,-3,-2]
Output: [1]

Constraints:
- The given linked list will contain between 1 and 1000 nodes.
- Each node in the linked list has -1000 <= node.val <= 1000.
```

## Observations

1. **Prefix Sum Pattern**: If two positions in the linked list have the same prefix sum, then all nodes between them sum to zero and should be removed.

2. **Hash Map Approach**: We can use a hash map to store prefix sums and their corresponding nodes. When we encounter a prefix sum that already exists, we know there's a zero-sum sequence between the stored node and current node.

3. **Two-Pass Solution**: 
   - First pass: Calculate prefix sums and store the latest occurrence of each prefix sum
   - Second pass: Use the stored information to skip over zero-sum sequences

4. **Dummy Node**: Using a dummy node simplifies handling edge cases where the head itself might be part of a zero-sum sequence.

5. **Why it works**: If `prefixSum[i] = prefixSum[j]` where `i < j`, then `sum(nodes from i+1 to j) = 0`, so these nodes should be removed.

## Solution

### Approach: Prefix Sum with Hash Map

**Algorithm:**

1. Create a dummy node pointing to the head to handle edge cases
2. **First Pass** - Build the prefix sum map:
   - Traverse the linked list and calculate cumulative prefix sum
   - Store each prefix sum with its corresponding node in a hash map
   - If a prefix sum appears multiple times, only keep the latest occurrence
3. **Second Pass** - Remove zero-sum sequences:
   - Traverse again with prefix sum calculation
   - Use the hash map to jump directly to the node after any zero-sum sequence
   - Link the current node to the next valid node from the map

**Why this works:**
- When we see a prefix sum that we've seen before, everything between the first occurrence and current node sums to zero
- By storing only the latest occurrence in the first pass, we effectively mark the boundaries of the zero-sum sequences to remove
- The second pass reconstructs the list by skipping over these sequences

**Time Complexity:** O(n) - two passes through the linked list
**Space Complexity:** O(n) - hash map storing up to n prefix sums

**Example Walkthrough:** `[1,2,-3,3,1]`

First Pass (building map):
```
Node: 1  -> prefixSum: 1  -> map[1] = node(1)
Node: 2  -> prefixSum: 3  -> map[3] = node(2)
Node: -3 -> prefixSum: 0  -> map[0] = node(-3)
Node: 3  -> prefixSum: 3  -> map[3] = node(3)  (overwrites previous)
Node: 1  -> prefixSum: 4  -> map[4] = node(1)
```

Second Pass (reconstructing):
```
Start: dummy -> prefixSum: 0 -> map[0] points to node(-3), so dummy.next = node(3)
Node: 3 -> prefixSum: 3 -> map[3] points to node(3), so node(3).next = node(1)
Node: 1 -> prefixSum: 4 -> map[4] points to node(1), so node(1).next = null
```

Result: `[3,1]`

# Tags

