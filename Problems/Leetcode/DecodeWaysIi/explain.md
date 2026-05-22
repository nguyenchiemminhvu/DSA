## Problem

https://leetcode.com/problems/decode-ways-ii/description

## Problem

https://leetcode.com/problems/decode-ways-ii/description

### Problem Description

A message containing letters from A-Z can be encoded into numbers using the following mapping:
- `'A' -> "1"`
- `'B' -> "2"`
- ...
- `'Z' -> "26"`

To decode an encoded message, all digits must be grouped and mapped back into letters using the reverse mapping (there may be multiple ways).

**Key Constraints:**
- Grouping must be valid: `"06"` cannot map to `'F'` because `"6"` ≠ `"06"`
- The encoded message may contain `'*'` character, which can represent any digit from `'1'` to `'9'` (0 is excluded)
- For example, `"1*"` can represent `"11", "12", ..., "19"` (9 possibilities)

### Examples

**Example 1:** `s = "*"`
- Output: `9`
- Explanation: `"*"` can represent `"1"` through `"9"`, each decoding to a single letter.

**Example 2:** `s = "1*"`
- Output: `18`
- Explanation: `"1*"` represents 9 encoded messages (`"11"` through `"19"`), each with 2 ways to decode.
- Total: `9 × 2 = 18`

**Example 3:** `s = "2*"`
- Output: `15`
- Explanation:
  - `"21"` through `"26"`: 6 messages × 2 ways = 12
  - `"27"` through `"29"`: 3 messages × 1 way = 3
  - Total: `12 + 3 = 15`

---

## Observations

1. **Dynamic Programming Problem:** This is a variant of the classic "Decode Ways" problem with wildcards. At each position, we need to count valid decodings.

2. **Wildcard Complexity:** The `'*'` character introduces branching:
   - A single `'*'` can be 1-9 (9 ways)
   - `'*'` as a pair can represent 10-29, but some combinations are invalid (like 27-29)

3. **Two-character groupings:**
   - `[digit][digit]`: Must be between 10-26 to be valid
   - `['*'][digit]`: Represents 10-19 if digit ≤ 6 (giving 2 options: 1-digit or 2-digit), or 17-19 if digit > 6 (only 1-digit option)
   - `[digit]['*']`: For digit=1, any of 11-19 (9 ways); for digit=2, any of 21-26 (6 ways)
   - `['*']['*']`: Represents any combination from 11-19 (9 ways) + 21-26 (6 ways) = 15 ways

4. **Memoization:** Use a memo dictionary to store results of `F(i)` to avoid recalculating.

5. **Modulo Operation:** Apply modulo `10^9 + 7` to prevent integer overflow.

---

## Solution

### Approach: Recursive DP with Memoization

The algorithm tries to decode starting from position `i`:
- **Single character decode:** Always try to take 1 character and recurse on `F(i+1)`
- **Two character decode:** Try to take 2 characters if valid and recurse on `F(i+2)`

### Base Cases

```python
if i > n:
    return 0  # Invalid: went past end
if i == n:
    return 1  # Valid: successfully decoded entire string
if s[i] == '0':
    return 0  # Invalid: '0' cannot start a code, and '0' cannot be paired with anything valid
```

### Recursive Logic

**Single character (always add):**
```
- If s[i] == '*': contributes 9 ways × F(i+1)
- If s[i] is digit 1-9: contributes 1 way × F(i+1)
```

**Two characters (when i < n-1):**

1. **Both are `'*'`:** `'*'*` represents 11-19 (9 ways) + 21-26 (6 ways) = 15 ways
   ```
   ways += 15 * F(i+2)
   ```

2. **First is `'*'`, second is digit:**
   - If digit ≤ 6: `'*'[d]` can be `1d` (1 digit) or `[1-2][d]` as 2-digit code
     - `1[d]` always works
     - `2[d]` works only if `d ≤ 6` (to stay ≤ 26)
     - Total: 2 ways
   - If digit > 6: Only `1[d]` works (since `2[d]` would exceed 26)
     - Total: 1 way
   ```
   ways += (2 if int(ch2) <= 6 else 1) * F(i+2)
   ```

3. **First is digit, second is `'*'`:**
   - If digit = 1: `1*` can be 11-19 (all valid, 9 ways)
     ```
     ways += 9 * F(i+2)
     ```
   - If digit = 2: `2*` can be 21-26 (6 ways, since 27-29 are invalid)
     ```
     ways += 6 * F(i+2)
     ```
   - If digit ≥ 3: `[d]*` cannot form a valid 2-digit code (would exceed 26)
     ```
     (no addition)
     ```

4. **Both are digits:**
   - Check if the 2-digit number is between 10-26
   ```
   if 10 <= int(ch1 + ch2) <= 26:
       ways += F(i+2)
   ```

### Time Complexity
- **O(n)** where n is the length of the string, since each position is computed at most once via memoization.

### Space Complexity
- **O(n)** for the memoization dictionary and recursion call stack.

### Code Walkthrough

```python
class Solution:
    def numDecodings(self, s: str) -> int:
        mod = 10**9 + 7
        n = len(s)
        mem = {}
        
        def F(i: int) -> int:
            # Base cases
            if i > n:
                return 0
            if i == n:
                return 1
            if s[i] == '0':
                return 0
            
            # Return memoized result if available
            if i in mem:
                return mem[i]
            
            ways = 0
            
            # Single character decode
            ch = s[i]
            ways += (9 if ch == '*' else 1) * F(i + 1)
            
            # Two character decode
            if i < n - 1:
                ch1, ch2 = s[i], s[i + 1]
                
                if ch1 == '*' and ch2 == '*':
                    ways += 15 * F(i + 2)
                else:
                    if ch1 == '*':
                        ways += (2 if int(ch2) <= 6 else 1) * F(i + 2)
                    elif ch2 == '*':
                        if ch1 == '1':
                            ways += 9 * F(i + 2)
                        if ch1 == '2':
                            ways += 6 * F(i + 2)
                    else:
                        if 10 <= int(ch1 + ch2) <= 26:
                            ways += F(i + 2)
            
            # Store and return memoized result
            mem[i] = ways % mod
            return ways % mod
        
        return F(0)
```

---

## Example Walkthroughs

### Example: `s = "1*"`

```
F(0) processes '1' and '*'
  └─ Single char: '1' → 1 * F(1)
  └─ Two chars: '1*' → can be "11"-"19" (9 ways) → 9 * F(2)

F(1) processes '*'
  └─ Single char: '*' → 9 * F(2)

F(2): i == n → return 1

Back to F(1): ways = 9 * 1 = 9
Back to F(0): ways = 1 * 9 + 9 * 1 = 9 + 9 = 18
```

### Example: `s = "2*"`

```
F(0) processes '2' and '*'
  └─ Single char: '2' → 1 * F(1)
  └─ Two chars: '2*' → can be "21"-"26" (6 ways) → 6 * F(2)

F(1) processes '*'
  └─ Single char: '*' → 9 * F(2)

F(2): i == n → return 1

Back to F(1): ways = 9 * 1 = 9
Back to F(0): ways = 1 * 9 + 6 * 1 = 9 + 6 = 15
```

---

## Tags

- Dynamic Programming
- Memoization
- Recursion
- Combinatorics
- String Parsing
- Medium Difficulty

## Observations

## Solution

# Tags

