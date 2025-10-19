## Problem

https://leetcode.com/problems/maximum-number-of-coins-you-can-get/description/

```
There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:

In each step, you will choose any 3 piles of coins (not necessarily consecutive).
Of your choice, Alice will pick the pile with the maximum number of coins.
You will pick the next pile with the maximum number of coins.
Your friend Bob will pick the last pile.
Repeat until there are no more piles of coins.
Given an array of integers piles where piles[i] is the number of coins in the ith pile.

Return the maximum number of coins that you can have.

Example 1:

Input: piles = [2,4,1,2,7,8]
Output: 9
Explanation: Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile with 2 coins and Bob the last one.
The maximum number of coins which you can have are: 7 + 2 = 9.
On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6 coins which is not optimal.

Example 2:

Input: piles = [2,4,5]
Output: 4

Example 3:

Input: piles = [9,8,7,6,5,1,2,3,4]
Output: 18

Constraints:

3 <= piles.length <= 105
piles.length % 3 == 0
1 <= piles[i] <= 104
```

## Observations

1. **Game Theory Context**: This is a game theory problem where three players (Alice, You, Bob) pick piles in a specific order: Alice gets the maximum, you get the second maximum, Bob gets the minimum from each chosen triplet.

2. **Key Insight**: To maximize your coins, you want to be in situations where:
   - Alice takes the absolute largest pile (which she will anyway)
   - You get the second-largest pile possible
   - Bob gets stuck with the smallest piles

3. **Optimal Strategy**: 
   - Sort the piles in descending order
   - Always group the largest remaining pile with the second-largest and the smallest remaining pile
   - This ensures you consistently get the second-best pile while Bob gets the worst

4. **Pattern Recognition**: 
   - After sorting: [largest, 2nd largest, 3rd largest, ..., 3rd smallest, 2nd smallest, smallest]
   - Optimal groupings: (piles[0], piles[1], piles[n-1]), (piles[2], piles[3], piles[n-2]), ...
   - You always get: piles[1], piles[3], piles[5], ... (every second element starting from index 1)

5. **Two-Pointer Technique**: 
   - Left pointer advances by 2 each iteration (skipping Alice's pile)
   - Right pointer retreats by 1 each iteration (giving Bob the smallest available pile)
   - This naturally creates the optimal triplets

## Solution

1. **Sort Descending**: `piles.sort(reverse=True)` arranges piles from largest to smallest
2. **Initialize Pointers**: `left = 0`, `right = len(piles) - 1`
3. **Greedy Selection**: In each iteration:
   - Alice automatically gets `piles[left]` (the largest remaining)
   - You get `piles[left + 1]` (the second largest remaining)
   - Bob gets `piles[right]` (the smallest remaining)
4. **Update Pointers**: 
   - `left += 2` (skip past the two piles Alice and you took)
   - `right -= 1` (Bob took the rightmost pile)
5. **Accumulate Result**: Add your pile value to the result

**Example Walkthrough** with `piles = [2,4,1,2,7,8]`:

1. After sorting: `[8,7,4,2,2,1]`
2. Iteration 1: Alice(8), You(7), Bob(1) → result = 7
3. Iteration 2: Alice(4), You(2), Bob(2) → result = 7 + 2 = 9

**Time Complexity**: O(n log n) - dominated by sorting
**Space Complexity**: O(1) - only using constant extra space (excluding input array)

## Tags

array, greedy, two pointers