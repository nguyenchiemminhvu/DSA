## Problem

https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/

```
In a mystic dungeon, n magicians are standing in a line. Each magician has an attribute that gives you energy. Some magicians can give you negative energy, which means taking energy from you.

You have been cursed in such a way that after absorbing energy from magician i, you will be instantly transported to magician (i + k). This process will be repeated until you reach the magician where (i + k) does not exist.

In other words, you will choose a starting point and then teleport with k jumps until you reach the end of the magicians' sequence, absorbing all the energy during the journey.

You are given an array energy and an integer k. Return the maximum possible energy you can gain.

Note that when you are reach a magician, you must take energy from them, whether it is negative or positive energy.

Example 1:

Input: energy = [5,2,-10,-5,1], k = 3

Output: 3

Explanation: We can gain a total energy of 3 by starting from magician 1 absorbing 2 + 1 = 3.

Example 2:

Input: energy = [-2,-3,-1], k = 2

Output: -1

Explanation: We can gain a total energy of -1 by starting from magician 2.

Constraints:

1 <= energy.length <= 105
-1000 <= energy[i] <= 1000
1 <= k <= energy.length - 1
```

## Observations

1. **Movement Pattern**: We can only move from position `i` to position `i + k`, creating distinct chains of positions.

2. **Chain Structure**: Starting positions `0, 1, 2, ..., k-1` create separate chains that never intersect:
   - Chain 0: `0 → k → 2k → 3k → ...`
   - Chain 1: `1 → 1+k → 1+2k → 1+3k → ...`
   - Chain j: `j → j+k → j+2k → j+3k → ...`

3. **Key Insight**: We can start from any position in the array, not just position 0. The goal is to find the starting position that gives us the maximum total energy.

4. **Dynamic Programming Opportunity**: For any position `i`, if we know the maximum energy we can get starting from position `i+k`, we can calculate the maximum energy starting from position `i` as `energy[i] + maxEnergyFrom(i+k)`.

5. **Backwards Calculation**: Since each position depends on the position `k` steps ahead, we should calculate from right to left (backwards) to ensure we have the required information when we need it.

## Solution

**Algorithm**: Dynamic Programming with In-place Optimization

**Strategy**: 
- Transform the `energy` array so that `energy[i]` represents the maximum energy we can gain starting from position `i`
- Work backwards from the end of the array to ensure we have computed values for positions we depend on
- Use the recurrence relation: `energy[i] = energy[i] + energy[i+k]` (if `i+k` exists)

**Step-by-step Process**:

1. **Iterate backwards** from position `n-k-1` to `0`:
   - We start from `n-k-1` because positions `n-k` to `n-1` are terminal positions (cannot jump further)
   - For each position `i`, add `energy[i+k]` to `energy[i]`
   - This gives us the maximum energy obtainable starting from position `i`

2. **Find the maximum** among all possible starting positions (entire transformed array)

**Example Walkthrough** (`energy = [5,2,-10,-5,1], k = 3`):

Initial: `[5, 2, -10, -5, 1]`

- `i = 1`: `energy[1] += energy[4]` → `[5, 3, -10, -5, 1]`
- `i = 0`: `energy[0] += energy[3]` → `[0, 3, -10, -5, 1]`

Final array: `[0, 3, -10, -5, 1]`
Maximum: `3` (starting from position 1: 2 + 1 = 3)

**Time Complexity**: `O(n)` - single pass through the array
**Space Complexity**: `O(1)` - in-place modification of the input array

## Tags

array