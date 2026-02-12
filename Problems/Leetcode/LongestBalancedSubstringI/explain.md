# Longest Balanced Substring

## Problem

https://leetcode.com/problems/longest-balanced-substring-i/description/

You are given a string `s` consisting of lowercase English letters.

A substring of `s` is called **balanced** if all distinct characters in the substring appear the same number of times.

Return the length of the longest balanced substring of `s`.

### Examples

**Example 1:**
```
Input: s = "abbac"
Output: 4
Explanation: The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.
```

**Example 2:**
```
Input: s = "zzabccy"
Output: 4
Explanation: The longest balanced substring is "zabc" because the distinct characters 'z', 'a', 'b', and 'c' each appear exactly 1 time.
```

**Example 3:**
```
Input: s = "aba"
Output: 2
Explanation: One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".
```

### Constraints
- `1 <= s.length <= 1000`
- `s` consists of lowercase English letters.

---

## Observations

1. **Balanced Definition**: A substring is balanced when every distinct character appears with the same frequency.
   - "abba" → 'a':2, 'b':2 ✓ (balanced)
   - "abc" → 'a':1, 'b':1, 'c':1 ✓ (balanced)
   - "aab" → 'a':2, 'b':1 ✗ (not balanced)

2. **Brute Force Approach**: We need to check all possible substrings.
   - For a string of length `n`, there are `n*(n+1)/2` possible substrings.
   - For each substring, we need to verify if it's balanced.

3. **Frequency Tracking**: We can use a hash map (dictionary) to track character frequencies as we expand the substring.
   - This allows us to incrementally build the frequency map rather than recalculating from scratch.

4. **Balance Check**: A substring is balanced if all values in the frequency map are equal.
   - We can check this condition every time we add a new character.

5. **Optimization Insight**: As we expand the substring by adding characters, we only need to check if the newly added character's frequency matches all other frequencies.

6. **Time Complexity Consideration**: 
   - With constraints up to 1000 characters, an O(n²) or O(n²·k) solution is acceptable (where k is the number of distinct characters, max 26).

---

## Solution

### Approach: Brute Force with Frequency Map

The solution uses a nested loop approach to examine all possible substrings and check if they are balanced.

#### Algorithm Steps:

1. **Outer Loop (Starting Position)**: Iterate through each possible starting index `i` in the string.

2. **Inner Loop (Ending Position)**: For each starting position `i`, iterate through each possible ending index `j` from `i` to `n-1`.

3. **Frequency Tracking**: Maintain a `counter` dictionary that tracks the frequency of each character in the current substring `s[i:j+1]`.
   - As we expand the substring by incrementing `j`, we add `s[j]` to the counter.

4. **Balance Check**: After adding each character, check if all characters in the current substring have the same frequency.
   - Use the condition: `all(v == counter[s[j]] for v in counter.values())`
   - This checks if every frequency value equals the frequency of the newly added character.

5. **Update Result**: If the substring is balanced, update the result with the maximum length found so far.

### Code Implementation

```python
from collections import defaultdict

class Solution:
    def longestBalanced(self, s: str) -> int:
        n = len(s)
        res = 0
        
        # Try every starting position
        for i in range(n):
            counter = defaultdict(int)
            
            # Expand the substring to every ending position
            for j in range(i, n):
                counter[s[j]] += 1
                
                # Check if current substring is balanced
                if all(v == counter[s[j]] for v in counter.values()):
                    res = max(res, j - i + 1)
        
        return res
```

### Example Trace: s = "abbac"

```
i=0, j=0: "a" → {'a':1} → balanced ✓ → len=1
i=0, j=1: "ab" → {'a':1, 'b':1} → balanced ✓ → len=2
i=0, j=2: "abb" → {'a':1, 'b':2} → not balanced ✗
i=0, j=3: "abba" → {'a':2, 'b':2} → balanced ✓ → len=4
i=0, j=4: "abbac" → {'a':2, 'b':2, 'c':1} → not balanced ✗

i=1, j=1: "b" → {'b':1} → balanced ✓ → len=1
i=1, j=2: "bb" → {'b':2} → balanced ✓ → len=2
i=1, j=3: "bba" → {'b':2, 'a':1} → not balanced ✗
i=1, j=4: "bbac" → {'b':2, 'a':1, 'c':1} → not balanced ✗

... (continue for remaining positions)

Result: 4 (from "abba")
```

### Complexity Analysis

**Time Complexity**: O(n² · k)
- Outer loop: O(n)
- Inner loop: O(n)
- Balance check using `all()`: O(k), where k is the number of distinct characters (max 26)
- Overall: O(n² · k) ≈ O(n²) since k is constant

**Space Complexity**: O(k)
- The `counter` dictionary stores at most 26 characters (lowercase English letters)
- O(k) = O(26) = O(1) constant space

### Why This Solution Works

1. **Completeness**: By checking all possible substrings, we guarantee finding the longest balanced one.

2. **Incremental Frequency Update**: Instead of recounting characters for each substring, we incrementally update the frequency map, which is more efficient.

3. **Efficient Balance Check**: The `all()` function with generator expression checks balance without creating additional data structures.

4. **Correct Length Calculation**: `j - i + 1` correctly calculates the substring length from indices `i` to `j` inclusive.

### Alternative Approaches

While this brute force solution works well for the given constraints, there are potential optimizations:

1. **Early Termination**: If the remaining string length is smaller than the current best result, we can skip that starting position.

2. **Pattern Recognition**: Some patterns can be eliminated early (e.g., if we have more than `(j-i+1)/2` distinct characters in a substring of length `j-i+1`, it cannot be balanced with all frequencies ≥ 2).

However, given the constraint `n ≤ 1000`, the current O(n²) solution is perfectly acceptable and easy to understand.

# Tags

`string` `hash-map` `brute-force` `sliding-window` `frequency-counting`

