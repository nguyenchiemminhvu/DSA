## Problem

https://leetcode.com/problems/find-mirror-score-of-a-string/description/

You are given a string s.

We define the mirror of a letter in the English alphabet as its corresponding letter when the alphabet is reversed. For example, the mirror of 'a' is 'z', and the mirror of 'y' is 'b'.

Initially, all characters in the string s are unmarked.

You start with a score of 0, and you perform the following process on the string s:

- Iterate through the string from left to right.
- At each index i, find the **closest** unmarked index j such that j < i and s[j] is the mirror of s[i]. Then, mark both indices i and j, and add the value i - j to the total score.
- If no such index j exists for the index i, move on to the next index without making any changes.

Return the total score at the end of the process.

**Example 1:**
- Input: s = "aczzx"
- Output: 5
- Explanation:
  - i = 0: No mirror found before, skip
  - i = 1: No mirror found before, skip
  - i = 2 ('z'): Found mirror 'a' at j = 0, mark both, score += 2 - 0 = 2
  - i = 3 ('z'): No unmarked mirror found before, skip
  - i = 4 ('x'): Found mirror 'c' at j = 1, mark both, score += 4 - 1 = 3
  - Total: 2 + 3 = 5

**Example 2:**
- Input: s = "abcdef"
- Output: 0
- Explanation: No character has its mirror in the string.

**Constraints:**
- 1 <= s.length <= 10^5
- s consists only of lowercase English letters.

## Observations

1. **Mirror Relationship**: The mirror of a character at position `k` from 'a' is at position `25 - k` from 'a':
   - 'a' (0) ↔ 'z' (25)
   - 'b' (1) ↔ 'y' (24)
   - 'c' (2) ↔ 'x' (23)
   - etc.

2. **Closest Match**: We need to find the **closest** (most recent) unmarked index j where s[j] is the mirror of s[i]. This suggests using a stack (LIFO) structure - the last pushed element is the closest one.

3. **Greedy Matching**: Once we find a mirror match, we immediately mark both indices and add to the score. This is optimal because:
   - Waiting won't give us a better score
   - The closest match gives the smallest distance but is still valid
   - Each character can only be used once (marking prevents reuse)

4. **Data Structure**: For each of the 26 letters, maintain a stack of unmarked indices where that letter appears. When processing character at index i:
   - Check if the mirror character has any unmarked indices
   - If yes, pop the most recent one (closest) and calculate score
   - If no, push current index to its own character's stack

5. **Time Complexity**: O(n) - single pass through the string
6. **Space Complexity**: O(n) - in worst case, all characters are stored in stacks

## Solution

```python
class Solution:
    def calculateScore(self, s: str) -> int:
        def get_reflection(val: int) -> int:
            return 25 - val
        
        # Convert string to numeric values (0-25)
        s = [ord(c) - ord('a') for c in s]
        
        # Create 26 stacks, one for each letter
        # sts[i] stores indices where letter i appears (unmarked)
        sts = [[] for _ in range(26)]
        
        res = 0
        for i, val in enumerate(s):
            # Find the mirror character
            ref = get_reflection(val)
            
            # Check if the mirror character has any unmarked indices
            if sts[ref]:
                # Pop the closest (most recent) index
                j = sts[ref].pop()
                # Add distance to score
                res += i - j
            else:
                # No mirror found, store current index for future matching
                sts[val].append(i)
        
        return res
```

**Algorithm Walkthrough (Example 1: "aczzx"):**

```
Initial: sts = [[], [], ..., []]  (26 empty lists)

i=0, val='a'(0), ref='z'(25):
  sts[25] is empty → push 0 to sts[0]
  sts[0] = [0]

i=1, val='c'(2), ref='x'(23):
  sts[23] is empty → push 1 to sts[2]
  sts[2] = [1]

i=2, val='z'(25), ref='a'(0):
  sts[0] = [0] not empty → pop j=0
  res += 2 - 0 = 2
  sts[0] = []

i=3, val='z'(25), ref='a'(0):
  sts[0] is empty → push 3 to sts[25]
  sts[25] = [3]

i=4, val='x'(23), ref='c'(2):
  sts[2] = [1] not empty → pop j=1
  res += 4 - 1 = 3
  Total res = 5
```

**Key Insight**: Using stacks for each character ensures we always get the **closest** unmarked match, which is exactly what the problem requires. The pop operation naturally gives us the most recently added (closest) index.

# Tags

