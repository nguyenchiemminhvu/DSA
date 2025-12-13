## Problem

https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/description/

A happy string is a string that:
- consists only of letters of the set ['a', 'b', 'c']
- s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed)

For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order. Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

**Example 1:**
```
Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
```

**Example 2:**
```
Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.
```

**Example 3:**
```
Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
```

**Constraints:**
- 1 <= n <= 10
- 1 <= k <= 100

## Observations

1. **Constraint Analysis**: With n <= 10, we can generate all possible happy strings without worrying about time/space complexity since the total number is bounded.

2. **Counting Happy Strings**: 
   - For n = 1: 3 strings ("a", "b", "c")
   - For n = 2: Each of the 3 starting letters can be followed by 2 different letters = 3 × 2 = 6 strings
   - For n = 3: 3 × 2 × 2 = 12 strings
   - General formula: 3 × 2^(n-1) strings

3. **Lexicographical Order**: Since we need the kth string in lexicographical order, we can use backtracking to generate strings in this natural order by:
   - Iterating through letters in 'abc' order
   - Ensuring no adjacent characters are the same

4. **Early Termination**: We could optimize by calculating if k exceeds the total possible happy strings (3 × 2^(n-1)) before generating, but with the constraints, generating all is feasible.

## Solution

1. **Initialize**:
   - `letters = 'abc'`: The allowed characters
   - `words = []`: Store all generated happy strings

2. **Recursive Generation** (`generating` function):
   - **Base Case**: If buffer length equals n, we've formed a complete happy string:
     - Join the buffer into a string and append to `words`
     - Return to explore other branches
   
   - **Recursive Case**: For each letter in 'abc':
     - **Constraint Check**: Skip if the current letter equals the last character in buffer (to avoid adjacent duplicates)
     - **Recurse**: Add the current letter to buffer and continue building

3. **Result Selection**:
   - If k exceeds the total number of generated strings, return empty string
   - Otherwise, return the (k-1)th string (0-indexed)

**Why This Works:**

- **Lexicographical Order**: By iterating through 'abc' in order and building strings left-to-right, we naturally generate strings in lexicographical order
- **Happy String Property**: The constraint check ensures no two adjacent characters are the same
- **Completeness**: The backtracking explores all valid combinations

**Example Trace (n=3, k=9):**

```
Generation order:
"aba" → "abc" → "aca" → "acb" → "bab" → "bac" → "bca" → "bcb" → "cab" → ...
         ↑                                                            ↑
        index 1                                                   index 8 (9th string)
```

**Complexity Analysis:**

- **Time Complexity**: O(3 × 2^(n-1) × n)
  - Generate 3 × 2^(n-1) strings
  - Each string requires O(n) to construct and join
  - For n=10: ~1,536 strings, very manageable

- **Space Complexity**: O(3 × 2^(n-1) × n)
  - Store all generated strings
  - Recursion depth is O(n)

### Optimization Note:

For larger constraints, we could avoid generating all strings by:
1. Calculating k's position directly using the formula 3 × 2^(n-1)
2. Building the kth string digit by digit by determining which "branch" to take
3. This would reduce to O(n) time and O(n) space

However, given the constraints (n ≤ 10, k ≤ 100), the current approach is simpler and sufficient.

# Tags

`Backtracking` `String` `Recursion` `Combinatorics`

