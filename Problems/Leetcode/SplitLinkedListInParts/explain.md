## Problem

https://leetcode.com/problems/split-linked-list-in-parts/description/

Given the head of a singly linked list and an integer `k`, split the linked list into `k` consecutive linked list parts.

The length of each part should be as equal as possible: no two parts should have a size differing by more than one. This may lead to some parts being null.

The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have a size greater than or equal to parts occurring later.

Return an array of the `k` parts.

**Example 1:**
```
Input: head = [1,2,3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The first element output[0] has output[0].val = 1, output[0].next = null.
The last element output[4] is null, but its string representation as a ListNode is [].
```

**Example 2:**
```
Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
Output: [[1,2,3,4],[5,6,7],[8,9,10]]
Explanation:
The input has been split into consecutive parts with size difference at most 1, and earlier parts are a larger size than the later parts.
```

**Constraints:**
- The number of nodes in the list is in the range `[0, 1000]`.
- `0 <= Node.val <= 1000`
- `1 <= k <= 50`

## Observations

1. **Calculate List Length**: First, we need to count the total number of nodes in the linked list.

2. **Distribution Strategy**:
   - Base size: `n // k` nodes per part
   - Remainder: `n % k` parts will get one extra node
   - The first `n % k` parts should have size `(n // k) + 1`
   - The remaining parts should have size `n // k`

3. **Key Insight**: We need to split the list in-place by breaking links, not by creating new nodes with copied values.

4. **Edge Cases**:
   - If `k > n`, some parts will be `null`
   - If `k = 1`, the entire list is one part
   - If `head` is `null`, all parts are `null`

## Solution

### Initial Approach (Array-based - Not Optimal)

The provided solution converts the linked list to an array, creates parts, and reconstructs linked lists. This works but is inefficient.

**Issues:**
- **Space Complexity**: O(n) extra space for the array
- **Time Complexity**: O(n) for multiple passes (list→array, filling parts, array→lists)
- **Unnecessary Work**: Creating new ListNode objects instead of reusing existing ones

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        arr = []
        while head:
            arr.append(head.val)
            head = head.next
        n = len(arr)

        parts = [[0] * (n // k) for i in range(k)]
        for i in range(n % k):
            parts[i].append(0)

        # fill parts
        ip = 0
        ipp = 0
        for val in arr:
            while not parts[ip] or ipp >= len(parts[ip]):
                ip += 1
                ipp = 0
            if parts[ip] and ipp < len(parts[ip]):
                parts[ip][ipp] = val
                ipp += 1
        
        res = []
        for part in parts:
            head = ListNode(0)
            p = head
            for val in part:
                p.next = ListNode(val)
                p = p.next
            res.append(head.next)
        return res
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n) - for the array and parts

### Optimized Approach (In-Place Splitting)

The optimal solution splits the linked list in-place by breaking the links between nodes.

**Algorithm:**
1. Count the total number of nodes `n`
2. Calculate:
   - Base size: `base_size = n // k`
   - Extra nodes: `extra = n % k`
3. For each of the `k` parts:
   - Determine part size: `part_size = base_size + (1 if i < extra else 0)`
   - Traverse `part_size - 1` nodes
   - Save the current head
   - Break the link to create the part
   - Move to the next part

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def splitListToParts(self, head: Optional[ListNode], k: int) -> List[Optional[ListNode]]:
        # Step 1: Count the total number of nodes
        n = 0
        curr = head
        while curr:
            n += 1
            curr = curr.next
        
        # Step 2: Calculate base size and extra nodes
        base_size = n // k  # Minimum size for each part
        extra = n % k       # Number of parts that get one extra node
        
        # Step 3: Split the list into k parts
        result = []
        curr = head
        
        for i in range(k):
            # Determine the size of current part
            part_size = base_size + (1 if i < extra else 0)
            
            # Save the head of current part
            part_head = curr
            
            # Traverse to the end of current part
            for j in range(part_size - 1):
                if curr:
                    curr = curr.next
            
            # Break the link to create the part
            if curr:
                next_part = curr.next
                curr.next = None
                curr = next_part
            
            result.append(part_head)
        
        return result
```

**Time Complexity**: O(n) - Single pass to count + single pass to split  
**Space Complexity**: O(1) - Only the result array (which is required output)

### Why This is Better:

1. **No Extra Space**: We reuse existing nodes instead of creating new ones
2. **Single Pass Split**: After counting, we split in one pass
3. **In-Place**: We modify the original list by breaking links
4. **Cleaner Logic**: Direct calculation of part sizes without complex indexing

### Example Walkthrough:

**Example: head = [1,2,3,4,5,6,7,8,9,10], k = 3**

1. Count: `n = 10`
2. Calculate: `base_size = 10 // 3 = 3`, `extra = 10 % 3 = 1`
3. Part sizes: `[4, 3, 3]` (first part gets extra node)
4. Split:
   - Part 0: Take 4 nodes [1,2,3,4], break after 4
   - Part 1: Take 3 nodes [5,6,7], break after 7
   - Part 2: Take 3 nodes [8,9,10], end of list

**Example: head = [1,2,3], k = 5**

1. Count: `n = 3`
2. Calculate: `base_size = 3 // 5 = 0`, `extra = 3 % 5 = 3`
3. Part sizes: `[1, 1, 1, 0, 0]`
4. Split: First 3 parts get 1 node each, last 2 parts are null

# Tags

`#linked-list` `#array` `#two-pointers` `#medium`

