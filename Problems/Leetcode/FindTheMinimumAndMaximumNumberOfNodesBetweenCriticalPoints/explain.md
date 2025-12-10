## Problem

https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/description/

A **critical point** in a linked list is defined as either a **local maxima** or a **local minima**.

- A node is a **local maxima** if the current node has a value strictly greater than the previous node and the next node.
- A node is a **local minima** if the current node has a value strictly smaller than the previous node and the next node.

**Note:** A node can only be a local maxima/minima if there exists both a previous node and a next node.

Given a linked list `head`, return an array of length 2 containing `[minDistance, maxDistance]` where:
- `minDistance` is the minimum distance between any two distinct critical points
- `maxDistance` is the maximum distance between any two distinct critical points

If there are fewer than two critical points, return `[-1, -1]`.

### Examples

**Example 1:**
```
Input: head = [3,1]
Output: [-1,-1]
Explanation: There are no critical points in [3,1].
```

**Example 2:**
```
Input: head = [5,3,1,2,5,1,2]
Output: [1,3]
Explanation: There are three critical points:
- Index 2: Local minima (1 < 3 and 1 < 2)
- Index 4: Local maxima (5 > 2 and 5 > 1)
- Index 5: Local minima (1 < 5 and 1 < 2)
minDistance = 5 - 4 = 1
maxDistance = 5 - 2 = 3
```

**Example 3:**
```
Input: head = [1,3,2,2,3,2,2,2,7]
Output: [3,3]
Explanation: Two critical points:
- Index 1: Local maxima (3 > 1 and 3 > 2)
- Index 4: Local maxima (3 > 2 and 3 > 2)
Both distances = 4 - 1 = 3
```

### Constraints
- The number of nodes in the list is in the range `[2, 10^5]`
- `1 <= Node.val <= 10^5`

---

## Observations

1. **Critical Point Requirements:**
   - A node must have both a previous and next node to be considered
   - First and last nodes can NEVER be critical points
   - We need at least 3 nodes total to have even one critical point

2. **Distance Calculations:**
   - **Maximum distance:** Always between the first and last critical points
   - **Minimum distance:** Could be between any two consecutive critical points
   - Need at least 2 critical points to calculate distances

3. **Edge Cases:**
   - List with fewer than 3 nodes → return `[-1, -1]`
   - Fewer than 2 critical points found → return `[-1, -1]`
   - All values equal → no critical points
   - Monotonically increasing/decreasing → no critical points

4. **Key Insight:**
   - We only need to store the **indices** of critical points
   - No need to store the actual values
   - Once we have indices, distance calculation is straightforward

---

## Solution

### Algorithm

The solution uses a **single-pass traversal** with the following steps:

1. **Early Termination Check:**
   ```python
   if head.next.next == None:
       return [-1, -1]
   ```
   If we don't have at least 3 nodes, no critical points are possible.

2. **Traverse and Identify Critical Points:**
   - Keep track of:
     - Current index `i`
     - Previous node value `prev`
     - Current node value
     - Next node value (via `head.next.val`)
   
   - For each node (excluding first and last):
     - Check if it's a local maxima: `val > prev AND val > next`
     - Check if it's a local minima: `val < prev AND val < next`
     - If either condition is true, store the index

3. **Calculate Distances:**
   - If fewer than 2 critical points → return `[-1, -1]`
   - **Max distance:** `arr[-1] - arr[0]` (last index - first index)
   - **Min distance:** Iterate through consecutive pairs and find minimum difference

### Complexity Analysis

- **Time Complexity:** O(n)
  - Single pass through the linked list: O(n)
  - Finding minimum distance among critical points: O(k) where k ≤ n
  - Overall: O(n)

- **Space Complexity:** O(k)
  - Storing indices of critical points: O(k) where k is number of critical points
  - In worst case, k can be O(n) (e.g., alternating values like [1,2,1,2,1,2...])

### Example Trace

For `head = [5,3,1,2,5,1,2]`:

| Index | Value | Prev | Next | Critical? | Reason |
|-------|-------|------|------|-----------|--------|
| 0 | 5 | - | 3 | No | First node |
| 1 | 3 | 5 | 1 | No | 3 not > both, 3 not < both |
| 2 | 1 | 3 | 2 | **Yes (minima)** | 1 < 3 AND 1 < 2 |
| 3 | 2 | 1 | 5 | No | 2 not > both, 2 not < both |
| 4 | 5 | 2 | 1 | **Yes (maxima)** | 5 > 2 AND 5 > 1 |
| 5 | 1 | 5 | 2 | **Yes (minima)** | 1 < 5 AND 1 < 2 |
| 6 | 2 | 1 | - | No | Last node |

Critical points at indices: `[2, 4, 5]`
- Min distance: `min(4-2, 5-4) = min(2, 1) = 1`
- Max distance: `5 - 2 = 3`
- Result: `[1, 3]` ✓

---

### Alternative Approach: O(1) Space

Instead of storing all indices, we can track only what we need:
- First critical point index
- Last critical point index
- Previous critical point index
- Running minimum distance

```python
def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
    if not head.next.next:
        return [-1, -1]
    
    first_critical = -1
    last_critical = -1
    prev_critical = -1
    min_dist = float('inf')
    
    i = 0
    prev = float('inf')
    
    while head:
        val = head.val
        if i > 0 and head.next:
            is_critical = (val > prev and val > head.next.val) or \
                         (val < prev and val < head.next.val)
            
            if is_critical:
                if first_critical == -1:
                    first_critical = i
                if prev_critical != -1:
                    min_dist = min(min_dist, i - prev_critical)
                prev_critical = i
                last_critical = i
        
        prev = val
        i += 1
        head = head.next
    
    if first_critical == last_critical:  # Less than 2 critical points
        return [-1, -1]
    
    return [min_dist, last_critical - first_critical]
```

This approach uses **O(1) space** while maintaining **O(n) time complexity**.

# Tags

`Linked List` `Two Pointers` `Array`

