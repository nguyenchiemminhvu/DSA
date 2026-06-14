## Problem

https://leetcode.com/problems/candy/description/

There are `n` children standing in a line, each assigned a rating from the array `ratings`. Distribute candies under two rules:

1. Every child must receive **at least 1** candy.
2. A child with a **strictly higher** rating than an adjacent neighbor must receive **more** candies than that neighbor.

Return the **minimum total** candies needed.

**Example 1:**
```
Input:  ratings = [1, 0, 2]
Output: 5
# Allocate [2, 1, 2]
```

**Example 2:**
```
Input:  ratings = [1, 2, 2]
Output: 4
# Allocate [1, 2, 1]  — equal ratings do NOT require more candies
```

**Constraints:**
- `1 <= n <= 2 * 10^4`
- `0 <= ratings[i] <= 2 * 10^4`

---

## Observations

1. **Both neighbors matter independently.**  
   The constraint is two-sided: a child must beat its *left* neighbor if its rating is higher, and also beat its *right* neighbor if its rating is higher. These two directions can conflict, so they need to be reconciled.

2. **A single left-to-right pass is insufficient.**  
   A forward pass only enforces the constraint relative to the left neighbor. A valley followed by a rising slope (e.g. `[3,1,2]`) would be wrong after just one pass.

3. **Two independent passes cover both directions.**  
   - *Left pass* — for each position `i`, if `ratings[i] > ratings[i-1]`, then `candy[i] = candy[i-1] + 1`. This guarantees every child beats its left neighbor where required.  
   - *Right pass* — for each position `i` (right to left), if `ratings[i] > ratings[i+1]`, then `candy[i] = max(candy[i], candy[i+1] + 1)`. The `max` keeps the result from the left pass when it was already large enough.

4. **`max` is the key reconciliation step.**  
   After the left pass, `candy[i]` already satisfies the left-neighbor constraint. The right pass must not destroy that. Taking `max(candy[i], candy[i+1] + 1)` satisfies the right-neighbor constraint while preserving the left one.

5. **Equal ratings require no extra candy.**  
   The condition is *strictly greater*, so equal-rated neighbors may receive the same number of candies.

---

## Solution

```python
class Solution:
    def candy(self, rate: List[int]) -> int:
        n = len(rate)
        temp = [1] * n               # every child starts with 1 candy

        # Left pass: enforce rating[i] > rating[i-1]  →  candy[i] > candy[i-1]
        for i in range(1, n):
            if rate[i] > rate[i - 1]:
                temp[i] = temp[i - 1] + 1

        # Right pass: enforce rating[i] > rating[i+1]  →  candy[i] > candy[i+1]
        # Use max() to preserve any larger value already set by the left pass
        for i in range(n - 2, -1, -1):
            if rate[i] > rate[i + 1]:
                temp[i] = max(temp[i], temp[i + 1] + 1)

        return sum(temp)
```

### Walkthrough — `ratings = [1, 0, 2]`

| Step | temp |
|------|------|
| Init | `[1, 1, 1]` |
| Left pass (`i=1`: 0 < 1, skip; `i=2`: 2 > 0, `temp[2]=2`) | `[1, 1, 2]` |
| Right pass (`i=1`: 0 < 2, skip; `i=0`: 1 > 0, `temp[0]=max(1,1+1)=2`) | `[2, 1, 2]` |
| Sum | **5** |

### Walkthrough — `ratings = [1, 2, 2]`

| Step | temp |
|------|------|
| Init | `[1, 1, 1]` |
| Left pass (`i=1`: 2>1 → `temp[1]=2`; `i=2`: 2==2, skip) | `[1, 2, 1]` |
| Right pass (`i=1`: 2==2, skip; `i=0`: 1<2, skip) | `[1, 2, 1]` |
| Sum | **4** |

### Complexity

| | |
|---|---|
| **Time** | $O(n)$ — two linear scans |
| **Space** | $O(n)$ — the `temp` array |
