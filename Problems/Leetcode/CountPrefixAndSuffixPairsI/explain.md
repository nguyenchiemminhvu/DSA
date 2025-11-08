## Problem

https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/description/

```
You are given a 0-indexed string array words.

Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:

isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and false otherwise.
For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.

Return an integer denoting the number of index pairs (i, j) such that i < j, and isPrefixAndSuffix(words[i], words[j]) is true.

Example 1:

Input: words = ["a","aba","ababa","aa"]
Output: 4
Explanation: In this example, the counted index pairs are:
i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
Therefore, the answer is 4.
Example 2:

Input: words = ["pa","papa","ma","mama"]
Output: 2
Explanation: In this example, the counted index pairs are:
i = 0 and j = 1 because isPrefixAndSuffix("pa", "papa") is true.
i = 2 and j = 3 because isPrefixAndSuffix("ma", "mama") is true.
Therefore, the answer is 2.

Example 3:

Input: words = ["abab","ab"]
Output: 0
Explanation: In this example, the only valid index pair is i = 0 and j = 1, and isPrefixAndSuffix("abab", "ab") is false.
Therefore, the answer is 0.

Constraints:

1 <= words.length <= 50
1 <= words[i].length <= 10
words[i] consists only of lowercase English letters.
```

## Observations

1. **Problem Requirements**: We need to count pairs (i, j) where i < j and `words[i]` is both a prefix and suffix of `words[j]`.

2. **isPrefixAndSuffix Logic**: For string `s1` to be both prefix and suffix of `s2`:
   - `s1` must not be longer than `s2` (if `len(s1) > len(s2)`, return false)
   - If `s1` and `s2` have the same length, they must be identical
   - Otherwise, `s1` must match both the beginning (`s2[:len(s1)]`) and end (`s2[-len(s1):]`) of `s2`

3. **Edge Cases**:
   - Empty strings are handled by the constraint that all strings have length ≥ 1
   - Single character strings can be both prefix and suffix of longer strings
   - A string is always both prefix and suffix of itself

4. **Brute Force Approach**: With constraints (n ≤ 50, string length ≤ 10), a simple O(n²) approach checking all pairs is efficient enough.

5. **Key Insight**: The suffix check uses `s2[n2-n1:]` which extracts the last `n1` characters of `s2`, equivalent to `s2[-n1:]`.

## Solution

**Algorithm:**
1. **Helper Function `is_prefix_suffix`**: 
   - Check if `s1` length > `s2` length → return False
   - If lengths are equal → check if strings are identical
   - Otherwise → verify `s1` matches both prefix `s2[:n1]` and suffix `s2[n2-n1:]`

2. **Main Logic**:
   - Use nested loops to check all pairs (i, j) where i < j
   - For each pair, call `is_prefix_suffix(words[i], words[j])`
   - Count valid pairs and return the total

**Time Complexity**: O(n² × m) where n is the number of words and m is the average string length
**Space Complexity**: O(1) - only using constant extra space

**Example Walkthrough** (`words = ["a","aba","ababa","aa"]`):
- (0,1): `is_prefix_suffix("a", "aba")` → "a" == "a"[prefix] and "a" == "a"[suffix] → ✓
- (0,2): `is_prefix_suffix("a", "ababa")` → "a" == "a"[prefix] and "a" == "a"[suffix] → ✓  
- (0,3): `is_prefix_suffix("a", "aa")` → "a" == "a"[prefix] and "a" == "a"[suffix] → ✓
- (1,2): `is_prefix_suffix("aba", "ababa")` → "aba" == "aba"[prefix] and "aba" == "aba"[suffix] → ✓
- (1,3): `is_prefix_suffix("aba", "aa")` → length mismatch → ✗
- (2,3): `is_prefix_suffix("ababa", "aa")` → length mismatch → ✗

**Result**: 4 valid pairs

**Why This Works:**
- The nested loop ensures we check all valid pairs (i, j) where i < j
- The helper function correctly identifies when a string is both prefix and suffix
- String slicing operations handle the prefix/suffix checks efficiently

# Tags

- Array
- String
- Brute Force
- Two Pointers
- Easy

