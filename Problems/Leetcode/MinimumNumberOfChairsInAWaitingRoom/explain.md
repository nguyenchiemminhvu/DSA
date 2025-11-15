## Problem

https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/description/

```
You are given a string s. Simulate events at each second i:

If s[i] == 'E', a person enters the waiting room and takes one of the chairs in it.
If s[i] == 'L', a person leaves the waiting room, freeing up a chair.
Return the minimum number of chairs needed so that a chair is available for every person who enters the waiting room given that it is initially empty.


Example 1:

Input: s = "EEEEEEE"

Output: 7

Explanation:

After each second, a person enters the waiting room and no person leaves it. Therefore, a minimum of 7 chairs is needed.

Example 2:

Input: s = "ELELEEL"

Output: 2

Explanation:

Let's consider that there are 2 chairs in the waiting room. The table below shows the state of the waiting room at each second.

Second	Event	People in the Waiting Room	Available Chairs
0	Enter	1	1
1	Leave	0	2
2	Enter	1	1
3	Leave	0	2
4	Enter	1	1
5	Enter	2	0
6	Leave	1	1

Example 3:

Input: s = "ELEELEELLL"

Output: 3

Explanation:

Let's consider that there are 3 chairs in the waiting room. The table below shows the state of the waiting room at each second.

Second	Event	People in the Waiting Room	Available Chairs
0	Enter	1	2
1	Leave	0	3
2	Enter	1	2
3	Enter	2	1
4	Leave	1	2
5	Enter	2	1
6	Enter	3	0
7	Leave	2	1
8	Leave	1	2
9	Leave	0	3

Constraints:

1 <= s.length <= 50
s consists only of the letters 'E' and 'L'.
s represents a valid sequence of entries and exits.
```

## Observations

1. **Problem Understanding**: We need to simulate a waiting room where people enter ('E') and leave ('L'). We need to find the minimum number of chairs required so that everyone can always find a seat.

2. **Key Insight**: The minimum number of chairs needed is the maximum number of people present in the room at any given time during the simulation.

3. **Tracking Occupancy**: 
   - When someone enters ('E'), the current occupancy increases by 1
   - When someone leaves ('L'), the current occupancy decreases by 1
   - We need to track the maximum occupancy reached throughout the process

4. **Edge Cases**:
   - All entries followed by all exits: maximum chairs = length of consecutive 'E's
   - Interleaved entries and exits: need to simulate step by step
   - The problem guarantees valid sequences (no leaving when room is empty)

## Solution

1. **Initialize**: `n = 0` (max chairs), `cur = 0` (current occupancy)
2. **Process each character**:
   - **'E' (Enter)**: Increment current count and update maximum
   - **'L' (Leave)**: Decrement current count
3. **Return the maximum**: This represents the peak occupancy

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using two variables

**Example Walkthrough** (`s = "ELELEEL"`):
- E: cur=1, max=1
- L: cur=0, max=1  
- E: cur=1, max=1
- L: cur=0, max=1
- E: cur=1, max=1
- E: cur=2, max=2 ← Peak occupancy
- L: cur=1, max=2

Result: 2 chairs needed

# Tags

- **Simulation**
- **Array/String Processing** 
- **Running Maximum**
- **Greedy Algorithm**
- **Easy Difficulty**

