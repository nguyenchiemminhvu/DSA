## Problem

https://leetcode.com/problems/ipo/description/

LeetCode is preparing for its IPO and wants to maximize its capital by completing at most `k` projects. Each project `i` requires a minimum capital of `capital[i]` to start, and yields a `profits[i]` gain. Starting capital is `w`. After finishing a project, its profit is added to the current capital. Return the maximum capital after completing at most `k` projects.

**Example 1:**
```
Input:  k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4
```
Start project 0 (needs 0, profit 1) → w = 1. Then project 2 (needs 1, profit 3) → w = 4.

**Example 2:**
```
Input:  k = 3, w = 0, profits = [1,2,3], capital = [0,1,2]
Output: 6
```

**Constraints:**
- `1 <= k <= 10^5`
- `0 <= w <= 10^9`
- `1 <= n <= 10^5`
- `0 <= profits[i] <= 10^4`
- `0 <= capital[i] <= 10^9`

---

## Observations

1. **Greedy is optimal.** At every step, among all projects we can currently afford, picking the one with the highest profit maximizes capital gain — and a higher capital only unlocks more choices in future steps. There is no scenario where choosing a lower-profit affordable project now leads to a better overall outcome.

2. **Two-phase filtering.** There are two natural criteria to manage:
   - *Affordability*: a project can only be started when `w >= capital[i]`.
   - *Profitability*: among affordable projects, we want the maximum profit.

   These two concerns map cleanly onto two data structures:
   - A **min-heap by capital** to efficiently find newly-affordable projects as `w` grows.
   - A **max-heap by profit** to efficiently pick the best project among those already affordable.

3. **Monotone unlocking.** Because `w` only ever increases, a project that becomes affordable stays affordable. This means we never need to "put back" a project once it has been pushed into the profit heap.

4. **Early termination.** If the profit heap is empty (no project is currently affordable) before `k` rounds are done, no further progress is possible regardless of remaining rounds.

---

## Solution

```python
import heapq

class Solution:
    def findMaximizedCapital(self, k: int, w: int, profits: List[int], capital: List[int]) -> int:
        n = len(profits)
        projects = sorted(zip(capital, profits))   # min-heap by capital (sorted list)

        pq = []   # max-heap by profit (stored as negatives for Python's min-heap)
        ip = 0    # pointer into sorted projects

        for _ in range(k):
            # Unlock all projects now affordable with current capital w
            while ip < n and projects[ip][0] <= w:
                heapq.heappush(pq, -projects[ip][1])
                ip += 1

            if not pq:          # no affordable project left — stop early
                break

            best_profit = -heapq.heappop(pq)   # pick highest-profit affordable project
            w += best_profit

        return w
```

### Step-by-step walkthrough

| Round | Action | `w` after |
|-------|--------|-----------|
| Setup | Sort projects by capital: `[(0,1),(1,2),(1,3)]` | `w = 0` |
| 1 | Unlock `(0,1)` → push profit 1. Pop best profit = 1. | `w = 1` |
| 2 | Unlock `(1,2)` and `(1,3)` → push profits 2 and 3. Pop best profit = 3. | `w = 4` |

Result: **4**.

### Complexity

| | |
|---|---|
| **Time** | $O(n \log n)$ — sorting + at most $n$ heap pushes and $k$ heap pops, each $O(\log n)$ |
| **Space** | $O(n)$ — for the sorted list and the profit heap |
