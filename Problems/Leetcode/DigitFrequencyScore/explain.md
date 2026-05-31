## Problem

https://leetcode.com/problems/digit-frequency-score/description/

Given an integer `n`, return its **score**, defined as:

$$\text{score}(n) = \sum_{d \in \text{distinct digits of } n} d \times \text{freq}(d)$$

where $\text{freq}(d)$ is the number of times digit $d$ appears in $n$.

**Example 1:** `n = 122` → `1*1 + 2*2 = 5`  
**Example 2:** `n = 101` → `0*1 + 1*2 = 2`

**Constraints:** $1 \leq n \leq 10^9$

---

## Observations

1. **Extract digits via repeated modulo:** `n % 10` gives the last digit; `n //= 10` removes it. Repeat until `n == 0`.
2. **Digit range is fixed:** digits are 0–9, so frequency counting is O(1) space (at most 10 buckets).
3. **Digit 0 contributes nothing:** `0 * freq(0) = 0` regardless of how many times 0 appears, so it is safely included without affecting correctness.
4. **No sorting needed:** the formula sums over distinct digits independently; order doesn't matter.
5. **Time complexity:** O(log n) — one pass to extract all digits, one pass over at most 10 buckets.

---

## Solution Explanation

```python
class Solution:
    def digitFrequencyScore(self, n: int) -> int:
        f = defaultdict(int)
        while n:
            d = n % 10
            f[d] += 1
            n //= 10
        
        res = 0
        for k, v in f.items():
            res += k * v
        return res
```

**Step 1 — Build frequency map:**  
Extract each digit of `n` from least significant to most significant using `n % 10`, increment its count in `f`, then floor-divide `n` by 10. The loop runs exactly $\lfloor \log_{10} n \rfloor + 1$ times.

**Step 2 — Accumulate score:**  
Iterate over the (digit, count) pairs. For each pair, add `digit * count` to the result. This directly computes the formula $\sum d \times \text{freq}(d)$.

**Why `defaultdict(int)`?**  
It initializes any unseen digit to 0 automatically, avoiding explicit key-existence checks.

**Trace on `n = 122`:**

| Iteration | `d` | `f` after update |
|-----------|-----|------------------|
| 1 | 2 | `{2: 1}` |
| 2 | 2 | `{2: 2}` |
| 3 | 1 | `{2: 2, 1: 1}` |

Score: `2*2 + 1*1 = 5` ✓
