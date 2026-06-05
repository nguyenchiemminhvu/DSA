## Problem

https://leetcode.com/problems/single-number-iii/description/

```
Given an integer array nums, in which exactly two elements appear only once and all the
other elements appear exactly twice. Find the two elements that appear only once.
You can return the answer in any order.

You must write an algorithm that runs in linear runtime complexity and uses only constant
extra space.

Example 1:
Input: nums = [1,2,1,3,2,5]
Output: [3,5]
Explanation: [5, 3] is also a valid answer.

Example 2:
Input: nums = [-1,0]
Output: [-1,0]

Example 3:
Input: nums = [0,1]
Output: [1,0]

Constraints:
- 2 <= nums.length <= 3 * 10^4
- -2^31 <= nums[i] <= 2^31 - 1
- Each integer in nums will appear twice, only two integers will appear once.
```

## Observations

1. **XOR Cancels Duplicates**: XORing a number with itself always yields 0 (`a ^ a = 0`), and XOR with 0 is identity (`a ^ 0 = a`). So XORing all elements cancels every duplicate pair, leaving only the XOR of the two unique numbers.

2. **The Two Unique Numbers Must Differ in at Least One Bit**: If the two unique numbers were equal, they would be a duplicate pair — contradicting the problem's guarantee. Therefore, their XOR result is non-zero, meaning there is at least one bit position where they differ.

3. **A Differing Bit is the Key to Separation**: Once we know a bit position `i` where the two target numbers differ, we can use it as a classifier:
   - Every duplicate pair will have both copies land in the same group (same bit value → same group → cancel each other out by XOR).
   - Each of the two unique numbers will land in different groups, surviving as the sole unpaired element in each group.

4. **Any Set Bit of the XOR Result Works**: We don't need to find a special bit — any bit that is `1` in the XOR result of the two unique numbers is a valid separator. The simplest approach is to find the lowest set bit using `x & (1 << i)`.

5. **Complexity**:
   - **Time**: O(n) — two linear passes through the array.
   - **Space**: O(1) — only a constant number of integer variables are used.

## Solution

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> List[int]:
        # Step 1: XOR all numbers to get (unique1 ^ unique2)
        x = 0
        for val in nums:
            x ^= val
        
        # Step 2: Find a bit index where the two unique numbers differ
        i = 0
        while x & (1 << i) == 0:
            i += 1
        
        # Step 3: Partition numbers into two groups by bit i and XOR each group
        group1 = 0  # all numbers with bit i equal to 0
        group2 = 0  # all numbers with bit i equal to 1
        for val in nums:
            if val & (1 << i) == 0:
                group1 ^= val
            else:
                group2 ^= val
        
        return [group1, group2]
```

**How it works:**

1. **Step 1 — XOR All Elements**:
   - Since duplicates cancel out, the result `x = unique1 ^ unique2`.
   - Example: `[1,2,1,3,2,5]` → `1^2^1^3^2^5 = 3^5 = 6` (binary `110`).

2. **Step 2 — Find a Differing Bit**:
   - Scan from bit 0 upward until we find a bit that is `1` in `x`.
   - This bit must be set in exactly one of `unique1` or `unique2`.
   - Example: `6 = 110` → bit 1 is the lowest set bit (`i = 1`).

3. **Step 3 — Partition and XOR**:
   - All numbers with bit `i` = 0 go into `group1`, all others into `group2`.
   - Duplicates cancel within their group; each unique number is the lone survivor.
   - Example (bit 1):
     - `group1` (bit 1 = 0): `1, 1, 5` → `1^1^5 = 5`
     - `group2` (bit 1 = 1): `2, 3, 2` → `2^3^2 = 3`
   - Result: `[5, 3]` ✓

**Time Complexity**: O(n) — one pass for the combined XOR, one pass for the partitioned XOR.  
**Space Complexity**: O(1) — only integer variables `x`, `i`, `group1`, `group2`.

# Tags

- Array
- Bit Manipulation
- XOR
