## Problem

https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/description/

```
You are given two 0-indexed integer arrays player1 and player2, representing the number of pins that player 1 and player 2 hit in a bowling game, respectively.

The bowling game consists of n turns, and the number of pins in each turn is exactly 10.

Assume a player hits xi pins in the ith turn. The value of the ith turn for the player is:
- 2xi if the player hits 10 pins in either (i - 1)th or (i - 2)th turn.
- Otherwise, it is xi.

The score of the player is the sum of the values of their n turns.

Return:
- 1 if the score of player 1 is more than the score of player 2,
- 2 if the score of player 2 is more than the score of player 1, and
- 0 in case of a draw.

Constraints:
- n == player1.length == player2.length
- 1 <= n <= 1000
- 0 <= player1[i], player2[i] <= 10

Example 1:
Input: player1 = [5,10,3,2], player2 = [6,5,7,3]
Output: 1
Explanation: 
The score of player 1 is 5 + 10 + 2*3 + 2*2 = 25.
The score of player 2 is 6 + 5 + 7 + 3 = 21.

Example 2:
Input: player1 = [3,5,7,6], player2 = [8,10,10,2]
Output: 2
Explanation:
The score of player 1 is 3 + 5 + 7 + 6 = 21.
The score of player 2 is 8 + 10 + 2*10 + 2*2 = 42.
```

## Observations

1. **Bonus Mechanism**: A player gets double points for the current turn if they scored 10 (strike) in either of the previous two turns
   - Turn 0: No bonus possible (no previous turns)
   - Turn 1: Bonus only if turn 0 was a strike
   - Turn 2+: Bonus if turn (i-1) OR turn (i-2) was a strike

2. **Score Calculation**: Each turn contributes to the score:
   - Base score: Always add the pins hit in current turn
   - Bonus score: If bonus condition is met, add the pins again (effectively doubling)
   - Formula when bonus applies: `xi + xi = 2 * xi`

3. **Edge Cases to Handle**:
   - First turn (i=0): No bonus possible
   - Second turn (i=1): Only check turn (i-1) for bonus
   - Remaining turns: Check both turn (i-1) and turn (i-2)

4. **Independence**: Both players' scores are calculated independently using identical rules

5. **Efficiency**: Single pass through arrays is sufficient - O(n) time complexity

## Solution

**Approach: Simulation with Conditional Scoring**

The solution simulates the bowling game by iterating through each turn and calculating scores according to the bonus rules.

**Algorithm:**
1. Initialize score counters `s1` and `s2` for both players
2. For each turn `i` from 0 to n-1:
   - Add base score: `s1 += player1[i]` and `s2 += player2[i]`
   - Check bonus conditions based on turn index:
     - **i > 1**: Check if `player[i-1] == 10` OR `player[i-2] == 10`
     - **i > 0 (but not > 1)**: Only check if `player[i-1] == 10`
     - **i == 0**: No bonus check needed
   - If bonus applies, add the current pins again to the score
3. Compare final scores and return 1, 2, or 0 accordingly

**Time Complexity:** O(n) - Single pass through both arrays  
**Space Complexity:** O(1) - Only constant extra space for score variables

**Example Walkthrough (Example 1):**
- `player1 = [5,10,3,2]`, `player2 = [6,5,7,3]`

Player 1:
- Turn 0: 5 (no bonus) → s1 = 5
- Turn 1: 10 (no bonus, previous was 5 ≠ 10) → s1 = 15
- Turn 2: 3 (bonus! turn i-1 = 10) → s1 = 15 + 3 + 3 = 21
- Turn 3: 2 (bonus! turn i-2 = 10) → s1 = 21 + 2 + 2 = 25

Player 2:
- Turn 0: 6 → s2 = 6
- Turn 1: 5 (no bonus) → s2 = 11
- Turn 2: 7 (no bonus) → s2 = 18
- Turn 3: 3 (no bonus) → s2 = 21

Result: 25 > 21 → return 1

# Tags

`Array` `Simulation` `Game-Theory`