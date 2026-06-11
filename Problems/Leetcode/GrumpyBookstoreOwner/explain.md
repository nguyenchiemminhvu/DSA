## Problem

https://leetcode.com/problems/grumpy-bookstore-owner/description/

A bookstore owner has a store open for `n` minutes. You are given:
- An integer array `customers` of length `n`, where `customers[i]` is the number of customers entering at the start of minute `i`.
- A binary array `grumpy` of length `n`, where `grumpy[i] = 1` means the owner is grumpy during minute `i`, and `grumpy[i] = 0` means they are not.

Customers are only **satisfied** during minutes when the owner is **not grumpy**. The owner has a secret technique that lets them stay not grumpy for `k` consecutive minutes, but can only use it **once**.

Return the **maximum number of customers** that can be satisfied throughout the day.

**Example 1:**
```
Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16
Explanation:
  Use technique on last 3 minutes (indices 5,6,7): grumpy minutes 5 and 7 become not-grumpy.
  Satisfied = 1 + 1 + 1 + 1 + 7 + 5 = 16.
```

**Example 2:**
```
Input: customers = [1], grumpy = [0], minutes = 1
Output: 1
```

**Constraints:**
- `n == customers.length == grumpy.length`
- `1 <= minutes <= n <= 2 * 10^4`
- `0 <= customers[i] <= 1000`
- `grumpy[i]` is either `0` or `1`

---

## Observations

1. **Base satisfied customers are fixed.** Every minute where `grumpy[i] == 0` always contributes its customers regardless of where the technique is applied. This forms a fixed baseline.

2. **The technique only matters on grumpy minutes.** Applying the technique to a window that covers already-not-grumpy minutes wastes the technique since those customers are already satisfied.

3. **The goal is to maximize extra gain.** Given a sliding window of size `k`, the additional customers gained equals the sum of `customers[i]` for all grumpy minutes (`grumpy[i] == 1`) inside the window.

4. **Sliding window is the right tool.** We need to find the window of exactly `k` consecutive minutes that maximizes the sum of customers in grumpy minutes. This is a classic fixed-size sliding window problem.

5. **Answer = base + best extra gain.** Once we find the window with maximum extra gain, we add it to the baseline to get the final answer.

---

## Solution Explanation

```python
class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], k: int) -> int:
        n = len(customers)

        # Step 1: Compute baseline — customers satisfied without using the technique.
        # These are customers in minutes where the owner is already not grumpy.
        total = sum(val for i, val in enumerate(customers) if grumpy[i] == 0)

        res = total
        l = 0
        additional = 0

        # Step 2: Slide a window of size k across all minutes.
        for r in range(n):
            # Expand window: accumulate extra customers from grumpy minutes on the right.
            if grumpy[r] == 1:
                additional += customers[r]
            
            # Shrink window from the left if it exceeds size k.
            while r - l + 1 > k:
                if grumpy[l] == 1:
                    additional -= customers[l]
                l += 1
            
            # Update result: baseline + best extra gain seen so far.
            res = max(res, total + additional)
        
        return res
```

### Step-by-step walkthrough (Example 1)

```
customers = [1, 0, 1, 2, 1, 1, 7, 5]
grumpy    = [0, 1, 0, 1, 0, 1, 0, 1]
k = 3
```

**Step 1 — Baseline:**  
Non-grumpy minutes: indices 0, 2, 4, 6 → `1 + 1 + 1 + 7 = 10`

**Step 2 — Sliding window (tracking extra from grumpy minutes only):**

| Window `[l..r]` | `additional` | `total + additional` |
|-----------------|:------------:|:--------------------:|
| `[0..0]`        | 0            | 10                   |
| `[0..1]`        | 0 (g=1, +0)  | 10 + 0 = 10          |
| `[0..2]`        | 0            | 10                   |
| `[0..1..2]` → wait, let's be precise: |  |  |
| `[0..2]` (r=2)  | 0            | 10                   |
| `[1..3]` (r=3)  | 0+2=2        | 12                   |
| `[2..4]` (r=4)  | 0 (only idx3 grumpy, removed idx1) → 2 | 12 |
| `[3..5]` (r=5)  | 2+1=3        | 13                   |
| `[4..6]` (r=6)  | 1 (removed idx3, 2 out) → 1 | 11 |
| `[5..7]` (r=7)  | 1+5=6        | **16** ✓             |

**Best window is `[5..7]`**, gaining 6 extra → `10 + 6 = 16`.

### Complexity

| | |
|---|---|
| **Time** | $O(n)$ — single pass with a sliding window |
| **Space** | $O(1)$ — only a few variables used |
