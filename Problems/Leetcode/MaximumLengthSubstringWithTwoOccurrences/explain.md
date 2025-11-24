## Problem

https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/description/

```
Given a string s, return the maximum length of a substring such that it contains at most two occurrences of each character.

Example 1:

Input: s = "bcbbbcba"

Output: 4

Explanation:

The following substring has a length of 4 and contains at most two occurrences of each character: "bcbbbcba".

Example 2:

Input: s = "aaaa"

Output: 2

Explanation:

The following substring has a length of 2 and contains at most two occurrences of each character: "aaaa".

Constraints:

2 <= s.length <= 100
s consists only of lowercase English letters.
```

## Observations

1. **Sliding Window Problem**: This is a classic sliding window problem where we need to maintain a window that satisfies the constraint (at most 2 occurrences of each character).

2. **Character Frequency Tracking**: We need to track the frequency of each character in the current window using a hash map/dictionary.

3. **Window Expansion and Contraction**: 
   - Expand the window by moving the right pointer and adding characters
   - Contract the window by moving the left pointer when the constraint is violated (any character appears more than 2 times)

4. **Constraint Violation**: When any character in the current window appears more than 2 times, we need to shrink the window from the left until the constraint is satisfied again.

5. **Maximum Length Tracking**: Keep track of the maximum valid window size encountered during the process.

## Solution

1. **Initialization**: Set up left (`l`) and right (`r`) pointers at 0, frequency map (`f`), and result (`res`) variable.

2. **Window Expansion**: Move right pointer and add the character at `s[r]` to the frequency map.

3. **Constraint Check**: Check if any character in the current window has more than 2 occurrences.

4. **Window Contraction**: If constraint is violated, shrink the window from the left:
   - Decrease the frequency of character at `s[l]`
   - Remove the character from the map if its count becomes 0
   - Move left pointer forward

5. **Update Result**: After ensuring the window is valid, update the maximum length.

6. **Continue**: Move right pointer and repeat until the entire string is processed.

**Example Walkthrough** (`s = "bcbbbcba"`):
- Window `"bc"` (length 2) → valid
- Window `"bcb"` (length 3) → valid  
- Window `"bcbb"` (length 4) → valid (b appears 2 times)
- Window `"bcbbb"` → invalid (b appears 3 times), shrink to `"cbbb"`, still invalid, shrink to `"bbb"`, still invalid, shrink to `"bb"` → valid
- Continue expanding... maximum length found is 4

**Time Complexity**: O(n) - Each character is visited at most twice (once by right pointer, once by left pointer)
**Space Complexity**: O(1) - At most 26 lowercase letters in the frequency map

# Tags
- Sliding Window
- Two Pointers  
- Hash Map
- String

