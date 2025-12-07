## Problem

https://leetcode.com/problems/maximum-enemy-forts-that-can-be-captured/description/

```
You are given a 0-indexed integer array forts of length n representing the positions of several forts. 
forts[i] can be -1, 0, or 1 where:
- -1 represents there is no fort at the ith position (empty position)
- 0 indicates there is an enemy fort at the ith position
- 1 indicates the fort at the ith position is under your command

Now you have decided to move your army from one of your forts at position i to an empty position j such that:
- 0 <= i, j <= n - 1
- The army travels over enemy forts only. Formally, for all k where min(i,j) < k < max(i,j), forts[k] == 0.
- While moving the army, all the enemy forts that come in the way are captured.

Return the maximum number of enemy forts that can be captured. In case it is impossible to move your army, 
or you do not have any fort under your command, return 0.

Example 1:
Input: forts = [1,0,0,-1,0,0,0,0,1]
Output: 4
Explanation:
- Moving the army from position 0 to position 3 captures 2 enemy forts, at 1 and 2.
- Moving the army from position 8 to position 3 captures 4 enemy forts.
Since 4 is the maximum number of enemy forts that can be captured, we return 4.

Example 2:
Input: forts = [0,0,1,-1]
Output: 0
Explanation: Since no enemy fort can be captured, 0 is returned.

Constraints:
- 1 <= forts.length <= 1000
- -1 <= forts[i] <= 1
```

## Observations

1. **Valid Move Requirements**: To capture enemy forts, we must move from a position with value `1` (our fort) to a position with value `-1` (empty position), and all positions in between must be `0` (enemy forts).

2. **Pattern Recognition**: We're looking for a pattern like `1 -> 0* -> -1` or `-1 -> 0* -> 1`, where `0*` represents one or more consecutive enemy forts.

3. **Bidirectional Search**: Since we can move in either direction (left to right or right to left), we need to check both directions from each of our forts.

4. **Count Enemy Forts**: The number of captures equals the count of consecutive `0`s between a `1` and a `-1`.

5. **Break Conditions**: 
   - If we encounter another `1` before reaching `-1`, the path is invalid
   - If we encounter `-1`, we have a valid path and should record the count

## Solution

### Approach: Bidirectional Scanning from Our Forts

**Algorithm:**
1. First, identify all positions where we have our forts (value = 1)
2. For each fort, scan in both directions:
   - **Left to Right**: Count consecutive `0`s until we hit either `-1` (valid capture) or `1` (invalid)
   - **Right to Left**: Same logic but scanning backwards
3. Keep track of the maximum number of enemy forts captured

**Time Complexity:** O(n²) in worst case where all positions are `1` and we scan the entire array from each
**Space Complexity:** O(n) for storing positions of our forts

**Example Walkthrough** (forts = [1,0,0,-1,0,0,0,0,1]):
- Our forts at positions: [0, 8]
- From position 0 going right: `1 -> 0 -> 0 -> -1` → captures 2 enemy forts
- From position 8 going left: `1 -> 0 -> 0 -> 0 -> 0 -> -1` → captures 4 enemy forts
- Maximum: 4

### Alternative Optimized Approach

We can optimize by scanning the array once and finding valid `1...0*...-1` or `-1...0*...1` patterns:

```python
class Solution:
    def captureForts(self, forts: List[int]) -> int:
        res = 0
        n = len(forts)
        
        for i in range(n):
            if forts[i] == 1 or forts[i] == -1:
                # Look for the opposite marker
                count = 0
                for j in range(i + 1, n):
                    if forts[j] == 0:
                        count += 1
                    elif forts[j] == -forts[i]:  # Found opposite marker
                        res = max(res, count)
                        break
                    else:  # Same marker, stop
                        break
        
        return res
```

**Time Complexity:** O(n²) worst case
**Space Complexity:** O(1)

# Tags
- Array
- Two Pointers
- Simulation

