## Problem

https://leetcode.com/problems/furthest-point-from-origin/

```
You are given a string moves of length n consisting only of characters 'L', 'R', and '_'. The string represents your movement on a number line starting from the origin 0.

In the ith move, you can choose one of the following directions:

move to the left if moves[i] = 'L' or moves[i] = '_'
move to the right if moves[i] = 'R' or moves[i] = '_'
Return the distance from the origin of the furthest point you can get to after n moves.

Example 1:

Input: moves = "L_RL__R"
Output: 3
Explanation: The furthest point we can reach from the origin 0 is point -3 through the following sequence of moves "LLRLLLR".

Example 2:

Input: moves = "_R__LL_"
Output: 5
Explanation: The furthest point we can reach from the origin 0 is point -5 through the following sequence of moves "LRLLLLL".

Example 3:

Input: moves = "_______"
Output: 7
Explanation: The furthest point we can reach from the origin 0 is point 7 through the following sequence of moves "RRRRRRR".

Constraints:

1 <= moves.length == n <= 50
moves consists only of characters 'L', 'R' and '_'.
```

## Observations

1. **Movement Rules**: We can move left ('L'), right ('R'), or choose direction for wildcard ('_')
2. **Goal**: Maximize distance from origin (0) after all moves
3. **Key Insight**: To maximize distance, we should use all wildcards ('_') to move in the same direction as our net movement
4. **Net Movement**: After fixed moves (L and R), we have a net position of `right_moves - left_moves`
5. **Optimal Strategy**: Use all wildcards to amplify the net movement direction

## Solution

**Approach**: Count and Calculate

The solution uses a greedy approach:

1. **Count Moves**: 
   - Count left moves ('L')
   - Count right moves ('R') 
   - Count wildcards ('_')

2. **Calculate Net Position**: 
   - Net movement from fixed moves = `right_moves - left_moves`
   - Absolute value gives us the distance from origin after fixed moves

3. **Maximize with Wildcards**:
   - Use all wildcards to move in the same direction as the net movement
   - This amplifies the distance by the number of wildcards

4. **Final Distance**: `abs(left_moves - right_moves) + wildcards`

**Example Walkthrough** (`moves = "L_RL__R"`):
- L = 2, R = 2, _ = 3
- Net from fixed moves: |2 - 2| = 0
- Use all 3 wildcards in same direction: 0 + 3 = 3
- Maximum distance = 3

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using three counters

# Tags

`Greedy` `Math` `String`

