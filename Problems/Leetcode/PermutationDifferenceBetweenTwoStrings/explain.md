## Problem

https://leetcode.com/problems/permutation-difference-between-two-strings/description/

```
You are given two strings s and t such that every character occurs at most once in s and t is a permutation of s.

The permutation difference between s and t is defined as the sum of the absolute difference between the index of the occurrence of each character in s and the index of the occurrence of the same character in t.

Return the permutation difference between s and t.

Example 1:

Input: s = "abc", t = "bac"

Output: 2

Explanation:

For s = "abc" and t = "bac", the permutation difference of s and t is equal to the sum of:

The absolute difference between the index of the occurrence of "a" in s and the index of the occurrence of "a" in t.
The absolute difference between the index of the occurrence of "b" in s and the index of the occurrence of "b" in t.
The absolute difference between the index of the occurrence of "c" in s and the index of the occurrence of "c" in t.
That is, the permutation difference between s and t is equal to |0 - 1| + |1 - 0| + |2 - 2| = 2.

Example 2:

Input: s = "abcde", t = "edbac"

Output: 12

Explanation: The permutation difference between s and t is equal to |0 - 3| + |1 - 2| + |2 - 4| + |3 - 1| + |4 - 0| = 12.

Constraints:

1 <= s.length <= 26
Each character occurs at most once in s.
t is a permutation of s.
s consists only of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find the sum of absolute differences between the positions of each character in two strings where one is a permutation of the other.

2. **Key Insights**:
   - Both strings have the same characters, just in different positions
   - Each character appears exactly once in both strings
   - We need to track the index of each character in both strings
   - The difference is calculated as `|index_in_s - index_in_t|` for each character

3. **Example Walkthrough** (s = "abc", t = "bac"):
   - 'a': position 0 in s, position 1 in t → |0 - 1| = 1
   - 'b': position 1 in s, position 0 in t → |1 - 0| = 1  
   - 'c': position 2 in s, position 2 in t → |2 - 2| = 0
   - Total: 1 + 1 + 0 = 2

4. **Approach**: Use hash maps to store character-to-index mappings for both strings, then calculate the sum of absolute differences.

## Solution

1. **Build Index Maps**: 
   - Create `ds` dictionary to map each character in string `s` to its index
   - Create `dt` dictionary to map each character in string `t` to its index

2. **Calculate Differences**:
   - Iterate through each character in string `s`
   - For each character, find its position in both strings using the dictionaries
   - Calculate the absolute difference between these positions
   - Add this difference to the running sum

3. **Return Result**: Return the total sum of all absolute differences

**Time Complexity**: O(n) where n is the length of the strings
- O(n) to build the first dictionary
- O(n) to build the second dictionary  
- O(n) to calculate the sum of differences

**Space Complexity**: O(n) for storing the two dictionaries

**Alternative Approach**: Since we only need one character's position from each string at a time, we could optimize space by using just one dictionary and calculating differences on-the-fly, but the current solution is more readable.

## Tags

array, string, hash table