## Problem

https://leetcode.com/problems/last-stone-weight/

```
You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.

Example 1:

Input: stones = [2,7,4,1,8,1]
Output: 1
Explanation: 
We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1] then,
we combine 2 and 4 to get 2 so the array converts to [2,1,1,1] then,
we combine 2 and 1 to get 1 so the array converts to [1,1,1] then,
we combine 1 and 1 to get 0 so the array converts to [1] then that's the value of the last stone.

Example 2:

Input: stones = [1]
Output: 1

Constraints:

1 <= stones.length <= 30
1 <= stones[i] <= 1000
```

## Observations

1. **Greedy Approach**: We always need to process the two heaviest stones first, which suggests using a max heap data structure.

2. **Heap Operations**: Since Python's `heapq` provides a min heap, we can simulate a max heap by negating all values.

3. **Game Rules**: 
   - If two stones have equal weight (x == y), both are destroyed
   - If different weights (x != y), the lighter one is destroyed and the heavier becomes (y - x)

4. **Edge Cases**:
   - Single stone: return its weight
   - All stones destroyed: return 0
   - Odd number of stones: one will remain

5. **Time Complexity**: O(n log n) where n is the number of stones, due to heap operations.



## Solution

**Approach**: Max Heap with Priority Queue

The solution uses a max heap to efficiently retrieve the two heaviest stones at each step.

**Algorithm**:
1. **Initialize**: Create a max heap by pushing all stone weights as negative values (since Python's heapq is a min heap)
2. **Process**: While there are stones in the heap:
   - Pop the heaviest stone (convert back to positive)
   - If heap is empty, return this stone's weight
   - Pop the second heaviest stone
   - Calculate the difference and push back if > 0
3. **Return**: 0 if no stones remain

**Key Points**:
- Uses negative values to simulate max heap with Python's min heap
- Time: O(n log n), Space: O(n)
- **Bug Fix**: Original code pushes 0 back to heap, should only push positive differences

**Alternative Variable Names**:
- `val` and `valval` could be renamed to `heaviest` and `second_heaviest` for clarity

# Tags

