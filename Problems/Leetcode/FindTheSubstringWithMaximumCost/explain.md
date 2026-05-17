## Problem

https://leetcode.com/problems/find-the-substring-with-maximum-cost/description

Given:
- A string `s` of lowercase English letters
- A string `chars` containing distinct characters
- An integer array `vals` of the same length as `chars`

Find the maximum cost among all substrings of `s`, where:
- **Cost of a substring** = sum of values of characters in the substring
- **Cost of empty string** = 0
- **Character value**:
  - If character is NOT in `chars`: its value is its position in alphabet (1-indexed). E.g., 'a' = 1, 'z' = 26
  - If character IS in `chars`: its value is `vals[index]` where index is its position in `chars`

**Example 1:**
- Input: `s = "adaa"`, `chars = "d"`, `vals = [-1000]`
- The value of 'a' is 1 (alphabet position), 'd' is -1000 (custom value)
- Maximum cost substring is "aa" with cost 1 + 1 = 2
- Output: 2

**Example 2:**
- Input: `s = "abc"`, `chars = "abc"`, `vals = [-1,-1,-1]`
- All characters have negative values
- Maximum cost is from empty substring with cost 0
- Output: 0

## Observations

1. **Kadane's Algorithm Variant**: This is a variant of the maximum subarray sum problem. We want to find a contiguous substring (or empty) with maximum total cost.

2. **Character Value Mapping**: We need a preprocessing step to build a character-to-value mapping:
   - Initialize all lowercase letters with their alphabet positions (1-26)
   - Override values for characters in `chars` with their custom values from `vals`

3. **Empty String is Valid**: Since the cost of an empty string is 0, the answer is **always ≥ 0**. This means we never need to skip characters—we can always choose to not include any substring.

4. **Greedy Decision at Each Step**: For each character, we make a local decision:
   - Should we extend the current substring? (Yes, if `cur_max + value ≥ 0`)
   - Should we start a new substring from here? (Yes, if `value > cur_max + value`)
   - Should we exclude this character? (Yes, if both options above are negative—reset to 0, which implicitly gives empty string)
   
   The key insight: `cur_max = max(value, cur_max + value)` handles starting fresh vs extending.

5. **Time Complexity**: O(n) where n is the length of string `s`. Single pass through the string after O(26) preprocessing.

6. **Space Complexity**: O(1) since the scores dictionary is bounded by 26 characters (lowercase alphabet).

## Solution

```python
class Solution:
    def maximumCostSubstring(self, s: str, chars: str, vals: List[int]) -> int:
        # Step 1: Build character-to-value mapping
        scores = {}
        for c in string.ascii_lowercase:
            val = ord(c) - ord('a') + 1
            scores[c] = val
        
        # Step 2: Override with custom values
        for i, c in enumerate(chars):
            scores[c] = vals[i]
        
        # Step 3: Apply Kadane's algorithm with a twist
        n = len(s)
        res = 0  # Initialize to 0 because empty string is valid
        cur_max = 0  # Maximum cost ending at current position
        
        for c in s:
            # Decide: extend current substring or start new
            cur_max = max(scores[c], cur_max + scores[c])
            # Track overall maximum
            res = max(res, cur_max)
        
        return res
```

### Step-by-Step Walkthrough (Example 1: `s = "adaa"`, `chars = "d"`, `vals = [-1000]`)

**Initial Setup:**
```
scores = {'a': 1, 'b': 2, ..., 'd': -1000, ..., 'z': 26}
res = 0, cur_max = 0
```

**Iteration 1** (character 'a'):
```
cur_max = max(1, 0 + 1) = max(1, 1) = 1
res = max(0, 1) = 1
Meaning: substring "a" has cost 1
```

**Iteration 2** (character 'd'):
```
cur_max = max(-1000, 1 + (-1000)) = max(-1000, -999) = -999
res = max(1, -999) = 1
Meaning: including 'd' makes cost negative, but we keep best so far
```

**Iteration 3** (character 'a'):
```
cur_max = max(1, -999 + 1) = max(1, -998) = 1
res = max(1, 1) = 1
Meaning: we start fresh with just "a" (cost 1) instead of extending
```

**Iteration 4** (character 'a'):
```
cur_max = max(1, 1 + 1) = max(1, 2) = 2
res = max(1, 2) = 2
Meaning: we extend to get "aa" (cost 2)
```

**Result: 2** ✓

### Key Insight

The line `cur_max = max(scores[c], cur_max + scores[c])` is the heart of the algorithm:
- `scores[c]`: Cost of starting a fresh substring from current character
- `cur_max + scores[c]`: Cost of extending the current substring
- We pick whichever is larger (greedier approach)

Since `res` is initialized to 0, we implicitly handle the empty substring case. If all values are negative, `res` stays 0.

# Tags

#maximum-subarray #kadane-algorithm #dynamic-programming #prefix-sum

