## Problem

https://leetcode.com/problems/maximum-subsequence-score/description/

You are given two 0-indexed integer arrays `nums1` and `nums2` of equal length `n` and a positive integer `k`. You must choose a subsequence of indices from `nums1` of length `k`.

For chosen indices `i0, i1, ..., ik-1`, your score is defined as:
- The sum of the selected elements from `nums1` multiplied with the minimum of the selected elements from `nums2`.
- Formula: `(nums1[i0] + nums1[i1] + ... + nums1[ik-1]) * min(nums2[i0], nums2[i1], ..., nums2[ik-1])`

Return the maximum possible score.

**Example 1:**
- Input: `nums1 = [1,3,3,2]`, `nums2 = [2,1,3,4]`, `k = 3`
- Output: `12`
- Explanation: Choosing indices `[0,2,3]` gives `(1+3+2) * min(2,3,4) = 12`

**Example 2:**
- Input: `nums1 = [4,2,3,1,1]`, `nums2 = [7,5,10,9,6]`, `k = 1`
- Output: `30`
- Explanation: Choosing index `2` gives `3 * 10 = 30`

**Constraints:**
- `n == nums1.length == nums2.length`
- `1 <= n <= 10^5`
- `0 <= nums1[i], nums2[j] <= 10^5`
- `1 <= k <= n`

## Observations

1. **Key Insight**: The score formula has two components:
   - Sum of selected elements from `nums1` (we want this as large as possible)
   - Minimum of selected elements from `nums2` (this acts as a multiplier)

2. **Strategic Approach**: If we fix the minimum value from `nums2`, we should maximize the sum from `nums1` to get the best score with that minimum.

3. **Greedy Strategy**: 
   - Sort pairs by `nums2` values in descending order
   - When we iterate through sorted pairs, any element we consider can be treated as the minimum (since all previous elements have higher or equal `nums2` values)
   - For each potential minimum, maintain the k largest `nums1` values seen so far

4. **Why Min-Heap?**: We need to efficiently maintain the top k elements from `nums1` and remove the smallest when we have more than k elements.

## Solution

```python
import heapq

class Solution:
    def maxScore(self, nums1: List[int], nums2: List[int], k: int) -> int:
        n = len(nums1)
        # Create pairs (nums2[i], nums1[i]) and sort by nums2 descending
        pairs = [(p[0], p[1]) for p in zip(nums2, nums1)]
        pairs.sort(key=lambda x: x[0], reverse=True)

        # Min-heap to maintain top k elements from nums1
        pq = []
        # Pre-load first k-1 elements
        for i in range(k - 1):
            heapq.heappush(pq, pairs[i][1])

        res = 0
        s = sum(pq)  # Running sum of k largest nums1 values
        
        # Iterate from position k-1 onwards
        for i in range(k - 1, n):
            val2, val1 = pairs[i]  # (nums2 value, nums1 value)
            s += val1
            heapq.heappush(pq, val1)
            
            # Maintain exactly k elements
            if len(pq) > k:
                s -= heapq.heappop(pq)  # Remove smallest nums1 value
            
            # val2 is guaranteed to be the minimum nums2 value in current selection
            # because pairs are sorted by nums2 in descending order
            res = max(res, val2 * s)
        
        return res
```

**Algorithm Explanation:**

1. **Sorting Phase**: Create pairs of `(nums2[i], nums1[i])` and sort by `nums2` in descending order
   - Time: O(n log n)

2. **Initialization**: Add first `k-1` elements' `nums1` values to a min-heap

3. **Main Loop** (from index `k-1` to `n-1`):
   - Add current element's `nums1` value to the heap and sum
   - If heap size exceeds `k`, remove the smallest `nums1` value (maintain top k)
   - Calculate score: `current_nums2_value * sum_of_top_k_nums1_values`
   - The current `nums2` value is guaranteed to be the minimum because we sorted in descending order

4. **Why This Works**:
   - At position `i`, `pairs[i][0]` (from `nums2`) is the minimum among all considered elements
   - We maintain the k largest `nums1` values seen so far in the heap
   - This gives us the optimal sum for this particular minimum value

**Complexity:**
- **Time**: O(n log n) for sorting + O(n log k) for heap operations = O(n log n)
- **Space**: O(n) for pairs + O(k) for heap = O(n)

# Tags
`Greedy` `Heap` `Priority Queue` `Sorting` `Array`

