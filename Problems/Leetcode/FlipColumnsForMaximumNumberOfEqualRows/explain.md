## Problem

https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/description/

You are given an `m x n` binary matrix. You can choose **any number of columns** and flip every cell in those columns (0 → 1, 1 → 0). Return the **maximum number of rows** that have all values equal (all 0s or all 1s) after some number of flips.

**Examples:**
- `[[0,1],[1,1]]` → `1` (no flips needed, row `[1,1]` is already uniform)
- `[[0,1],[1,0]]` → `2` (flip column 0 → both rows become `[1,1]` and `[1,1]`)
- `[[0,0,0],[0,0,1],[1,1,0]]` → `2` (flip columns 0 & 1 → rows 1 and 2 become equal)

**Constraints:** `1 <= m, n <= 300`, values are `0` or `1`.

---

## Observations

1. **When can two rows both become uniform after the same set of column flips?**  
   A row becomes all-equal if every cell ends up the same value. For that to happen to two rows *simultaneously* using the **exact same** column flips, the two rows must be either:
   - **Identical** — they flip in lockstep and reach the same uniform state.
   - **Complementary (bitwise inverse)** — one is `[0,1,0]` and the other is `[1,0,1]`. Flipping the same columns takes one to all-0s and the other to all-1s simultaneously.

2. **Key insight:** Group rows by their "canonical pattern". Two rows belong to the same group if one is the bitwise complement of the other (or they are identical). The answer is the size of the **largest such group**.

3. **How to detect complement pairs efficiently?**  
   For each row, compute its flipped version. If row A and flip(A) are both in the map, they are in the same equivalence class. The count for row A's group = `freq[A] + freq[flip(A)]`.

4. **Why not normalize to a single key?**  
   We could normalize every row to always start with `0` (flip the whole row if it starts with `1`), then count frequencies of normalized rows. Both approaches give the same result. The solution below uses the "row + its complement" trick directly.

---

## Solution Explanation

```python
class Solution:
    def maxEqualRowsAfterFlips(self, grid: List[List[int]]) -> int:
        # mp[tuple(row)] denotes the number of times this row pattern appears in the grid
        mp = defaultdict(int)
        for row in grid:
            mp[tuple(row)] += 1
        
        res = 0
        for row in grid:
            flip = [(val + 1) % 2 for val in row]   # bitwise complement of the row
            res = max(res, mp[tuple(row)] + mp[tuple(flip)])
        return res
```

**Step-by-step walkthrough:**

1. **Build a frequency map** of every row pattern (stored as a tuple for hashability).  
   `mp[pattern]` = how many rows look exactly like `pattern`.

2. **For each row**, compute its complement (`flip`), then ask:  
   *"How many rows are identical to me OR are my complement?"*  
   That sum is `mp[row] + mp[flip]` — exactly the number of rows that can all be made uniform with the same column flips.

3. **Track the maximum** across all rows.

**Why this works:**  
- If we apply column flips that turn row `R` into all-0s, then every row identical to `R` also becomes all-0s, and every row equal to `flip(R)` becomes all-1s. So all of them are "equal rows" after the flips.
- We are essentially finding the largest equivalence class under the relation "identical or complementary".

**Complexity:**
- **Time:** O(m · n) — building the map is O(m·n), and iterating over rows with complement computation is O(m·n).
- **Space:** O(m · n) — the frequency map stores at most `m` entries each of length `n`.
