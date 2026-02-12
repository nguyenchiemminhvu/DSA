## Problem

https://leetcode.com/problems/merge-k-sorted-lists/description/

```
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted linked list:
1->1->2->3->4->4->5->6

Example 2:
Input: lists = []
Output: []

Example 3:
Input: lists = [[]]
Output: []

Constraints:
- k == lists.length
- 0 <= k <= 10^4
- 0 <= lists[i].length <= 500
- -10^4 <= lists[i][j] <= 10^4
- lists[i] is sorted in ascending order.
- The sum of lists[i].length will not exceed 10^4.
```

## Observations

1. **Problem Nature**: This is a multi-way merge problem where we need to merge k sorted linked lists into one sorted list.

2. **Key Insights**:
   - Each individual linked list is already sorted
   - We need to maintain the sorted order while merging
   - At any point, the smallest unprocessed element must be at the head of one of the k lists

3. **Naive Approach**: 
   - Compare heads of all k lists repeatedly to find minimum (O(k) per element)
   - Time Complexity: O(N*k) where N is total number of nodes
   - This is inefficient for large k

4. **Optimized Approach - Min Heap**:
   - Use a min-heap (priority queue) to efficiently find the minimum among k elements
   - Heap operations are O(log k), much better than O(k) linear scan
   - Time Complexity: O(N*log k) where N is total number of nodes
   - Space Complexity: O(k) for the heap

5. **Edge Cases**:
   - Empty input array
   - Array with empty lists
   - Single list
   - Lists of varying lengths

## Solution

### Approach: Min-Heap (Priority Queue)

**Algorithm**:
1. Initialize a min-heap and push the first node from each non-empty list
2. Use a `global_id` counter to break ties when values are equal (Python's heapq requires comparable elements)
3. Create a dummy head node for the result list
4. While heap is not empty:
   - Pop the node with minimum value
   - Add it to the result list
   - If the popped node has a next node, push that next node to the heap
5. Return the next of dummy head (actual result)

**Why Min-Heap?**
- At any moment, we only care about the smallest element among the current heads of all lists
- A min-heap maintains the minimum element at the top in O(log k) time
- This is much more efficient than scanning all k heads linearly

**Implementation Details**:
```python
import heapq

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        global_id = 0
        
        # Initialize heap with first node from each list
        pq = []
        for p in lists:
            if p:
                heapq.heappush(pq, (p.val, global_id, p.next))
                global_id += 1
        
        # Build result list
        res = ListNode()  # dummy head
        p = res
        while pq:
            val, _, pnext = heapq.heappop(pq)
            p.next = ListNode(val)
            p = p.next
            
            # Add next node from same list to heap
            if pnext:
                heapq.heappush(pq, (pnext.val, global_id, pnext.next))
                global_id += 1
        
        return res.next
```

**Time Complexity**: O(N * log k)
- N = total number of nodes across all lists
- Each node is pushed and popped from heap once: O(log k) per operation
- Total: N push/pop operations × O(log k) = O(N * log k)

**Space Complexity**: O(k)
- Heap stores at most k nodes (one from each list)
- Result list is not counted as it's required output
- Call stack is O(1) as we use iteration

**Alternative Approach - Divide and Conquer**:
- Merge lists pairwise recursively (similar to merge sort)
- Time: O(N * log k), Space: O(log k) for recursion stack
- More efficient in terms of space but slightly more complex to implement

# Tags
`Linked List` `Divide and Conquer` `Heap (Priority Queue)` `Merge Sort` `Multi-way Merge`

