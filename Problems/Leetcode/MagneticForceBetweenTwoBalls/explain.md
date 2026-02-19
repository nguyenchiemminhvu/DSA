## Problem

https://leetcode.com/problems/magnetic-force-between-two-balls/description/

```
In the universe Earth C-137, Rick discovered a special form of magnetic force between 
two balls if they are put in his new invented basket. Rick has n empty baskets, the 
ith basket is at position[i], Morty has m balls and needs to distribute the balls 
into the baskets such that the minimum magnetic force between any two balls is maximum.

Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

Given the integer array position and the integer m. Return the required force.

Example 1:
Input: position = [1,2,3,4,7], m = 3
Output: 3
Explanation: Distributing the 3 balls into baskets 1, 4 and 7 will make the magnetic 
force between ball pairs [3, 3, 6]. The minimum magnetic force is 3. We cannot achieve 
a larger minimum magnetic force than 3.

Example 2:
Input: position = [5,4,3,2,1,1000000000], m = 2
Output: 999999999
Explanation: We can use baskets 1 and 1000000000.

Constraints:
- n == position.length
- 2 <= n <= 10^5
- 1 <= position[i] <= 10^9
- All integers in position are distinct
- 2 <= m <= position.length
```

## Observations

1. **Maximize the minimum** - This is a classic optimization problem where we want to maximize the minimum distance. This pattern strongly suggests using binary search on the answer.

2. **Greedy placement check** - For a given minimum distance `d`, we can check if it's possible to place all `m` balls by greedily placing them: place the first ball at the first position, then place each subsequent ball at the first position that is at least distance `d` away from the previous ball.

3. **Monotonicity** - If we can place `m` balls with minimum distance `d`, then we can also place them with any distance less than `d`. Conversely, if we cannot place `m` balls with distance `d`, we cannot place them with any distance greater than `d`. This monotonic property makes binary search viable.

4. **Search space** - The minimum possible distance is 1, and the maximum possible distance is `max(position) - min(position)` (when we place balls at the two extreme positions).

5. **Sorting is key** - We need to sort positions first to apply the greedy placement strategy from left to right.

## Solution

**Approach: Binary Search on Answer + Greedy Verification**

### Algorithm Steps:

1. **Sort the positions** - This allows us to try placing balls from left to right in order.

2. **Binary search on the answer**:
   - `left = 1` (minimum possible distance)
   - `right = pos[-1] - pos[0]` (maximum possible distance)
   - For each mid value, check if we can place all `m` balls with at least `mid` distance between them

3. **Greedy verification function** `check_possible(dist)`:
   - Start with `prev_pos = -infinity` (or a very small value)
   - Iterate through sorted positions
   - Place a ball whenever the current position is at least `dist` away from the previous ball
   - Count how many balls we successfully placed
   - Return `True` if we placed at least `m` balls, `False` otherwise

4. **Update search range**:
   - If `check_possible(mid)` returns `True`: we can achieve distance `mid`, so try a larger distance → `left = mid + 1`, and save `mid` as a candidate answer
   - Otherwise: distance `mid` is too large → `right = mid - 1`

### Time Complexity:
- Sorting: O(n log n)
- Binary search: O(log(max_distance)) iterations
- Each check: O(n)
- **Total: O(n log n + n log(max_distance))**

### Space Complexity:
- O(1) if we don't count the sorting space
- O(n) or O(log n) depending on the sorting algorithm used

### Example Walkthrough:

Input: `position = [1,2,3,4,7], m = 3`

1. After sorting: `[1,2,3,4,7]`
2. Search range: `left=1, right=6`
3. Binary search iterations:
   - `mid=3`: Can we place 3 balls with distance ≥3?
     - Place at pos=1, next at pos=4 (1+3≤4), next at pos=7 (4+3≤7)
     - Placed 3 balls ✓ → Try larger: `left=4, res=3`
   - `mid=5`: Can we place 3 balls with distance ≥5?
     - Place at pos=1, next at pos=7 (1+5≤7), no more positions
     - Placed 2 balls ✗ → Try smaller: `right=4`
   - `mid=4`: Can we place 3 balls with distance ≥4?
     - Place at pos=1, next at pos=7 (1+4≤7), no more positions  
     - Placed 2 balls ✗ → Try smaller: `right=3`
   - `left > right` → Stop
4. Return `res = 3`

### Code Explanation:

```python
class Solution:
    def maxDistance(self, pos: List[int], m: int) -> int:
        pos.sort()  # Sort positions for greedy placement
        n = len(pos)

        def check_possible(dist: int) -> bool:
            """Check if we can place m balls with minimum distance 'dist'"""
            i = 0
            prev_pos = float('-inf')  # Previous ball position
            count = m  # Balls remaining to place
            
            while i < n:
                diff = pos[i] - prev_pos
                if diff >= dist:  # Can place a ball here
                    count -= 1
                    prev_pos = pos[i]
                i += 1
            
            return count <= 0  # Successfully placed all balls

        # Binary search on the answer
        left = 1  # Minimum possible distance
        right = pos[-1] - pos[0]  # Maximum possible distance
        res = right
        
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid  # mid is achievable, try larger
                left = mid + 1
            else:
                right = mid - 1  # mid is too large, try smaller
        
        return res
```

### Key Insights:

- **Binary search on answer** is powerful for "maximize minimum" or "minimize maximum" problems
- **Greedy verification** works because if we can place balls with distance `d`, placing them as early as possible leaves more room for subsequent balls
- The problem transforms from "find optimal placement" to "verify if distance d is achievable"

# Tags
`binary-search` `greedy` `array` `sorting` `binary-search-on-answer` `optimization`

