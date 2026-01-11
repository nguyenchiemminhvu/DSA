## Problem

https://leetcode.com/problems/count-residue-prefixes/

You are given a string `s` consisting only of lowercase English letters.

A **prefix** of `s` is called a **residue** if the number of distinct characters in the prefix is equal to `len(prefix) % 3`.

Return the count of residue prefixes in `s`.

A prefix of a string is a non-empty substring that starts from the beginning of the string and extends to any point within it.

**Example 1:**
```
Input: s = "abc"
Output: 2
Explanation:
- Prefix "a" has 1 distinct character and length modulo 3 is 1, so it is a residue.
- Prefix "ab" has 2 distinct characters and length modulo 3 is 2, so it is a residue.
- Prefix "abc" has 3 distinct characters but length modulo 3 is 0, so it is not a residue.
```

**Example 2:**
```
Input: s = "dd"
Output: 1
Explanation:
- Prefix "d" has 1 distinct character and length modulo 3 is 1, so it is a residue.
- Prefix "dd" has 1 distinct character but length modulo 3 is 2, so it is not a residue.
```

**Example 3:**
```
Input: s = "bob"
Output: 2
Explanation:
- Prefix "b" has 1 distinct character and length modulo 3 is 1, so it is a residue.
- Prefix "bo" has 2 distinct characters and length modulo 3 is 2, so it is a residue.
- Prefix "bob" has 2 distinct characters but length modulo 3 is 0, so it is not a residue.
```

**Constraints:**
- `1 <= s.length <= 100`
- `s` contains only lowercase English letters.

## Observations

1. **Prefix Definition**: We need to check every prefix of the string starting from index 0 to every position.

2. **Residue Condition**: A prefix at position `i` (0-indexed) is a residue if:
   - Number of distinct characters in `s[0:i+1]` equals `(i + 1) % 3`

3. **Modulo 3 Values**: The result of `length % 3` can only be 0, 1, or 2:
   - If length % 3 = 0: We need 0 distinct characters (impossible for non-empty prefix)
   - If length % 3 = 1: We need 1 distinct character
   - If length % 3 = 2: We need 2 distinct characters

4. **Key Insight**: We can track distinct characters incrementally using a set, avoiding recalculating for each prefix.

5. **Edge Cases**:
   - Single character strings: Will always have 1 residue (length=1, 1%3=1, 1 distinct char)
   - Strings where length % 3 = 0 can never be residues (need 0 distinct chars, impossible)

## Solution

```python
class Solution:
    def residuePrefixes(self, s: str) -> int:
        count = 0
        ss = set()
        for i, c in enumerate(s):
            ss.add(c)
            if len(ss) == (i + 1) % 3:
                count += 1
        return count
```

### Approach

**Algorithm**: Incremental Tracking with Set

1. **Initialize**:
   - `count = 0`: Counter for residue prefixes
   - `ss = set()`: Set to track distinct characters seen so far

2. **Iterate**: For each character at index `i`:
   - Add character to the set (automatically handles duplicates)
   - Check if `len(ss) == (i + 1) % 3`
   - If condition is met, increment count

3. **Return** the total count

### Complexity Analysis

- **Time Complexity**: O(n)
  - Single pass through the string
  - Set operations (add, len) are O(1)
  - Overall: O(n) where n is the length of string

- **Space Complexity**: O(min(n, 26))
  - Set can contain at most 26 distinct lowercase English letters
  - In practice: O(1) since alphabet size is constant
  - Worst case: O(26) = O(1)

### Why This Works

The solution leverages the fact that:
- We need to check each prefix exactly once
- The set maintains all distinct characters seen from start to current position
- We only care about the count of distinct characters, not which characters they are
- The modulo operation naturally cycles through 0, 1, 2, making it easy to check the condition

### Example Walkthrough

For `s = "abc"`:

| i | c | ss | len(ss) | (i+1) % 3 | Match? | count |
|---|---|----|---------|-----------| -------|-------|
| 0 | a | {a} | 1 | 1 | ✓ | 1 |
| 1 | b | {a,b} | 2 | 2 | ✓ | 2 |
| 2 | c | {a,b,c} | 3 | 0 | ✗ | 2 |

Result: 2

# Tags

#string #prefix #hash-set #counting #modulo-arithmetic

