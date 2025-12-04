## Problem

https://leetcode.com/problems/find-the-losers-of-the-circular-game/description/

There are `n` friends playing a game in a circular arrangement, numbered from 1 to `n` in clockwise order. The game follows these rules:

1. The 1st friend starts with the ball
2. On the ith turn, the friend with the ball passes it `i * k` steps clockwise
3. The game ends when someone receives the ball for the **second time**
4. **Losers** are friends who never received the ball

**Goal**: Return an array of losers in ascending order.

**Examples**:

```
Input: n = 5, k = 2
Output: [4,5]

Turn 1: Friend 1 → Friend 3 (2 steps)
Turn 2: Friend 3 → Friend 2 (4 steps)
Turn 3: Friend 2 → Friend 3 (6 steps)
Game ends (Friend 3 receives ball twice)
Losers: Friends 4 and 5
```

```
Input: n = 4, k = 4
Output: [2,3,4]

Turn 1: Friend 1 → Friend 1 (4 steps = full circle)
Game ends (Friend 1 receives ball twice)
Losers: Friends 2, 3, and 4
```

**Constraints**: `1 <= k <= n <= 50`

## Observations

1. **Circular Movement**: Since friends sit in a circle, we use modulo arithmetic: `next_position = (current + steps) % n`

2. **Increasing Steps**: Each turn, steps increase by `k`:
   - Turn 1: `k` steps
   - Turn 2: `2k` steps  
   - Turn 3: `3k` steps
   - Turn i: `i * k` steps

3. **Tracking Visits**: We need to track which friends received the ball at least once. A boolean array works perfectly for this.

4. **Termination Condition**: The game ends when we try to pass to someone who already has `visited = true`

5. **Edge Case**: When `k % n == 0`, the ball returns to friend 1 immediately (Example 2)

6. **Time Complexity**: O(n) - In the worst case, each friend receives the ball once before someone gets it twice

7. **Space Complexity**: O(n) - We use a boolean array to track n friends

## Solution

**Algorithm Walkthrough** (Example 1: n=5, k=2):

```
Initial: members = [F, F, F, F, F], cur_idx = 0

Turn 1: 
  - Mark members[0] = T → [T, F, F, F, F]
  - next_idx = (0 + 2) % 5 = 2
  - members[2] = F, continue
  - cur_idx = 2, steps = 4

Turn 2:
  - Mark members[2] = T → [T, F, T, F, F]
  - next_idx = (2 + 4) % 5 = 1
  - members[1] = F, continue
  - cur_idx = 1, steps = 6

Turn 3:
  - Mark members[1] = T → [T, T, T, F, F]
  - next_idx = (1 + 6) % 5 = 2
  - members[2] = T, BREAK!

Result: Losers are indices [3, 4] → Friends [4, 5]
```

**Key Insights**:
- We increment `steps` by `k` after each turn (not before), matching the problem's "i * k" pattern
- Using modulo handles the circular nature elegantly
- We mark the current position before checking if the game should end
- Converting from 0-indexed to 1-indexed happens in the final return

# Tags

`Array` `Simulation` `Hash Table` `Circular Array` `Modulo Arithmetic`

