## Problem

https://leetcode.com/problems/rotated-digits/description

An integer x is a **good number** if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

**Digit rotation rules:**
- 0, 1, and 8 rotate to themselves
- 2 and 5 rotate to each other (mirrored)
- 6 and 9 rotate to each other
- 3, 4, 7 are invalid (don't form valid digits after rotation)

**Task:** Given an integer n, return the number of good integers in the range [1, n].

**Example 1:** n = 10 → Output: 4 (numbers: 2, 5, 6, 9)
**Example 2:** n = 1 → Output: 0
**Example 3:** n = 2 → Output: 1

**Constraints:** 1 ≤ n ≤ 10⁴

## Observations

1. **Valid vs. Invalid Digits:** Only 7 digits (0, 1, 2, 5, 6, 8, 9) can be part of a good number. Any number containing 3, 4, or 7 is automatically not good.

2. **Change vs. No-Change Digits:** Among the valid digits, 2, 5, 6, 9 actually change when rotated. The digits 0, 1, 8 map to themselves. For a number to be "good," it must have at least one digit that changes; otherwise, the rotated number equals the original.

3. **Brute Force Approach:** Since n ≤ 10⁴, we can check every number from 1 to n individually without significant performance concerns.

4. **Per-Number Check:** For each number, we extract digits one by one and verify:
   - All digits are valid
   - At least one digit changes during rotation

## Solution

**Approach: Digit Extraction + Classification**

The solution uses two key sets:
- `valid = {0, 1, 2, 5, 6, 8, 9}` - digits that produce valid results after rotation
- `change = {2, 5, 6, 9}` - digits that transform into a different digit

**Algorithm:**

```python
def rotatedDigits(self, n: int) -> int:
    valid = {0, 1, 2, 5, 6, 8, 9}
    change = {2, 5, 6, 9}
    
    def is_good(x):
        has_change = False
        while x:
            d = x % 10
            if d not in valid:
                return False
            if d in change:
                has_change = True
            x //= 10
        return has_change
    
    count = 0
    for i in range(1, n + 1):
        if is_good(i):
            count += 1
    return count
```

**Step-by-step walkthrough:**

1. **Helper function `is_good(x)`:**
   - Extract each digit using modulo 10
   - If any digit is invalid (not in `valid`), return `False` immediately
   - Track whether at least one digit changes
   - Return `True` only if all digits are valid AND at least one changed

2. **Main loop:**
   - Iterate through each number from 1 to n
   - Count how many satisfy `is_good()`

**Example with n = 10:**
- 1: valid digits {1}, no changes → not good
- 2: valid digits {2}, has change → good ✓
- 3: invalid digit 3 → not good
- 4: invalid digit 4 → not good
- 5: valid digits {5}, has change → good ✓
- 6: valid digits {6}, has change → good ✓
- 7: invalid digit 7 → not good
- 8: valid digits {8}, no changes → not good
- 9: valid digits {9}, has change → good ✓
- 10: valid digits {1, 0}, no changes → not good

Result: 4 good numbers (2, 5, 6, 9)

**Time Complexity:** O(n log n) - for each of n numbers, we extract O(log n) digits
**Space Complexity:** O(1) - only constant extra space

# Tags

rotated-digits, digit-rotation, brute-force, enumeration

