# Count Special Triplets

## Problem

https://leetcode.com/problems/count-special-triplets/description/

You are given an integer array `nums`.

A **special triplet** is defined as a triplet of indices `(i, j, k)` such that:
- `0 <= i < j < k < n`, where `n = nums.length`
- `nums[i] == nums[j] * 2`
- `nums[k] == nums[j] * 2`

Return the total number of special triplets in the array.

Since the answer may be large, return it modulo `10^9 + 7`.

### Examples

**Example 1:**
```
Input: nums = [6,3,6]
Output: 1

Explanation:
The only special triplet is (i, j, k) = (0, 1, 2), where:
- nums[0] = 6, nums[1] = 3, nums[2] = 6
- nums[0] = nums[1] * 2 = 3 * 2 = 6
- nums[2] = nums[1] * 2 = 3 * 2 = 6
```

**Example 2:**
```
Input: nums = [0,1,0,0]
Output: 1

Explanation:
The only special triplet is (i, j, k) = (0, 2, 3), where:
- nums[0] = 0, nums[2] = 0, nums[3] = 0
- nums[0] = nums[2] * 2 = 0 * 2 = 0
- nums[3] = nums[2] * 2 = 0 * 2 = 0
```

**Example 3:**
```
Input: nums = [8,4,2,8,4]
Output: 2

Explanation:
There are exactly two special triplets:
1. (i, j, k) = (0, 1, 3):
   - nums[0] = 8, nums[1] = 4, nums[3] = 8
   - nums[0] = nums[1] * 2 = 4 * 2 = 8
   - nums[3] = nums[1] * 2 = 4 * 2 = 8

2. (i, j, k) = (1, 2, 4):
   - nums[1] = 4, nums[2] = 2, nums[4] = 4
   - nums[1] = nums[2] * 2 = 2 * 2 = 4
   - nums[4] = nums[2] * 2 = 2 * 2 = 4
```

### Constraints
- `3 <= n == nums.length <= 10^5`
- `0 <= nums[i] <= 10^5`

---

## Observations

1. **Understanding the relationship**: For a special triplet `(i, j, k)`:
   - Both `nums[i]` and `nums[k]` must equal `nums[j] * 2`
   - This means `j` is the "middle" element, and we need to find elements before and after it that are double its value

2. **Brute force approach** (O(n³)):
   - Try all combinations of `(i, j, k)` where `i < j < k`
   - Check if conditions are met
   - This is too slow for `n = 10^5`

3. **Optimized approach**: For each middle index `j`:
   - Count how many elements **before** `j` have value `nums[j] * 2`
   - Count how many elements **after** `j` have value `nums[j] * 2`
   - Multiply these counts to get all valid triplets with `j` as the middle

4. **Why multiplication works**:
   - If there are `a` elements with value `nums[j] * 2` before index `j`
   - And `b` elements with value `nums[j] * 2` after index `j`
   - Then we can form `a × b` special triplets (each prefix element can pair with each suffix element)

5. **Edge case**: The value `0` is special because `0 * 2 = 0`, so zeros can form triplets with other zeros

---

## Solution

### Algorithm: Prefix-Suffix Counting

**Intuition**: Instead of checking all triplets, we iterate through potential middle elements and count valid prefix/suffix pairs.

**Steps**:
1. Initialize:
   - `prefix`: Dictionary to count occurrences of each value seen so far (before current index)
   - `suffix`: Counter with all values in the array (represents values after current index)
   - `res`: Result counter

2. For each element `val` at index `j`:
   - Decrement `suffix[val]` (remove current element from suffix count)
   - Calculate valid triplets: `prefix[val * 2] × suffix[val * 2]`
     - `prefix[val * 2]`: Count of `val * 2` before index `j` (possible `i` positions)
     - `suffix[val * 2]`: Count of `val * 2` after index `j` (possible `k` positions)
   - Add current `val` to `prefix` for future iterations
   - Update result with modulo

3. Return the total count

**Time Complexity**: O(n) - Single pass through the array with O(1) dictionary operations

**Space Complexity**: O(n) - For prefix and suffix dictionaries

### Detailed Example Walkthrough

Let's trace through `nums = [8, 4, 2, 8, 4]`:

**Initial state**:
- `prefix = {}`
- `suffix = {8: 2, 4: 2, 2: 1}`
- `res = 0`

**Iteration 1**: `val = 8`
- `suffix[8] -= 1` → `suffix = {8: 1, 4: 2, 2: 1}`
- `val * 2 = 16`
- `res += prefix[16] * suffix[16] = 0 * 0 = 0`
- `prefix[8] += 1` → `prefix = {8: 1}`

**Iteration 2**: `val = 4`
- `suffix[4] -= 1` → `suffix = {8: 1, 4: 1, 2: 1}`
- `val * 2 = 8`
- `res += prefix[8] * suffix[8] = 1 * 1 = 1` ✓ (triplet: 0, 1, 3)
- `prefix[4] += 1` → `prefix = {8: 1, 4: 1}`

**Iteration 3**: `val = 2`
- `suffix[2] -= 1` → `suffix = {8: 1, 4: 1, 2: 0}`
- `val * 2 = 4`
- `res += prefix[4] * suffix[4] = 1 * 1 = 1` (total = 2) ✓ (triplet: 1, 2, 4)
- `prefix[2] += 1` → `prefix = {8: 1, 4: 1, 2: 1}`

**Iteration 4**: `val = 8`
- `suffix[8] -= 1` → `suffix = {8: 0, 4: 1, 2: 0}`
- `val * 2 = 16`
- `res += prefix[16] * suffix[16] = 0 * 0 = 0`
- `prefix[8] += 1` → `prefix = {8: 2, 4: 1, 2: 1}`

**Iteration 5**: `val = 4`
- `suffix[4] -= 1` → `suffix = {8: 0, 4: 0, 2: 0}`
- `val * 2 = 8`
- `res += prefix[8] * suffix[8] = 2 * 0 = 0`
- `prefix[4] += 1` → `prefix = {8: 2, 4: 2, 2: 1}`

**Final result**: `res = 2`

### Why This Solution Works

1. **Correct ordering**: By processing left to right, we ensure `i < j < k`
   - Elements in `prefix` are always before current index
   - Elements in `suffix` are always after current index

2. **Counting principle**: For each middle element, we multiply prefix and suffix counts
   - This gives us all valid combinations without double-counting

3. **Efficiency**: O(n) time instead of O(n³) brute force

4. **Modulo handling**: Applied at each step to prevent overflow

---

# Tags
`Array` `Hash Table` `Counting` `Prefix Sum`
