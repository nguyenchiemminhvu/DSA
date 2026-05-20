## Problem

**Link:** https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/description

You are given **two identical eggs** and a building with **n floors** (labeled 1 to n).

**Critical Property:** There exists a floor `f` (where `0 <= f <= n`) such that:
- Any egg dropped from a floor **higher than f** will **break**
- Any egg dropped from floor **f or below** will **not break**

**Goal:** Determine the minimum number of moves (drops) needed to find floor `f` with **certainty** in the **worst case**.

**Constraints:**
- You can reuse an unbroken egg
- Once an egg breaks, you can no longer use it
- You must identify `f` exactly (distinguish between all n+1 possible values: 0, 1, ..., n)

**Examples:**

Example 1:
- Input: n = 2
- Output: 2
- Explanation: Drop egg 1 from floor 1. If breaks → f=0. If not, drop from floor 2. If breaks → f=1. Else → f=2.

Example 2:
- Input: n = 100
- Output: 14
- Strategy: Drop first egg at floors 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 102, 104, 105. When it breaks, use the second egg to linearly search the remaining range.

---

## Observations

### 1. **Two-Egg Constraint Creates a Trade-off**
- With 1 egg: You must drop linearly from floor 1, 2, 3, etc. → **O(n) moves** in worst case
- With 2 eggs: You can be strategic with the first egg, then use the second as a fallback
- The second egg becomes your "insurance" when the first breaks

### 2. **Optimal Strategy Uses Decreasing Intervals**
The key insight is to use **variable-sized intervals** instead of binary/linear search:
- Drop first egg at: `k, k+(k-1), k+(k-1)+(k-2), ...`
- Each interval decreases by 1
- When first egg breaks, use second egg to linearly search the remaining range
- This ensures every decision path takes exactly the same number of moves (balanced worst-case)

### 3. **Maximum Coverage Formula**
With **m moves**, the maximum number of floors you can determine is the sum:
$$m + (m-1) + (m-2) + \ldots + 1 = \frac{m(m+1)}{2}$$

To find f among n floors, you need the minimum m where:
$$\frac{m(m+1)}{2} \geq n$$

### 4. **Worst-Case Equalization**
Every execution path through the decision tree takes exactly **m moves**:
- If first egg breaks on 1st drop: `1 + (m-1) remaining` = m moves total
- If first egg breaks on 2nd drop: `2 + (m-2 remaining)` = m moves total  
- If first egg never breaks: m moves total

This balanced property is what makes the greedy interval strategy optimal.

---

## Solution

### Algorithm
```python
class Solution:
    def twoEggDrop(self, n: int) -> int:
        k = 1
        while k * (k - 1) // 2 < n:
            k += 1
        return k - 1
```

### How It Works

**Step 1: Find Minimum k**
- Start with `k = 1`
- Increment `k` until `k * (k-1) / 2 >= n`
- Return `k - 1`

**Step 2: The Math**

When we exit the loop with some value `k`, we have:
- `k * (k-1) / 2 >= n` (loop condition became false)
- We return `k - 1` as the answer

The returned value represents the minimum number of moves because:
- With `m = k - 1` moves, we can cover `(k-1) * k / 2` floors
- We need `(k-1) * k / 2 >= n` for m moves to be sufficient
- This is exactly our loop condition when rearranged

**Step 3: Example Walkthrough**

**Example 1: n = 2**
```
k=1: 1 * 0 / 2 = 0 < 2 → increment k
k=2: 2 * 1 / 2 = 1 < 2 → increment k  
k=3: 3 * 2 / 2 = 3 >= 2 → exit loop
return 3 - 1 = 2
```

With 2 moves, we can cover: 2 + 1 = 3 floors (f ∈ {0, 1, 2})

**Example 2: n = 100**
```
k=14: 14 * 13 / 2 = 91 < 100 → increment k
k=15: 15 * 14 / 2 = 105 >= 100 → exit loop
return 15 - 1 = 14
```

With 14 moves, we can cover: 14 + 13 + 12 + ... + 1 = 105 floors

### Why This Works

The algorithm leverages the mathematical relationship between:
1. **Move count (m)** and **floor capacity**: m + (m-1) + ... + 1 = m(m+1)/2
2. **Optimal drop intervals**: Drop first egg at positions that decrease by 1 each time

Instead of simulating the decision tree (which would require dynamic programming), we directly solve the quadratic inequality to find the minimum m.

### Complexity Analysis

- **Time Complexity:** `O(√n)`
  - The while loop runs until `k² ≈ 2n`, so k ≈ √(2n) iterations
  
- **Space Complexity:** `O(1)`
  - Only constant extra space used

---

## Key Insights

1. **Problem transformation:** Converting "minimize moves for n floors" to "find minimum k such that k(k+1)/2 ≥ n"
2. **Greedy intervals:** Using decreasing intervals (k, k-1, k-2, ...) naturally creates a balanced decision tree
3. **Closed-form solution:** This elegant formulation replaces complex DP with simple arithmetic

# Tags
#egg-drop #greedy #binary-search-on-answer #quadratic-formula #two-pointers

