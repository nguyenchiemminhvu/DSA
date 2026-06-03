## Problem

https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/description/

Given a 0-indexed integer array `nums` and a positive integer `k`, you can apply the following operation any number of times:

- Choose any element of the array and **flip one bit** in its binary representation (change a `0` to `1` or vice versa). Leading zero bits may also be flipped.

Return the **minimum number of operations** required to make the bitwise XOR of all elements of the final array equal to `k`.

**Example 1:**
```
Input: nums = [2,1,3,4], k = 1
Output: 2
```

**Example 2:**
```
Input: nums = [2,0,2,0], k = 0
Output: 0
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^6`
- `0 <= k <= 10^6`

---

## Observations

1. **One flip = one bit change in the XOR result.**  
   When you flip bit `i` in any single element, the overall XOR of the array flips bit `i` as well — because that element's contribution to each bit position in the XOR is toggled. So each operation changes exactly one bit in the total XOR.

2. **Compute the current XOR first.**  
   Let `x = nums[0] ^ nums[1] ^ ... ^ nums[n-1]`. This is the current XOR of the whole array.

3. **Find the "distance" between current XOR and target.**  
   We need the final XOR to equal `k`. Since each operation flips exactly one bit in the running XOR, the minimum number of operations equals the number of bit positions where `x` and `k` differ.  
   That is simply the **number of set bits (popcount) of `x ^ k`**.

4. **Why `x ^ k`?**  
   `x ^ k` produces a `1` in every bit position where `x` and `k` disagree. Each such disagreement requires exactly one flip operation to resolve.

---

## Solution Explanation

```python
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        x = 0
        for val in nums:
            x ^= val          # Step 1: compute current XOR of the whole array

        diff = x ^ k          # Step 2: find bits that differ between current XOR and k
        op = 0
        while diff:
            diff = diff & (diff - 1)   # Step 3: clear the lowest set bit (Brian Kernighan's trick)
            op += 1                    # count it as one required operation
        return op
```

**Step-by-step walkthrough (Example 1: `nums = [2,1,3,4]`, `k = 1`):**

| Step | Value |
|------|-------|
| Current XOR `x` | `2 ^ 1 ^ 3 ^ 4 = 4` → `(100)₂` |
| Target `k` | `1` → `(001)₂` |
| `diff = x ^ k` | `4 ^ 1 = 5` → `(101)₂` |
| Set bits in `diff` | **2** (bits 0 and 2) |
| Answer | **2** |

**Brian Kernighan's bit-counting trick:**  
The expression `diff & (diff - 1)` clears the lowest set bit of `diff` in O(1). Repeating this until `diff == 0` counts exactly how many set bits exist — i.e., how many flips are needed.

**Time complexity:** $O(n + \log(\max\_val))$ — linear scan of the array plus at most 20 bit iterations (since values ≤ 10⁶ < 2²⁰).  
**Space complexity:** $O(1)$.
