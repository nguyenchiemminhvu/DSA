## Problem

https://leetcode.com/problems/count-digit-appearances/description/

Given an integer array `nums` and an integer `digit`, return the total number of times `digit` appears across the decimal representations of all elements in `nums`.

**Example 1:**
```
Input:  nums = [12, 54, 32, 22], digit = 2
Output: 4
```
- `12` → one `2`
- `54` → zero `2`s
- `32` → one `2`
- `22` → two `2`s
- Total: `1 + 0 + 1 + 2 = 4`

**Example 2:**
```
Input:  nums = [1, 34, 7], digit = 9
Output: 0
```

**Constraints:**
- `1 <= nums.length <= 1000`
- `1 <= nums[i] <= 10^6`
- `0 <= digit <= 9`

---

## Observations

1. **Each number is independent.** The count is a simple sum — count occurrences of `digit` in each element and accumulate.

2. **Digit extraction via arithmetic vs. string conversion.** Two natural approaches exist:
   - *Arithmetic*: repeatedly take `val % 10` to inspect the last digit, then `val //= 10` to shift right. Pure math, no memory allocations per element.
   - *String conversion*: convert each number to its string representation and count character occurrences. More concise in Python.

3. **The string approach can be collapsed to a single expression.** Because `str.count` scans a substring linearly, concatenating all numbers into one big string and calling `.count` once is equivalent to summing per-element counts. This works because digit characters never span element boundaries.

4. **Constraints are small** (`nums.length ≤ 1000`, `nums[i] ≤ 10^6`). Either approach is well within time limits; the choice is purely stylistic.

---

## Solution

### Approach 1 — Arithmetic digit extraction (commented out)

```python
def countDigitOccurrences(self, nums: list[int], digit: int) -> int:
    def count_d(val: int, d: int) -> int:
        c = 0
        while val:
            c += int((val % 10) == d)
            val //= 10
        return c

    return sum(count_d(val, digit) for val in nums)
```

- For each `val`, peel digits one by one from the right with `% 10` / `// 10`.
- Time: **O(n · log₁₀ M)** where M is the maximum value.
- Space: **O(1)** per element.

### Approach 2 — Single-pass string join (submitted solution)

```python
def countDigitOccurrences(self, nums: list[int], digit: int) -> int:
    return "".join(str(val) for val in nums).count(str(digit))
```

**Step-by-step:**
1. `str(val) for val in nums` — convert every integer to its decimal string.
2. `"".join(...)` — concatenate all strings into one (e.g. `[12,54,32,22]` → `"12543222"`).
3. `.count(str(digit))` — count non-overlapping occurrences of the single-character target string. Since `digit` is a single decimal digit, `str(digit)` is always one character, so this is identical to counting character occurrences.

**Why the join trick is valid:**  
Digit characters are single characters `'0'`–`'9'`. Joining numbers without a separator cannot create a spurious occurrence of a single-digit target across a boundary (a boundary joins the *last* char of one number with the *first* char of the next — that only matters for multi-character patterns, not single characters).

- Time: **O(n · log₁₀ M)** — same asymptotic cost as approach 1; string conversion of an integer is O(number of digits).
- Space: **O(n · log₁₀ M)** — the joined string.

The string approach trades a small amount of extra memory for significantly more concise code, which is acceptable given the problem constraints.
