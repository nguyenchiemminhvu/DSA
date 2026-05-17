## Problem

https://leetcode.com/problems/number-of-good-ways-to-split-a-string/description

**Given a string `s`, a split is called "good" if you can split `s` into two non-empty strings `sleft` and `sright` where:**
- Their concatenation equals `s` (i.e., `sleft + sright = s`)
- The number of distinct letters in `sleft` and `sright` is the same

**Return the number of good splits you can make in `s`.**

### Constraints
- `1 <= s.length <= 10^5`
- `s` consists of only lowercase English letters

### Examples

**Example 1:** `s = "aacaba"`
- Output: `2`
- Explanation:
  - `("a", "acaba")`: 1 vs 3 distinct letters ❌
  - `("aa", "caba")`: 1 vs 3 distinct letters ❌
  - `("aac", "aba")`: 2 vs 2 distinct letters ✅
  - `("aaca", "ba")`: 2 vs 2 distinct letters ✅
  - `("aacab", "a")`: 3 vs 1 distinct letters ❌

**Example 2:** `s = "abcd"`
- Output: `1`
- Split: `("ab", "cd")` with 2 distinct letters on each side

## Observations

1. **Two-Pointer/Two-Dictionary Approach**: We need to track the distinct characters on both the left and right sides as we move a split point through the string.

2. **Initialization**: Start with all characters in the right dictionary and nothing in the left dictionary. Then progressively move characters from right to left.

3. **Character Movement**: As we iterate through the string:
   - Add the current character to the left dictionary (incrementing its count)
   - Remove the current character from the right dictionary (decrementing its count)
   - If a character's count in the right dictionary becomes 0, remove it completely

4. **Comparison Point**: We can only make a split after processing each character (not after the last character, since we need both parts to be non-empty). We check if `len(left) == len(right)` at each valid position.

5. **Efficiency**: This solution runs in **O(n)** time with **O(1)** space (at most 26 lowercase letters). We avoid the naive approach of checking every split position with complete re-counting.

## Solution

```python
class Solution:
    def numSplits(self, s: str) -> int:
        n = len(s)
        left, right = {}, {}
        
        # Initialize: put all characters in right dictionary
        for c in s:
            right[c] = right.get(c, 0) + 1
        
        res = 0
        # Iterate through the string, moving characters from right to left
        for c in s:
            # Add current character to left
            left[c] = left.get(c, 0) + 1
            
            # Remove current character from right
            right[c] -= 1
            if right[c] <= 0:
                right.pop(c)
            
            # Check if this creates a good split
            # We don't check after the last character (implicitly handled by the loop)
            if len(left) == len(right):
                res += 1
        
        return res
```

### Step-by-Step Walkthrough (s = "aacaba")

```
Initial state:
left = {}, right = {'a': 4, 'c': 1, 'b': 1}

i=0, c='a':
  left = {'a': 1}, right = {'a': 3, 'c': 1, 'b': 1}
  len(left)=1, len(right)=3 ❌

i=1, c='a':
  left = {'a': 2}, right = {'a': 2, 'c': 1, 'b': 1}
  len(left)=1, len(right)=3 ❌

i=2, c='c':
  left = {'a': 2, 'c': 1}, right = {'a': 2, 'b': 1}
  len(left)=2, len(right)=2 ✅ (split at position 2: "aac" | "aba")

i=3, c='a':
  left = {'a': 3, 'c': 1}, right = {'a': 1, 'b': 1}
  len(left)=2, len(right)=2 ✅ (split at position 3: "aaca" | "ba")

i=4, c='b':
  left = {'a': 3, 'c': 1, 'b': 1}, right = {'a': 1}
  len(left)=3, len(right)=1 ❌

i=5, c='a':
  left = {'a': 4, 'c': 1, 'b': 1}, right = {}
  len(left)=3, len(right)=0 ❌
```

Result: `2` good splits ✅

### Complexity Analysis

- **Time Complexity**: **O(n)** - Single pass through the string
- **Space Complexity**: **O(1)** - At most 26 lowercase English letters in each dictionary

# Tags

#HashMap #TwoPointers #CountingCharacters #String

