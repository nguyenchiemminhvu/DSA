## Problem

https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/description/

```
A string is good if there are no repeated characters.

Given a string s​​​​​, return the number of good substrings of length three in s​​​​​​.

Note that if there are multiple occurrences of the same substring, every occurrence should be counted.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: s = "xyzzaz"
Output: 1
Explanation: There are 4 substrings of size 3: "xyz", "yzz", "zza", and "zaz". 
The only good substring of length 3 is "xyz".

Example 2:

Input: s = "aababcabc"
Output: 4
Explanation: There are 7 substrings of size 3: "aab", "aba", "bab", "abc", "bca", "cab", and "abc".
The good substrings are "abc", "bca", "cab", and "abc".

Constraints:

1 <= s.length <= 100
s​​​​​​ consists of lowercase English letters.
```

## Observations

1. **Problem Requirements**: We need to find all substrings of exactly length 3 where all characters are distinct (no repeated characters).

2. **Key Insights**:
   - We need to examine all possible substrings of length 3
   - For a substring to be "good", it must have exactly 3 distinct characters
   - We can use a sliding window approach to efficiently check all substrings

3. **Examples Analysis**:
   - `s = "xyzzaz"`: substrings are "xyz" ✓, "yzz" ✗, "zza" ✗, "zaz" ✗ → count = 1
   - `s = "aababcabc"`: substrings are "aab" ✗, "aba" ✗, "bab" ✗, "abc" ✓, "bca" ✓, "cab" ✓, "abc" ✓ → count = 4

4. **Edge Cases**:
   - String length < 3: return 0
   - All characters the same: return 0
   - String with all distinct characters: return (length - 2)

## Solution

### Approach: Sliding Window with Hash Map

The solution uses a sliding window technique with a frequency counter to efficiently track character occurrences in the current window.

**Algorithm Steps**:
1. Initialize variables: `res` (result counter), `counter` (frequency map), `left` and `right` pointers
2. Expand the window by moving `right` pointer:
   - Add current character to frequency counter
   - If window size exceeds 3, shrink from left:
     - Decrease frequency of left character
     - Remove it from counter if frequency becomes 0
     - Move `left` pointer forward
3. Check if current window is valid:
   - Window size equals 3 AND
   - Number of distinct characters equals 3 (len(counter) == 3)
   - If valid, increment result counter

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - counter map stores at most 3 characters

**Code Walkthrough**:
```python
class Solution:
    def countGoodSubstrings(self, s: str) -> int:
        res = 0
        counter = {}  # Frequency map for current window
        n = len(s)
        left, right = 0, 0
        
        while right < n:
            # Expand window: add right character
            counter[s[right]] = counter.get(s[right], 0) + 1
            
            # Shrink window if size > 3
            if right - left + 1 > 3:
                counter[s[left]] -= 1
                if counter[s[left]] <= 0:
                    counter.pop(s[left])  # Remove if frequency is 0
                left += 1
            
            # Check if current window is a good substring
            if right - left + 1 == 3 and len(counter.keys()) == 3:
                res += 1
            
            right += 1
        
        return res
```

**Example Trace** (s = "xyzzaz"):
- Window "xyz": counter = {'x':1, 'y':1, 'z':1}, len=3, distinct=3 ✓ (res=1)
- Window "yzz": counter = {'y':1, 'z':2}, len=3, distinct=2 ✗
- Window "zza": counter = {'z':1, 'a':1}, len=3, distinct=2 ✗
- Window "zaz": counter = {'z':2, 'a':1}, len=3, distinct=2 ✗

**Alternative Simpler Approach**:
```python
def countGoodSubstrings(self, s: str) -> int:
    count = 0
    for i in range(len(s) - 2):
        substr = s[i:i+3]
        if len(set(substr)) == 3:  # All characters distinct
            count += 1
    return count
```

# Tags

- **Sliding Window**
- **Hash Map / Hash Table**
- **String Processing**
- **Two Pointers**

