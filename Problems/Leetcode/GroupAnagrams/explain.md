## Problem Description

https://leetcode.com/problems/group-anagrams/

```
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]

Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Explanation:

There is no string in strs that can be rearranged to form "bat".
The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.

Example 2:

Input: strs = [""]

Output: [[""]]

Example 3:

Input: strs = ["a"]

Output: [["a"]]

Constraints:

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] consists of lowercase English letters.
```

## Observations

### What are Anagrams?
- **Anagrams** are words that contain the same letters with the same frequency, just rearranged
- For example: "eat", "tea", "ate" are all anagrams because they all have exactly one 'e', one 'a', and one 't'

### Key Insights:
1. **Grouping Strategy**: We need to find a way to identify which strings belong to the same anagram group
2. **Common Characteristic**: All anagrams of the same group will have identical character frequencies
3. **Hash Map Approach**: We can use character frequency as a "signature" or "key" to group anagrams together

### Why Character Frequency Works:
- If two strings are anagrams, they must have exactly the same count of each character
- Example: "eat" → [1,0,0,0,1,0,...,1,0,0] (frequency array for 'a','b','c'...'e'...'t')
- Example: "tea" → [1,0,0,0,1,0,...,1,0,0] (same frequency array!)

## Solution

### Approach: Character Frequency Mapping

The solution uses character frequency counting as a unique identifier for each anagram group.

#### Step-by-Step Explanation:

1. **Initialize Data Structures**:
   ```python
   groups = []  # Final result to return
   d : Dict[Tuple[int], List[str]] = {}  # Hash map to group anagrams
   ```

2. **Process Each String**:
   ```python
   for s in strs:
       freq = [0] * 26  # Frequency array for 26 lowercase letters
   ```
   - Create a frequency array of size 26 (for 'a' to 'z')
   - Each index represents a letter: index 0='a', index 1='b', ..., index 25='z'

3. **Count Character Frequencies**:
   ```python
   for c in s:
       freq[ord(c) - ord('a')] += 1
   ```
   - For each character in the string, increment its count in the frequency array
   - `ord(c) - ord('a')` converts character to array index (e.g., 'a'→0, 'b'→1, 'c'→2)

4. **Create Unique Key**:
   ```python
   freq = tuple(freq)
   ```
   - Convert frequency list to tuple so it can be used as a dictionary key
   - Lists can't be dictionary keys, but tuples can!

5. **Group Anagrams**:
   ```python
   if freq in d:
       d[freq].append(s)  # Add to existing group
   else:
       d[freq] = [s]      # Create new group
   ```
   - If we've seen this frequency pattern before, add string to existing group
   - Otherwise, create a new group with this string

6. **Collect Results**:
   ```python
   for key, val in d.items():
       groups.append(val)
   ```
   - Extract all groups from the hash map and add to final result

#### Example Walkthrough:

For input `["eat", "tea", "tan", "ate", "nat", "bat"]`:

| String | Frequency Array | Tuple Key | Group |
|--------|----------------|-----------|-------|
| "eat" | [1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0] | (1,0,0,0,1,0,...,1,0,0) | Group 1 |
| "tea" | [1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0] | (1,0,0,0,1,0,...,1,0,0) | Group 1 |
| "tan" | [1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0] | (1,0,0,0,0,0,...,1,0,0) | Group 2 |
| "ate" | [1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0] | (1,0,0,0,1,0,...,1,0,0) | Group 1 |
| "nat" | [1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0] | (1,0,0,0,0,0,...,1,0,0) | Group 2 |
| "bat" | [1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0] | (1,1,0,0,0,0,...,1,0,0) | Group 3 |

**Result**: `[["eat","tea","ate"], ["tan","nat"], ["bat"]]`

#### Time & Space Complexity:
- **Time**: O(N × M) where N = number of strings, M = average length of strings
- **Space**: O(N × M) for storing all strings in the hash map

## Tags

array, string, hash table