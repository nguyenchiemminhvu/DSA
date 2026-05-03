## Problem

https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/description

Given a string `s` and an integer `k`, return the maximum number of vowel letters in any substring of `s` with length `k`.

Vowel letters in English are `'a'`, `'e'`, `'i'`, `'o'`, and `'u'`.

**Constraints:**
- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters
- `1 <= k <= s.length`

**Examples:**

1. Input: `s = "abciiidef"`, `k = 3` → Output: `3`
   - The substring `"iii"` contains 3 vowel letters.

2. Input: `s = "aeiou"`, `k = 2` → Output: `2`
   - Any substring of length 2 contains 2 vowels.

3. Input: `s = "leetcode"`, `k = 3` → Output: `2`
   - `"lee"`, `"eet"`, and `"ode"` contain 2 vowels each.

## Observations

1. **Fixed Window Size**: We need to find the maximum vowel count in a window of **exactly** size `k`. Unlike variable-size sliding windows, the window size is fixed and doesn't change.

2. **Sliding Window Applicability**: As we move the window from position 0 to position `n-k`, we remove one character from the left and add one character from the right. This allows us to compute the vowel count incrementally rather than recounting from scratch.

3. **Key Insight**: For a fixed-size window, once the window reaches size `k`, we can immediately compute its vowel count. Then:
   - Remove the leftmost character (decrement count if it's a vowel)
   - Add the next character (increment count if it's a vowel)
   - Update the maximum

4. **Window Lifecycle**:
   - **Building phase** (`r - l < k - 1`): Expand the window by moving the right pointer
   - **Active phase** (`r - l == k - 1`): Window is exactly size `k`, update the result
   - **Sliding phase** (implicit): Window continues to be size `k` as both pointers move

## Solution

### Approach: Sliding Window with Two Pointers

```python
class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        def is_vowel(ch: str) -> bool:
            return ch=='a' or ch=='e' or ch=='i' or ch=='o' or ch=='u'
        
        n = len(s)
        l = 0
        count = 0
        res = 0
        
        for r in range(n):
            # Expand window: add the right character
            count += int(is_vowel(s[r]))
            
            # Shrink window if size exceeds k
            while r - l > k - 1:
                count -= int(is_vowel(s[l]))
                l += 1
            
            # When window is exactly size k, update result
            if r - l == k - 1:
                res = max(res, count)
        
        return res
```

### Explanation

1. **Initialization**:
   - `l = 0`: Left pointer
   - `count = 0`: Current vowel count in the window
   - `res = 0`: Maximum vowel count found so far

2. **Main Loop** (iterate right pointer `r` from 0 to n-1):
   - **Add character**: `count += int(is_vowel(s[r]))`
     - Convert boolean to integer (1 if vowel, 0 if consonant)
     - Add to the current window's vowel count
   
   - **Maintain window size** (while loop):
     - If window size exceeds `k` (checked by `r - l > k - 1`):
       - Remove the leftmost character: `count -= int(is_vowel(s[l]))`
       - Move left pointer: `l += 1`
   
   - **Update result** (when window is exactly size k):
     - Condition: `r - l == k - 1` means window size is exactly `k`
     - Update maximum: `res = max(res, count)`

### Complexity Analysis

- **Time Complexity**: $O(n)$
  - The right pointer traverses the entire string once: $O(n)$
  - The left pointer moves from 0 to n-1 only once (amortized): $O(n)$
  - Each character is visited by both pointers exactly once
  - Total: $O(2n) = O(n)$

- **Space Complexity**: $O(1)$
  - Only a few variables (`l`, `count`, `res`, `r`) are used
  - No additional data structures needed

### Why This Works (Correctness)

The algorithm checks all possible substrings of length exactly `k`:
- When `r = k-1`, the window `[0, k-1]` is evaluated
- When `r = k`, the window `[1, k]` is evaluated
- When `r = n-1`, the window `[n-k, n-1]` is evaluated

Total windows checked: $n - k + 1$, covering all possible substrings of length `k`.

# Tags

- Sliding Window
- Two Pointers
- String
- Fixed Window Size

