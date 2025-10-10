## Problem

https://leetcode.com/problems/open-the-lock/

```
You have a lock in front of you with 4 circular wheels. Each wheel has 10 slots: '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'. The wheels can rotate freely and wrap around: for example we can turn '9' to be '0', or '0' to be '9'. Each move consists of turning one wheel one slot.

The lock initially starts at '0000', a string representing the state of the 4 wheels.

You are given a list of deadends dead ends, meaning if the lock displays any of these codes, the wheels of the lock will stop turning and you will be unable to open it.

Given a target representing the value of the wheels that will unlock the lock, return the minimum total number of turns required to open the lock, or -1 if it is impossible.

Example 1:

Input: deadends = ["0201","0101","0102","1212","2002"], target = "0202"
Output: 6
Explanation: 
A sequence of valid moves would be "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202".
Note that a sequence like "0000" -> "0001" -> "0002" -> "0102" -> "0202" would be invalid,
because the wheels of the lock become stuck after the display becomes the dead end "0102".

Example 2:

Input: deadends = ["8888"], target = "0009"
Output: 1
Explanation: We can turn the last wheel in reverse to move from "0000" -> "0009".

Example 3:

Input: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
Output: -1
Explanation: We cannot reach the target without getting stuck.

Constraints:

1 <= deadends.length <= 500
deadends[i].length == 4
target.length == 4
target will not be in the list deadends.
target and deadends[i] consist of digits only.
```

## Observations

1. **Problem Type**: This is a shortest path problem in an implicit graph where each node represents a lock state (`4-digit` combination) and edges connect states that differ by exactly one wheel rotation.

2. **State Space**: The total state space is `10^4 = 10,000` possible combinations (`0000` to `9999`).

3. **Graph Structure**: 
   - Each state has exactly `8` neighbors (`2` directions × `4` wheels)
   - For each wheel, you can rotate clockwise `(+1)` or counterclockwise `(-1)`
   - Rotations wrap around: `9→0` and `0→9`

4. **Constraints**:
   - Starting position is always `"0000"`
   - Some states are `"deadends"` - if reached, the lock gets stuck
   - Need to find minimum moves to reach target, or `-1` if impossible

5. **Algorithm Choice**: `BFS` is optimal here because:
   - We need the shortest path (minimum number of moves)
   - All edges have equal weight (`1` move per transition)
   - `BFS` guarantees we find the minimum number of steps

## Solution

1. **Edge Cases**: 
   - If starting position `"0000"` is a deadend, return `-1` immediately
   - If target is `"0000"`, return `0` (already at target)

2. **Data Representation**:
   - Convert strings to tuples of integers for easier manipulation
   - Use tuples because they're hashable (can be stored in sets)

3. **Neighbor Generation**:
   - For each wheel position `(0-3)`, generate two neighbors:
     - Clockwise: `(digit + 1) % 10`
     - Counterclockwise: `((digit - 1) + 10) % 10`
   - The `+10` ensures no negative results when wrapping `0→9`

4. **BFS Implementation**:
   - Use level-by-level BFS to track steps accurately
   - `cur_len = len(Q)` captures current level size
   - Process entire level before incrementing steps
   - Check for target when dequeuing (not when enqueuing)

5. **State Management**:
   - `visited`: Prevents revisiting states (avoids cycles)
   - `disabled`: Stores deadend states to avoid
   - Both use sets for `O(1)` lookup time

**Time Complexity**: `O(V + E)` where `V = 10^4` states, `E = 8×10^4` edges = `O(10^4)`
**Space Complexity**: `O(V)` for visited set and queue = `O(10^4)`

**Key Insights**:
- BFS guarantees minimum steps due to equal edge weights
- Tuple representation enables efficient hashing and set operations  
- Level-by-level processing ensures accurate step counting
- Early termination when target is found optimizes performance

## Tags

string, bfs