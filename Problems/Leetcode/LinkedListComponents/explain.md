## Problem

https://leetcode.com/problems/linked-list-components/description/

```
You are given the head of a linked list containing unique integer values and an integer array nums that is a subset of the linked list values.

Return the number of connected components in nums where two values are connected if they appear consecutively in the linked list.

Example 1:
Input: head = [0,1,2,3], nums = [0,1,3]
Output: 2
Explanation: 0 and 1 are connected, so [0, 1] and [3] are the two connected components.

Example 2:
Input: head = [0,1,2,3,4], nums = [0,3,1,4]
Output: 2
Explanation: 0 and 1 are connected, 3 and 4 are connected, so [0, 1] and [3, 4] are the two connected components.

Constraints:
- The number of nodes in the linked list is n
- 1 <= n <= 10^4
- 0 <= Node.val < n
- All the values Node.val are unique
- 1 <= nums.length <= n
- 0 <= nums[i] < n
- All the values of nums are unique
```

## Observations

1. **Connected Component Definition**: Two values form a connected component if they appear consecutively in the linked list AND both values are present in the `nums` array.

2. **Key Insight**: We need to count the number of "groups" or "segments" where consecutive nodes in the linked list have values that are all in `nums`.

3. **Component Boundary**: A component ends when:
   - We reach a node whose value is in `nums` but the next node's value is NOT in `nums`
   - We reach a node whose value is in `nums` and it's the last node (next is None)

4. **Traversal Strategy**: We only need one pass through the linked list to count components.

5. **Data Structure Choice**: Using a set for `nums` provides O(1) lookup time to check if a value exists.

## Solution

### Approach: Single Pass with Component End Detection

**Algorithm:**
1. Convert `nums` array to a set for O(1) lookup
2. Traverse the linked list from head to end
3. For each node, check if its value is in the set
4. If the current node is in the set AND it's the end of a component (either the next node is None or the next node's value is not in the set), increment the component count
5. Return the total count

**Why This Works:**
- We only count a component when we reach its END (last node of the component)
- This ensures each component is counted exactly once
- A component ends when we encounter a value in `nums` that is either:
  - Followed by a value NOT in `nums` (component boundary)
  - At the end of the list (no next node)

**Example Walkthrough (Example 1):**
```
Linked List: 0 -> 1 -> 2 -> 3
nums = [0, 1, 3]
set(nums) = {0, 1, 3}

Traversal:
- Node 0: val=0 is in set, next.val=1 IS in set → continue (not end of component)
- Node 1: val=1 is in set, next.val=2 NOT in set → count++ (end of component [0,1])
- Node 2: val=2 NOT in set → skip
- Node 3: val=3 is in set, next=None → count++ (end of component [3])

Result: 2 components
```

**Time Complexity:** O(n) where n is the number of nodes in the linked list
- Single pass through the linked list
- O(m) to create the set where m is the length of nums array
- O(1) set lookup for each node

**Space Complexity:** O(m) where m is the length of nums array
- Set storage for nums values

**Code:**
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def numComponents(self, head: Optional[ListNode], nums: List[int]) -> int:
        # Convert nums to set for O(1) lookup
        s = set(nums)
        count = 0
        
        # Traverse the linked list
        while head:
            # Check if current node is in nums AND it's the end of a component
            if head.val in s and (head.next is None or head.next.val not in s):
                count += 1
            head = head.next
            
        return count
```

**Key Points:**
- The condition `head.val in s and (head.next is None or head.next.val not in s)` detects component boundaries
- We count at the END of each component to avoid double counting
- This elegant solution requires only one traversal without needing to track component state explicitly

# Tags
Linked List, Hash Table, Set, Two Pointers

