## Problem

https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/

```
You are given a string s consisting of lowercase English letters ('a' to 'z').

Your task is to:

Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the maximum frequency.
Find the consonant (all other letters excluding vowels) with the maximum frequency.
Return the sum of the two frequencies.

Note: If multiple vowels or consonants have the same maximum frequency, you may choose any one of them. If there are no vowels or no consonants in the string, consider their frequency as 0.

The frequency of a letter x is the number of times it occurs in the string.


Example 1:

Input: s = "successes"

Output: 6

Explanation:

The vowels are: 'u' (frequency 1), 'e' (frequency 2). The maximum frequency is 2.
The consonants are: 's' (frequency 4), 'c' (frequency 2). The maximum frequency is 4.
The output is 2 + 4 = 6.

Example 2:

Input: s = "aeiaeia"

Output: 3

Explanation:

The vowels are: 'a' (frequency 3), 'e' ( frequency 2), 'i' (frequency 2). The maximum frequency is 3.
There are no consonants in s. Hence, maximum consonant frequency = 0.
The output is 3 + 0 = 3.

Constraints:

1 <= s.length <= 100
s consists of lowercase English letters only.
```

## Observations

1. **Problem Breakdown**: We need to find two separate maximum frequencies:
   - Maximum frequency among vowels ('a', 'e', 'i', 'o', 'u')
   - Maximum frequency among consonants (all other lowercase letters)

2. **Edge Cases to Consider**:
   - String contains only vowels → consonant max frequency = 0
   - String contains only consonants → vowel max frequency = 0
   - Multiple letters with same maximum frequency → any one can be chosen

3. **Key Insight**: We need to:
   - Count frequency of each character in the string
   - Separate vowels from consonants
   - Find maximum frequency in each category
   - Sum the two maximum frequencies

4. **Time Complexity**: O(n) where n is the length of string
   - One pass to count frequencies
   - One pass through all 26 lowercase letters to find max frequencies

5. **Space Complexity**: O(1) - at most 26 entries in the frequency map

## Solution

### Approach: Frequency Count + Category Separation

**Algorithm**:
1. Create a frequency map for all characters in the string
2. Iterate through all 26 lowercase letters
3. For each letter, check if it's a vowel or consonant
4. Track maximum frequency for vowels and consonants separately
5. Return sum of both maximum frequencies

**Code Walkthrough**:
```python
import string

class Solution:
    def maxFreqSum(self, s: str) -> int:
        vowels = set(list('aeiou'))  # Create vowel set for O(1) lookup
        max_vow = 0  # Track maximum vowel frequency
        max_con = 0  # Track maximum consonant frequency
        freq = {}    # Frequency map for all characters
        
        # Step 1: Count frequency of each character
        for c in s:
            freq[c] = freq.get(c, 0) + 1
        
        # Step 2: Find max frequency for vowels and consonants
        for c in list(string.ascii_lowercase):
            if c in vowels:
                max_vow = max(max_vow, freq.get(c, 0))  # Update max vowel freq
            else:
                max_con = max(max_con, freq.get(c, 0))  # Update max consonant freq
        
        return max_vow + max_con
```

**Why This Works**:
- **Frequency Counting**: First loop builds complete frequency map
- **Category Separation**: Uses vowel set to classify each letter
- **Maximum Tracking**: Maintains separate maximums for each category
- **Default Handling**: `freq.get(c, 0)` handles letters not in string (frequency 0)

**Example Trace (s = "successes")**:
1. Frequency map: {'s': 4, 'u': 1, 'c': 2, 'e': 2}
2. Check each letter:
   - 'a' (vowel): freq = 0, max_vow = max(0, 0) = 0
   - 'b' (consonant): freq = 0, max_con = max(0, 0) = 0
   - 'c' (consonant): freq = 2, max_con = max(0, 2) = 2
   - ...
   - 'e' (vowel): freq = 2, max_vow = max(0, 2) = 2
   - ...
   - 's' (consonant): freq = 4, max_con = max(2, 4) = 4
   - 'u' (vowel): freq = 1, max_vow = max(2, 1) = 2
3. Result: max_vow + max_con = 2 + 4 = 6

**Alternative Approaches**:
1. **Two-pass with filtering**: Separate vowels and consonants first, then find max
2. **Single-pass tracking**: Track max frequencies while building frequency map
3. **Collections.Counter**: Use Counter for cleaner frequency counting

## Tags

array, string, hash table