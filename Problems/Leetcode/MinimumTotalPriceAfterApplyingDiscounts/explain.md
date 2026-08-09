## Problem

https://leetcode.com/problems/minimum-total-price-after-applying-discounts/

Given arrays `prices` and `discounts`, apply each discount to at most one item and each item receives at most one discount. Applying discount `d` to price `p` yields `p * (100 - d) / 100`. Return the minimum possible sum of final prices.

---

## Observations

- We want to **minimize** the total price, which is equivalent to **maximizing** the total savings.
- The savings from applying discount `d` to price `p` is `p * d / 100`, which is a product of two independent values.
- To maximize the sum of products when pairing two arrays, we should pair the **largest with largest** (rearrangement inequality).

**Proof by exchange argument:**  
Given prices $p_1 \geq p_2$ and discounts $d_1 \geq d_2$, compare the two possible pairings:

$$\text{Savings}_\text{sorted} = p_1 d_1 + p_2 d_2$$
$$\text{Savings}_\text{swapped} = p_1 d_2 + p_2 d_1$$

$$\text{Savings}_\text{sorted} - \text{Savings}_\text{swapped} = (p_1 - p_2)(d_1 - d_2) \geq 0$$

So sorted pairing always yields savings at least as large. This generalizes to any number of pairs.

- Discounts fewer than prices: pair each discount with a top price, leave remaining prices undiscounted — they contribute their full value.

---

## Solution

**Greedy — sort both descending, pair index by index.**

```python
class Solution:
    def minPrice(self, prices: list[int], discounts: list[int]) -> float:
        prices.sort(reverse=True)
        discounts.sort(reverse=True)
        
        total = 0.0
        n = len(prices)
        m = len(discounts)
        
        for i in range(n):
            if i < m:
                total += prices[i] * (100 - discounts[i]) / 100
            else:
                total += prices[i]
        
        return total
```

1. Sort `prices` descending and `discounts` descending.
2. Pair `prices[i]` with `discounts[i]` for every `i < m` (number of discounts).
3. Prices without a paired discount are added at full value.
4. Return the accumulated total.

**Complexity:** $O(n \log n + m \log m)$ time, $O(1)$ extra space.
