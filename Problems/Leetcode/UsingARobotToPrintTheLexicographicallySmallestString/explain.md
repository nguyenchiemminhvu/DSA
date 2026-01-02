## Problem

https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/description/

Given a string `s` and a robot that holds an empty string `t`, apply operations until both are empty:
- **Operation 1**: Remove first character of `s` and append it to `t`
- **Operation 2**: Remove last character of `t` and write it on paper

Return the lexicographically smallest string that can be written on paper.

**Examples:**
- `s = "zza"` → `"azz"` (move all to t, then pop all)
- `s = "bac"` → `"abc"` (strategically use t as a stack)
- `s = "bdda"` → `"addb"` (move all to t, then pop all)

**Constraints:**
- `1 <= s.length <= 10^5`
- `s` consists of only lowercase English letters

## Observations

1. **Stack Behavior**: String `t` acts as a stack (LIFO - Last In, First Out)
   - We can only append to `t` from `s` (push)
   - We can only remove from end of `t` to paper (pop)

2. **Greedy Strategy**: To get lexicographically smallest result, we want to write smaller characters first
   - Process characters in alphabetical order ('a' → 'z')
   - For each character in alphabetical order, find all occurrences in `s`

3. **Key Insight**: When we encounter a target character in `s`:
   - Move all characters from current position up to (and including) the target to `t`
   - Before pushing each character, pop from `t` any characters that are ≤ target character
   - This ensures we write smaller characters as early as possible

4. **Why This Works**:
   - By processing in alphabetical order, we ensure smaller characters get written first when possible
   - Using a stack allows us to temporarily hold characters and rearrange them optimally
   - Popping characters ≤ current target ensures we don't miss opportunities to write smaller characters

## Solution

```python
import string
from collections import Counter

class Solution:
    def robotWithString(self, s: str) -> str:
        counter = Counter(s)  # Track remaining occurrences
        left = 0              # Current position in s
        n = len(s)
        st = []               # Stack t
        res = []              # Result paper
        
        # Process each character in alphabetical order
        for c in string.ascii_lowercase:
            while counter[c] > 0 and left < n:
                # Find next occurrence of c in s
                idx = s.find(c, left, n)
                
                if idx != -1:
                    # Move characters from left to idx into stack
                    for cc in s[left:idx+1]:
                        # Pop any characters from stack that are <= c
                        # These should be written now (smaller or equal to current target)
                        while st and st[-1] <= c:
                            res.append(st.pop())
                        st.append(cc)
                    
                    left = idx + 1
                    counter[c] -= 1
                else:
                    # No more occurrences of c
                    counter[c] = 0
        
        # Pop remaining characters from stack
        while st:
            res.append(st.pop())
        
        return "".join(res)
```

**Algorithm Walkthrough (s = "bac"):**

1. **Target 'a'**: 
   - Find 'a' at index 1
   - Move 'b', 'a' to stack: `st = ['b', 'a']`
   - Pop 'a' (≤ 'a'): `res = ['a']`, `st = ['b']`

2. **Target 'b'**:
   - Find 'b' already processed (left=2)
   - Pop 'b' from stack: `res = ['a', 'b']`, `st = []`

3. **Target 'c'**:
   - Find 'c' at index 2
   - Move 'c' to stack: `st = ['c']`
   
4. **Finish**: Pop remaining: `res = ['a', 'b', 'c']` → `"abc"`

**Time Complexity**: O(n × 26) = O(n) where n is length of s
- We iterate through 26 letters
- For each letter, we process portions of the string

**Space Complexity**: O(n)
- Stack can hold up to n characters
- Result array holds n characters

# Tags

