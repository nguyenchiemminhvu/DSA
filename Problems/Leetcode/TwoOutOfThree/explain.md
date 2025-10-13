## Problem

https://leetcode.com/problems/two-out-of-three/

```
Given three integer arrays nums1, nums2, and nums3, return a distinct array containing all the values that are present in at least two out of the three arrays. You may return the values in any order.

Example 1:

Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
Output: [3,2]
Explanation: The values that are present in at least two arrays are:
- 3, in all three arrays.
- 2, in nums1 and nums2.

Example 2:

Input: nums1 = [3,1], nums2 = [2,3], nums3 = [1,2]
Output: [2,3,1]
Explanation: The values that are present in at least two arrays are:
- 2, in nums2 and nums3.
- 3, in nums1 and nums2.
- 1, in nums1 and nums3.

Example 3:

Input: nums1 = [1,2,2], nums2 = [4,3,3], nums3 = [5]
Output: []
Explanation: No value is present in at least two arrays.

Constraints:

1 <= nums1.length, nums2.length, nums3.length <= 100
1 <= nums1[i], nums2[j], nums3[k] <= 100
```

## Observations

1. **Duplicate handling**: Each array can contain duplicates, but we only care if a value appears in an array at least once (not how many times).

2. **Counting arrays, not occurrences**: We need to track which arrays contain each value, not how many times a value appears across all arrays.

3. **Bit manipulation for tracking**: We can use 3 bits to represent presence in the 3 arrays:
   - Bit 0 (0b001): present in nums1
   - Bit 1 (0b010): present in nums2
   - Bit 2 (0b100): present in nums3

4. **Power of two property**: If a number appears in exactly one array, its bit representation will be a power of 2 (only one bit set). If it appears in 2 or more arrays, it will have multiple bits set, making it NOT a power of 2.

5. **Power of two check**: A number `n` is a power of 2 if and only if `n & (n - 1) == 0`. Conversely, if `n & (n - 1) != 0`, then `n` has at least 2 bits set.

## Solution

### Approach: Hash Table with Bit Manipulation

**Algorithm:**

1. **Build frequency map with bit flags**:
   - Use a dictionary where keys are values from any array
   - Values are 3-bit numbers tracking which arrays contain that key
   - Iterate through nums1 and set bit 0 for each value: `d[val] |= 0b001`
   - Iterate through nums2 and set bit 1 for each value: `d[val] |= 0b010`
   - Iterate through nums3 and set bit 2 for each value: `d[val] |= 0b100`

2. **Filter values present in at least 2 arrays**:
   - For each value in the dictionary, check if it has at least 2 bits set
   - Use the trick: `v & (v - 1) != 0` to detect if multiple bits are set
   - If true, the value appears in at least 2 arrays

**Example walkthrough:**

For `nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]`:

After processing:
- `d[1] = 0b001` (only in nums1)
- `d[3] = 0b111` (in all three: 0b001 | 0b010 | 0b100)
- `d[2] = 0b011` (in nums1 and nums2: 0b001 | 0b010)

Filtering:
- `1`: `0b001 & 0b000 = 0` → skip
- `3`: `0b111 & 0b110 = 0b110` (non-zero) → include
- `2`: `0b011 & 0b010 = 0b010` (non-zero) → include

Result: `[3, 2]`

**Why `v & (v - 1)` works:**

- If `v = 0b001` (power of 2): `v - 1 = 0b000`, `v & (v - 1) = 0`
- If `v = 0b010` (power of 2): `v - 1 = 0b001`, `v & (v - 1) = 0`
- If `v = 0b100` (power of 2): `v - 1 = 0b011`, `v & (v - 1) = 0`
- If `v = 0b011` (not power of 2): `v - 1 = 0b010`, `v & (v - 1) = 0b010` ≠ 0
- If `v = 0b111` (not power of 2): `v - 1 = 0b110`, `v & (v - 1) = 0b110` ≠ 0

**Complexity:**
- Time: O(n₁ + n₂ + n₃) where nᵢ is the length of each array
- Space: O(min(n₁ + n₂ + n₃, 100)) since values are in range [1, 100]

## Tags

bit manipulation, hash table