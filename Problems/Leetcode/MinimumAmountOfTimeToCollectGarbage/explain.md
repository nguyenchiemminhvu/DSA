## Problem

https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/description/

You are given a 0-indexed array of strings `garbage` where `garbage[i]` represents the assortment of garbage at the `i`-th house. `garbage[i]` consists only of the characters `'M'`, `'P'`, and `'G'` representing one unit of metal, paper, and glass garbage respectively. Picking up one unit of any type of garbage takes **1 minute**.

You are also given a 0-indexed integer array `travel` where `travel[i]` is the number of minutes needed to go from house `i` to house `i + 1`.

There are **three garbage trucks**, each responsible for picking up one type of garbage. Each truck starts at house 0 and must visit houses **in order**, but does not need to visit every house. Only one truck may be active at any given moment.

Return the **minimum number of minutes** needed to pick up all the garbage.

---

## Observations

1. **Each unit of garbage costs exactly 1 minute to collect**, regardless of type. So the total collection time across all trucks is simply `sum of lengths of all garbage[i]`.

2. **Each truck only needs to travel as far as the last house containing its type of garbage.** A truck collecting metal only needs to travel up to the last house that has `'M'`; it never needs to go further.

3. **Travel cost for a truck** = sum of `travel[0..last_idx - 1]`, i.e., the prefix sum of travel up to (but not including) the last index it must visit.

4. **The three trucks operate independently** — their times are additive. The total answer is the sum of each truck's total time (collection + travel).

5. If a garbage type does not appear at all, its truck contributes 0 to the answer (it never moves).

---

## Solution Explanation

```python
class Solution:
    def garbageCollection(self, garbage: List[str], travel: List[int]) -> int:
        n = len(garbage)

        # Step 1: Every garbage unit takes 1 minute to collect.
        # Total collection time = total number of characters across all strings.
        res = sum(len(g) for g in garbage)

        # Step 2: Find the last house index each truck needs to visit.
        last_idx_m = last_idx_g = last_idx_p = 0
        for i in range(n):
            if 'M' in garbage[i]:
                last_idx_m = i
            if 'G' in garbage[i]:
                last_idx_g = i
            if 'P' in garbage[i]:
                last_idx_p = i

        # Step 3: Add travel time for each truck.
        # A truck traveling to house k must traverse travel[0] + travel[1] + ... + travel[k-1].
        for i in range(last_idx_m):
            res += travel[i]
        for i in range(last_idx_g):
            res += travel[i]
        for i in range(last_idx_p):
            res += travel[i]

        return res
```

### Walkthrough — Example 1

`garbage = ["G","P","GP","GG"]`, `travel = [2,4,3]`

- Total collection time: `1 + 1 + 2 + 2 = 6`
- Last `'M'` index: 0 → metal truck travel = 0
- Last `'G'` index: 3 → glass truck travel = `travel[0] + travel[1] + travel[2]` = `2 + 4 + 3 = 9`
- Last `'P'` index: 2 → paper truck travel = `travel[0] + travel[1]` = `2 + 4 = 6`
- **Total = 6 + 0 + 9 + 6 = 21** ✅

### Walkthrough — Example 2

`garbage = ["MMM","PGM","GP"]`, `travel = [3,10]`

- Total collection time: `3 + 3 + 2 = 8`
- Last `'M'` index: 1 → metal truck travel = `travel[0]` = 3 → total metal = 4 + 3 = 7
- Last `'G'` index: 2 → glass truck travel = `travel[0] + travel[1]` = 13 → total glass = 2 + 13 = 15
- Last `'P'` index: 2 → paper truck travel = `travel[0] + travel[1]` = 13 → total paper = 2 + 13 = 15
- **Total = 8 + 3 + 13 + 13 = 37** ✅

---

## Complexity

| | Complexity |
|---|---|
| **Time** | $O(n \cdot k)$ where $n$ = number of houses, $k$ = max length of `garbage[i]` (for the `in` checks) |
| **Space** | $O(1)$ extra space |
