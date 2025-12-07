## Problem

https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/description/

```
Given a binary string s without leading zeros, return true if s contains 
at most one contiguous segment of ones. Otherwise, return false.

Example 1:
Input: s = "1001"
Output: false
Explanation: The ones do not form a contiguous segment.

Example 2:
Input: s = "110"
Output: true

Constraints:
- 1 <= s.length <= 100
- s[i] is either '0' or '1'
- s[0] is '1'
```

## Observations

1. **No Leading Zeros**: The string always starts with '1' (guaranteed by constraints)

2. **Contiguous Segment**: We need to check if all '1's appear together without any '0' separating them

3. **Key Insight**: If there's more than one segment of ones, there must be a pattern "01" somewhere in the string (a '1' that comes after a '0')
   - Valid: "1", "11", "110", "1110000"
   - Invalid: "1001", "10101", "11011"

4. **Alternative Approaches**:
   - Split by '0' and count non-empty segments
   - Check if "01" substring exists in the string
   - Use state machine to track transitions

## Solution

### Approach 1: Split and Count (Implemented)

```python
class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        return len([sub for sub in s.split('0') if sub]) <= 1
```

**How it works:**
1. Split the string by '0' character
   - `"1001".split('0')` → `['1', '', '', '1']`
   - `"110".split('0')` → `['11', '']`
2. Filter out empty strings (consecutive zeros create empty substrings)
   - `['1', '', '', '1']` → `['1', '1']` (2 segments)
   - `['11', '']` → `['11']` (1 segment)
3. Check if count of segments ≤ 1

**Time Complexity:** O(n) where n is the length of string
**Space Complexity:** O(n) for storing split results

### Approach 2: Pattern Matching (More Efficient)

```python
class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        return "01" not in s
```

**How it works:**
- If there's more than one segment of ones, there must be a '0' followed by a '1'
- This is the simplest and most efficient solution
- Examples:
  - `"1001"` contains "01" → False
  - `"110"` doesn't contain "01" → True
  - `"1"` doesn't contain "01" → True

**Time Complexity:** O(n) for substring search
**Space Complexity:** O(1)

### Approach 3: State Machine

```python
class Solution:
    def checkOnesSegment(self, s: str) -> bool:
        seen_zero = False
        for char in s:
            if char == '0':
                seen_zero = True
            elif seen_zero:  # char == '1' and we've seen a zero
                return False
        return True
```

**How it works:**
- Track if we've encountered a '0'
- If we find a '1' after seeing a '0', we have multiple segments
- Otherwise, all ones are contiguous

**Time Complexity:** O(n)
**Space Complexity:** O(1)

### Comparison

| Approach | Time | Space | Readability |
|----------|------|-------|-------------|
| Split & Count | O(n) | O(n) | Medium |
| Pattern Match | O(n) | O(1) | High |
| State Machine | O(n) | O(1) | Medium |

**Recommendation:** Approach 2 (`"01" not in s`) is the best solution - clean, efficient, and easy to understand.

# Tags
`string` `pattern-matching` `easy`

