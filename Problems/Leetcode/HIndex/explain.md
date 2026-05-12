## Problem

https://leetcode.com/problems/h-index/description

# H-Index

## Problem

https://leetcode.com/problems/h-index/description

Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their ith paper, return the researcher's h-index.

**Definition (from Wikipedia):** The h-index is defined as the maximum value of $h$ such that the given researcher has published at least $h$ papers that have each been cited at least $h$ times.

### Examples

**Example 1:**
```
Input: citations = [3,0,6,1,5]
Output: 3
Explanation: The researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.
```

**Example 2:**
```
Input: citations = [1,3,1]
Output: 1
```

### Constraints

- $n = \text{citations.length}$
- $1 \leq n \leq 5000$
- $0 \leq \text{citations}[i] \leq 1000$

## Observations

1. **H-index Definition:** We need to find the maximum $h$ where at least $h$ papers have at least $h$ citations each.

2. **Key Insight:** If we sort the citations in ascending order, we can use the index position to infer how many papers have citations greater than or equal to a certain value.
   - At index $i$ in a sorted array of length $n$, there are $n - i$ papers with citations $\geq \text{citations}[i]$.
   - For h-index to be valid at position $i$: we need $\text{citations}[i] \geq n - i$ (the number of papers with at least this many citations).

3. **Example Walkthrough with `[3,0,6,1,5]`:**
   - Sorted: `[0,1,3,5,6]`
   - Index 0: 5 papers with citations ≥ 0 (h=5 is invalid because citations[0]=0 < 5)
   - Index 1: 4 papers with citations ≥ 1 (h=4 is invalid because citations[1]=1 < 4)
   - Index 2: 3 papers with citations ≥ 3 (h=3 is **valid** because citations[2]=3 ≥ 3) ✓
   - Index 3: 2 papers with citations ≥ 5 (h=2 is valid because citations[3]=5 ≥ 2)
   - Index 4: 1 paper with citations ≥ 6 (h=1 is valid because citations[4]=6 ≥ 1)
   - **Maximum valid h = 3**

4. **Binary Search Optimization:** Since we're looking for the maximum valid h-index, we can use binary search to find the first position where `citations[mid] >= n - mid`.

## Solution

### Algorithm: Binary Search on Sorted Array

**Time Complexity:** $O(n \log n)$ due to sorting  
**Space Complexity:** $O(1)$ if we don't count the sorting space

```python
class Solution:
    def hIndex(self, cts: List[int]) -> int:
        n = len(cts)
        cts.sort()  # Sort in ascending order: O(n log n)
        left, right = 0, n - 1
        
        while left <= right:
            mid = left + (right - left) // 2
            h = n - mid  # Number of papers with citations >= cts[mid]
            
            # If we have at least h papers with h citations, 
            # try to find a larger h-index (move left)
            if cts[mid] >= h:
                right = mid - 1
            else:
                # Otherwise, look at papers with fewer papers count (move right)
                left = mid + 1
        
        # At the end, left points to the first position where 
        # cts[left] >= n - left, or n if no such position exists
        return n - left
```

### Step-by-Step Explanation

1. **Sort the array:** We arrange citations in ascending order to make the relationship between index and citation count clear.

2. **Binary search logic:**
   - `h = n - mid`: Calculate how many papers exist from index `mid` onwards.
   - If `cts[mid] >= h`: The paper at index `mid` has enough citations. This position is valid, so we try to find an even better h-index by searching left (smaller indices have more papers).
   - If `cts[mid] < h`: Not enough citations for this position. Search right.

3. **Return value:** After the loop, `left` is the first index where `cts[left] >= n - left`. The h-index is `n - left`.

### Tracing Example: `citations = [3,0,6,1,5]`

```
Sorted: [0,1,3,5,6]
n = 5

Iteration 1: left=0, right=4
  mid = 2, h = 5-2 = 3
  cts[2]=3 >= h=3? YES
  right = 1

Iteration 2: left=0, right=1
  mid = 0, h = 5-0 = 5
  cts[0]=0 >= h=5? NO
  left = 1

Iteration 3: left=1, right=1
  mid = 1, h = 5-1 = 4
  cts[1]=1 >= h=4? NO
  left = 2

Loop ends: left=2, right=1

Return: n - left = 5 - 2 = 3 ✓
```

## Tags

- Binary Search
- Sorting
- Two Pointers
- Array

## Observations

## Solution

# Tags

