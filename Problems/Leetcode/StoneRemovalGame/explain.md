## Problem

https://leetcode.com/problems/stone-removal-game/

Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.

- Alice starts by removing exactly **10 stones** on her first turn.
- For each subsequent turn, each player removes exactly **1 fewer stone** than the previous opponent.
- The player who **cannot make a move loses** the game.

Given a positive integer `n`, return `true` if Alice wins the game and `false` otherwise.

### Examples

**Example 1:**
```
Input: n = 12
Output: true

Explanation:
- Alice removes 10 stones on her first turn, leaving 2 stones for Bob.
- Bob cannot remove 9 stones, so Alice wins.
```

**Example 2:**
```
Input: n = 1
Output: false

Explanation:
- Alice cannot remove 10 stones, so Alice loses.
```

### Constraints
- `1 <= n <= 50`

## Observations

1. **Turn Pattern**: 
   - Alice starts by removing 10 stones
   - Bob removes 9 stones (1 fewer than Alice)
   - Alice removes 8 stones (1 fewer than Bob)
   - Bob removes 7 stones (1 fewer than Alice)
   - And so on: 10, 9, 8, 7, 6, 5, 4, 3, 2, 1...

2. **Win Condition**: 
   - A player wins when their opponent cannot make a valid move
   - A player loses if they cannot remove the required number of stones

3. **Key Insight**:
   - The number of stones to remove decreases by 1 each turn
   - The game continues as long as there are enough stones remaining
   - We need to track whose turn it is when the game ends

4. **Edge Cases**:
   - If n < 10, Alice cannot even make her first move and loses immediately
   - The maximum number of stones that can be removed in a complete game is: 10 + 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 55

5. **Game Simulation**:
   - We can simulate the game turn by turn
   - Track the current player (Alice or Bob)
   - Subtract stones and decrease the removal count each turn
   - When a player cannot make their move, the other player wins

## Solution

### Approach: Simulation

The solution simulates the game by tracking:
- `n`: remaining stones
- `k`: number of stones to remove on current turn (starts at 10)
- `alice_turn`: boolean flag to track whose turn it is

**Algorithm:**
1. Initialize `k = 10` (Alice's first move) and `alice_turn = True`
2. While the current player can remove `k` stones (`n - k >= 0`):
   - Remove `k` stones from the pile: `n -= k`
   - Decrease the removal count for next turn: `k -= 1`
   - Switch turns: `alice_turn = not alice_turn`
3. When the loop ends, the current player cannot make a move
4. If `alice_turn` is `True`, Alice cannot move → Bob wins (return `False`)
5. If `alice_turn` is `False`, Bob cannot move → Alice wins (return `True`)

**Example Walkthrough (n = 12):**
```
Initial: n = 12, k = 10, alice_turn = True

Turn 1 (Alice):
- Can remove 10 stones? Yes (12 - 10 = 2 >= 0)
- n = 2, k = 9, alice_turn = False

Turn 2 (Bob):
- Can remove 9 stones? No (2 - 9 = -7 < 0)
- Exit loop

alice_turn = False → Bob cannot move → Alice wins → return True
```

**Example Walkthrough (n = 1):**
```
Initial: n = 1, k = 10, alice_turn = True

Turn 1 (Alice):
- Can remove 10 stones? No (1 - 10 = -9 < 0)
- Exit loop immediately

alice_turn = True → Alice cannot move → Bob wins → return False
```

### Complexity Analysis

- **Time Complexity**: O(1) - The maximum number of turns is 10 (removing 10, 9, 8, ..., 1), which is constant
- **Space Complexity**: O(1) - Only using a few variables

### Alternative Approach: Mathematical Formula

Since the pattern is deterministic, we could potentially derive a mathematical formula based on the sum of the arithmetic sequence, but the simulation approach is more intuitive and still runs in constant time given the constraint (n <= 50).

# Tags

Game Theory, Simulation

