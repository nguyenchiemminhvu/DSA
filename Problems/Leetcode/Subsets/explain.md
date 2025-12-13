## Problem

https://leetcode.com/problems/subsets/description/

Given an integer array `nums` of **unique elements**, return all possible **subsets** (the power set).

The solution set must not contain duplicate subsets. Return the solution in **any order**.

**Example 1:**
```
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

**Example 2:**
```
Input: nums = [0]
Output: [[],[0]]
```

**Constraints:**
- `1 <= nums.length <= 10`
- `-10 <= nums[i] <= 10`
- All the numbers of nums are unique

## Observations

1. **Power Set Size**: For an array with `n` elements, the power set contains exactly `2^n` subsets
   - This is because each element has 2 choices: either include it or exclude it
   - For `[1,2,3]`: 2³ = 8 subsets

2. **Binary Representation**: Each subset can be represented as a binary number
   - Each bit position corresponds to an element in the array
   - If bit `i` is 1, include `nums[i]`; if 0, exclude it
   - Example with `[1,2,3]`:
     - `000` (0) → `[]`
     - `001` (1) → `[1]`
     - `010` (2) → `[2]`
     - `011` (3) → `[1,2]`
     - `100` (4) → `[3]`
     - `101` (5) → `[1,3]`
     - `110` (6) → `[2,3]`
     - `111` (7) → `[1,2,3]`

3. **No Duplicates**: Since all numbers are unique, bit manipulation naturally avoids duplicates

## Solution

1. **Calculate total subsets**: `nn = (1 << n)` computes 2^n
   - `1 << n` is equivalent to `2^n`

2. **Iterate through all masks**: Loop from `0` to `2^n - 1`
   - Each number represents a unique subset configuration

3. **Check each bit**: For each mask, check which bits are set
   - `(1 << i) & mask` checks if bit `i` is set in `mask`
   - If true, include `nums[i]` in the current subset

4. **Use set to avoid duplicates**: Converts lists to tuples for hashing

### Issue in the Code:

The inner loop `for i in range(32)` should be `for i in range(n)`:
- Currently iterates through 32 bits, which can cause **IndexError** when `i >= n`
- Should only check the first `n` bits since we have `n` elements

### Complexity Analysis:

- **Time Complexity**: O(n × 2^n)
  - Generate 2^n subsets
  - Each subset takes O(n) time to construct
  
- **Space Complexity**: O(n × 2^n)
  - Store 2^n subsets
  - Average subset size is n/2

### Alternative Approaches:

1. **Backtracking**: Recursively build subsets by including/excluding each element
2. **Iterative**: Start with `[[]]`, for each number, add it to all existing subsets
3. **Cascading**: Similar to iterative but creates new subsets by appending current element

# Tags

`Array` `Backtracking` `Bit Manipulation` `Power Set` `Combinations`

