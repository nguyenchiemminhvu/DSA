## Problem

https://leetcode.com/problems/find-the-child-who-has-the-ball-after-k-seconds/

```
You are given two positive integers n and k. There are n children numbered from 0 to n - 1 standing in a queue in order from left to right.

Initially, child 0 holds a ball and the direction of passing the ball is towards the right direction. After each second, the child holding the ball passes it to the child next to them. Once the ball reaches either end of the line, i.e. child 0 or child n - 1, the direction of passing is reversed.

Return the number of the child who receives the ball after k seconds.

Example 1:
Input: n = 3, k = 5
Output: 1

Example 2:
Input: n = 5, k = 6
Output: 2

Example 3:
Input: n = 4, k = 2
Output: 2

Constraints:
- 2 <= n <= 50
- 1 <= k <= 50
```

## Observations

1. **Pattern Recognition**: The ball bounces back and forth between positions 0 and n-1
   - Starting at position 0, it moves right: 0 → 1 → 2 → ... → (n-1)
   - Then reverses and moves left: (n-1) → (n-2) → ... → 0
   - This creates a repeating cycle

2. **Cycle Length**: One complete cycle (0 to n-1 and back to 0) takes `2 * (n - 1)` seconds
   - Going from 0 to n-1 takes (n-1) steps
   - Going from n-1 back to 0 takes another (n-1) steps
   - Total: 2 * (n-1) steps per full cycle

3. **Modulo Optimization**: Since the pattern repeats every `2 * (n - 1)` seconds, we can use modulo to reduce k
   - `k % (2 * (n - 1))` gives us the effective position within one cycle
   - This optimization handles large k values efficiently

4. **Two Phases**:
   - **Forward phase** (0 to n-1): If `k <= n-1`, the ball is still moving right, so position = k
   - **Backward phase** (n-1 to 0): If `k > n-1`, the ball is moving left from position n-1

## Solution

```python
class Solution:
    def numberOfChild(self, n: int, k: int) -> int:
        k %= (2 * (n - 1))
        if k <= n - 1:
            return k
        return (n - 1) - (k - (n - 1))
```

**Algorithm Explanation**:

1. **Reduce k using modulo**: `k %= (2 * (n - 1))`
   - Eliminates complete cycles since the pattern repeats
   - We only need to track position within the current cycle

2. **Check if in forward phase**: `if k <= n - 1`
   - If true, the ball is moving from 0 towards n-1
   - Position is simply k (since we start at 0)

3. **Handle backward phase**: `return (n - 1) - (k - (n - 1))`
   - If k > n-1, the ball has reached n-1 and is bouncing back
   - `k - (n - 1)` = steps taken after reaching n-1
   - `(n - 1) - steps` = current position while moving backward

**Example Walkthrough** (n = 5, k = 6):
- Cycle length = 2 * (5 - 1) = 8
- k % 8 = 6 (no reduction needed)
- Since 6 > 4 (n - 1), we're in the backward phase
- Steps after reaching position 4: 6 - 4 = 2
- Current position: 4 - 2 = 2 ✓

**Time Complexity**: O(1)  
**Space Complexity**: O(1)

# Tags
#math #simulation #pattern-recognition #modulo

