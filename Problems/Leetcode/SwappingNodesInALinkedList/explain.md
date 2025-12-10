## Problem

https://leetcode.com/problems/swapping-nodes-in-a-linked-list/description/

```
You are given the head of a linked list, and an integer k.

Return the head of the linked list after swapping the values of the kth node from the beginning 
and the kth node from the end (the list is 1-indexed).

Example 1:
Input: head = [1,2,3,4,5], k = 2
Output: [1,4,3,2,5]

Example 2:
Input: head = [7,9,6,6,7,8,3,0,9,5], k = 5
Output: [7,9,6,6,8,7,3,0,9,5]

Constraints:
- The number of nodes in the list is n.
- 1 <= k <= n <= 10^5
- 0 <= Node.val <= 100
```

## Observations

1. **Understanding the Problem:**
   - We need to swap the VALUES (not the nodes themselves) of two specific nodes
   - The kth node from the beginning and kth node from the end
   - The list uses 1-based indexing (first node is at position 1)

2. **Key Insights:**
   - For a list of length n, the kth node from beginning and kth node from end are:
     - kth from beginning: position k
     - kth from end: position (n - k + 1)
   - Example: In a list of 5 nodes, k=2 means positions 2 and 4 (5-2+1=4)

3. **Challenges:**
   - We don't know the length of the list in advance
   - We need to find both nodes efficiently without multiple passes
   - Need to handle edge cases (single node, k=1, k=n)

4. **Two-Pointer Approach:**
   - Use a clever technique to find both nodes in a single pass
   - First pointer advances k-1 steps to reach the kth node from beginning
   - Use a "runner" technique: when the first pointer reaches position k, start a second pointer from head
   - When the first pointer reaches the end, the second pointer will be at the kth node from end

## Solution

### Algorithm Explanation:

**Step 1: Find the kth node from beginning**
- Move `left` pointer k-1 steps forward from head
- This positions `left` at the kth node from the beginning
- Store this reference as `front` for the next step

**Step 2: Find the kth node from end using two-pointer technique**
- Initialize `right` pointer at head
- Move both `front` and `right` together until `front` reaches the last node
- When `front.next` becomes None, `right` will be at the kth node from the end
- This works because the gap between `front` and the end is k-1 nodes

**Step 3: Swap the values**
- Simply swap `left.val` and `right.val`
- No need to adjust pointers or restructure the list

**Step 4: Return the head**
- The list structure remains the same, only values are swapped

### Complexity Analysis:

- **Time Complexity:** O(n) where n is the number of nodes
  - First loop: O(k) to find kth node from beginning
  - Second loop: O(n-k) to find kth node from end
  - Total: O(k + n-k) = O(n)
  
- **Space Complexity:** O(1)
  - Only uses a constant amount of extra space (3 pointers: left, right, front)
  - No additional data structures needed

### Visualization:

```
Example: head = [1,2,3,4,5], k = 2

Step 1: Move left k-1 times (1 time)
[1, 2, 3, 4, 5]
    ↑
   left (also front)

Step 2: Move front and right together until front.next is None
[1, 2, 3, 4, 5]
    ↑        ↑
   left    front
    
[1, 2, 3, 4, 5]
       ↑     ↑
      right front.next=None
      
Now: left is at node 2, right is at node 4

Step 3: Swap values
[1, 4, 3, 2, 5]
    ↑     ↑
   left right
```

### Why This Works:

The key insight is the **runner technique**:
- When `left` is at position k, it's (n-k) nodes away from the end
- If we start `right` at head and move both pointers together:
  - `front` moves from position k to position n (travels n-k steps)
  - `right` moves from position 1 to position 1+(n-k) = n-k+1
- Position n-k+1 is exactly the kth position from the end!

# Tags

`Linked List` `Two Pointers` `Fast and Slow Pointers` `Runner Technique`

