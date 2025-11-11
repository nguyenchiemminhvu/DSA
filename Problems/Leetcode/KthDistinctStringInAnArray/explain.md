## Problem

https://leetcode.com/problems/kth-distinct-string-in-an-array/description/

```
A distinct string is a string that is present only once in an array.

Given an array of strings arr, and an integer k, return the kth distinct string present in arr. If there are fewer than k distinct strings, return an empty string "".

Note that the strings are considered in the order in which they appear in the array.

Example 1:

Input: arr = ["d","b","c","b","c","a"], k = 2
Output: "a"
Explanation:
The only distinct strings in arr are "d" and "a".
"d" appears 1st, so it is the 1st distinct string.
"a" appears 2nd, so it is the 2nd distinct string.
Since k == 2, "a" is returned. 

Example 2:

Input: arr = ["aaa","aa","a"], k = 1
Output: "aaa"
Explanation:
All strings in arr are distinct, so the 1st string "aaa" is returned.

Example 3:

Input: arr = ["a","b","a"], k = 3
Output: ""
Explanation:
The only distinct string is "b". Since there are fewer than 3 distinct strings, we return an empty string "".

Constraints:

1 <= k <= arr.length <= 1000
1 <= arr[i].length <= 5
arr[i] consists of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find the kth distinct string, where "distinct" means a string that appears exactly once in the array.

2. **Order Matters**: The problem asks for the kth distinct string in the order they appear in the original array, not in any sorted order.

3. **Two-Pass Approach**: 
   - First pass: Count frequency of each string
   - Second pass: Find the kth string with frequency = 1

4. **Edge Cases**:
   - If there are fewer than k distinct strings, return empty string
   - k is 1-indexed (1st distinct, 2nd distinct, etc.)

5. **Constraints Analysis**:
   - Small array size (≤ 1000) allows O(n) solution
   - Short strings (≤ 5 chars) make string operations efficient

## Solution

1. **Frequency Counting**: 
   - Use dictionary to count occurrences of each string
   - `d.get(val, 0) + 1` safely increments count (0 if key doesn't exist)

2. **Linear Search in Original Order**:
   - Iterate through original array to preserve order
   - For each string with frequency = 1 (distinct), decrement k
   - When k reaches 0, we've found the kth distinct string

3. **Return Logic**:
   - If we find the kth distinct string, return it immediately
   - If loop completes without k reaching 0, return empty string

### Example Walkthrough

For `arr = ["d","b","c","b","c","a"], k = 2`:

1. **Frequency Count**: `{"d": 1, "b": 2, "c": 2, "a": 1}`
2. **Linear Search**:
   - "d": frequency = 1 → k becomes 1
   - "b": frequency = 2 → skip
   - "c": frequency = 2 → skip  
   - "b": frequency = 2 → skip
   - "c": frequency = 2 → skip
   - "a": frequency = 1 → k becomes 0 → return "a"

### Complexity Analysis

- **Time Complexity**: O(n) where n = length of array
  - First pass: O(n) for counting
  - Second pass: O(n) for searching
- **Space Complexity**: O(n) for the frequency dictionary

### Alternative Approaches

1. **Single Pass with Ordered Dict**: Use OrderedDict to maintain insertion order
2. **List + Set**: Store distinct strings in order, but requires more space

The current solution is optimal for this problem size and constraints.

# Tags

- Hash Table / Dictionary
- Array Traversal
- Frequency Counting
- String Processing

