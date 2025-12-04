## Problem

https://leetcode.com/problems/second-largest-digit-in-a-string/description/

Given an alphanumeric string `s`, return the **second largest** numerical digit that appears in `s`, or `-1` if it does not exist.

An **alphanumeric string** is a string consisting of lowercase English letters and digits.

### Examples

**Example 1:**
```
Input: s = "dfa12321afd"
Output: 2
Explanation: The digits that appear in s are [1, 2, 3]. The second largest digit is 2.
```

**Example 2:**
```
Input: s = "abc1111"
Output: -1
Explanation: The digits that appear in s are [1]. There is no second largest digit.
```

### Constraints

- `1 <= s.length <= 500`
- `s` consists of only lowercase English letters and digits.

---

## Observations

1. **Unique Digits Only**: We need to find unique digits in the string. Duplicates should be counted only once (e.g., "1111" contains only one unique digit: 1).

2. **Mixed Characters**: The string contains both letters and digits. We need to filter out only the digits.

3. **Second Largest**: We need at least 2 distinct digits to have a second largest. If there are fewer than 2 distinct digits, return -1.

4. **Digit Range**: Digits range from 0-9, so we're working with a small bounded set (maximum 10 unique digits possible).

5. **Edge Cases**:
   - String with no digits → return -1
   - String with only one unique digit → return -1
   - String with two or more unique digits → return the second largest

---

## Solution

### Approach: Set + Sorting

**Algorithm:**

1. **Extract Unique Digits**: Use a set to store unique digits found in the string
   - Iterate through each character
   - Check if it's a digit using `isdigit()`
   - Convert to integer and add to set (automatically handles duplicates)

2. **Check Validity**: If we have fewer than 2 unique digits, return -1

3. **Find Second Largest**: 
   - Convert set to sorted list
   - Return the second-to-last element (index -2)

**Time Complexity:** O(n + k log k)
- O(n) to iterate through the string
- O(k log k) to sort the unique digits, where k ≤ 10 (at most 10 digits: 0-9)
- Since k is bounded by 10, sorting is effectively O(1)
- **Overall: O(n)**

**Space Complexity:** O(k) where k ≤ 10
- Set stores at most 10 unique digits
- **Overall: O(1)** (constant space)

**Example 1: s = "dfa12321afd"**
1. Iterate through string:
   - 'd', 'f', 'a' → skip (not digits)
   - '1' → add 1 to set: {1}
   - '2' → add 2 to set: {1, 2}
   - '3' → add 3 to set: {1, 2, 3}
   - '2', '1' → already in set, no change
   - 'a', 'f', 'd' → skip
2. Set: {1, 2, 3}, length = 3 ≥ 2 ✓
3. Sorted list: [1, 2, 3]
4. Return element at index -2: **2**

**Example 2: s = "abc1111"**
1. Iterate through string:
   - 'a', 'b', 'c' → skip
   - '1', '1', '1', '1' → all add same digit: {1}
2. Set: {1}, length = 1 < 2 ✗
3. Return **-1**

---

### Alternative Approach: Two Variables (More Efficient)

Instead of sorting, we can track the largest and second largest in a single pass:

```python
class Solution:
    def secondHighest(self, s: str) -> int:
        largest = second_largest = -1
        
        for c in s:
            if c.isdigit():
                digit = int(c)
                if digit > largest:
                    second_largest = largest
                    largest = digit
                elif digit > second_largest and digit != largest:
                    second_largest = digit
        
        return second_largest
```

**Time Complexity:** O(n)  
**Space Complexity:** O(1)

This approach is slightly more efficient as it avoids the sorting step and uses constant space without a set.

---

## Key Takeaways

- Using a **set** is an elegant way to handle duplicates automatically
- The problem has a bounded input space (only 10 possible digits), making certain operations effectively O(1)
- Always check edge cases: insufficient unique elements, empty results, etc.
- When the input domain is small and bounded, simple solutions often work best

# Tags

`String` `Hash Table` `Set` `Sorting`

