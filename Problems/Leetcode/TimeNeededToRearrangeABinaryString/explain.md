## Problem

https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/description

Given a binary string `s`, in one second all occurrences of "01" are simultaneously replaced with "10". This process repeats until no occurrences of "01" exist.

**Return** the number of seconds needed to complete this process.

### Examples

**Example 1:**
```
Input: s = "0110101"
Output: 4
Explanation:
After one second, s becomes "1011010".
After another second, s becomes "1101100".
After the third second, s becomes "1110100".
After the fourth second, s becomes "1111000".
```

**Example 2:**
```
Input: s = "11100"
Output: 0
Explanation: No occurrence of "01" exists in s.
```

### Constraints
- 1 <= s.length <= 1000
- s[i] is either '0' or '1'

### Follow-up
- Can you solve this problem in O(n) time complexity?

---

## Observations

1. **Pattern Recognition**: Each swap moves a '0' one position to the right. When we have multiple consecutive '0's, they all move right simultaneously, each passing through one '1' per second.

2. **Key Insight - "Bubble" Movement**: Think of '0's as needing to "bubble" rightward, passing through '1's:
   - A single '0' followed by k '1's takes k seconds to reach its final position
   - Multiple '0's stacked together must pass through the same '1's

3. **Greedy Observation**: We don't need to simulate the entire process. We can calculate the answer in a single pass:
   - Track count of '0's seen so far
   - When we encounter a '1' after seeing '0's, those '0's need to move right
   - The time needed depends on:
     - How many swap operations occurred previously (`times + 1`)
     - How many '0's are "waiting" to move (`count_0`)
     - Take the maximum: the bottleneck determines total time

4. **Example Walkthrough**: `s = "0110101"`
   ```
   Index 0: '0' → count_0 = 1, times = 0
   Index 1: '1' → count_0 > 0, times = max(0+1, 1) = 1
   Index 2: '1' → count_0 > 0, times = max(1+1, 1) = 2
   Index 3: '0' → count_0 = 2, times = 2
   Index 4: '1' → count_0 > 0, times = max(2+1, 2) = 3
   Index 5: '0' → count_0 = 3, times = 3
   Index 6: '1' → count_0 > 0, times = max(3+1, 3) = 4
   ```
   Result: 4 ✓

---

## Solution

### Approach: Single-Pass Greedy with Counter

**Core Idea**: Instead of simulating swaps, track:
- `count_0`: number of '0's waiting to move past the current position
- `times`: minimum seconds needed to clear all "01" patterns

When we encounter a '1':
- All accumulated '0's to its left need to move right past it
- `times + 1` = at least one more swap round
- `count_0` = minimum time for all accumulated '0's to pass through
- Take max because both constraints must be satisfied

```python
class Solution:
    def secondsToRemoveOccurrences(self, s: str) -> int:
        times = 0
        count_0 = 0
        
        for c in s:
            if c == '0':
                # Accumulate count of zeros
                count_0 += 1
            else:  # c == '1'
                if count_0 > 0:
                    # Each '1' forces another round of swaps
                    # Need max(previous rounds + 1, accumulated zeros)
                    times = max(times + 1, count_0)
        
        return times
```

### Complexity Analysis

- **Time Complexity**: **O(n)** - Single pass through the string
- **Space Complexity**: **O(1)** - Only using two counters

### Why `max(times + 1, count_0)` Works

Consider the string structure: `[...0s...][1s...]`

**Case 1**: More swap rounds needed (times + 1 > count_0)
- Example: "001" → "010" → "100" (2 seconds, count_0=1)
- Previous operations establish a "flow" requiring times+1 seconds minimum

**Case 2**: More zeros accumulated (count_0 > times + 1)
- Example: "0001" → "0010" → "0100" → "1000" (3 seconds, count_0=3)
- Three zeros in a row need 3 seconds to fully pass through a '1'

**Example Trace**: `s = "0110101"`
- Pos 0: '0' | count_0=1, times=0
- Pos 1: '1' | one '0' needs to pass → times = max(1, 1) = 1
- Pos 2: '1' | that '0' still moving + now blocked by second '1' → times = max(2, 1) = 2
- Pos 3: '0' | count_0=2, times=2 (another zero waiting)
- Pos 4: '1' | two '0's now need to pass → times = max(3, 2) = 3
- Pos 5: '0' | count_0=3, times=3 (third zero joining)
- Pos 6: '1' | three '0's accumulated → times = max(4, 3) = 4 ✓

# Tags
- Greedy
- String Simulation
- Pattern Recognition
- Time Complexity Optimization

