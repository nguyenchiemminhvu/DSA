## Problem

https://leetcode.com/problems/tuple-with-same-product/description/

Given an array `nums` of **distinct positive integers**, return the number of tuples `(a, b, c, d)` such that `a * b = c * d` where `a, b, c, d` are elements of `nums`, and `a != b != c != d`.

---

## Observations

1. **Pair-product grouping:** Every valid tuple is formed by two disjoint pairs from `nums` that share the same product. Instead of iterating over all 4-tuples (O(n⁴)), we can enumerate all pairs (O(n²)) and group them by their product.

2. **Choosing two pairs:** If a product value appears in `v` different pairs, we need to pick any 2 of those pairs to form a valid tuple. The number of ways to choose 2 pairs from `v` is the combination:

$$\binom{v}{2} = \frac{v \cdot (v-1)}{2}$$

3. **Counting arrangements:** Once we fix two pairs `{a, b}` and `{c, d}`, the tuple `(a, b, c, d)` can be arranged in **8 distinct ways**:
   - Swap positions of `a` and `b` within the first slot → ×2
   - Swap positions of `c` and `d` within the second slot → ×2
   - Swap the two pairs (first pair ↔ second pair) → ×2
   - Total: 2 × 2 × 2 = **8**

4. **All elements are distinct:** Because all values in `nums` are distinct, any two different pairs automatically have 4 distinct elements, so no extra deduplication is needed.

---

## Solution

```python
class Solution:
    def tupleSameProduct(self, nums: List[int]) -> int:
        n = len(nums)
        mp = defaultdict(int)

        # Step 1: Count how many pairs produce each product
        for i in range(n):
            for j in range(i + 1, n):
                mp[nums[i] * nums[j]] += 1
        
        res = 0

        # Step 2: For each product with v pairs, choose 2 pairs (C(v,2)) and multiply by 8
        for k, v in mp.items():
            res += (v * (v - 1) // 2) * 8

        return res
```

### Walkthrough

| Step | Action |
|------|--------|
| 1 | Enumerate all $\binom{n}{2}$ pairs `(nums[i], nums[j])`, compute their product, and increment the count in a hashmap. |
| 2 | For every product with count `v`, there are $\binom{v}{2}$ ways to pick 2 pairs, each yielding **8** distinct tuples. |

### Example: `nums = [2, 3, 4, 6]`

Pairs and products:
- 2×3=6, 2×4=8, 2×6=**12**, 3×4=**12**, 3×6=18, 4×6=24

Product 12 appears `v = 2` times → $\binom{2}{2} \times 8 = 1 \times 8 = 8$ ✅

### Complexity

| | |
|---|---|
| **Time** | $O(n^2)$ — enumerate all pairs |
| **Space** | $O(n^2)$ — at most $\binom{n}{2}$ entries in the hashmap |
