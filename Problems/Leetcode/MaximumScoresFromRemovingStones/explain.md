## Problem

https://leetcode.com/problems/maximum-score-from-removing-stones/description/

```
You are playing a solitaire game with three piles of stones of sizes a​​​​​​, b,​​​​​​ and c​​​​​​ respectively. Each turn you choose two different non-empty piles, take one stone from each, and add 1 point to your score. The game stops when there are fewer than two non-empty piles (meaning there are no more available moves).

Given three integers a​​​​​, b,​​​​​ and c​​​​​, return the maximum score you can get.

Example 1:

Input: a = 2, b = 4, c = 6
Output: 6
Explanation: The starting state is (2, 4, 6). One optimal set of moves is:
- Take from 1st and 3rd piles, state is now (1, 4, 5)
- Take from 1st and 3rd piles, state is now (0, 4, 4)
- Take from 2nd and 3rd piles, state is now (0, 3, 3)
- Take from 2nd and 3rd piles, state is now (0, 2, 2)
- Take from 2nd and 3rd piles, state is now (0, 1, 1)
- Take from 2nd and 3rd piles, state is now (0, 0, 0)
There are fewer than two non-empty piles, so the game ends. Total: 6 points.

Example 2:

Input: a = 4, b = 4, c = 6
Output: 7
Explanation: The starting state is (4, 4, 6). One optimal set of moves is:
- Take from 1st and 2nd piles, state is now (3, 3, 6)
- Take from 1st and 3rd piles, state is now (2, 3, 5)
- Take from 1st and 3rd piles, state is now (1, 3, 4)
- Take from 1st and 3rd piles, state is now (0, 3, 3)
- Take from 2nd and 3rd piles, state is now (0, 2, 2)
- Take from 2nd and 3rd piles, state is now (0, 1, 1)
- Take from 2nd and 3rd piles, state is now (0, 0, 0)
There are fewer than two non-empty piles, so the game ends. Total: 7 points.

Example 3:

Input: a = 1, b = 8, c = 8
Output: 8
Explanation: One optimal set of moves is to take from the 2nd and 3rd piles for 8 turns until they are empty.
After that, there are fewer than two non-empty piles, so the game ends.

Constraints:

1 <= a, b, c <= 105
```

## Observations

1. **Game Rules**: 
   - We have three piles of stones with sizes `a`, `b`, and `c`
   - Each turn, we must pick two different non-empty piles and remove one stone from each
   - We gain 1 point per turn
   - Game ends when fewer than 2 piles have stones (0 or 1 pile remaining)

2. **Greedy Strategy**:
   - To maximize score, we should always pick stones from the two largest piles
   - This strategy balances the piles and allows us to continue playing as long as possible
   - If we don't follow this strategy, we might exhaust smaller piles too quickly

3. **Mathematical Insight**:
   - Maximum possible score is limited by total stones: `(a + b + c) / 2`
   - However, if one pile is too large compared to others, we might not reach this theoretical maximum
   - Specifically, if the largest pile >= sum of other two piles, then max score = sum of two smaller piles

4. **Heap Usage**:
   - Max heap helps us efficiently get the two largest values at each step
   - Python's `heapq` is a min heap, so we use negative values to simulate max heap
   - We only keep non-zero values in the heap

5. **Termination Condition**:
   - Game ends when heap has fewer than 2 elements (fewer than 2 non-empty piles)

## Solution

The solution uses a **greedy approach with a max heap**:

### Algorithm Steps:
1. **Initialize**: Create a max heap with all three pile sizes (using negative values for min heap simulation)
2. **Main Loop**: While we have at least 2 non-empty piles:
   - Extract the two largest piles from heap
   - Remove one stone from each pile (increment score)
   - Put back any non-empty piles into the heap
3. **Return**: Total score accumulated

### Time Complexity: O(S log 3) where S = total stones
- Each iteration reduces total stones by 2
- Heap operations on at most 3 elements take O(log 3) = O(1)
- Total iterations: O(S)

### Space Complexity: O(1)
- Heap contains at most 3 elements

### Alternative Mathematical Solution:
```python
def maximumScore(self, a: int, b: int, c: int) -> int:
    return min((a + b + c) // 2, a + b + c - max(a, b, c))
```
This O(1) solution uses the insight that the answer is the minimum of:
- Half the total stones (theoretical maximum)
- Total stones minus the largest pile (when largest pile dominates)

## Tags

array, priority queue, max heap, greedy