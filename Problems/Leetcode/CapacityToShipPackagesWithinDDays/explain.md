## Problem

https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/

A conveyor belt has packages that must be shipped from one port to another within `days` days.

The `ith` package on the conveyor belt has a weight of `weights[i]`. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.

Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within `days` days.

**Constraints:**
- 1 <= days <= weights.length <= 5 * 10^4
- 1 <= weights[i] <= 500

**Example 1:**
```
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15
Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10
```

**Example 2:**
```
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6
Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4
```

## Observations

1. **Constraint on Order**: Packages must be shipped in the order given. We cannot rearrange or split packages.

2. **Search Space Bounds**: 
   - The minimum possible capacity is `max(weights)` - we must be able to ship the heaviest package
   - The maximum capacity needed is `sum(weights)` - ship everything in one day

3. **Monotonic Property**: If we can ship all packages in `days` days with capacity `C`, then we can also do it with any capacity > `C`. This monotonic property makes binary search applicable.

4. **Optimization Goal**: Find the **minimum** capacity that satisfies the constraint (ship within `days` days).

5. **Greedy Simulation**: For a given capacity, we can greedily determine the number of days needed by loading as many packages as possible each day until the capacity is reached.

## Solution

This is a classic **"Binary Search on Answer"** problem. Instead of searching for an element in an array, we search for the answer in a range of possible values.

### Approach:

1. **Binary Search Setup**:
   - `left = 1` (or `max(weights)` for optimization)
   - `right = sum(weights)`
   - Search for the minimum capacity that allows shipping within `days` days

2. **Check Function** (`check_possible`):
   - Given a capacity `cap`, simulate the shipping process greedily
   - Start with day 1 and current load = 0
   - For each package:
     - If package weight > capacity, it's impossible (return False)
     - If adding the package exceeds capacity, move to next day
     - Otherwise, add package to current day's load
   - Return True if total days needed ≤ `days`

3. **Binary Search Logic**:
   - If `check_possible(mid)` returns True:
     - Current capacity works, but we want smaller
     - Save `mid` as potential answer
     - Search left half: `right = mid - 1`
   - Otherwise:
     - Need larger capacity
     - Search right half: `left = mid + 1`

### Time Complexity:
- Binary search: O(log(sum(weights)))
- Each check scans all packages: O(n)
- **Total: O(n × log(sum(weights)))**

### Space Complexity:
- **O(1)** - only using a few variables

### Code Walkthrough:

```python
class Solution:
    def shipWithinDays(self, nums: List[int], days: int) -> int:
        n = len(nums)

        def check_possible(cap: int) -> bool:
            total_day = 1
            cur_load = 0
            for val in nums:
                if cap < val:  # Can't ship this package
                    return False
                if cur_load + val > cap:  # Would exceed capacity
                    total_day += 1  # Start new day
                    cur_load = 0
                cur_load += val  # Add package to current day
            return total_day <= days

        left = 1
        right = sum(nums)
        res = right
        
        while left <= right:
            mid = left + (right - left) // 2
            if check_possible(mid):
                res = mid  # Valid capacity, try to minimize
                right = mid - 1
            else:
                left = mid + 1  # Need larger capacity
        
        return res
```

# Tags
- Binary Search
- Binary Search on Answer
- Array
- Greedy
- Optimization Problem

