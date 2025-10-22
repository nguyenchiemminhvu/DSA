## Problem

https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/description/

```
You are given two strings of the same length s and t. In one step you can choose any character of t and replace it with another character.

Return the minimum number of steps to make t an anagram of s.

An Anagram of a string is a string that contains the same characters with a different (or the same) ordering.

Example 1:

Input: s = "bab", t = "aba"
Output: 1
Explanation: Replace the first 'a' in t with b, t = "bba" which is anagram of s.

Example 2:

Input: s = "leetcode", t = "practice"
Output: 5
Explanation: Replace 'p', 'r', 'a', 'i' and 'c' from t with proper characters to make t anagram of s.

Example 3:

Input: s = "anagram", t = "mangaar"
Output: 0
Explanation: "anagram" and "mangaar" are anagrams. 

Constraints:

1 <= s.length <= 5 * 104
s.length == t.length
s and t consist of lowercase English letters only.
```

## Observations

1. **Same Length Constraint**: Both strings `s` and `t` have the same length, which is crucial for the solution approach.

2. **Anagram Definition**: An anagram means both strings must contain exactly the same characters with the same frequencies, just possibly in different orders.

3. **Character Replacement**: We can only replace characters in string `t` to match string `s`. We cannot add or remove characters.

4. **Frequency Analysis**: The key insight is that we need to analyze the character frequency difference between the two strings.

5. **Bidirectional Matching**: If string `s` has more of character 'x' than string `t`, then string `t` must have more of some other character 'y' than string `s` (since both strings have the same length).

6. **Minimum Steps**: The minimum number of steps equals the number of characters in `t` that need to be replaced to match the frequency distribution of `s`.

## Solution

The solution uses a **frequency counting approach** with the following strategy:

### Algorithm:

1. **Create Frequency Array**: Use an array `f` of size 128 to handle ASCII characters (covers all lowercase English letters).

2. **Count Characters in `s`**: For each character in string `s`, increment its frequency in the array.
   ```python
   for c in s:
       f[ord(c)] += 1
   ```

3. **Subtract Characters in `t`**: For each character in string `t`, decrement its frequency in the array.
   ```python
   for c in t:
       f[ord(c)] -= 1
   ```

4. **Calculate Differences**: After processing both strings:
   - Positive values in `f[i]` indicate that character `i` appears more in `s` than in `t`
   - Negative values indicate that character `i` appears more in `t` than in `s`
   - Zero values indicate equal frequencies

5. **Sum Absolute Differences**: Count the total absolute difference across all characters.
   ```python
   count = sum(abs(val) for val in f)
   ```

6. **Return Half the Sum**: Divide by 2 because each replacement fixes two imbalances:
   - Reduces excess of one character in `t`
   - Increases deficit of another character in `t`

### Why Divide by 2?

When we replace a character in `t`:
- We remove one instance of an "excess" character (negative difference becomes less negative)
- We add one instance of a "needed" character (positive difference becomes less positive)

Each replacement operation fixes 2 units of imbalance, so the minimum steps = total imbalance / 2.

### Time Complexity: O(n)
- Single pass through both strings
- Constant time array operations

### Space Complexity: O(1)
- Fixed-size array of 128 elements
- Independent of input size

## Tags

array, string, hash table, greedy