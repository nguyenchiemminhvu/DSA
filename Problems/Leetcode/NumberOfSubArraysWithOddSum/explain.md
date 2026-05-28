## Problem

https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description

````markdown
## Problem

https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description

Given an array of integers `arr`, return the number of subarrays with an **odd sum**.

Since the answer can be very large, return it modulo $10^9 + 7$.

**Example 1:**
```
Input: arr = [1,3,5]
Output: 4
```

**Example 2:**
```
Input: arr = [2,4,6]
Output: 0
```

**Example 3:**
```
Input: arr = [1,2,3,4,5,6,7]
Output: 16
```

**Constraints:**
- `1 <= arr.length <= 10^5`
- `1 <= arr[i] <= 100`

## Observations

- The sum of a subarray `arr[i..j]` can be expressed as `prefix[j] - prefix[i-1]`.
- A subarray sum is **odd** if and only if exactly one of `prefix[j]` and `prefix[i-1]` is odd (odd XOR even = odd).
- So the number of subarrays with odd sum equals the number of pairs `(odd prefix, even prefix)` where the odd prefix index is to the right of the even prefix index.
- As we scan left to right, maintaining counts of how many prefix sums have been odd vs even so far tells us immediately how many new odd-sum subarrays end at the current position:
  - If the current prefix sum is **odd**, every previously seen **even** prefix sum pairs with it to form an odd-sum subarray.
  - If the current prefix sum is **even**, every previously seen **odd** prefix sum pairs with it to form an odd-sum subarray.
- We initialize `pre_even = 1` (representing the empty prefix `prefix[0] = 0`, which is even) and `pre_odd = 0`.
- Only the **parity** of the prefix sum matters, so we track `s & 1` instead of the full sum.

## Solution

```python
class Solution:
    def numOfSubarrays(self, arr: List[int]) -> int:
        mod = 10 ** 9 + 7

        pre_even = 1  # count of prefix sums that are even (start with 1 for the empty prefix = 0)
        pre_odd = 0   # count of prefix sums that are odd
        s = 0         # running prefix sum parity
        for val in arr:
            s = (s + val) & 1          # update parity: 0 = even, 1 = odd
            if s:                       # current prefix sum is odd
                pre_odd += 1
            else:                       # current prefix sum is even
                pre_even += 1
        # Every (odd prefix, even prefix) pair gives a subarray with odd sum.
        # Total pairs = pre_odd * pre_even
        return ((pre_odd % mod) * (pre_even % mod)) % mod
```

**Why `pre_odd * pre_even`?**

A subarray `arr[i..j]` has an odd sum iff `prefix[j] - prefix[i-1]` is odd, which happens iff one of them is odd and the other is even. After processing all elements, `pre_odd` holds the total count of prefix indices with odd parity, and `pre_even` holds the count with even parity. Any combination of one from each group (with the even prefix appearing *before* the odd one, or vice versa) yields an odd-sum subarray. Because we count prefix sums from index 0 to n, every such unordered pair corresponds to exactly one valid subarray — so the answer is simply `pre_odd × pre_even`.

**Complexity:**
- **Time:** $O(n)$ — single pass through the array.
- **Space:** $O(1)$ — only two counters and a parity variable.

# Tags

`prefix-sum` `math` `parity` `counting`
````
