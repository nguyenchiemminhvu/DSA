## Problem

https://leetcode.com/problems/find-the-winning-player-in-coin-game/description/

You are given two positive integers `x` and `y`, denoting the number of coins with values 75 and 10 respectively.

Alice and Bob are playing a game. Each turn, starting with Alice, the player must pick up coins with a total value 115. If the player is unable to do so, they lose the game.

Return the name of the player who wins the game if both players play optimally.

### Examples

**Example 1:**
```
Input: x = 2, y = 7
Output: "Alice"
Explanation:
The game ends in a single turn:
- Alice picks 1 coin with a value of 75 and 4 coins with a value of 10.
```

**Example 2:**
```
Input: x = 4, y = 11
Output: "Bob"
Explanation:
The game ends in 2 turns:
- Alice picks 1 coin with a value of 75 and 4 coins with a value of 10.
- Bob picks 1 coin with a value of 75 and 4 coins with a value of 10.
```

### Constraints
- `1 <= x, y <= 100`

## Observations

1. **Fixed Move Pattern**: To make exactly 115 in value, the only combination is:
   - 1 coin of value 75 + 4 coins of value 10 = 75 + 40 = 115
   - This is the ONLY way to achieve 115 (since 75 × 2 = 150 > 115)

2. **Game Termination**: The game continues until a player cannot make a valid move (pick 1 coin of 75 and 4 coins of 10).

3. **Turn-Based Logic**: 
   - Alice goes first
   - Players alternate turns
   - The player who cannot make a move loses
   - The other player wins

4. **Maximum Turns**: The maximum number of turns possible is `min(x, y // 4)` because:
   - Each turn requires exactly 1 coin of value 75
   - Each turn requires exactly 4 coins of value 10
   - The game ends when either `x < 1` or `y < 4`

5. **Winning Condition**:
   - If the total number of valid turns is odd, Alice wins (she makes the last valid move)
   - If the total number of valid turns is even, Bob wins (he makes the last valid move)

## Solution

1. **Initialize**: Start with `alice_turn = True` (Alice goes first)

2. **Simulate Each Turn**:
   - Check if current player can make a move (`x >= 1` and `y >= 4`)
   - If yes: deduct 1 from x and 4 from y, then toggle turn
   - If no: break the loop (current player cannot move)

3. **Determine Winner**:
   - After the loop, `alice_turn` indicates whose turn it would be next
   - If `alice_turn = True`, Alice cannot move → Bob wins
   - If `alice_turn = False`, Bob cannot move → Alice wins

### Step-by-Step Example

**Example 1: x = 2, y = 7**
```
Initial: x = 2, y = 7, alice_turn = True
Turn 1: Alice moves → x = 1, y = 3, alice_turn = False
Loop check: x = 1, y = 3 → y < 4, break
Result: alice_turn = False → Alice wins
```

**Example 2: x = 4, y = 11**
```
Initial: x = 4, y = 11, alice_turn = True
Turn 1: Alice moves → x = 3, y = 7, alice_turn = False
Turn 2: Bob moves → x = 2, y = 3, alice_turn = True
Loop check: x = 2, y = 3 → y < 4, break
Result: alice_turn = True → Bob wins
```

### Optimized Approach

Instead of simulation, we can calculate the winner directly:

```python
class Solution:
    def winningPlayer(self, x: int, y: int) -> str:
        # Calculate maximum number of turns
        max_turns = min(x, y // 4)
        
        # If odd number of turns, Alice wins (she makes last move)
        # If even number of turns, Bob wins (he makes last move)
        return "Alice" if max_turns % 2 == 1 else "Bob"
```

### Complexity Analysis

**Simulation Approach:**
- **Time Complexity**: O(min(x, y/4)) - iterates once per valid turn
- **Space Complexity**: O(1) - only uses a few variables

**Optimized Approach:**
- **Time Complexity**: O(1) - direct calculation
- **Space Complexity**: O(1) - only uses a few variables

### Key Insights

1. The problem is essentially counting how many complete turns can be played
2. The winner is determined by the parity (odd/even) of total turns
3. Since the move pattern is fixed (1×75 + 4×10 = 115), no other strategy exists
4. Both players playing optimally means they both make the same move when possible
5. The constraint is simply who runs out of valid moves first

# Tags

`Game Theory` `Math` `Simulation`

