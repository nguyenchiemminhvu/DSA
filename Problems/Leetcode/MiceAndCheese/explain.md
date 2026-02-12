## Problem

https://leetcode.com/problems/mice-and-cheese/description/

```
There are two mice and n different types of cheese, each type of cheese should be eaten by exactly one mouse.

A point of the cheese with index i (0-indexed) is:
- reward1[i] if the first mouse eats it.
- reward2[i] if the second mouse eats it.

You are given a positive integer array reward1, a positive integer array reward2, and a non-negative integer k.

Return the maximum points the mice can achieve if the first mouse eats exactly k types of cheese.

Example 1:
Input: reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2
Output: 15
Explanation: First mouse eats indices 2 and 3 (3+4=7), second mouse eats indices 0 and 1 (4+4=8). Total = 15.

Example 2:
Input: reward1 = [1,1], reward2 = [1,1], k = 2
Output: 2
Explanation: First mouse eats all cheese (1+1=2). Total = 2.

Constraints:
- 1 <= n == reward1.length == reward2.length <= 10^5
- 1 <= reward1[i], reward2[i] <= 1000
- 0 <= k <= n
```

## Observations

1. **Key Constraint**: Each cheese must be eaten by exactly one mouse - first mouse eats k cheeses, second mouse eats (n-k) cheeses.

2. **Greedy Approach**: We need to decide which k cheeses should go to the first mouse to maximize total points.

3. **Decision Metric**: For each cheese, we should consider the **difference** `reward1[i] - reward2[i]`:
   - If `reward1[i] - reward2[i]` is large and positive, giving it to mouse 1 provides more value
   - If `reward1[i] - reward2[i]` is negative, mouse 2 should eat it
   - The difference represents the **opportunity gain** of choosing mouse 1 over mouse 2

4. **Example Analysis** (reward1 = [1,1,3,4], reward2 = [4,4,1,1], k = 2):
   - Differences: [1-4=-3, 1-4=-3, 3-1=2, 4-1=3]
   - Sort by difference (descending): indices [3, 2, 0, 1] with differences [3, 2, -3, -3]
   - Give top k=2 (indices 3, 2) to mouse 1: 4 + 3 = 7
   - Give rest (indices 0, 1) to mouse 2: 4 + 4 = 8
   - Total: 15

## Solution

### Approach: Greedy with Max Heap

**Strategy**:
1. Calculate the difference `reward1[i] - reward2[i]` for each cheese
2. Use a max heap to select the k cheeses with the largest differences for mouse 1
3. Assign remaining cheeses to mouse 2

**Algorithm**:
```python
import heapq

class Solution:
    def miceAndCheese(self, nums1: List[int], nums2: List[int], k: int) -> int:
        # Max heap based on difference (reward1[i] - reward2[i])
        pq = []
        for i, (val1, val2) in enumerate(zip(nums1, nums2)):
            # Use negative for max heap (Python has min heap by default)
            heapq.heappush(pq, (-(val1 - val2), i))
        
        res = 0
        # Give k cheeses with largest differences to mouse 1
        while pq and k > 0:
            _, i = heapq.heappop(pq)
            res += nums1[i]
            k -= 1
        
        # Give remaining cheeses to mouse 2
        while pq:
            _, i = heapq.heappop(pq)
            res += nums2[i]
        
        return res
```

**Why This Works**:
- By maximizing the difference `reward1[i] - reward2[i]`, we select cheeses where mouse 1 has the greatest **advantage** over mouse 2
- Even if a cheese has high absolute values for both mice, what matters is the relative gain
- This greedy choice is optimal because we're essentially choosing k items that maximize the total when switching from "all to mouse 2" to "k to mouse 1"

**Complexity**:
- **Time**: O(n log n) - heap operations for n elements
- **Space**: O(n) - heap storage

**Alternative**: Sort by difference instead of heap (same complexity, cleaner code):
```python
def miceAndCheese(self, nums1: List[int], nums2: List[int], k: int) -> int:
    # Create list of (difference, index)
    diff = [(nums1[i] - nums2[i], i) for i in range(len(nums1))]
    # Sort by difference descending
    diff.sort(reverse=True)
    
    res = 0
    # Top k to mouse 1
    for i in range(k):
        res += nums1[diff[i][1]]
    # Rest to mouse 2
    for i in range(k, len(diff)):
        res += nums2[diff[i][1]]
    
    return res
```

# Tags
`Greedy` `Heap` `Priority Queue` `Sorting` `Array`

