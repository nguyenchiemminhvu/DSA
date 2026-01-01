## Problem

https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/description/

You are given a string `s` consisting only of characters 'a' and 'b'.

You can delete any number of characters in `s` to make `s` balanced. `s` is **balanced** if there is no pair of indices `(i,j)` such that `i < j` and `s[i] = 'b'` and `s[j] = 'a'`.

Return the minimum number of deletions needed to make `s` balanced.

**Example 1:**
```
Input: s = "aababbab"
Output: 2
Explanation: You can either:
- Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
- Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
```

**Example 2:**
```
Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters.
```

**Constraints:**
- `1 <= s.length <= 10^5`
- `s[i]` is 'a' or 'b'

## Observations

1. **Definition of "balanced":**
   - A string is balanced if no 'b' appears before any 'a'
   - The final string must follow the pattern: `a*b*` (zero or more 'a's followed by zero or more 'b's)
   - Valid examples: "aaa", "bbb", "aaabbb", "a", "b", ""
   - Invalid examples: "ba", "aabab"

2. **Key insight - Split point approach:**
   - The optimal string after deletions will have all 'a's on the left and all 'b's on the right
   - We can think of this as choosing a "split point" in the string
   - At each position `i`, we can consider:
     - Everything before `i` should be 'a' → delete all 'b's before `i`
     - Everything after `i` should be 'b' → delete all 'a's after `i`

3. **Optimization:**
   - Precompute counts using prefix/suffix arrays to avoid redundant counting
   - For each position, the cost is: `(number of b's before) + (number of a's after)`
   - The minimum cost across all positions is the answer

## Solution

### Approach: Prefix and Suffix Arrays

**Algorithm:**

1. Create two arrays:
   - `prefix_b[i]`: count of 'b's **before** index `i` (in range `[0, i-1]`)
   - `suffix_a[i]`: count of 'a's **after** index `i` (in range `[i+1, n-1]`)

2. For each position `i`, calculate deletions needed if we split at position `i`:
   - Delete all 'b's before position `i`: `prefix_b[i]`
   - Delete all 'a's after position `i`: `suffix_a[i]`
   - Total deletions at split point `i`: `prefix_b[i] + suffix_a[i]`

3. Return the minimum across all positions

**Example walkthrough for s = "aababbab":**

```
Index:     0   1   2   3   4   5   6   7
String:    a   a   b   a   b   b   a   b
           
prefix_b:  0   0   0   1   1   2   3   3
           ↑ count of 'b's before each index

suffix_a:  2   2   1   1   1   1   0   0
           ↑ count of 'a's after each index

Total:     2   2   1   2   2   3   3   3
                   ↑ minimum = 1
```

Wait, this gives minimum 1, but expected is 2. Let me recalculate...

Actually, looking at index 2:
- `prefix_b[2] = 0` (no 'b's before index 2: "aa")
- `suffix_a[2] = 1` (one 'a' after index 2: "abbab" has 'a' at indices 3, 6)

Actually suffix_a[2] should count 'a's at indices 3 and 6, so it's 2, not 1.

Let me recalculate suffix_a properly:
- suffix_a[7] = 0 (nothing after index 7)
- suffix_a[6] = 0 (s[7] = 'b', so no 'a' after 6)
- suffix_a[5] = 1 (s[6] = 'a', so one 'a' after 5)
- suffix_a[4] = 2 (s[5]='b', s[6]='a', so suffix_a[4] = suffix_a[5] + 0 = 1... wait)

Let me trace the code:
```python
for i in range(n - 2, -1, -1):  # i goes from n-2 down to 0
    suffix_a[i] = suffix_a[i + 1]
    if s[i + 1] == 'a':
        suffix_a[i] += 1
```

For s = "aababbab" (indices 0-7):
- i=6: suffix_a[6] = suffix_a[7] + (1 if s[7]=='a' else 0) = 0 + 0 = 0
- i=5: suffix_a[5] = suffix_a[6] + (1 if s[6]=='a' else 0) = 0 + 1 = 1
- i=4: suffix_a[4] = suffix_a[5] + (1 if s[5]=='b' else 0) = 1 + 0 = 1
- i=3: suffix_a[3] = suffix_a[4] + (1 if s[4]=='b' else 0) = 1 + 0 = 1
- i=2: suffix_a[2] = suffix_a[3] + (1 if s[3]=='a' else 0) = 1 + 1 = 2
- i=1: suffix_a[1] = suffix_a[2] + (1 if s[2]=='b' else 0) = 2 + 0 = 2
- i=0: suffix_a[0] = suffix_a[1] + (1 if s[1]=='a' else 0) = 2 + 0 = 2

So suffix_a = [2, 2, 2, 1, 1, 1, 0, 0]

And prefix_b:
- i=1: prefix_b[1] = prefix_b[0] + (1 if s[0]=='b' else 0) = 0 + 0 = 0
- i=2: prefix_b[2] = prefix_b[1] + (1 if s[1]=='b' else 0) = 0 + 0 = 0  
- i=3: prefix_b[3] = prefix_b[2] + (1 if s[2]=='b' else 0) = 0 + 1 = 1
- i=4: prefix_b[4] = prefix_b[3] + (1 if s[3]=='b' else 0) = 1 + 0 = 1
- i=5: prefix_b[5] = prefix_b[4] + (1 if s[4]=='b' else 0) = 1 + 1 = 2
- i=6: prefix_b[6] = prefix_b[5] + (1 if s[5]=='b' else 0) = 2 + 1 = 3
- i=7: prefix_b[7] = prefix_b[6] + (1 if s[6]=='b' else 0) = 3 + 0 = 3

So prefix_b = [0, 0, 0, 1, 1, 2, 3, 3]

Total = [2, 2, 2, 2, 2, 3, 3, 3]

Minimum = 2. That's correct!

**Complexity:**
- **Time:** O(n) - three linear passes through the array
- **Space:** O(n) - two arrays of size n

```python
class Solution:
    def minimumDeletions(self, s: str) -> int:
        n = len(s)
        prefix_b = [0] * n
        suffix_a = [0] * n
        
        # Build prefix_b: count of 'b's before each position
        for i in range(1, n):
            prefix_b[i] = prefix_b[i - 1]
            if s[i - 1] == 'b':
                prefix_b[i] += 1
        
        # Build suffix_a: count of 'a's after each position
        for i in range(n - 2, -1, -1):
            suffix_a[i] = suffix_a[i + 1]
            if s[i + 1] == 'a':
                suffix_a[i] += 1
        
        # Find minimum deletions across all split points
        removed = float('inf')
        for i in range(n):
            removed = min(removed, prefix_b[i] + suffix_a[i])
        
        return 0 if removed == float('inf') else removed
```

### Alternative: O(1) Space DP Solution

```python
def minimumDeletions(self, s: str) -> int:
    deletions = 0
    b_count = 0
    
    for char in s:
        if char == 'b':
            b_count += 1
        else:  # char == 'a'
            # Choice: delete this 'a' OR delete all previous 'b's
            deletions = min(deletions + 1, b_count)
    
    return deletions
```

This greedy approach tracks the number of 'b's seen so far. When encountering an 'a', we have two options:
1. Delete this 'a' (cost: `deletions + 1`)
2. Delete all previous 'b's to maintain balance (cost: `b_count`)

# Tags

String, Dynamic Programming, Prefix Sum, Greedy

