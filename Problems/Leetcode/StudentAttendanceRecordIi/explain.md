## Problem

https://leetcode.com/problems/student-attendance-record-ii/description/

````markdown
## Problem

https://leetcode.com/problems/student-attendance-record-ii/description/

An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

- `'A'`: Absent.
- `'L'`: Late.
- `'P'`: Present.

Any student is eligible for an attendance award if they meet **both** of the following criteria:

- The student was absent (`'A'`) for **strictly fewer than 2 days total**.
- The student was **never** late (`'L'`) for **3 or more consecutive days**.

Given an integer `n`, return the number of possible attendance records of length `n` that make a student eligible for an attendance award. The answer may be very large, so return it **modulo 10⁹ + 7**.

### Examples

**Example 1:**
- Input: `n = 2`
- Output: `8`
- Explanation: There are 8 records with length 2 that are eligible: `"PP"`, `"AP"`, `"PA"`, `"LP"`, `"PL"`, `"AL"`, `"LA"`, `"LL"`. Only `"AA"` is not eligible.

**Example 2:**
- Input: `n = 1`
- Output: `3`

**Example 3:**
- Input: `n = 10101`
- Output: `183236316`

### Constraints

- `1 <= n <= 10^5`

## Observations

1. **State Space**: At any point in building a valid record, what matters is:
   - How many `'A'`s have been used so far (0 or 1 — once we hit 2 it's invalid).
   - How many consecutive `'L'`s trail the current end of the string (0, 1, or 2 — hitting 3 is invalid).
   
   These two values fully capture all information needed to decide what characters can be appended next. This is the key insight that allows a compact DP.

2. **State Definition**: Define `dp[a][l]` as the number of valid records of the current length ending with exactly `l` consecutive `'L'`s and having used exactly `a` absences total, where `a ∈ {0, 1}` and `l ∈ {0, 1, 2}`.

3. **Transitions** — from state `(a, l)` with count `dp[a][l]`, appending each character:
   - Append `'P'`: resets consecutive lates to 0, absences unchanged → goes to state `(a, 0)`.
   - Append `'A'`: resets consecutive lates to 0, increments absences → goes to state `(a+1, 0)`, only valid when `a + 1 < 2`.
   - Append `'L'`: increments consecutive lates by 1 → goes to state `(a, l+1)`, only valid when `l + 1 < 3`.

4. **Initialization**: Before any day is processed, we have one "empty" record with 0 absences and 0 trailing lates, so `dp[0][0] = 1` and all other cells are 0.

5. **Modular Arithmetic**: Since `n` can be up to 10⁵ and counts grow exponentially, every addition is taken modulo 10⁹ + 7.

6. **Space Optimization**: Because each day's `dp` only depends on the previous day's `dp`, we only need two 2×3 grids at a time (rolling array), giving O(1) extra space.

7. **Answer**: After processing all `n` days, sum every cell in `dp` — every reachable valid state corresponds to valid records.

## Solution

### Approach 1: Top-Down Memoization (Commented Out)

```python
from functools import lru_cache

@lru_cache(None)
def F(i: int, late: int, absent: int) -> int:
    if late >= 3 or absent >= 2:
        return 0
    if i >= n:
        return 1
    res = 0
    res += F(i + 1, 0, absent)         % mod  # next is P
    res += F(i + 1, 0, absent + 1)     % mod  # next is A
    res += F(i + 1, late + 1, absent)  % mod  # next is L
    return res % mod

return F(0, 0, 0)
```

**How it works:**
- `F(i, late, absent)` counts valid completions from position `i` onwards, given `late` trailing L's and `absent` total A's used so far.
- **Pruning**: return 0 immediately if constraints are violated (`late >= 3` or `absent >= 2`).
- **Base case**: return 1 when `i == n` (a complete valid record).
- **Recursive case**: branch on appending `'P'`, `'A'`, or `'L'`, updating state accordingly.
- `@lru_cache` memoizes results so each `(i, late, absent)` triple is computed at most once.

**Complexity:**
- Time: O(n × 3 × 2) = O(n) — number of distinct states.
- Space: O(n) for the cache and recursion stack.

### Approach 2: Bottom-Up DP with Rolling Array (Active Solution)

```python
dp = [[0] * 3 for _ in range(2)]
dp[0][0] = 1

for d in range(n):
    next_dp = [[0] * 3 for _ in range(2)]
    for a in range(2):
        for l in range(3):
            count = dp[a][l]
            if count == 0:
                continue

            next_dp[a][0] = (next_dp[a][0] + count) % mod          # append 'P'
            if a + 1 < 2:
                next_dp[a + 1][0] = (next_dp[a + 1][0] + count) % mod  # append 'A'
            if l + 1 < 3:
                next_dp[a][l + 1] = (next_dp[a][l + 1] + count)    # append 'L'
    dp = next_dp

res = 0
for row in dp:
    for val in row:
        res = (res + val) % mod
return res
```

**How it works:**

1. **Initialize**: A 2×3 grid where `dp[a][l]` counts records of the current length with `a` absences and `l` trailing lates. Start with `dp[0][0] = 1` (the empty record).

2. **Iterate** over each of the `n` days, computing `next_dp` from `dp`:
   - For every valid state `(a, l)` with a non-zero count:
     - **Append `'P'`**: always allowed; sends count to `next_dp[a][0]`.
     - **Append `'A'`**: allowed only if `a < 1` (i.e., no absences used yet); sends count to `next_dp[a+1][0]`.
     - **Append `'L'`**: allowed only if `l < 2` (i.e., fewer than 2 trailing lates); sends count to `next_dp[a][l+1]`.
   - Replace `dp` with `next_dp`.

3. **Sum all cells** of the final `dp` grid to get the total number of valid length-`n` records.

**Example Walkthrough** (`n = 2`):

```
Initial dp (before any day):
  l=0  l=1  l=2
a=0 [ 1,   0,   0 ]
a=1 [ 0,   0,   0 ]

After day 1:
  Transitions from dp[0][0]=1:
    → next_dp[0][0] += 1  (append P)
    → next_dp[1][0] += 1  (append A)
    → next_dp[0][1] += 1  (append L)
  dp after day 1:
    l=0  l=1  l=2
  a=0 [ 1,   1,   0 ]   (P, L)
  a=1 [ 1,   0,   0 ]   (A)

After day 2:
  From dp[0][0]=1 (ends with P):  → [0][0]+=1(PP), [1][0]+=1(PA), [0][1]+=1(PL)
  From dp[0][1]=1 (ends with L):  → [0][0]+=1(LP), [1][0]+=1(LA), [0][2]+=1(LL)
  From dp[1][0]=1 (ends with A):  → [1][0]+=1(AP),                [1][1]+=1(AL)
  dp after day 2:
    l=0  l=1  l=2
  a=0 [ 2,   1,   1 ]   (PP, LP, PL, LL)
  a=1 [ 3,   1,   0 ]   (PA, LA, AP, AL)

Sum = 2+1+1+3+1+0 = 8  ✓
```

**Complexity:**
- Time: O(n × 2 × 3) = O(n) — one pass per day over the constant-size state grid.
- Space: O(1) — only two 2×3 grids are kept at any time, independent of `n`.

### Why Bottom-Up Over Top-Down?

- Eliminates recursion stack overhead and avoids Python's default recursion limit.
- Constant extra memory instead of O(n) cache.
- More predictable performance for large `n` (up to 10⁵).

# Tags

#dynamic-programming #memoization #state-machine #modular-arithmetic


````
