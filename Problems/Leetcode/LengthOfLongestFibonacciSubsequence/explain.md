## Problem

https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description

````markdown
## Problem

https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description

Given a **strictly increasing** array `arr` of positive integers, return the **length of the longest Fibonacci-like subsequence** of `arr`. If none exists, return `0`.

A sequence `x1, x2, ..., xn` is **Fibonacci-like** if:
- `n >= 3`
- `xi + xi+1 == xi+2` for all valid `i`

A **subsequence** keeps relative order but may skip elements (e.g., `[3,5,8]` is a subsequence of `[3,4,5,6,7,8]`).

**Example 1:**
```
Input:  arr = [1,2,3,4,5,6,7,8]
Output: 5
Reason: [1,2,3,5,8]
```

**Example 2:**
```
Input:  arr = [1,3,7,11,12,14,18]
Output: 3
Reason: [1,11,12], [3,11,14], or [7,11,18]
```

**Constraints:**
- `3 <= arr.length <= 1000`
- `1 <= arr[i] < arr[i+1] <= 10^9`

## Observations

1. **A Fibonacci-like sequence is fully determined by its first two elements.**  
   Once you fix `a = arr[i2]` and `b = arr[i1]`, every subsequent term is forced: `a+b`, `b+(a+b)`, etc. There is no branching — you just keep extending as long as the next required value exists in `arr`.

2. **Membership check needs to be O(1).**  
   `arr` can be up to 1000 elements, but the values can be up to `10^9`. A hash map `{value → index}` gives constant-time lookup for "does value `x` exist in `arr`?".

3. **We only need to try all pairs as starting points.**  
   There are `O(n^2)` pairs `(i2, i1)` with `i2 < i1`. For each pair, we greedily extend the chain. Each extension step is O(1), and chains can't be longer than O(log(max_value)) because Fibonacci numbers grow exponentially — so the inner `while` loop is effectively bounded.

4. **Result filtering: only count chains of length ≥ 3.**  
   Every pair trivially has length 2, so we only update the answer when we've actually found a Fibonacci-like subsequence.

## Solution

```python
from collections import defaultdict
from typing import List

class Solution:
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        n = len(arr)

        # Step 1: Build a value-to-index map for O(1) lookups
        mp = defaultdict(int)
        for i, val in enumerate(arr):
            mp[val] = i

        res = 0

        # Step 2: Try every pair (arr[i2], arr[i1]) as the first two elements
        for i2 in range(n - 2):
            for i1 in range(i2 + 1, n - 1):
                length = 2
                a, b = arr[i2], arr[i1]

                # Step 3: Greedily extend the Fibonacci chain
                while True:
                    s = a + b          # the next required value
                    if s not in mp:    # if it's not in arr, chain ends
                        break
                    length += 1
                    a, b = b, s        # slide the window forward

                # Step 4: Only record chains of valid length (>= 3)
                if length >= 3:
                    res = max(res, length)

        return res
```

**How it works, step by step:**

| Step | What happens |
|------|-------------|
| Build `mp` | Map each value in `arr` to its index so we can check "does value X exist?" in O(1). |
| Outer loops | Pick every ordered pair `(a, b)` from `arr` where `a` comes before `b`. These become the seed of a potential Fibonacci chain. |
| Inner `while` | Compute the required next term `s = a + b`. If `s` is in `arr`, extend the chain and advance `a, b = b, s`. Repeat until the chain can no longer grow. |
| Update result | If the chain reached length ≥ 3, it's a valid Fibonacci-like subsequence — update the global max. |

**Complexity:**
- **Time:** $O(n^2 \log M)$ — $n^2$ pairs, each extended at most $O(\log M)$ times where $M = \max(\text{arr})$ (because Fibonacci values grow exponentially).
- **Space:** $O(n)$ for the hash map.

# Tags

`Hash Map` `Greedy` `Subsequence` `Dynamic Programming`
````
