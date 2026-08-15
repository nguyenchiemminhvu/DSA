## Problem

https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/

Given an integer array `nums`, return the length of the **longest subsequence** whose bitwise XOR is **non-zero**. If no such subsequence exists, return `0`.

**Examples:**
- `nums = [1,2,3]` → `2` (`[2,3]`, XOR = 1)
- `nums = [2,3,4]` → `3` (`[2,3,4]`, XOR = 5)

**Constraints:**
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^9`

---

## Ideas

### Key Observation

XOR has a useful property: `XOR(all elements) XOR x = XOR(all elements without x)`.

**Case 1: XOR of all elements ≠ 0**
The entire array is the longest valid subsequence → return `n`.

**Case 2: XOR of all elements = 0**
We must remove at least one element. Removing a non-zero element `x` yields XOR = `0 XOR x = x ≠ 0`.
So if any non-zero element exists → return `n - 1`.

**Case 3: All elements are 0**
XOR of any subsequence is always 0 → return `0`.

### Algorithm — O(n) time, O(1) space

```
total_xor = XOR of all elements
if total_xor != 0:
    return n
if any element != 0:
    return n - 1
return 0
```
