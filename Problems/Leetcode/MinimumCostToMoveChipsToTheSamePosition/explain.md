## Problem

https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/description/

```
We have n chips, where the position of the ith chip is position[i].

We need to move all the chips to the same position. In one step, we can change the position of the ith chip from position[i] to:

position[i] + 2 or position[i] - 2 with cost = 0.
position[i] + 1 or position[i] - 1 with cost = 1.
Return the minimum cost needed to move all the chips to the same position.

Example 1:

Input: position = [1,2,3]
Output: 1
Explanation: First step: Move the chip at position 3 to position 1 with cost = 0.
Second step: Move the chip at position 2 to position 1 with cost = 1.
Total cost is 1.

Example 2:

Input: position = [2,2,2,3,3]
Output: 2
Explanation: We can move the two chips at position  3 to position 2. Each move has cost = 1. The total cost = 2.

Example 3:

Input: position = [1,1000000000]
Output: 1

Constraints:

1 <= position.length <= 100
1 <= position[i] <= 10^9
```

## Observations

1. **Cost Analysis**: 
   - Moving by 2 positions (left or right) costs 0
   - Moving by 1 position (left or right) costs 1

2. **Parity Insight**: 
   - Moving by 2 positions preserves parity (even stays even, odd stays odd)
   - Moving by 1 position changes parity (even becomes odd, odd becomes even)

3. **Key Realization**:
   - All chips at even positions can be moved to any even position with cost 0
   - All chips at odd positions can be moved to any odd position with cost 0
   - To move a chip from even to odd position (or vice versa) costs exactly 1

4. **Optimal Strategy**:
   - Count chips at even positions vs odd positions
   - The minimum cost is moving all chips from the smaller group to the larger group
   - Each chip in the smaller group needs exactly 1 move to change parity

## Solution

```python
class Solution:
    def minCostToMoveChips(self, position: List[int]) -> int:
        prefix = [0] * 2
        for pos in position:
            prefix[pos & 1] += 1
        return min(prefix)
```

**Algorithm Explanation**:

1. **Count by Parity**: Use `prefix[pos & 1]` to count chips at even (index 0) and odd (index 1) positions
   - `pos & 1` gives 0 for even numbers, 1 for odd numbers (bitwise AND with 1)

2. **Find Minimum**: Return the smaller count between even and odd positioned chips
   - This represents the minimum number of chips we need to move to achieve same parity

**Time Complexity**: O(n) - single pass through all positions
**Space Complexity**: O(1) - only using constant extra space (array of size 2)

**Example Walkthrough**:
- Input: `[1,2,3]`
- Even positions (2): 1 chip
- Odd positions (1,3): 2 chips  
- Move 1 chip from even to odd positions → Cost = 1

- Input: `[2,2,2,3,3]`
- Even positions (2,2,2): 3 chips
- Odd positions (3,3): 2 chips
- Move 2 chips from odd to even positions → Cost = 2

# Tags

Array, Math, Bit Manipulation, Greedy

