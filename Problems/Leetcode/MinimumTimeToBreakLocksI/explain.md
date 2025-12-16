## Problem

https://leetcode.com/problems/minimum-time-to-break-locks-i/description/

Bob is stuck in a dungeon and must break n locks, each requiring some amount of energy to break. The required energy for each lock is stored in an array called `strength` where `strength[i]` indicates the energy needed to break the ith lock.

To break a lock, Bob uses a sword with the following characteristics:
- The initial energy of the sword is 0.
- The initial factor x by which the energy of the sword increases is 1.
- Every minute, the energy of the sword increases by the current factor x.
- To break the ith lock, the energy of the sword must reach at least `strength[i]`.
- After breaking a lock, the energy of the sword resets to 0, and the factor x increases by a given value k.

Your task is to determine the minimum time in minutes required for Bob to break all n locks and escape the dungeon.

**Example 1:**
```
Input: strength = [3,4,1], k = 1
Output: 4
Explanation:
Time    Energy    x    Action           Updated x
0       0         1    Nothing          1
1       1         1    Break 3rd Lock   2
2       2         2    Nothing          2
3       4         2    Break 2nd Lock   3
4       3         3    Break 1st Lock   3
```

**Example 2:**
```
Input: strength = [2,5,4], k = 2
Output: 5
Explanation:
Time    Energy    x    Action           Updated x
0       0         1    Nothing          1
1       1         1    Nothing          1
2       2         1    Break 1st Lock   3
3       3         3    Nothing          3
4       6         3    Break 2nd Lock   5
5       5         5    Break 3rd Lock   7
```

**Constraints:**
- n == strength.length
- 1 <= n <= 8
- 1 <= k <= 10
- 1 <= strength[i] <= 10^6

## Observations

1. **Order Matters**: The order in which we break locks significantly affects the total time because:
   - Each lock broken increases the factor x by k
   - Higher x means faster energy accumulation for subsequent locks
   - Breaking easier locks first might not always be optimal

2. **Small Input Size**: With n <= 8, we have at most 8! = 40,320 permutations, making brute force feasible.

3. **Time Calculation**: For a lock with strength S and current factor x:
   - Energy accumulates at rate x per minute
   - Time needed = ⌈S / x⌉ = (S + x - 1) / x (using integer division)
   - This can be computed as: `S // x + (1 if S % x > 0 else 0)`

4. **Greedy Doesn't Work**: Simply sorting by strength (ascending or descending) doesn't guarantee the optimal solution because the increasing factor x creates complex trade-offs.

5. **State After Each Lock**:
   - Energy resets to 0
   - Factor increases: x_new = x_old + k
   - This creates a dependency chain where earlier choices affect later efficiency

## Solution

### Approach: Brute Force with Permutations

Since n is small (max 8), we can try all possible orders of breaking locks and find the minimum time.

```python
from itertools import permutations

class Solution:
    def findMinimumTime(self, nums: List[int], k: int) -> int:
        n = len(nums)
        res = float('inf')
        perms = permutations(nums)
        
        for arr in perms:
            times = 0
            x = 1  # Initial factor
            
            for val in arr:
                # Calculate time to break this lock
                # Time = ceiling(val / x)
                times += val // x
                if val % x > 0:
                    times += 1
                
                # After breaking, factor increases
                x += k
            
            res = min(res, times)
        
        return res
```

### Explanation:

1. **Generate All Permutations**: Use `itertools.permutations(nums)` to generate all possible orders of breaking locks.

2. **Simulate Each Order**:
   - Initialize `times = 0` (total time counter)
   - Initialize `x = 1` (current energy factor)
   - For each lock in the current order:
     - Calculate time needed: ⌈strength / x⌉
     - Add to total time
     - Increase factor: x += k

3. **Find Minimum**: Track the minimum time across all permutations.

### Time Complexity: O(n! × n)
- n! permutations to generate and evaluate
- n locks to process per permutation

### Space Complexity: O(n)
- Space for storing one permutation at a time

### Why This Works:

The solution exhaustively tries all possible orderings and picks the best one. While not the most efficient in terms of algorithmic complexity, it's practical given the constraints (n <= 8).

**Example Walkthrough** (strength = [3,4,1], k = 1):

For permutation [1, 3, 4]:
- Lock 1: x=1, time = ⌈1/1⌉ = 1, total = 1, x becomes 2
- Lock 3: x=2, time = ⌈3/2⌉ = 2, total = 3, x becomes 3  
- Lock 4: x=3, time = ⌈4/3⌉ = 2, total = 5

For permutation [1, 4, 3]:
- Lock 1: x=1, time = ⌈1/1⌉ = 1, total = 1, x becomes 2
- Lock 4: x=2, time = ⌈4/2⌉ = 2, total = 3, x becomes 3
- Lock 3: x=3, time = ⌈3/3⌉ = 1, total = 4 ✓ (optimal)

# Tags

`Permutation` `Brute Force` `Simulation` `Math`

