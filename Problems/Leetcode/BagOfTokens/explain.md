## Problem

https://leetcode.com/problems/bag-of-tokens/description/

You start with `power` points and score `0`. Given an array `tokens`, each token can be played in one of two ways:

- **Face-up**: Spend `tokens[i]` power → gain `1` score (requires `power >= tokens[i]`)
- **Face-down**: Spend `1` score → gain `tokens[i]` power (requires `score >= 1`)

Return the **maximum score** achievable after playing any number of tokens.

---

## Key Insight

Sorting the tokens lets us apply a **greedy two-pointer** strategy:

- To **gain score cheaply**, always play the **smallest** token face-up (costs the least power).
- To **recover power efficiently**, always play the **largest** token face-down (gives the most power back).

This greedy choice is optimal because the order in which we exchange tokens doesn't affect feasibility — only the relative sizes matter.

---

## Solution

```python
class Solution:
    def bagOfTokensScore(self, tokens: List[int], power: int) -> int:
        n = len(tokens)
        tokens.sort()
        l, r = 0, n - 1
        cur_score = 0
        res = 0

        while l <= r:
            if power >= tokens[l]:        # Can afford the cheapest token
                cur_score += 1
                res = max(res, cur_score)
                power -= tokens[l]
                l += 1
            elif cur_score > 0:           # Sacrifice score to buy power
                cur_score -= 1
                power += tokens[r]
                r -= 1
            else:                         # Can't do either → stop
                break

        return res
```

---

## Walkthrough (Example 3)

`tokens = [100, 200, 300, 400]`, `power = 200`  
After sort: `[100, 200, 300, 400]`, `l=0`, `r=3`

| Step | Action | power | cur_score | res |
|------|--------|-------|-----------|-----|
| 1 | Face-up `tokens[0]=100` | 100 | 1 | 1 |
| 2 | Face-down `tokens[3]=400` | 500 | 0 | 1 |
| 3 | Face-up `tokens[1]=200` | 300 | 1 | 1 |
| 4 | Face-up `tokens[2]=300` | 0 | 2 | **2** |

---

## Complexity

| | Value |
|---|---|
| Time | $O(n \log n)$ — dominated by sorting |
| Space | $O(1)$ — only pointers and counters |
