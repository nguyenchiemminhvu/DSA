## Problem

https://leetcode.com/problems/distinct-subsequences-ii/description

Given a string `s`, return the number of **distinct non-empty subsequences** of `s`. Since the answer may be very large, return it modulo $10^9 + 7$.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters.

**Examples:**
- Input: `s = "abc"` → Output: `7`
  - Subsequences: "a", "b", "c", "ab", "ac", "bc", "abc"
  
- Input: `s = "aba"` → Output: `6`
  - Subsequences: "a", "b", "ab", "aa", "ba", "aba"
  
- Input: `s = "aaa"` → Output: `3`
  - Subsequences: "a", "aa", "aaa"

**Constraints:**
- $1 \leq s.length \leq 2000$
- `s` consists of lowercase English letters

## Observations

1. **Subsequence vs. Substring**: A subsequence doesn't need to be contiguous, only the relative order matters.

2. **Key Insight - Building Subsequences Character by Character**:
   - When we process each character, we can either include it or exclude it from existing subsequences
   - If we process character `c` at position `i`, we can:
     - Create new subsequences ending with `c` by appending `c` to all previous subsequences (including the empty subsequence, giving us just "c")
     - This means new count = 1 (just "c") + (count of all subsequences before position `i`)

3. **Handling Duplicates**:
   - When we encounter a character we've seen before, we need to avoid counting duplicate subsequences
   - If character `c` appeared before at position `j`, some subsequences ending with `c` might be duplicates
   - The key observation: subsequences ending with the previous `c` are exactly the duplicates we need to exclude

4. **State Tracking**:
   - For each character `c`, track how many distinct subsequences **end with** character `c`
   - When processing character `c` again:
     - New subsequences ending with `c` = 1 (just `c`) + (sum of all distinct subsequences ending with any character from positions before current position)
     - But we must subtract the old subsequences ending with `c` to avoid duplicates

## Solution

### Algorithm: Dynamic Programming with Character-Based Tracking

**Core Idea:**
- `end_with[c]` = number of distinct subsequences ending with character `c`
- For each character in the string:
  1. Calculate the sum of all previous subsequences (this represents all possible ways to extend existing subsequences)
  2. Add 1 to include the new subsequence containing just the current character
  3. Update `end_with[current_char]` with this new count
  4. This automatically handles duplicates because we overwrite the old value

**Why This Works:**
- When we see character `c` again:
  - `val` = sum of all subsequences ending with any character (using the **latest** counts)
  - `end_with[c]` = `val + 1` (overwrites the old value)
  - The old subsequences ending with `c` are implicitly removed from consideration because we only look at the current `end_with[c]` value
  - The `val` only includes counts up to the previous character, so no double-counting occurs

**Example Walkthrough for "aba":**

| Position | Char | val (sum of all) | end_with | end_with dict |
|----------|------|------------------|----------|---------------|
| 0        | 'a'  | 0                | 1        | {a: 1} |
| 1        | 'b'  | 1 (from 'a')     | 2        | {a: 1, b: 2} |
| 2        | 'a'  | 3 (1 + 2)        | 4        | {a: 4, b: 2} |
| **Final** | | | | Result = 4 + 2 = **6** |

**Trace of what each value represents:**
- After 'a' at pos 0: {a: 1} = {"a"}
- After 'b' at pos 1: {a: 1, b: 2} = {"a"} + {"b", "ab"}
- After 'a' at pos 2: {a: 4, b: 2} = {"a", "aa", "ba", "aba"} + {"b", "ab"}
- Total distinct subsequences = 6 ✓

### Code Implementation:

```python
class Solution:
    def distinctSubseqII(self, s: str) -> int:
        n = len(s)
        mod = 10 ** 9 + 7

        end_with = defaultdict(int)
        for c in s:
            # Sum of all distinct subsequences ending with any character so far
            val = 0
            for it in string.ascii_lowercase:
                val = ((val % mod) + (end_with[it] % mod)) % mod
            
            # Update subsequences ending with current character
            # = all previous subsequences + current char as single subsequence
            end_with[c] = (val + 1) % mod
        
        # Sum all subsequences ending with each character
        res = 0
        for c, count in end_with.items():
            res = ((res % mod) + (count % mod)) % mod
        return res
```

**Time Complexity:** $O(n \times 26) = O(n)$ where $n$ is the string length (we iterate through 26 lowercase letters for each character)

**Space Complexity:** $O(26) = O(1)$ for the `end_with` dictionary (at most 26 keys)

### Optimization Note:

Instead of summing all 26 letters each time, we can maintain a running total:

```python
class Solution:
    def distinctSubseqII(self, s: str) -> int:
        end_with = {}
        total = 0
        mod = 10 ** 9 + 7
        
        for c in s:
            # New subsequences ending with c = all previous + current char
            new_count = (total + 1) % mod
            
            # Update total by removing old count of c and adding new count
            total = (total - end_with.get(c, 0) + new_count) % mod
            
            end_with[c] = new_count
        
        return total
```

**Time Complexity:** $O(n)$ - much better!

# Tags

- Dynamic Programming
- Subsequences
- Character Frequency Tracking
- Modular Arithmetic

