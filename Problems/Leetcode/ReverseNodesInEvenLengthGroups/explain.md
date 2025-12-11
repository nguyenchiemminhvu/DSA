## Problem

https://leetcode.com/problems/reverse-nodes-in-even-length-groups/description/

You are given the head of a linked list. The nodes are sequentially assigned to non-empty groups whose lengths form the sequence of natural numbers (1, 2, 3, 4, ...).

**Grouping Rules:**
- Group 1: 1 node
- Group 2: 2 nodes  
- Group 3: 3 nodes
- Group k: k nodes (or remaining nodes if less than k)

**Task:** Reverse the nodes in each group with an **even length**, and return the head of the modified linked list.

**Examples:**

**Example 1:**
- Input: `head = [5,2,6,3,9,1,7,3,8,4]`
- Output: `[5,6,2,3,9,1,4,8,3,7]`
- Explanation:
  - Group 1 (length 1): `[5]` → odd, no reversal
  - Group 2 (length 2): `[2,6]` → even, reverse to `[6,2]`
  - Group 3 (length 3): `[3,9,1]` → odd, no reversal
  - Group 4 (length 4): `[7,3,8,4]` → even, reverse to `[4,8,3,7]`

**Example 2:**
- Input: `head = [1,1,0,6]`
- Output: `[1,0,1,6]`
- Groups: `[1]`, `[1,0]` (reversed), `[6]`

**Example 3:**
- Input: `head = [1,1,0,6,5]`
- Output: `[1,0,1,5,6]`
- Groups: `[1]`, `[1,0]` (reversed), `[6,5]` (reversed - last group has only 2 nodes instead of 3)

**Constraints:**
- The number of nodes in the list is in the range `[1, 10^5]`
- `0 <= Node.val <= 10^5`

## Observations

1. **Group Formation Pattern**: Groups follow the natural number sequence: 1, 2, 3, 4, ... The k-th group should contain k nodes, but the last group may contain fewer nodes if the list ends.

2. **Even Length Detection**: We need to identify which groups have even lengths. Note that the actual length of a group matters, not the expected length (especially for the last group).

3. **Reversal Requirement**: Only groups with even lengths need to be reversed. Odd-length groups remain unchanged.

4. **Last Group Special Case**: The last group may have fewer nodes than expected. For example, if we expect a group of size 5 but only 2 nodes remain, the group size is 2 (even), so it should be reversed.

5. **Linked List Manipulation**: We need to:
   - Split the list into groups
   - Reverse each even-length group
   - Reconnect all groups to form the final result

## Solution

### Approach: Split, Reverse, Reconnect

**Strategy:**
1. **Split into Groups**: Traverse the linked list and split it into separate groups following the natural number sequence
2. **Count and Reverse**: For each group, count its actual length. If the length is even, reverse the group
3. **Reconnect**: Connect all groups back together in order

**Algorithm Steps:**

**Step 1: Split the list into groups**
- Use a counter `n` starting from 1 to track the expected group size
- For each group, try to collect `n` nodes
- If we reach the end of the list before collecting `n` nodes, that's the last group
- Store each group's head in an array

**Step 2: Identify and reverse even-length groups**
- For each group in the array:
  - Count the actual number of nodes in the group
  - If the count is even, reverse the entire group
  - Update the array with the new head after reversal

**Step 3: Reconnect all groups**
- Iterate through the array of group heads
- Connect the tail of each group to the head of the next group
- Return the head of the first group

**Implementation Details:**

```python
def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
    # Helper function to reverse a linked list
    def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
        back = None
        cur = head
        while cur:
            front = cur.next
            cur.next = back
            back = cur
            cur = front
        return back
```

**Phase 1: Split into groups**
```python
    arr = []
    p = head
    n = 1  # Expected group size
    
    while p:
        count = 1
        phead = p  # Head of current group
        
        # Try to collect n nodes for this group
        while p and count < n:
            count += 1
            p = p.next
        
        # If reached end or group is smaller than expected
        if not p or count < n:
            arr.append(phead)
            break
        else:
            # Disconnect this group from the rest
            temp = p
            p = p.next
            temp.next = None
            arr.append(phead)
        
        n += 1  # Next group should be larger
```

**Phase 2: Reverse even-length groups**
```python
    for i in range(len(arr)):
        p = arr[i]
        count = 0
        
        # Count actual nodes in this group
        while p:
            count += 1
            p = p.next
        
        # Reverse if even length
        if arr[i] and count % 2 == 0:
            p = reverse_list(arr[i])
            arr[i] = p  # Update with new head
```

**Phase 3: Reconnect groups**
```python
    head = arr[0]
    
    for i in range(0, len(arr) - 1):
        p = arr[i]
        # Find tail of current group
        while p.next:
            p = p.next
        # Connect to next group
        p.next = arr[i + 1]
    
    return head
```

**Complexity Analysis:**

- **Time Complexity**: O(n) where n is the number of nodes
  - First pass: O(n) to split into groups
  - Second pass: O(n) to count and reverse (each node visited once)
  - Third pass: O(n) to reconnect (each node visited once)
  - Total: O(n)

- **Space Complexity**: O(√n)
  - The array stores group heads. With groups of size 1, 2, 3, ..., k, we have k groups where 1+2+...+k ≈ n
  - This gives k ≈ √(2n), so O(√n) space

**Key Insights:**

1. **Group Boundary Detection**: Carefully handle the case where the list ends mid-group
2. **Two-Pass Counting**: First split groups, then count and reverse (cleaner than trying to do everything in one pass)
3. **Disconnection is Key**: When splitting groups, disconnect them (`temp.next = None`) to avoid issues during reversal
4. **Reconnection Logic**: Find the tail of each group to connect to the next group's head

# Tags

`Linked List` `Two Pointers` `Simulation`
