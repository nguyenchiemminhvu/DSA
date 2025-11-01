## Problems

https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/

```
You are given an array of integers nums and the head of a linked list. Return the head of the modified linked list after removing all nodes from the linked list that have a value that exists in nums.

Example 1:

Input: nums = [1,2,3], head = [1,2,3,4,5]

Output: [4,5]

Explanation:

Remove the nodes with values 1, 2, and 3.

Example 2:

Input: nums = [1], head = [1,2,1,2,1,2]

Output: [2,2,2]

Explanation:

Remove the nodes with value 1.

Example 3:

Input: nums = [5], head = [1,2,3,4]

Output: [1,2,3,4]

Explanation:

No node has value 5.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
All elements in nums are unique.
The number of nodes in the given list is in the range [1, 105].
1 <= Node.val <= 105
The input is generated such that there is at least one node in the linked list that has a value not present in nums.
```

## Observations

1. **Problem Type**: This is a linked list manipulation problem where we need to delete nodes based on values present in an array.

2. **Key Insight**: We need to efficiently check if a node's value exists in the given array. Using a set for O(1) lookup is optimal.

3. **Edge Cases to Consider**:
   - Head node needs to be deleted
   - Multiple consecutive nodes need to be deleted
   - All nodes except the last few need to be deleted
   - No nodes need to be deleted

4. **Dummy Node Pattern**: Using a dummy node simplifies the logic by eliminating special handling for head deletion.

5. **Two-Pointer Approach**: We need to maintain both current and previous pointers to safely delete nodes.

6. **Time Complexity**: O(n + m) where n is the length of the linked list and m is the length of nums array
   - O(m) to create the set from nums
   - O(n) to traverse the linked list

7. **Space Complexity**: O(m) for the set to store nums values

## Solution

1. **Preprocessing**: Convert `nums` array to a set for O(1) lookup time
2. **Initialize**: Create a dummy node pointing to head, and set up two pointers
3. **Traverse**: For each node in the linked list:
   - If the node's value is in the set, delete it by updating `prev.next`
   - If the node's value is not in the set, keep it and advance both pointers
4. **Return**: The new head is `dummy.next`

**Why this works**:
- The dummy node eliminates the need for special handling when the head needs to be deleted
- The two-pointer technique (`prev` and `cur`) allows safe deletion without losing references
- When deleting a node, we don't advance `prev` because the next node might also need deletion

**Example walkthrough** with `nums = [1,2,3]`, `head = [1,2,3,4,5]`:
```
Initial: dummy -> 1 -> 2 -> 3 -> 4 -> 5
                  prev cur

Step 1: cur.val = 1 (in set), delete it
        dummy -> 2 -> 3 -> 4 -> 5
        prev     cur

Step 2: cur.val = 2 (in set), delete it  
        dummy -> 3 -> 4 -> 5
        prev     cur

Step 3: cur.val = 3 (in set), delete it
        dummy -> 4 -> 5
        prev     cur

Step 4: cur.val = 4 (not in set), keep it
        dummy -> 4 -> 5
                 prev cur

Step 5: cur.val = 5 (not in set), keep it
        dummy -> 4 -> 5
                      prev cur

Result: [4, 5]
```

## Tags

array, hash table, linked list