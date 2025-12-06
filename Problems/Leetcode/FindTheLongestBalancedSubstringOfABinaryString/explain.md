## Problem

https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/description/

You are given a binary string `s` consisting only of zeroes and ones.

A substring of `s` is considered **balanced** if:
- All zeroes are before ones
- The number of zeroes is equal to the number of ones inside the substring

Notice that the empty substring is considered a balanced substring.

Return the length of the longest balanced substring of `s`.

**Example 1:**
```
Input: s = "01000111"
Output: 6
Explanation: The longest balanced substring is "000111", which has length 6.
```

**Example 2:**
```
Input: s = "00111"
Output: 4
Explanation: The longest balanced substring is "0011", which has length 4.
```

**Example 3:**
```
Input: s = "111"
Output: 0
Explanation: There is no balanced substring except the empty substring, so the answer is 0.
```

**Constraints:**
- `1 <= s.length <= 50`
- `'0' <= s[i] <= '1'`

## Observations

1. **Balanced Substring Requirements:**
   - Must have the pattern: consecutive 0s followed by consecutive 1s
   - Equal count of 0s and 1s (e.g., "01", "0011", "000111")
   - Cannot have interleaved patterns like "0101" or "0110"

2. **Key Insight:**
   - When we encounter a '1' after seeing '0's, we have a potential balanced substring
   - The length of the balanced substring = `2 * min(count_0, count_1)`
   - When we see a '0' after '1', the previous sequence breaks and we start fresh

3. **State Transitions:**
   - `0 → 0`: Continue counting zeros
   - `0 → 1`: Start counting ones, check for balanced substring
   - `1 → 1`: Continue counting ones, update maximum balanced length
   - `1 → 0`: **Reset!** Previous sequence is broken, start new count from this 0

4. **Why Reset on '1' → '0'?**
   - A balanced substring must be contiguous with 0s before 1s
   - If we see "0011**0**", the last 0 cannot extend the previous "0011" pattern
   - We must start counting fresh from this new 0

## Solution

**Variables:**
- `count_0`: Number of consecutive 0s in current sequence
- `count_1`: Number of consecutive 1s following those 0s
- `prev`: Previous character to detect transitions
- `res`: Maximum balanced substring length found

**Step-by-Step Walkthrough (Example: s = "01000111"):**

| Index | Char | prev | Action | count_0 | count_1 | min * 2 | res |
|-------|------|------|--------|---------|---------|---------|-----|
| 0 | '0' | '#' | Start counting 0s | 1 | 0 | 0 | 0 |
| 1 | '1' | '0' | Start counting 1s | 1 | 1 | 2 | 2 |
| 2 | '0' | '1' | **Reset!** New sequence | 1 | 0 | 0 | 2 |
| 3 | '0' | '0' | Continue 0s | 2 | 0 | 0 | 2 |
| 4 | '0' | '0' | Continue 0s | 3 | 0 | 0 | 2 |
| 5 | '1' | '0' | Start counting 1s | 3 | 1 | 2 | 2 |
| 6 | '1' | '1' | Continue 1s | 3 | 2 | 4 | 4 |
| 7 | '1' | '1' | Continue 1s | 3 | 3 | 6 | **6** |

The longest balanced substring is "000111" with length 6.

### Complexity Analysis:

- **Time Complexity:** $O(n)$ where n is the length of string s
  - Single pass through the string
  - Constant time operations for each character
  
- **Space Complexity:** $O(1)$
  - Only using a fixed number of variables regardless of input size

### Why This Works:

The algorithm efficiently tracks "valid sequences" where zeros come before ones. By resetting `count_1` when we see a '0' and resetting `count_0` when transitioning from '1' to '0', we ensure we only consider valid balanced patterns. At each step, we calculate the maximum possible balanced substring ending at the current position using the formula `2 * min(count_0, count_1)`.

# Tags
#string #two-pointers #greedy #sliding-window

