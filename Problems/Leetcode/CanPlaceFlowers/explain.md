## Problem

https://leetcode.com/problems/can-place-flowers/description/

```
You have a long flowerbed in which some of the plots are planted, and some are not. However, flowers cannot be planted in adjacent plots.

Given an integer array flowerbed containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n, return true if n new flowers can be planted in the flowerbed without violating the no-adjacent-flowers rule and false otherwise.

Example 1:

Input: flowerbed = [1,0,0,0,1], n = 1
Output: true

Example 2:

Input: flowerbed = [1,0,0,0,1], n = 2
Output: false

Constraints:

1 <= flowerbed.length <= 2 * 104
flowerbed[i] is 0 or 1.
There are no two adjacent flowers in flowerbed.
0 <= n <= flowerbed.length
```

## Observations

1. **Greedy Approach**: We can solve this problem greedily by iterating through the flowerbed from left to right and planting flowers whenever possible. This works because planting a flower at the earliest valid position never prevents us from planting more flowers later.

2. **Placement Rule**: A flower can be planted at position `i` if:
   - The current position is empty (`bench[i] == 0`)
   - The left neighbor is either out of bounds OR empty (`i == 0` OR `bench[i-1] == 0`)
   - The right neighbor is either out of bounds OR empty (`i == len(bench)-1` OR `bench[i+1] == 0`)

3. **Edge Cases**:
   - Single element array: Only need to check if it's 0
   - First position (`i == 0`): Only check right neighbor
   - Last position (`i == len(bench)-1`): Only check left neighbor

4. **In-place Modification**: The solution modifies the input array to mark planted positions, which helps prevent planting adjacent flowers in subsequent iterations.

5. **Early Termination Opportunity**: Once `k` becomes 0 or negative, we could return immediately (though this solution waits until the end).

**Time Complexity**: O(n) where n is the length of the flowerbed
- Single pass through the array

**Space Complexity**: O(1)
- Only uses a constant amount of extra space
- Modifies input array in-place

**How It Works**:
1. Traverse the flowerbed array from left to right
2. For each empty position (0), check if both neighbors are safe:
   - If left neighbor exists and has a flower (1), skip this position
   - If right neighbor exists and has a flower (1), skip this position
3. If both checks pass (or neighbors don't exist), plant a flower:
   - Set `bench[i] = 1`
   - Decrement `k`
4. After the loop, check if we planted at least `k` flowers (`k <= 0`)

**Example Walkthrough**:
```
Input: bench = [1,0,0,0,1], k = 1

i=0: bench[0]=1 (skip, already planted)
i=1: bench[1]=0, left=1 (skip, adjacent to flower)
i=2: bench[2]=0, left=0, right=0 → plant! bench=[1,0,1,0,1], k=0
i=3: bench[3]=0, left=1 (skip, adjacent to flower)
i=4: bench[4]=1 (skip, already planted)

Result: k=0 → return True
```

## Tags

array, greedy