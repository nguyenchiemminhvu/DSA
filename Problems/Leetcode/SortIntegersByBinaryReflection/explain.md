## Problem

https://leetcode.com/problems/sort-integers-by-binary-reflection/description/

You are given an integer array `nums`.

The **binary reflection** of a positive integer is defined as the number obtained by reversing the order of its binary digits (ignoring any leading zeros) and interpreting the resulting binary number as a decimal.

Sort the array in ascending order based on the binary reflection of each element. If two different numbers have the same binary reflection, the smaller original number should appear first.

Return the resulting sorted array.

**Example 1:**
```
Input: nums = [4,5,4]
Output: [4,4,5]

Explanation:
Binary reflections are:
- 4 -> (binary) 100 -> (reversed) 001 -> 1
- 5 -> (binary) 101 -> (reversed) 101 -> 5
- 4 -> (binary) 100 -> (reversed) 001 -> 1

Sorting by the reflected values gives [4, 4, 5].
```

**Example 2:**
```
Input: nums = [3,6,5,8]
Output: [8,3,6,5]

Explanation:
Binary reflections are:
- 3 -> (binary) 11 -> (reversed) 11 -> 3
- 6 -> (binary) 110 -> (reversed) 011 -> 3
- 5 -> (binary) 101 -> (reversed) 101 -> 5
- 8 -> (binary) 1000 -> (reversed) 0001 -> 1

Sorting by the reflected values gives [8, 3, 6, 5].
Note that 3 and 6 have the same reflection, so we arrange them in increasing order of original value.
```

**Constraints:**
- `1 <= nums.length <= 100`
- `1 <= nums[i] <= 10^9`

## Observations

1. **Binary Reflection Definition**: We need to reverse the binary representation of a number (without leading zeros) and convert it back to decimal.

2. **Bit Manipulation Approach**: The reflection can be computed efficiently using bit operations:
   - Extract the least significant bit using `val & 1`
   - Shift the result left and add the extracted bit: `temp = (temp << 1) | (val & 1)`
   - Right shift the original value: `val >>= 1`
   - Repeat until the value becomes 0

3. **Example of Reflection Process**:
   - For `6` (binary: `110`):
     - Step 1: temp = 0, extract 0 → temp = 0
     - Step 2: temp = 0, extract 1 → temp = 1
     - Step 3: temp = 1, extract 1 → temp = 3 (binary: `11`)
     - Result: 3

4. **Sorting Requirements**:
   - Primary sort key: binary reflection value
   - Secondary sort key: original value (for stability when reflections are equal)
   - Python's tuple sorting naturally handles this: `(reflection, original_value)`

5. **Time Complexity**: O(n log n) for sorting + O(n × k) for computing reflections where k is the average number of bits
   - Overall: O(n log n) since k ≤ 30 for numbers up to 10^9

6. **Space Complexity**: O(n) for storing the tuples

## Solution

1. **Reflection Function**: 
   - Uses bit manipulation instead of string conversion for efficiency
   - `temp << 1` shifts all bits left (multiplies by 2)
   - `val & 1` extracts the rightmost bit
   - `val >>= 1` moves to the next bit

2. **Tuple Sorting**:
   - Python sorts tuples lexicographically
   - `(reflection, value)` ensures correct ordering when reflections are equal
   - This automatically handles the tie-breaking requirement

3. **Alternative Approaches**:
   - String manipulation: `int(bin(val)[2:][::-1], 2)` (less efficient)
   - Custom comparator: More verbose but equivalent

**Walkthrough with Example 2:**
```
nums = [3, 6, 5, 8]

Reflections:
- 3 (11) → 3 (11)
- 6 (110) → 3 (11)
- 5 (101) → 5 (101)
- 8 (1000) → 1 (1)

Tuples: [(3, 3), (3, 6), (5, 5), (1, 8)]
Sorted: [(1, 8), (3, 3), (3, 6), (5, 5)]
Result: [8, 3, 6, 5]
```

# Tags

`Sorting` `Bit Manipulation` `Array`

