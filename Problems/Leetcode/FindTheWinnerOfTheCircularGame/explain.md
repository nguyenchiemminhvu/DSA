## Problem

https://leetcode.com/problems/find-the-winner-of-the-circular-game/description/

```
There are n friends that are playing a game. The friends are sitting in a circle and are numbered from 1 to n in clockwise order. More formally, moving clockwise from the ith friend brings you to the (i+1)th friend for 1 <= i < n, and moving clockwise from the nth friend brings you to the 1st friend.

The rules of the game are as follows:
1. Start at the 1st friend.
2. Count the next k friends in the clockwise direction including the friend you started at. The counting wraps around the circle and may count some friends more than once.
3. The last friend you counted leaves the circle and loses the game.
4. If there is still more than one friend in the circle, go back to step 2 starting from the friend immediately clockwise of the friend who just lost and repeat.
5. Else, the last friend in the circle wins the game.

Given the number of friends, n, and an integer k, return the winner of the game.

Example 1:
Input: n = 5, k = 2
Output: 3
Explanation: Here are the steps of the game:
1) Start at friend 1.
2) Count 2 friends clockwise, which are friends 1 and 2.
3) Friend 2 leaves the circle. Next start is friend 3.
4) Count 2 friends clockwise, which are friends 3 and 4.
5) Friend 4 leaves the circle. Next start is friend 5.
6) Count 2 friends clockwise, which are friends 5 and 1.
7) Friend 1 leaves the circle. Next start is friend 3.
8) Count 2 friends clockwise, which are friends 3 and 5.
9) Friend 5 leaves the circle. Only friend 3 is left, so they are the winner.

Example 2:
Input: n = 6, k = 5
Output: 1
Explanation: The friends leave in this order: 5, 4, 6, 2, 3. The winner is friend 1.

Constraints:
- 1 <= k <= n <= 500
```

## Observations

1. **Classic Josephus Problem**: This is a famous mathematical problem where people stand in a circle and every k-th person is eliminated until only one survives.

2. **Naive Simulation Approach**: 
   - We could simulate the entire process using a list/queue
   - Time: O(n*k), Space: O(n)
   - For each elimination, we need to count k positions

3. **Mathematical Pattern**:
   - The problem has a recursive mathematical solution
   - If we know the winner's position for n-1 people, we can deduce it for n people
   - The key insight is that after each elimination, the circle "rotates" and we can map positions between different sized circles

4. **0-indexed vs 1-indexed**:
   - The mathematical formula works naturally with 0-indexed positions
   - We need to adjust between 0-indexed (math) and 1-indexed (problem) representations

## Solution

### Mathematical Approach (Josephus Problem Formula)

**Key Insight**: This problem can be solved using dynamic programming with a recurrence relation.

**Recurrence Relation**:
- Let $J(n, k)$ be the position (0-indexed) of the winner with n people and elimination count k
- Base case: $J(1, k) = 0$ (with 1 person at position 0, they win)
- Recurrence: $J(n, k) = (J(n-1, k) + k) \mod n$

**Why does this work?**

1. When we have $n$ people numbered $0$ to $n-1$ (0-indexed), after the first elimination:
   - The $k$-th person (at index $(k-1) \mod n$) is removed
   - We have $n-1$ people left
   - The next person becomes the new starting position

2. If we renumber the remaining $n-1$ people starting from 0, there's a mapping between:
   - Position $p$ in the $(n-1)$-person circle
   - Position $(p + k) \mod n$ in the original $n$-person circle

3. By working backwards from $n=1$ to $n=n$, we can track how the winner's position changes as we add people back.

**Implementation Steps**:

```python
class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        # Start with winner position in 0-indexed system
        winner = 0
        
        # Build up from 2 people to n people
        for i in range(2, n + 1):
            # Recurrence: position in i-person circle = 
            # (position in (i-1)-person circle + k) % i
            winner = (winner + k) % i
        
        # Convert from 0-indexed to 1-indexed
        return winner + 1
```

Wait, the provided solution is slightly different. Let me analyze it:

```python
class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        winner = 1  # Start with 1-indexed
        for i in range(2, n + 1):
            winner = (winner + k - 1) % i + 1
        return winner
```

This version works directly with 1-indexed positions:
- It uses the transformation: `(winner + k - 1) % i + 1`
- The `-1` and `+1` handle the conversion between 0-indexed math and 1-indexed positions
- This is equivalent to: convert to 0-indexed, apply formula, convert back to 1-indexed

**Complexity Analysis**:
- **Time Complexity**: $O(n)$ - single loop from 2 to n
- **Space Complexity**: $O(1)$ - only using a single variable

**Step-by-step Example** (n=5, k=2):
```
i=2: winner = (1 + 2 - 1) % 2 + 1 = 2 % 2 + 1 = 0 + 1 = 1
i=3: winner = (1 + 2 - 1) % 3 + 1 = 2 % 3 + 1 = 2 + 1 = 3
i=4: winner = (3 + 2 - 1) % 4 + 1 = 4 % 4 + 1 = 0 + 1 = 1
i=5: winner = (1 + 2 - 1) % 5 + 1 = 2 % 5 + 1 = 2 + 1 = 3
Result: 3 ✓
```

### Alternative: Simulation Approach

```python
class Solution:
    def findTheWinner(self, n: int, k: int) -> int:
        friends = list(range(1, n + 1))
        idx = 0
        
        while len(friends) > 1:
            # Find the friend to eliminate
            idx = (idx + k - 1) % len(friends)
            friends.pop(idx)
            # idx is now pointing to the next friend
            # (no need to increment since we removed an element)
        
        return friends[0]
```

**Complexity**: Time O(n²) in worst case (due to list.pop), Space O(n)

# Tags

`Math` `Recursion` `Dynamic Programming` `Josephus Problem` `Simulation` `Queue`

