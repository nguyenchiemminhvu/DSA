## Problem

https://leetcode.com/problems/majority-frequency-characters/description/

```
You are given a string s consisting of lowercase English letters.

The frequency group for a value k is the set of characters that appear exactly k times in s.

The majority frequency group is the frequency group that contains the largest number of distinct characters.

Return a string containing all characters in the majority frequency group, in any order. If two or more frequency groups tie for that largest size, pick the group whose frequency k is larger.

Example 1:

Input: s = "aaabbbccdddde"

Output: "ab"

Explanation:

Frequency (k)	Distinct characters in group	Group size	Majority?
4	{d}	1	No
3	{a, b}	2	Yes
2	{c}	1	No
1	{e}	1	No
Both characters 'a' and 'b' share the same frequency 3, they are in the majority frequency group. "ba" is also a valid answer.

Example 2:

Input: s = "abcd"

Output: "abcd"

Explanation:

Frequency (k)	Distinct characters in group	Group size	Majority?
1	{a, b, c, d}	4	Yes
All characters share the same frequency 1, they are all in the majority frequency group.

Example 3:

Input: s = "pfpfgi"

Output: "fp"

Explanation:

Frequency (k)	Distinct characters in group	Group size	Majority?
2	{p, f}	2	Yes
1	{g, i}	2	No (tied size, lower frequency)
Both characters 'p' and 'f' share the same frequency 2, they are in the majority frequency group. There is a tie in group size with frequency 1, but we pick the higher frequency: 2.

Constraints:

1 <= s.length <= 100
s consists only of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find the frequency group with the most distinct characters. A frequency group for value k contains all characters that appear exactly k times.

2. **Key Steps**:
   - Count frequency of each character
   - Group characters by their frequencies
   - Find the group with maximum size (most distinct characters)
   - Handle ties by choosing the group with higher frequency

3. **Edge Cases**:
   - All characters have the same frequency → return all characters
   - Multiple groups have the same size → choose the one with higher frequency
   - Single character string → return that character

4. **Time Complexity**: O(n) where n is the length of string
5. **Space Complexity**: O(1) since we have at most 26 lowercase letters

## Solution

The solution follows a clear 3-step approach:

### Step 1: Count Character Frequencies
```python
f = Counter(list(s))
```
- Uses Counter to count frequency of each character
- Example: "aaabbbccdddde" → {'a': 3, 'b': 3, 'c': 2, 'd': 4, 'e': 1}

### Step 2: Group Characters by Frequency
```python
groups = {}
for k, val in f.items():
    if val not in groups:
        groups[val] = []
    groups[val].append(k)
```
- Creates reverse mapping: frequency → list of characters with that frequency
- Example: {3: ['a', 'b'], 2: ['c'], 4: ['d'], 1: ['e']}

### Step 3: Find Majority Frequency Group
```python
max_k = -1
max_len = 0
for k, arr in groups.items():
    if max_len < len(arr):
        max_k = k
        max_len = len(arr)
    elif max_len == len(arr):
        if max_k < k:
            max_k = k
```
- Finds the frequency group with maximum size
- In case of tie, chooses the group with higher frequency
- Example: Group with frequency 3 has size 2 (largest), so max_k = 3

### Step 4: Return Result
```python
return "".join(list(set(groups[max_k])))
```
- Joins characters from the majority frequency group
- Uses `set()` to remove duplicates (though shouldn't be needed here)
- Returns characters in any order as per problem requirements

### Algorithm Walkthrough

For `s = "aaabbbccdddde"`:
1. **Frequencies**: {'a': 3, 'b': 3, 'c': 2, 'd': 4, 'e': 1}
2. **Groups**: {3: ['a', 'b'], 2: ['c'], 4: ['d'], 1: ['e']}
3. **Group Sizes**: 
   - Frequency 3: size 2 ✓ (largest)
   - Frequency 2: size 1
   - Frequency 4: size 1  
   - Frequency 1: size 1
4. **Result**: Characters from frequency 3 group → "ab"

For `s = "pfpfgi"`:
1. **Frequencies**: {'p': 2, 'f': 2, 'g': 1, 'i': 1}
2. **Groups**: {2: ['p', 'f'], 1: ['g', 'i']}
3. **Group Sizes**: Both have size 2, but frequency 2 > frequency 1
4. **Result**: Characters from frequency 2 group → "pf"

# Tags

- Hash Table
- Counting
- String
- Frequency Analysis

