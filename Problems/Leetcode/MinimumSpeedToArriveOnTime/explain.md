## Problem

https://leetcode.com/problems/minimum-speed-to-arrive-on-time/

You are given a floating-point number `hour`, representing the amount of time you have to reach the office. To commute to the office, you must take `n` trains in sequential order. You are also given an integer array `dist` of length `n`, where `dist[i]` describes the distance (in kilometers) of the ith train ride.

Each train can only depart at an integer hour, so you may need to wait in between each train ride.

**Key constraint:** For the last train, you can arrive at any fractional time. For all other trains, you must wait until the next integer hour before departing the next train.

**Return** the minimum positive integer speed (in kilometers per hour) that all the trains must travel at for you to reach the office on time, or -1 if it is impossible.

### Examples

**Example 1:**
```
Input: dist = [1,3,2], hour = 6
Output: 1
Explanation: At speed 1:
- Train 1: 1/1 = 1 hour (arrive at hour 1)
- Depart train 2 at hour 1: 3/1 = 3 hours (arrive at hour 4)
- Depart train 3 at hour 4: 2/1 = 2 hours (arrive at hour 6)
```

**Example 2:**
```
Input: dist = [1,3,2], hour = 2.7
Output: 3
Explanation: At speed 3:
- Train 1: 1/3 ≈ 0.333 hours (arrive at 0.333, wait until hour 1)
- Depart train 2 at hour 1: 3/3 = 1 hour (arrive at hour 2)
- Depart train 3 at hour 2: 2/3 ≈ 0.667 hours (arrive at 2.667)
```

**Example 3:**
```
Input: dist = [1,3,2], hour = 1.9
Output: -1
Explanation: Impossible because the earliest train 3 can depart is at hour 2
```

## Observations

1. **Time Calculation Difference for Last Train:**
   - For trains 0 to n-2: Time taken = `ceil(dist[i] / speed)` hours (must round up to next integer for next train departure)
   - For the last train: Time taken = `dist[n-1] / speed` (can be fractional)

2. **Ceiling Division Without Floating Point:**
   - To avoid floating-point precision issues: `ceil(a / b) = (a + b - 1) // b` (integer division)
   - This prevents rounding errors when comparing with `hour`

3. **Binary Search Range:**
   - Minimum possible speed: 1 km/h
   - Maximum reasonable speed: Up to 10^7 (guaranteed answer won't exceed this)
   - If no valid speed exists, return -1

4. **Monotonic Property:**
   - As speed increases, total time decreases
   - This monotonic property makes binary search applicable

5. **Edge Cases:**
   - If even at maximum speed it's impossible, return -1
   - The last train calculation is critical (fractional time allowed)

## Solution

### Approach: Binary Search with Greedy Validation

The key insight is that we need to **find the minimum speed** where total time ≤ hour. Since time decreases monotonically with speed, we can use binary search.

**Algorithm:**

1. **Binary Search on Speed:**
   - Search range: [1, 10^7]
   - For each candidate speed, check if it's feasible using `check_possible()`

2. **Feasibility Check (`check_possible`):**
   - For first n-1 trains: Add `ceil(dist[i] / speed)` to total time
   - For last train: Add `dist[n-1] / speed` (fractional)
   - Return whether total time ≤ hour

3. **Answer Tracking:**
   - When a valid speed is found, record it and search for smaller speeds (right = mid - 1)
   - If no valid speed exists after search completes, return -1

### Code Explanation

```python
def minSpeedOnTime(self, dist: List[int], hour: float) -> int:
    n = len(dist)

    def check_possible(speed: int) -> bool:
        h = 0
        # For all trains except the last: use ceiling division
        for i in range(n - 1):
            d = dist[i]
            # ceil(d / speed) = (d + speed - 1) // speed
            h += (d + speed - 1) // speed
        # For the last train: allow fractional time
        h += dist[-1] / speed
        return h <= hour

    left, right = 1, 10**9
    res = right  # Initialize to impossible value
    
    # Binary search for minimum speed
    while left <= right:
        mid = left + (right - left) // 2
        if check_possible(mid):
            # Speed works, try to find smaller speed
            res = mid
            right = mid - 1
        else:
            # Speed doesn't work, need faster speed
            left = mid + 1
    
    return -1 if res == 10**9 else int(res)
```

### Complexity Analysis

- **Time Complexity:** O(n log(10^7)) = O(n × 23)
  - Binary search: log(10^7) ≈ 23 iterations
  - Each check_possible call: O(n) to compute total time
  - Overall: O(23n) ≈ O(n)

- **Space Complexity:** O(1)
  - Only using a few variables for computation

### Key Points

- **Ceiling without float errors:** Using `(d + speed - 1) // speed` ensures integer arithmetic
- **Last train handling:** The crucial difference is dist[-1] / speed is NOT rounded up
- **Binary search correctness:** The monotonic property guarantees we find the minimum valid speed
- **Edge case:** If even at speed 10^7 it fails, return -1

# Tags
#binary-search #optimization

