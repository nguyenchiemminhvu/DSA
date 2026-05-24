## Problem

https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description

Given a wooden stick of length `n` units labeled from `0` to `n`, and an integer array `cuts` where `cuts[i]` denotes a position at which to perform a cut.

**Constraints:**
- You can perform cuts in any order (not necessarily in the given order)
- The cost of one cut is the length of the stick being cut
- After a cut, the stick splits into two smaller sticks
- Total cost is the sum of all individual cut costs

**Goal:** Return the minimum total cost of performing all cuts.

**Example:**
- Input: `n = 7, cuts = [1,3,4,5]`
- Output: `16`
- Explanation: Using order `[3, 5, 1, 4]` gives cost `7 + 4 + 3 + 2 = 16`

## Observations

### Key Insights:

1. **Optimal Substructure**: When we cut a stick at position `c`, the problem decomposes into two independent subproblems: cutting the left segment `[l, c]` and the right segment `[c, r]`.

2. **The Cost Pattern**: The cost of cutting at position `c` within range `[l, r]` is always `(r - l)`, regardless of what cuts happened before. This is because at that moment, we're cutting a stick of length `(r - l)`.

3. **Order Matters for Total Cost**: Different orderings produce different total costs. A greedy "cut smallest piece first" approach doesn't work. For example, cutting a stick requires maintaining awareness of which cuts still need to happen within each resulting segment.

4. **Interval DP Framework**: This is a classic interval dynamic programming problem. We compute the minimum cost for all possible contiguous ranges `[l, r]` of the stick.

5. **Finding Relevant Cuts**: For a given range `[l, r]`, we only care about cuts that fall strictly between `l` and `r` (using `bisect_right` for `l` and `bisect_left` for `r`). Cuts outside this range are irrelevant.

6. **Base Case**: If there are no cuts in a range, the cost is 0 (nothing to cut in that segment).

## Solution

### Approach: Interval Dynamic Programming

**Core Idea**: Use memoization to compute `F(l, r)` = minimum cost to make all cuts in the range `(l, r)`.

**Algorithm Steps:**

```python
def minCost(n: int, cuts: List[int]) -> int:
    # Step 1: Sort cuts for binary search
    cuts.sort()
    nc = len(cuts)
    
    # Step 2: Helper function to find cuts in a range
    def find_range_indices(sorted: List[int], low: int, high: int):
        # bisect_right(low): first cut > low
        # bisect_left(high): first cut >= high
        left = bisect.bisect_right(sorted, low)
        right = bisect.bisect_left(sorted, high)
        return (left, right)
    
    # Step 3: Memoization cache
    mem = {}
    
    # Step 4: DP function
    def F(l: int, r: int) -> int:
        # Find indices of cuts strictly between l and r
        lc, rc = find_range_indices(cuts, l, r)
        
        # Base case: no cuts in this range
        if lc >= rc:
            return 0
        
        # Check memo
        if (l, r) in mem:
            return mem[(l, r)]
        
        # Try each possible cut as the "first" cut in this range
        res = float('inf')
        for i in range(lc, rc):
            # Cost = cutting at cuts[i] + solving left segment + solving right segment
            res = min(
                res,
                (r - l) + F(l, cuts[i]) + F(cuts[i], r)
            )
        
        mem[(l, r)] = res
        return res
    
    return F(0, n)
```

### Why This Works:

1. **State Definition**: `F(l, r)` represents the minimum cost to perform all cuts that fall strictly between positions `l` and `r` on a stick segment of length `(r - l)`.

2. **Transition**: For a range `[l, r]` with cuts at positions `cuts[lc], cuts[lc+1], ..., cuts[rc-1]`:
   - We try each cut position `cuts[i]` as the last cut to perform in this range
   - When we make the last cut at `cuts[i]`, the stick still has length `(r - l)` (all previous cuts were made on subsegments)
   - After this cut, we recursively solve two independent subproblems: `F(l, cuts[i])` and `F(cuts[i], r)`

3. **Cost Accumulation**: The total cost is:
   ```
   (r - l) + min over all i of [F(l, cuts[i]) + F(cuts[i], r)]
   ```

### Complexity Analysis:

- **Time Complexity**: $O(n^3)$ where $n$ is the number of cuts
  - Number of unique states: $O(n^2)$ (all possible pairs `(l, r)`)
  - Each state requires trying all intermediate cuts: $O(n)$
  - Total: $O(n^3)$

- **Space Complexity**: $O(n^2)$ for the memoization cache

### Example Walkthrough:

For `n = 7, cuts = [1, 3, 4, 5]`:

```
F(0, 7) tries each cut:
  - Cut at 1: 7 + F(0,1) + F(1,7)
  - Cut at 3: 7 + F(0,3) + F(3,7)
  - Cut at 4: 7 + F(0,4) + F(4,7)
  - Cut at 5: 7 + F(0,5) + F(5,7)

Each F(l, r) recursively solves smaller problems.
The algorithm picks the order that minimizes total cost: [3, 5, 1, 4] → cost 16
```

# Tags
- Interval DP
- Memoization
- Binary Search (bisect)
- Greedy fails (order matters)
- Matrix Chain Multiplication pattern

