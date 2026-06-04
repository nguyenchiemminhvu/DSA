## Problem

https://leetcode.com/problems/maximum-xor-after-operations/description/

You are given a 0-indexed integer array `nums`. In one operation, select any non-negative integer `x` and an index `i`, then update:

```
nums[i] = nums[i] AND (nums[i] XOR x)
```

You may apply the operation any number of times. Return the **maximum possible bitwise XOR** of all elements of `nums`.

**Example 1:**
- Input: `nums = [3,2,4,6]`
- Output: `7`
- Explanation: Set `x=4, i=3` → `nums[3] = 6 AND (6 XOR 4) = 6 AND 2 = 2`. Then `3 XOR 2 XOR 4 XOR 2 = 7`.

**Example 2:**
- Input: `nums = [1,2,3,9,2]`
- Output: `11`
- Explanation: Apply zero operations. `1 XOR 2 XOR 3 XOR 9 XOR 2 = 11`.

**Constraints:**
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^8`

---

## Observations

**1. The operation can only turn bits OFF, never ON.**

Let's examine `nums[i] = nums[i] AND (nums[i] XOR x)`:
- `nums[i] XOR x` flips any bits in `nums[i]` where `x` has a `1` bit.
- Then `nums[i] AND (...)` masks the result back with the original `nums[i]`.
- A bit in the result can only be `1` if it was already `1` in `nums[i]`.
- Therefore, **we can selectively clear any subset of bits from any element, but we can never set a new bit that wasn't already there**.

**2. We can clear bits independently and freely.**

For any element `nums[i]` and any bit position `b`:
- To clear bit `b`: choose `x` such that bit `b` of `x` equals bit `b` of `nums[i]`. Then `nums[i] XOR x` will have bit `b` = `0`, and after AND, bit `b` is cleared.
- Other bits of `nums[i]` are unaffected if `x` only targets bit `b`.

So for each bit position independently, we have full control over which elements keep that bit set.

**3. To maximize XOR, we want each bit in the result to be `1`.**

For a given bit position `b`:
- If **no element** has bit `b` set → bit `b` of the XOR result is always `0` (no operation can help).
- If **at least one element** has bit `b` set → we can clear bit `b` from all other elements that have it, leaving exactly **one** element with bit `b` set → XOR over all elements for bit `b` = `1`.

**Conclusion:** A bit position `b` can be `1` in the answer **if and only if** at least one element in `nums` has bit `b` set. The answer is simply the **bitwise OR of all elements**.

---

## Solution

```python
class Solution:
    def maximumXOR(self, nums: List[int]) -> int:
        res = 0
        for val in nums:
            res |= val
        return res
```

**How it works:**
- `res |= val` accumulates every bit that appears in *any* element.
- The final `res` is the OR of all values, which equals the maximum achievable XOR.

**Time Complexity:** O(n) — one pass through the array.  
**Space Complexity:** O(1) — only a single integer accumulator.

---

## Why the Commented-Out Solution Also Works

The verbose version explicitly tracks which bit positions are "available" (set in at least one element), then constructs the answer bit by bit — this is the same logic, just made explicit. The concise `OR` approach is equivalent because OR does exactly that: it marks a bit as `1` if it appears in *any* operand.
