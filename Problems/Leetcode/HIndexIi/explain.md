## Problem

https://leetcode.com/problems/h-index-ii/description/

Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their ith paper and `citations` is sorted in non-descending order, return the researcher's h-index.

The h-index is defined as the maximum value of `h` such that the researcher has published at least `h` papers that have each been cited at least `h` times.

**Constraints:**
- `n == citations.length`
- `1 <= n <= 10^5`
- `0 <= citations[i] <= 1000`
- `citations` is sorted in ascending order
- Must solve in **logarithmic time** (O(log n))

**Examples:**

Example 1:
- Input: `citations = [0,1,3,5,6]`
- Output: `3`
- Explanation: The researcher has 5 papers. With h=3, there are 3 papers with at least 3 citations each (papers with 3, 5, 6 citations). The h-index is 3.

Example 2:
- Input: `citations = [1,2,100]`
- Output: `2`
- Explanation: With h=2, there are 2 papers with at least 2 citations each (papers with 2, 100 citations). With h=3, there's only 1 paper with at least 3 citations.

## Observations

1. **Key Insight:** For position `mid` in the array, there are `n - mid` papers from index `mid` onwards (including `mid`). Since the array is sorted, `citations[mid]` is the minimum citations among all papers at this position and beyond.

2. **H-index Property:** At position `mid`, if `citations[mid] >= (n - mid)`, then we have at least `(n - mid)` papers with at least `n - mid` citations each, making `n - mid` a valid h-index candidate.

3. **Search Space:** We need to find the **minimum position** where this property holds, because:
   - If the property holds at position `mid`, it also holds at all positions before `mid` (with potentially smaller h-index values)
   - The answer is `n - left` where `left` is the leftmost position satisfying the condition

4. **Binary Search Strategy:**
   - If `citations[mid] >= h` (where `h = n - mid`): We can move left to potentially find a better (larger) h-index
   - If `citations[mid] < h`: We must move right because this position doesn't satisfy the condition

5. **Why It Works:** The solution finds the leftmost position where citations are sufficient for that h-index, giving us the maximum h-index.

## Solution

```python
class Solution:
    def hIndex(self, citations: List[int]) -> int:
        n = len(citations)
        left, right = 0, n - 1
        
        # Binary search for the leftmost position where
        # citations[mid] >= n - mid
        while left <= right:
            mid = left + (right - left) // 2
            h = n - mid  # Number of papers from index mid onwards
            
            if citations[mid] >= h:
                # Condition satisfied, try to find a position further left
                # to get a larger h-index
                right = mid - 1
            else:
                # Condition not satisfied, move right
                left = mid + 1
        
        # At the end, left points to the leftmost position where
        # citations[left] >= n - left, so the h-index is n - left
        return n - left
```

**Complexity Analysis:**
- **Time:** O(log n) - Binary search on the array
- **Space:** O(1) - Only using constant extra space

**How the algorithm works step-by-step:**

For `citations = [0,1,3,5,6]`, `n = 5`:

| Iteration | left | right | mid | h=n-mid | cts[mid] | cts[mid]>=h? | Action |
|-----------|------|-------|-----|---------|----------|------------|--------|
| 1         | 0    | 4     | 2   | 3       | 3        | Yes        | right=1 |
| 2         | 0    | 1     | 0   | 5       | 0        | No         | left=1  |
| 3         | 1    | 1     | 1   | 4       | 1        | No         | left=2  |
| End       | left=2, right=1 (left > right, exit loop)                       |
| Result    | n - left = 5 - 2 = **3** ✓                                       |

The algorithm finds that position 2 is the leftmost where the condition is satisfied with h-index value of 3.

# Tags

binary-search, h-index, sorted-array

