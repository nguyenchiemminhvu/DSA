## Problem

https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/description/

Given two integers `num1` and `num2` representing an inclusive range `[num1, num2]`, calculate the **total waviness** of all numbers in this range.

**Waviness Definition:**
- A digit is a **peak** if it is strictly greater than both of its immediate neighbors
- A digit is a **valley** if it is strictly less than both of its immediate neighbors
- First and last digits cannot be peaks or valleys
- Numbers with fewer than 3 digits have waviness = 0
- Waviness = total count of peaks + valleys

**Constraints:**
- 1 ≤ num1 ≤ num2 ≤ 10⁵

## Observations

1. **Brute Force Approach**: We can iterate through every number in the range and calculate its waviness individually.

2. **Waviness Calculation**: For each number:
   - Extract digits one by one (from right to left)
   - For every three consecutive digits, check if the middle digit is a peak or valley
   - Count all peaks and valleys

3. **Digit Extraction**: Using modulo 10 and integer division to extract digits is efficient.

4. **Early Termination**: Once we have at least 3 digits extracted, we can start checking for peaks/valleys. For a 3-digit number, only the middle digit can be a peak/valley.

5. **Consecutive Digits**: The key insight is that we only need to examine consecutive triplets of digits. For a number like 4848:
   - Digits (right to left): 8, 4, 8, 4
   - Triplets: (8,4,8) → middle 4 is valley; (4,8,4) → middle 8 is peak
   - Total waviness = 2

6. **Time Complexity**: O((num2 - num1) × d) where d is the average number of digits (max ~5 for 10⁵). Since the range is at most 10⁵, this is acceptable.

7. **Space Complexity**: O(d) for storing digits of each number.

## Solution

The given solution uses a straightforward approach:

```python
class Solution:
    def totalWaviness(self, left: int, right: int) -> int:
        count = 0
        for val in range(left, right + 1):
            arr = []
            while val:
                arr.append(val % 10)
                if len(arr) >= 3:
                    a, b, c = arr[-3], arr[-2], arr[-1]
                    # Check if middle digit is peak or valley
                    if b > a and b > c:  # peak
                        count += 1
                    elif b < a and b < c:  # valley
                        count += 1
                val //= 10
        return count
```

**Algorithm Explanation:**

1. **Iterate** through each number in the range [left, right]
2. **Extract digits** from right to left into an array using modulo and division
3. **As we extract**, once we have 3 or more digits:
   - Get the last 3 digits: `a` (third-to-last), `b` (second-to-last), `c` (last)
   - Check if `b` is a peak: `b > a AND b > c`
   - Check if `b` is a valley: `b < a AND b < c`
   - If either condition is true, increment the count
4. **Return** the total count

**Example Walkthrough (num = 4848):**

- Extract digits: [8], then [8,4], then [8,4,8], then [8,4,8,4]
- When len=3: triplet=(8,4,8), middle=4, is 4 < 8 AND 4 < 8? YES → valley, count=1
- When len=4: triplet=(4,8,4), middle=8, is 8 > 4 AND 8 > 4? YES → peak, count=2
- Final result: 2 ✓

**Why Extract from Right to Left?**

This approach naturally processes digits in a way that allows us to detect all peaks and valleys. When we encounter the third digit, we already have the previous two, so we can immediately check if the second-to-last digit forms a peak or valley with its neighbors.

# Tags
- #digit-manipulation
- #iteration
- #brute-force
- #range-query

