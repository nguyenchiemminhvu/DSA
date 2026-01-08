## Problem

https://leetcode.com/problems/stone-game-vi/description/

Alice and Bob take turns playing a game, with Alice starting first.

There are `n` stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.

You are given two integer arrays of length `n`, `aliceValues` and `bobValues`. Each `aliceValues[i]` and `bobValues[i]` represents how Alice and Bob, respectively, value the ith stone.

The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally. Both players know the other's values.

Determine the result of the game, and:
- If Alice wins, return `1`.
- If Bob wins, return `-1`.
- If the game results in a draw, return `0`.

**Example 1:**
```
Input: aliceValues = [1,3], bobValues = [2,1]
Output: 1
Explanation: If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
Bob can only choose stone 0, and will only receive 2 points. Alice wins.
```

**Example 2:**
```
Input: aliceValues = [1,2], bobValues = [3,1]
Output: 0
Explanation: If Alice takes stone 0, and Bob takes stone 1, they will both have 1 point. Draw.
```

**Example 3:**
```
Input: aliceValues = [2,4,3], bobValues = [1,6,7]
Output: -1
Explanation: Regardless of how Alice plays, Bob will be able to have more points than Alice.
```

**Constraints:**
- `n == aliceValues.length == bobValues.length`
- `1 <= n <= 10^5`
- `1 <= aliceValues[i], bobValues[i] <= 100`

## Observations

1. **Both players play optimally** - This is crucial. Each player will make the best possible move at each turn.

2. **Opportunity cost matters** - When Alice picks a stone with value `aliceValues[i]`, she:
   - Gains `aliceValues[i]` points
   - Prevents Bob from gaining `bobValues[i]` points
   - The total swing in the game is `aliceValues[i] + bobValues[i]`

3. **Combined value is the key metric** - Similarly, when Bob picks a stone with value `bobValues[i]`, he:
   - Gains `bobValues[i]` points
   - Prevents Alice from gaining `aliceValues[i]` points
   - The total swing is also `aliceValues[i] + bobValues[i]`

4. **Greedy approach works** - Both players should prioritize stones with the highest combined value `aliceValues[i] + bobValues[i]` because:
   - If you take it, you get your value AND deny the opponent their value
   - If opponent takes it, they get their value AND deny you your value
   - The difference between these two outcomes is `aliceValues[i] + bobValues[i]`

5. **Turn order** - Alice goes first (turn 0, 2, 4, ...), Bob goes second (turn 1, 3, 5, ...)

## Solution

### Approach: Greedy with Max Heap

**Key Insight:** Both players should pick stones in descending order of `aliceValues[i] + bobValues[i]`.

**Why this works:**
- Consider stone i with combined value `C_i = aliceValues[i] + bobValues[i]`
- If Alice takes stone i: Alice gets `+aliceValues[i]`, Bob gets `+0`
- If Bob takes stone i: Bob gets `+bobValues[i]`, Alice gets `+0`
- The difference in outcomes for Alice is: `aliceValues[i] - (-bobValues[i]) = aliceValues[i] + bobValues[i]`
- So taking a stone with high combined value has the maximum impact on the final score difference

**Algorithm:**
1. Create a max heap (priority queue) of all stones sorted by `aliceValues[i] + bobValues[i]` in descending order
2. Simulate the game: alternately let Alice and Bob pick the top stone from the heap
3. Track scores for both players
4. Compare final scores and return the result

**Implementation:**
```python
import heapq

class Solution:
    def stoneGameVI(self, a: List[int], b: List[int]) -> int:
        n = len(a)
        pq = []
        
        # Build max heap based on combined value
        # Use negative values for max heap behavior
        for i in range(n):
            heapq.heappush(pq, (-(a[i] + b[i]), (a[i], b[i])))
        
        turn = 0  # 0 for Alice, 1 for Bob
        table = [0, 0]  # [Alice's score, Bob's score]
        
        # Simulate the game
        while pq:
            _, vals = heapq.heappop(pq)
            table[turn] += vals[turn]  # Add respective player's value
            turn = (turn + 1) % 2  # Switch turns
        
        # Determine winner
        if table[0] == table[1]:
            return 0  # Draw
        return 1 if table[0] > table[1] else -1  # 1 for Alice, -1 for Bob
```

**Complexity Analysis:**
- **Time Complexity:** O(n log n)
  - Building the heap: O(n log n)
  - Extracting all elements: O(n log n)
- **Space Complexity:** O(n)
  - Heap storage: O(n)

**Example Walkthrough (Example 3):**
```
aliceValues = [2,4,3], bobValues = [1,6,7]

Combined values:
Stone 0: 2 + 1 = 3
Stone 1: 4 + 6 = 10
Stone 2: 3 + 7 = 10

Sorted by combined value (stone index, combined value):
[(1, 10), (2, 10), (0, 3)]

Game simulation:
Turn 0 (Alice): Takes stone 1, Alice gets 4 points (total: 4)
Turn 1 (Bob): Takes stone 2, Bob gets 7 points (total: 7)
Turn 2 (Alice): Takes stone 0, Alice gets 2 points (total: 6)

Final: Alice = 6, Bob = 7 → Bob wins → return -1
```

# Tags

`Greedy` `Heap` `Priority Queue` `Game Theory` `Sorting`

