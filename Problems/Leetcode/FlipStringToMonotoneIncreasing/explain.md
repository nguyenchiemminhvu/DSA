## Problem

https://leetcode.com/problems/flip-string-to-monotone-increasing/description/

A binary string is **monotone increasing** if it consists of some number of 0's (possibly zero), followed by some number of 1's (also possibly zero). In other words, all 0's must come before all 1's, with no alternation between them.

Given a binary string `s`, you can flip any character `s[i]` (changing 0 to 1 or 1 to 0). Find the minimum number of flips needed to make the string monotone increasing.

### Examples

- **Input**: s = "00110" → **Output**: 1 (flip last 0 to get "00111")
- **Input**: s = "010110" → **Output**: 2 (flip to "011111" or "000111")  
- **Input**: s = "00011000" → **Output**: 2 (flip to "00000000")

### Constraints
- 1 ≤ s.length ≤ 10⁵
- s[i] is either '0' or '1'

## Observations

1. **Split Point Perspective**: A monotone increasing string has a "split point" - everything before (and including) the split should be 0, everything after should be 1. We need to find the optimal split point that minimizes flips.

2. **Key Insight**: At any position `i`, we can think of making `i` the boundary:
   - Flip all 1's in the left part (positions 0 to i-1) to 0's
   - Flip all 0's in the right part (positions i onwards) to 1's
   - The cost is: (count of 1's in left) + (count of 0's in right)

3. **Prefix/Suffix Approach**: 
   - Use a prefix counter for 1's as we scan left to right
   - Use a suffix array to count 0's from each position onwards
   - This allows $O(n)$ evaluation of all possible split points

4. **Why Two Calculations at Each Position**: The code considers two scenarios:
   - Whether the current character remains in its original form
   - Whether it gets flipped as part of the optimization at that split point
   - This explores all boundary positions efficiently

## Solution

```python
class Solution:
    def minFlipsMonoIncr(self, s: str) -> int:
        n = len(s)

        # suffix_0[i] = count of 0's from position i to end
        count_0 = 0
        suffix_0 = [0] * (n + 1)
        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                count_0 += 1
            suffix_0[i] = count_0

        res = n
        count_1 = 0  # count of 1's from position 0 to current
        for i, c in enumerate(s):
            if c == '1':
                # Scenario 1: Keep this '1' as part of right region (all 1's)
                # Cost: flip all 1's before it + flip all 0's after it
                res = min(res, count_1 + suffix_0[i + 1])
                count_1 += 1
                # Scenario 2: Flip this '1' to '0' (part of left region)
                # Cost: flip this new 1 + all 0's after it
                res = min(res, count_1 + suffix_0[i + 1])
            else:  # c == '0'
                # Scenario 1: Keep this '0' as part of right region (flip to 1)
                # Cost: flip all 1's before + flip this 0 and all after
                res = min(res, count_1 + suffix_0[i + 1])
                # Scenario 2: Keep this '0' as part of left region  
                # Cost: flip all 1's before + flip only 0's strictly after
                res = min(res, count_1 + suffix_0[i])
        
        return res
```

### Algorithm Walkthrough

**Step 1: Build suffix_0 array** (right to left)
- For "00110": suffix_0 = [3, 2, 1, 1, 1, 0]
  - Position 0: three 0's from position 0 onwards
  - Position 1: two 0's from position 1 onwards
  - etc.

**Step 2: Iterate and find minimum cost**
- At each position, we consider it as a potential boundary
- `count_1` tracks 1's in the left region (should be flipped to 0)
- `suffix_0[i]` / `suffix_0[i+1]` tracks 0's in the right region (should be flipped to 1)
- Update result with the minimum cost found

**Time Complexity**: $O(n)$ - two passes through the string
**Space Complexity**: $O(n)$ - suffix_0 array

# Tags

