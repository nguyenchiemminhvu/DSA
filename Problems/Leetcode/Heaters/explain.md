## Problem

https://leetcode.com/problems/heaters/description/

Given the integer arrays `houses` and `heaters` representing positions on a horizontal line, return the **minimum radius** that all heaters must use so that every house is within at least one heater's warm radius.

All heaters share the same radius. A house at position `h` is covered by a heater at position `p` with radius `r` if `|h - p| <= r`.

**Example 1:** `houses = [1,2,3], heaters = [2]` → `1`  
**Example 2:** `houses = [1,2,3,4], heaters = [1,4]` → `1`  
**Example 3:** `houses = [1,5], heaters = [2]` → `3`

**Constraints:** `1 <= houses.length, heaters.length <= 3×10⁴`, `1 <= houses[i], heaters[i] <= 10⁹`

## Observations

1. **Monotone feasibility**: if radius `k` is sufficient to cover all houses, then any radius `k' > k` is also sufficient. This monotone property makes the answer space amenable to **binary search**.

2. **Search space**: the minimum radius is somewhere in `[0, 10⁹]`. Binary search over this range runs in at most 30 iterations.

3. **Feasibility check with two pointers**: after sorting both arrays, we can check in `O(H + N)` whether a given radius `k` covers all houses:
   - Maintain a pointer `ih` into `heaters` and a pointer `ipos` into `houses`.
   - For each house, advance the heater pointer until the current heater could possibly cover the house (i.e., until the heater is not strictly to the left of the house's coverage window).
   - If `|houses[ipos] - heaters[ih]| <= k`, the house is covered — advance `ipos`.
   - Otherwise advance `ih` (the heater is too far left; future houses are further right so this heater is useless for them too).
   - If all houses are visited (`ipos >= len(houses)`), return `True`.

4. **Why we never retreat `ih`**: houses are sorted, so once `heaters[ih]` is too far left for `houses[ipos]`, it is even further left for any `houses[ipos + j]`. We can safely discard it.  
   If `heaters[ih]` is too far **right** (`heaters[ih] > houses[ipos] + k`), incrementing `ih` makes the distance larger for the current house. The outer while-loop will exhaust all heaters without covering `houses[ipos]`, correctly returning `False`.

5. **Complexity**: sorting is `O((H+N) log(H+N))`; each binary search iteration is `O(H+N)` with 30 iterations → overall **O((H+N) log(H+N) + 30·(H+N))** = `O((H+N) log(H+N))`.

## Solution

```python
class Solution:
    def findRadius(self, houses: List[int], heaters: List[int]) -> int:
        houses.sort()
        heaters.sort()

        def check_cover(k: int) -> bool:
            ipos = 0
            ih = 0
            while ipos < len(houses) and ih < len(heaters):
                if abs(houses[ipos] - heaters[ih]) > k:
                    # current heater cannot cover current house:
                    #   - if heater is too far LEFT  → try next (rightward) heater
                    #   - if heater is too far RIGHT → next heaters are even further
                    #     right; inner loop exhausts heaters and returns False
                    ih += 1
                else:
                    ipos += 1          # house covered, move to next house
            return ipos >= len(houses) # True iff every house was covered

        left, right = 0, 10**9
        res = right
        while left <= right:
            mid = left + (right - left) // 2
            if check_cover(mid):
                res = mid
                right = mid - 1    # try to shrink radius
            else:
                left = mid + 1     # radius too small
        return res
```

**Step-by-step on Example 3** (`houses=[1,5]`, `heaters=[2]`):

| Binary search `mid` | `check_cover` trace | result |
|---|---|---|
| 500000000 | house 1 covered by heater 2 (dist 1); house 5 covered (dist 3) | True → `res=500000000`, search left |
| … (converges) | … | … |
| 3 | house 1: \|1−2\|=1 ≤ 3 ✓; house 5: \|5−2\|=3 ≤ 3 ✓ | True → `res=3`, search left |
| 2 | house 1: \|1−2\|=1 ≤ 2 ✓; house 5: \|5−2\|=3 > 2, `ih++` → no more heaters | False → search right |
| **3** | already found; `left > right` → stop | **return 3** |

# Tags

Binary Search, Two Pointers, Sorting

