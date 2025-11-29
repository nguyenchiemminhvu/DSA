## Problem

https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/description/

```
Given a binary string s, return true if the longest contiguous segment of 1's is strictly longer than the longest contiguous segment of 0's in s, or return false otherwise.

For example, in s = "110100010" the longest continuous segment of 1s has length 2, and the longest continuous segment of 0s has length 3.
Note that if there are no 0's, then the longest continuous segment of 0's is considered to have a length 0. The same applies if there is no 1's.

Example 1:
Input: s = "1101"
Output: true
Explanation:
The longest contiguous segment of 1s has length 2: "1101"
The longest contiguous segment of 0s has length 1: "1101"
The segment of 1s is longer, so return true.

Example 2:
Input: s = "111000"
Output: false
Explanation:
The longest contiguous segment of 1s has length 3: "111000"
The longest contiguous segment of 0s has length 3: "111000"
The segment of 1s is not longer, so return false.

Example 3:
Input: s = "110100010"
Output: false
Explanation:
The longest contiguous segment of 1s has length 2: "110100010"
The longest contiguous segment of 0s has length 3: "110100010"
The segment of 1s is not longer, so return false.

Constraints:
- 1 <= s.length <= 100
- s[i] is either '0' or '1'.
```

## Observations

1. **Core Task**: Find the maximum length of consecutive 1's and consecutive 0's, then compare them
2. **Key Insight**: When we split a string by a delimiter, we get all segments between those delimiters
   - Splitting by '0' gives us all segments of consecutive 1's (plus empty strings at boundaries)
   - Splitting by '1' gives us all segments of consecutive 0's (plus empty strings at boundaries)
3. **Edge Cases**: 
   - If there are no 0's, split('0') returns the entire string
   - If there are no 1's, split('1') returns the entire string
   - Empty strings from split have length 0, which correctly represents "no segment"

## Solution

1. `s.split('0')` splits the string by '0', creating a list of all substrings between 0's
   - These substrings are consecutive segments of 1's
   - Example: "110100010".split('0') = ['11', '1', '', '', '1', '']
   
2. `s.split('1')` splits the string by '1', creating a list of all substrings between 1's
   - These substrings are consecutive segments of 0's
   - Example: "110100010".split('1') = ['', '', '0', '000', '0']

3. `max(len(sub) for sub in ...)` finds the maximum length among all segments
   - For ones: max(2, 1, 0, 0, 1, 0) = 2
   - For zeros: max(0, 0, 1, 3, 1) = 3

4. Compare: 2 > 3 = False

**Time Complexity**: O(n) where n is the length of string s
- Each split operation scans the string once: O(n)
- Finding max length scans the split results: O(n)

**Space Complexity**: O(n)
- The split operations create new lists with total length proportional to n

**Alternative approach** (more explicit but longer):
- Iterate through the string once, tracking current and maximum lengths for both 1's and 0's
- Would have O(1) space complexity but the code would be longer

# Tags
#string #array #simulation #one-pass

