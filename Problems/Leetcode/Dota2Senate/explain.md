## Problem

https://leetcode.com/problems/dota2-senate/description/

In the world of Dota2, there are two parties: the **Radiant** and the **Dire**.

The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:

1. **Ban one senator's right**: A senator can make another senator lose all his rights in this and all the following rounds.
2. **Announce the victory**: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.

Given a string `senate` representing each senator's party belonging. The character `'R'` and `'D'` represent the Radiant party and the Dire party. Then if there are n senators, the size of the given string will be n.

The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.

Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game. The output should be `"Radiant"` or `"Dire"`.

**Example 1:**
```
Input: senate = "RD"
Output: "Radiant"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
```

**Example 2:**
```
Input: senate = "RDD"
Output: "Dire"
Explanation: 
The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
And the second senator can't exercise any rights anymore since his right has been banned. 
And the third senator comes from Dire and he can ban the first senator's right in round 1. 
And in round 2, the third senator can just announce the victory since he is the only guy in the senate who can vote.
```

**Constraints:**
- `n == senate.length`
- `1 <= n <= 10^4`
- `senate[i]` is either `'R'` or `'D'`.

## Observations

1. **Greedy Strategy**: Each senator should ban the nearest opponent senator who comes after them (or wraps around). This is the optimal strategy because:
   - Banning the closest opponent maximizes the chance of your party members getting more turns
   - Waiting to ban a senator further away allows opponents to ban your party members first

2. **Round-based Process**: The voting continues in rounds. After all senators have their turn, a new round begins with the senators who still have rights.

3. **Order Matters**: Senators act in the order they appear in the string. A senator at position `i` will always act before a senator at position `j` where `i < j` (in the same round).

4. **Victory Condition**: When all remaining senators are from the same party, that party wins.

5. **Key Insight**: We need to track the indices/positions of senators because the order determines who acts first. A senator with a smaller index in the current round will ban an opponent before that opponent can act.

## Solution

### Approach: Two Queues (Greedy + Simulation)

**Algorithm:**
1. Create two queues: one for Radiant senators and one for Dire senators
2. Store the indices (positions) of each senator in their respective queue
3. Simulate the voting rounds:
   - In each iteration, take the first senator from each queue
   - The senator with the smaller index acts first and bans the other
   - The winning senator goes to the end of the queue with an updated index (`original_index + n`)
   - The updated index ensures they maintain their position for the next round
4. Continue until one queue is empty
5. Return the party of the non-empty queue

**Why add `n` to the index?**
When a senator survives a confrontation, they move to the next round. By adding `n` (the total number of senators) to their index, we ensure they maintain their relative position in subsequent rounds. For example:
- Round 1: indices are 0, 1, 2, ..., n-1
- Round 2: surviving senators get indices n, n+1, n+2, ... (representing their new positions)

**Example Walkthrough (`senate = "RDD"`):**

Initial state:
- Radiant queue: [0]
- Dire queue: [1, 2]

Round 1:
- Compare R(0) vs D(1): R has smaller index, so R bans D(1)
- R(0) moves to next round with index 0+3=3
- Radiant queue: [3]
- Dire queue: [2]

Round 2:
- Compare R(3) vs D(2): D has smaller index, so D bans R(3)
- D(2) moves to next round with index 2+3=5
- Radiant queue: []
- Dire queue: [5]

Result: Dire wins

**Code:**
```python
from collections import deque

class Solution:
    def predictPartyVictory(self, senate: str) -> str:
        n = len(senate)
        radiant = deque()
        dire = deque()

        # Store indices
        for i, s in enumerate(senate):
            if s == 'R':
                radiant.append(i)
            else:
                dire.append(i)

        # Simulate rounds
        while radiant and dire:
            r = radiant.popleft()
            d = dire.popleft()

            if r < d:
                # Radiant bans Dire
                radiant.append(r + n)
            else:
                # Dire bans Radiant
                dire.append(d + n)

        return "Radiant" if radiant else "Dire"
```

**Complexity Analysis:**
- **Time Complexity**: $O(n)$ where n is the length of the senate string. In the worst case, we process each senator once per round, and there can be at most n rounds.
- **Space Complexity**: $O(n)$ for the two queues storing indices.

# Tags
- Queue
- Greedy
- Simulation
- String

