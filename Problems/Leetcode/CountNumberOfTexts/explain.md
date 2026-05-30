## Problem

https://leetcode.com/problems/count-number-of-texts/description

Alice is texting Bob using a standard phone keypad:
- `2` → abc, `3` → def, `4` → ghi, `5` → jkl, `6` → mno, `7` → pqrs, `8` → tuv, `9` → wxyz
- To type a letter, Alice presses the key `i` times, where `i` is the letter's position on that key.
  - e.g., pressing `'7'` once = `'p'`, twice = `'q'`, three times = `'r'`, four times = `'s'`

Due to a transmission error, Bob received only the raw sequence of pressed keys instead of the text. Given `pressedKeys`, return the **total number of possible messages** Alice could have sent, modulo `10^9 + 7`.

**Constraints:**
- `1 <= pressedKeys.length <= 10^5`
- `pressedKeys` only consists of digits `'2'`–`'9'`

## Observations

1. **Groups of consecutive same digits are independent.** Each maximal run of the same digit can only produce letters from that key. Different runs cannot interact, so the total count is the **product** of each group's individual count.

2. **Each group is a "generalized staircase" problem.** For a run of `L` identical presses on a key with `opts` letters (3 or 4), we need to count the number of ways to partition `L` into ordered parts where each part is between 1 and `opts`. This is exactly: count ways to climb `L` steps taking 1 to `opts` steps at a time.

3. **Keys 7 and 9 have 4 options; all others have 3.** So `opts = 4` for digits `'7'` and `'9'`, and `opts = 3` for `'2'`–`'6'` and `'8'`.

4. **Recurrence for a group of length `L` with `opts` options:**
   ```
   F(i) = F(i+1) + F(i+2) + ... + F(i+opts)
   ```
   where `F(L) = 1` (consumed all presses, one valid decode) and `F(i) = 0` for `i > L`.

5. **Sentinel character trick.** Appending `'#'` to `pressedKeys` avoids a special case for the last group — when the current character differs from the previous, we process the completed group.

6. **Memoization via `lru_cache`.** Since `F` is called with different `(length, opts)` pairs, the inner `dfs` is recreated per group. The `lru_cache` on `dfs(i)` caches results within each group's computation.

## Solution

**Approach:** Split into groups → per-group DP (generalized staircase) → multiply results.

**Algorithm:**
1. Build `keys` map: each digit `'2'`–`'9'` maps to `3`, except `'7'` and `'9'` which map to `4`.
2. Append sentinel `'#'` to `pressedKeys` and scan left to right, tracking the current run length.
3. When a new digit (or sentinel) is seen, call `F(length, opts)` for the completed run and multiply into `res`.
4. `F(length, opts)` runs a top-down DP: `dfs(i)` = ways to decode presses from position `i` to `length`.
   - Base: `dfs(length) = 1`, `dfs(i) = 0` if `i > length`.
   - Recurrence: `dfs(i) = sum(dfs(i+j) for j in 1..opts)`.
5. Return `res % (10^9 + 7)`.

**Time Complexity:** O(n · opts) — each position in each run is visited once; `opts` ≤ 4.  
**Space Complexity:** O(n) — cache entries across all groups.

**Example walkthrough for `"22233"`:**
```
Groups: "222" (digit '2', opts=3, length=3), "33" (digit '3', opts=3, length=2)

F(3, 3):  dfs(0) = dfs(1)+dfs(2)+dfs(3)
  dfs(3) = 1  (base)
  dfs(2) = dfs(3)+dfs(4)+dfs(5) = 1+0+0 = 1
  dfs(1) = dfs(2)+dfs(3)+dfs(4) = 1+1+0 = 2
  dfs(0) = dfs(1)+dfs(2)+dfs(3) = 2+1+1 = 4

F(2, 3):  dfs(0) = dfs(1)+dfs(2)+dfs(3)
  dfs(2) = 1  (base)
  dfs(1) = dfs(2)+dfs(3)+dfs(4) = 1+0+0 = 1
  dfs(0) = dfs(1)+dfs(2)+dfs(3) = 1+1+0 = 2

res = 4 * 2 = 8 ✓
```

# Tags

#dynamic-programming #memoization #string #generalized-staircase #modular-arithmetic
