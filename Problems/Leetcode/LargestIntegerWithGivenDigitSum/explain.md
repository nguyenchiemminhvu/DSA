## Problem

https://leetcode.com/problems/largest-integer-with-given-digit-sum/description/

Given two non-negative integers `n` and `s`, return the **largest** integer that has **at most** `n` digits and whose digit sum equals `s`. Return `-1` if no such integer exists.

**Constraints:** `1 <= n <= 5`, `0 <= s <= 100`

---

## Approach: Greedy

To maximize the integer, we want it to be as large as possible. There are two dimensions to consider:

1. **Number of digits** — more digits means a larger number (e.g., 900 > 99).
2. **Leading digits** — higher digits in the most significant positions produce a larger number.

### Key Observations

- A number with more digits is always larger than one with fewer digits (for positive integers), so we should **use all `n` digits**.
- To maximize the value, we greedily assign **as large a digit as possible** to each position from left to right.
- The maximum single digit is `9`, so at each position assign `min(9, s)` and subtract it from the remaining sum `s`.
- After placing digits greedily, if `s > 0` but we've used all `n` positions, return `-1` (impossible).
- After placing all needed digits, fill remaining positions with `0` (shift left by multiplying by 10).

### Special Case

- If `s == 0`, the only valid number is `0`.

### Algorithm

```
result = 0
for each of n positions (left to right):
    digit = min(9, s)
    result = result * 10 + digit
    s -= digit
    if s == 0: break

if s > 0: return -1          # sum could not be satisfied

pad remaining positions with 0 (result *= 10 for each unused digit)
return result
```

### Complexity

- **Time:** $O(n)$ — at most 5 iterations.
- **Space:** $O(1)$
