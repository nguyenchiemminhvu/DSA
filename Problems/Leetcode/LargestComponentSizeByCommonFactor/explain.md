## Problem

https://leetcode.com/problems/largest-component-size-by-common-factor/description/

Given an integer array `nums` of unique positive integers, build an undirected graph where:
- Each element `nums[i]` is a node.
- There is an edge between `nums[i]` and `nums[j]` if they share a **common factor greater than 1**.

Return the **size of the largest connected component** in this graph.

---

## Observations

1. **Shared prime factor = same component.**  
   Two numbers share a common factor > 1 if and only if they share at least one common **prime** factor. So instead of checking every pair of numbers directly (O(n²)), it's sufficient to group numbers by their prime factors.

2. **Use prime factorization as the bridge.**  
   For each number, find all its prime factors. If two numbers share the same prime factor `p`, they must be in the same connected component.

3. **DSU is the right tool.**  
   We need to efficiently merge sets of numbers that share a prime factor and query the size of each resulting component. DSU (Disjoint Set Union / Union-Find) with union-by-size and path compression does both in near-constant amortized time.

4. **One representative per prime factor is enough.**  
   We only need to record the index of the *first* number seen for each prime factor `p`. Every subsequent number that also has `p` gets unioned with that representative — transitivity then handles chains automatically.

---

## Solution Explanation

### Key idea

Instead of asking "do `nums[i]` and `nums[j]` share a factor?", ask "do they share a *prime* factor?". Track the mapping `prime → index` and union numbers that share the same prime.

### Step-by-step walkthrough

**1. Initialize DSU**  
Create `n` nodes, one per index in `nums`.

**2. Factorize each number and union through primes**

For each `nums[i]`:
- Trial-divide by all `d` from 2 up to `sqrt(nums[i])`.
- If `d` divides `nums[i]`:
  - If `d` has never been seen as a prime factor before → record `mp[d] = i`.
  - Otherwise → union `i` with `mp[d]` (the first number that had factor `d`).
  - Divide out all occurrences of `d` from the running copy `temp`.
- After the loop, if `temp > 1`, it is the remaining large prime factor — apply the same lookup/union logic.

Why divide out `d` completely (`while temp % d == 0`)? So that the outer `while d*d <= val` loop only tests **prime** values of `d` effectively — composite divisors would have already been divided away. This is the standard trial division approach.

**3. Count component sizes**

Iterate over all indices, find each node's root with `dsu.find(i)`, and count occurrences of each root in a frequency map.

**4. Return the maximum frequency.**

### Dry run — `nums = [4, 6, 15, 35]` (indices 0–3)

| i | val | Prime factors | Actions |
|---|-----|---------------|---------|
| 0 | 4   | 2             | `mp[2] = 0` |
| 1 | 6   | 2, 3          | union(1, mp[2]=0); `mp[3] = 1` → {0,1} joined |
| 2 | 15  | 3, 5          | union(2, mp[3]=1) → {0,1,2}; `mp[5] = 2` |
| 3 | 35  | 5, 7          | union(3, mp[5]=2) → {0,1,2,3}; `mp[7] = 3` |

All four nodes end up in the same component → answer is **4**.

### Complexity

| | Complexity |
|---|---|
| Time | $O(n \cdot \sqrt{M})$ where $M = \max(\text{nums})$ |
| Space | $O(n + P)$ where $P$ is the number of distinct primes up to $M$ |

---

## Implementation

```python
class DSU:
    def __init__(self, size: int):
        self.parent = list(range(size))
        self.size = [1] * size

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # path compression
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False

        if self.size[root_x] < self.size[root_y]:
            root_x, root_y = root_y, root_x  # union by size

        self.parent[root_y] = root_x
        self.size[root_x] += self.size[root_y]
        return True

class Solution:
    def largestComponentSize(self, nums: List[int]) -> int:
        n = len(nums)
        dsu = DSU(n)

        mp = {}  # prime factor -> index of first number with that factor
        for i, val in enumerate(nums):
            d = 2
            temp = val
            while d * d <= val:
                if temp % d == 0:
                    if d not in mp:
                        mp[d] = i
                    else:
                        dsu.union(i, mp[d])

                    while temp % d == 0 and temp > 1:
                        temp //= d

                d += 1

            if temp > 1:  # remaining prime factor (> sqrt(val))
                if temp not in mp:
                    mp[temp] = i
                else:
                    dsu.union(i, mp[temp])

        # count component sizes
        count = defaultdict(int)
        for i in range(n):
            root = dsu.find(i)
            count[root] += 1
        return max(count.values())
```
