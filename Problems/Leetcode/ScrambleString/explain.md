## Problem

**URL:** https://leetcode.com/problems/scramble-string/description

### Problem Statement

Given two strings `s1` and `s2` of the **same length**, determine if `s2` is a scrambled string of `s1`.

A scrambled string is created using the following algorithm:
1. If the length of the string is 1, stop.
2. If the length is > 1, split the string at a random index into two non-empty substrings.
3. **Randomly** decide to swap or keep the two substrings in order.
4. Recursively apply steps 1-3 on each substring.

### Examples

**Example 1:**
```
Input: s1 = "great", s2 = "rgeat"
Output: true

Possible transformation:
"great" 
  → "gr/eat" (split at index 2)
  → "gr/eat" (no swap)
  → "g/r / e/at" (split each part recursively)
  → "r/g / e/at" (swap first part "gr" → "rg")
  → "r/g / e/ a/t" (split "at")
  → "r/g / e/ a/t" (no swap)
Result: "rgeat" ✓
```

**Example 2:**
```
Input: s1 = "abcde", s2 = "caebd"
Output: false
```

**Example 3:**
```
Input: s1 = "a", s2 = "a"
Output: true
```

### Constraints

- `s1.length == s2.length`
- `1 <= s1.length <= 30`
- `s1` and `s2` consist of lowercase English letters

---

## Observations

1. **Character Set Must Match:** For `s2` to be a scrambled version of `s1`, both must contain exactly the same characters with the same frequencies. If character counts differ, they cannot be scrambles of each other.

2. **Recursive Nature:** The scrambling process is inherently recursive:
   - The base case is when we have a single character (no scrambling possible)
   - Each recursive step splits the string and possibly swaps the parts
   - We must check both possibilities: with and without swap

3. **Two Split Scenarios:** When checking if substring of `s1` can transform to substring of `s2`, we have two cases to verify:
   - **Case 1 (No Swap):** Left part of `s1` → Left part of `s2` AND Right part of `s1` → Right part of `s2`
   - **Case 2 (With Swap):** Left part of `s1` → Right part of `s2` AND Right part of `s1` → Left part of `s2`

4. **Memoization is Crucial:** Without memoization, we'd recompute the same subproblems exponentially. The state is defined by: `(starting_index_in_s1, starting_index_in_s2, length)`.

5. **Early Termination:** We can prune search space by:
   - Checking character count equality first (cheap operation)
   - Checking if substrings are already equal (base case shortcut)

---

## Solution

### Approach: Dynamic Programming with Memoization

The solution uses a recursive approach with memoization to explore all possible scrambling scenarios:

```python
from collections import Counter

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        n = len(s1)

        from functools import cache
        @cache
        def F(i1: int, i2: int, length: int) -> bool:
            """
            Check if s1[i1:i1+length] can be scrambled to s2[i2:i2+length]
            
            Args:
                i1: Starting index in s1
                i2: Starting index in s2
                length: Length of substrings to compare
            
            Returns:
                True if s1's substring can be scrambled to s2's substring
            """
            
            # Base case: substrings are already equal
            if s1[i1:i1 + length] == s2[i2:i2 + length]:
                return True
            
            # Pruning: if character frequencies don't match, impossible to transform
            if Counter(s1[i1:i1 + length]) != Counter(s2[i2:i2 + length]):
                return False

            # Try all possible split points
            for sub_len in range(1, length):
                left_len = sub_len
                right_len = length - sub_len

                # Case 1: No swap
                # Left of s1 → Left of s2 AND Right of s1 → Right of s2
                if F(i1, i2, left_len) and F(i1 + sub_len, i2 + sub_len, right_len):
                    return True
                
                # Case 2: With swap
                # Left of s1 → Right of s2 AND Right of s1 → Left of s2
                if F(i1, i2 + length - right_len, right_len) and F(i1 + right_len, i2, left_len):
                    return True
            
            return False
        
        return F(0, 0, n)
```

### Algorithm Breakdown

1. **Initialize:** Call `F(0, 0, n)` where `n` is the length of both strings.

2. **Base Case - Exact Match:** 
   - If the substrings are already identical, return `True` immediately
   - This catches cases where no scrambling occurred

3. **Pruning via Character Count:**
   - Count character frequencies in both substrings
   - If they don't match, `False` (can never transform one to another)
   - This eliminates impossible branches early

4. **Try All Split Points:**
   - For each position `sub_len` from 1 to `length-1`:
     - `left_len = sub_len`, `right_len = length - sub_len`
     
   - **Case 1 - No Swap:**
     ```
     s1: [LEFT | RIGHT]
     s2: [LEFT | RIGHT]
     ```
     - Check if left parts can transform: `F(i1, i2, left_len)`
     - Check if right parts can transform: `F(i1+sub_len, i2+sub_len, right_len)`
   
   - **Case 2 - With Swap:**
     ```
     s1: [LEFT | RIGHT]
     s2: [RIGHT | LEFT]  (swapped positions)
     ```
     - Left of s1 maps to right of s2: `F(i1, i2 + length - right_len, right_len)`
     - Right of s1 maps to left of s2: `F(i1 + right_len, i2, left_len)`

5. **Return:** If any split scenario succeeds, return `True`; otherwise, `False`

### Complexity Analysis

- **Time Complexity:** $O(n^4 \cdot \log n)$ in worst case
  - There are $O(n^3)$ possible states: `(i1, i2, length)`
  - Each state does $O(n)$ iterations over split points
  - Each iteration does $O(\log n)$ character counting (or $O(n)$ with preprocessing)
  - With memoization, each unique state computed once

- **Space Complexity:** $O(n^3)$ for the memoization cache

### Why This Works

The algorithm correctly explores the search space by:
1. **Recognizing structure:** Any valid scrambling follows a specific recursive pattern
2. **Considering both swap options:** The problem states randomness, so we must verify both possibilities
3. **Memoizing aggressively:** States are uniquely identified by `(i1, i2, length)`, avoiding redundant computation
4. **Pruning intelligently:** Character count check eliminates impossible branches without exploring further

### Example Trace: `s1 = "great"`, `s2 = "rgeat"`

```
F(0, 0, 5):
  s1[0:5]="great" != s2[0:5]="rgeat"
  Counter matches ✓
  
  Try split_len=1:
    Case 1: F(0,0,1) AND F(1,1,4) → "g"="r"? NO
    Case 2: F(0,4,1) AND F(1,0,4) → "g"="t"? NO
  
  Try split_len=2:
    Case 1: F(0,0,2) AND F(2,2,3) → "gr"="rg"? NO, "eat"="eat"? YES but Case 1 fails
    Case 2: F(0,3,2) AND F(2,0,3) 
      → "gr" vs s2[3:5]="at"? NO
      → "ea" vs s2[0:3]="rge"? NO
  
  Try split_len=3:
    Case 1: F(0,0,3) AND F(3,3,2)
    Case 2: F(0,2,2) AND F(3,0,3)
      → "gr" vs s2[2:4]="ea"? NO
      → "at" vs s2[0:3]="rge"? NO
  
  Try split_len=4:
    Case 2: F(0,1,4) AND F(4,0,1)
      → Recursively explores deeper...
      → Eventually returns TRUE ✓
```

# Tags
- Dynamic Programming
- Memoization / Top-Down DP
- Recursion
- String Manipulation
- State Space Search

