## Problem

https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/description/

Given an integer array `nums`, find the number of pairs of **non-empty disjoint subsequences** `(seq1, seq2)` such that `GCD(seq1) == GCD(seq2)`. Return the answer modulo $10^9 + 7$.

---

## Observations

1. **Three choices per element:** For each element `nums[i]`, it can be:
   - Assigned to `seq1`
   - Assigned to `seq2`
   - Skipped (belongs to neither)

   This naturally suggests a DP where we track what happens to each element.

2. **GCD identity with zero:** We treat GCD `0` as a sentinel meaning "empty sequence so far". Since `gcd(0, x) = x` for any `x > 0`, this fits naturally — adding the first element to an empty group sets its GCD to that element.

3. **GCD value range is bounded:** Since `1 <= nums[i] <= 200`, all running GCDs are in the range `[0, 200]`. The state space is manageable.

4. **Symmetry:** The pair `(seq1, seq2)` and `(seq2, seq1)` are counted as **two distinct pairs** (since they are ordered pairs of subsequences). This is already handled naturally by the DP.

5. **Final condition:** A valid pair exists when both groups are non-empty (both GCDs > 0) and equal. So we sum `dp[g][g]` for all `g` from `1` to `200` after processing all elements.

---

## Approach — 2D DP on Running GCDs

**State definition:**

$$dp[g_1][g_2] = \text{number of ways to assign elements so far such that running GCD of seq1 is } g_1 \text{ and seq2 is } g_2$$

- `g1 = 0` means `seq1` is empty so far; `g2 = 0` means `seq2` is empty so far.

**Initial state:**

$$dp[0][0] = 1$$

**Transition for each element `x = nums[i]`:**

For every existing state `dp[g1][g2]`, we branch into three choices:

| Choice | New state |
|---|---|
| Skip `x` | `dp[g1][g2]` |
| Add `x` to seq1 | `dp[gcd(g1, x)][g2]` |
| Add `x` to seq2 | `dp[g1][gcd(g2, x)]` |

Where `gcd(0, x) = x` (adding first element to an empty group).

**Answer:**

$$\text{ans} = \sum_{g=1}^{200} dp[g][g]$$

**Complexity:**

- Time: $O(n \cdot V^2)$ where $V = \max(\text{nums}) = 200$
  → $200 \times 200 \times 200 = 8{,}000{,}000$ operations ✓
- Space: $O(V^2)$ for the DP table

---

## Walkthrough: `nums = [1, 2, 3, 4]` → Expected output `10`

- After processing all elements, `dp[1][1]` accumulates all ways where both groups have GCD 1.
- Since every non-empty subsequence of `[1,2,3,4]` has GCD 1 (due to the element `1`), many pairings are valid.
- The answer `10` is exactly `dp[1][1]` after processing all four elements.
