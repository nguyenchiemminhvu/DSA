## Problem

https://leetcode.com/problems/distance-between-bus-stops/

```
A bus has n stops numbered from 0 to n - 1 that form a circle. We know the distance between all pairs of neighboring stops where distance[i] is the distance between the stops number i and (i + 1) % n.

The bus goes along both directions i.e. clockwise and counterclockwise.

Return the shortest distance between the given start and destination stops.

Example 1:

Input: distance = [1,2,3,4], start = 0, destination = 1
Output: 1
Explanation: Distance between 0 and 1 is 1 or 9, minimum is 1.

Example 2:

Input: distance = [1,2,3,4], start = 0, destination = 2
Output: 3
Explanation: Distance between 0 and 2 is 3 or 7, minimum is 3.

Example 3:

Input: distance = [1,2,3,4], start = 0, destination = 3
Output: 4
Explanation: Distance between 0 and 3 is 6 or 4, minimum is 4.

Constraints:

1 <= n <= 10^4
distance.length == n
0 <= start, destination < n
0 <= distance[i] <= 10^4
```

## Observations

1. **Circular Bus Route**: The bus stops form a circle, meaning from the last stop (n-1), the bus can go to stop 0.

2. **Two Possible Paths**: Between any two stops, there are exactly two possible paths:
   - **Clockwise**: Moving in the forward direction (increasing indices)
   - **Counterclockwise**: Moving in the backward direction (decreasing indices)

3. **Distance Array**: `distance[i]` represents the distance from stop `i` to stop `(i+1) % n`. This is crucial - the distance is always from a stop to its next clockwise neighbor.

4. **Key Insight**: Since it's a circle, the sum of all distances in the array equals the total circumference. If we know one path's distance, the other path's distance = total_distance - known_path_distance.

5. **Edge Cases**: 
   - If `start == destination`, distance should be 0 (though not explicitly handled in constraints)
   - The algorithm works regardless of whether `start < destination` or `start > destination`

## Solution

### Approach: Two-Path Calculation

The solution calculates both possible paths and returns the minimum distance.

**Algorithm:**
1. **Option 1 (Clockwise)**: Start from `start` and move forward until reaching `destination`
   - Add `distance[i]` at each step where `i` is the current position
   - Use modular arithmetic `(i + 1) % n` to handle wraparound

2. **Option 2 (Counterclockwise)**: Start from `start` and move backward until reaching `destination`
   - At each step, move to previous position: `prev = ((i - 1) + n) % n`
   - Add `distance[prev]` because `distance[prev]` is the distance from `prev` to current position `i`

3. **Return**: `min(opt1, opt2)`

**Time Complexity**: O(n) - In worst case, we might traverse the entire circle
**Space Complexity**: O(1) - Only using constant extra space

### Example Walkthrough:
```
distance = [1,2,3,4], start = 0, destination = 2

Option 1 (Clockwise): 0 → 1 → 2
- From 0: add distance[0] = 1
- From 1: add distance[1] = 2
- Total: 1 + 2 = 3

Option 2 (Counterclockwise): 0 → 3 → 2
- From 0 to 3: add distance[3] = 4 (distance from 3 to 0)
- From 3 to 2: add distance[2] = 3 (distance from 2 to 3)
- Total: 4 + 3 = 7

Answer: min(3, 7) = 3
```

**Alternative Optimization:**
Since the paths are complementary in a circle, we could calculate just one path and use:
`other_path = total_sum - calculated_path`

# Tags
- Array
- Simulation
- Circular Array
- Two Pointers

