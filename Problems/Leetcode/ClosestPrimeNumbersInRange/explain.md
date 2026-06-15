## Problem

https://leetcode.com/problems/closest-prime-numbers-in-range/description/

Given two positive integers `left` and `right`, find two integers `num1` and `num2` such that:
- `left <= num1 < num2 <= right`
- Both `num1` and `num2` are prime numbers
- `num2 - num1` is **minimized**

Return `[num1, num2]`. If multiple pairs have the same minimum gap, return the one with the smallest `num1`. If no valid pair exists, return `[-1, -1]`.

---

## Observations

1. **Sieve of Eratosthenes** is the ideal tool here. With `right` up to $10^6$, generating all primes up to `right` takes $O(n \log \log n)$ time and is well within limits.

2. **Twin primes** (primes differing by 2, e.g. 11 and 13) are the smallest possible gap between two odd primes. If any twin prime pair exists in `[left, right]`, the answer is immediately one of them — no pair can be closer. So we can short-circuit early when gap == 2.

3. We only need to compare **consecutive** primes in the range. A non-consecutive prime pair will always have a gap ≥ the gap of the consecutive pair that sits between them.

4. A sliding window of size 2 (or a `deque` of capacity 2) suffices — at each new prime, compare it with the previous prime and update the best pair if the gap is smaller.

---

## Solution Walkthrough

```python
class Solution:
    def closestPrimes(self, left: int, right: int) -> List[int]:
        # Step 1: Sieve of Eratosthenes up to `right`
        primes = [True] * (right + 1)
        primes[0] = primes[1] = False
        for p in range(2, int((right + 1) ** 0.5) + 1):
            if primes[p]:
                for i in range(p * p, right + 1, p):
                    primes[i] = False

        # Step 2: Scan [left, right] and track the closest consecutive prime pair
        res = [-1, -1]
        min_dist = float('inf')
        q = deque()
        for i in range(left, right + 1):
            if primes[i]:
                q.append(i)
                if len(q) >= 2:
                    if q[-1] - q[-2] < min_dist:
                        min_dist = q[-1] - q[-2]
                        res = [q[-2], q[-1]]
                    q.popleft()   # keep window size at most 2
        return res
```

### Step-by-step

| Phase | What happens |
|---|---|
| **Sieve** | Mark composites by crossing out multiples of every prime $p$ from $p^2$ up to `right`. Only need to go up to $\sqrt{\text{right}}$. |
| **Scan** | Iterate `i` from `left` to `right`. Whenever `primes[i]` is `True`, push `i` into the deque. |
| **Window check** | Once the deque holds 2 elements, `q[-1] - q[-2]` is the gap between the two most recent consecutive primes. If it beats `min_dist`, update. Then pop the front to keep the deque at size ≤ 2. |
| **Early exit (optional)** | Since gap of 2 is the theoretical minimum for odd prime pairs, you could `break` as soon as `min_dist == 2`. |

### Why `q.popleft()` is safe

After the comparison we only ever need the **last seen prime** to compare with the next one. Keeping more than one element in the deque would be wasteful. Popping the front always leaves `q[-1]` (the newer prime) as the left anchor for the next comparison.

---

## Complexity

| | |
|---|---|
| **Time** | $O(n \log \log n)$ for the sieve + $O(n)$ for the scan = $O(n \log \log n)$ where $n = \text{right}$ |
| **Space** | $O(n)$ for the boolean sieve array |
