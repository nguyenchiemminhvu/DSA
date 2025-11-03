## Problem

https://leetcode.com/problems/single-number-ii

```
Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.

You must implement a solution with a linear runtime complexity and use only constant extra space.

Example 1:

Input: nums = [2,2,3,2]
Output: 3

Example 2:

Input: nums = [0,1,0,1,0,1,99]
Output: 99

Constraints:

1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
Each element in nums appears exactly three times except for one element which appears once.
```

## Observations

1. **Problem Pattern**: This is a variant of the classic "Single Number" problem where every element appears exactly 3 times except one that appears once.

2. **Constraint Analysis**: 
   - Linear time complexity O(n) is required
   - Constant space complexity O(1) is preferred (though the given solution uses O(n) space)
   - Array length can be up to 30,000 elements
   - Values can be negative (range: -2³¹ to 2³¹ - 1)

3. **Key Insight**: We need to identify the element with frequency 1 among elements with frequency 3.

4. **Alternative Approaches**:
   - **Hash Map Approach** (given solution): Count frequencies - O(n) time, O(n) space
   - **Bit Manipulation Approach**: Use XOR properties with state machines - O(n) time, O(1) space
   - **Mathematical Approach**: (3 × sum of unique elements) - sum of all elements = 2 × single element

## Solution

### Hash Map Approach (Given Solution)

```python
class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        f = {}
        for val in nums:
            f[val] = f.get(val, 0) + 1
        for val in nums:
            if f[val] == 1:
                return val
        return -1
```

**How it works:**

1. **First Pass - Count Frequencies**: 
   - Iterate through the array and build a frequency map
   - `f.get(val, 0) + 1` safely increments count (handles first occurrence)

2. **Second Pass - Find Single Element**:
   - Iterate through the array again
   - Return the first element with frequency 1

**Time Complexity**: O(n) - Two passes through the array
**Space Complexity**: O(n) - Hash map stores at most n/3 + 1 unique elements

**Pros:**
- Simple and intuitive approach
- Easy to understand and implement
- Handles negative numbers naturally

**Cons:**
- Uses O(n) extra space (doesn't meet the constant space requirement)
- Makes two passes through the array

### Optimal Bit Manipulation Solution

For the constant space requirement, a bit manipulation approach using digital circuit concepts would be optimal:

```python
def singleNumber_optimal(self, nums: List[int]) -> int:
    ones = twos = 0
    for num in nums:
        ones = (ones ^ num) & ~twos
        twos = (twos ^ num) & ~ones
    return ones
```

This uses a finite state machine concept where:
- `ones`: tracks bits that appeared once
- `twos`: tracks bits that appeared twice  
- When a bit appears 3 times, both `ones` and `twos` become 0 for that bit

# Tags

- Array
- Hash Table  
- Bit Manipulation
- Frequency Counting
- Single Pass vs Multiple Pass

