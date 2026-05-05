## Problem

https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description

## Problem

https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/description

### Problem Statement

There are spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array `points` where `points[i] = [xstart, xend]` denotes a balloon whose horizontal diameter stretches between `xstart` and `xend`. You do not know the exact y-coordinates of the balloons.

Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with `xstart` and `xend` is burst by an arrow shot at x if `xstart <= x <= xend`. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.

**Given the array `points`, return the minimum number of arrows that must be shot to burst all balloons.**

### Examples

**Example 1:**
```
Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
- Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
```

**Example 2:**
```
Input: points = [[1,2],[3,4],[5,6],[7,8]]
Output: 4
Explanation: One arrow needs to be shot for each balloon for a total of 4 arrows.
```

**Example 3:**
```
Input: points = [[1,2],[2,3],[3,4],[4,5]]
Output: 2
Explanation: The balloons can be burst by 2 arrows:
- Shoot an arrow at x = 2, bursting the balloons [1,2] and [2,3].
- Shoot an arrow at x = 4, bursting the balloons [3,4] and [4,5].
```

### Constraints

- 1 <= `points.length` <= 10^5
- `points[i].length` == 2
- -2^31 <= `xstart` < `xend` <= 2^31 - 1

---

## Observations

### Key Insights

1. **Greedy Strategy**: This problem lends itself to a greedy approach. If we can make a locally optimal choice at each step, we can arrive at a globally optimal solution.

2. **Sorting by End Position**: The critical observation is to sort balloons by their **end coordinate** (xend). Why? Because:
   - When we shoot an arrow, we want to maximize the number of balloons it bursts
   - An arrow shot at position x can burst any balloon where `xstart <= x <= xend`
   - To cover the most balloons with one arrow, we should position it as far to the right as possible
   - By processing balloons in order of their end positions, we ensure we always consider the "earliest ending" balloon first

3. **Overlapping Balloons**: Two balloons overlap if one's start is less than or equal to the other's end:
   - Balloon A: `[a_start, a_end]`
   - Balloon B: `[b_start, b_end]`
   - They overlap if: `b_start <= a_end` (when considering B after A in sorted order)

4. **Greedy Shooting Pattern**:
   - Process balloons in order of increasing end position
   - For the first balloon, shoot an arrow at its end position (this maximizes coverage)
   - For subsequent balloons:
     - If the current balloon overlaps with the previously shot arrow's position, it's already burst—skip it
     - Otherwise, shoot a new arrow at this balloon's end position

### Why This Works

The greedy approach is optimal because:
- By always shooting at the rightmost position of the first unshot balloon, we maximize the chance of hitting subsequent balloons
- Balloons sorted by end position ensure we process them in an order that naturally groups overlapping balloons together
- Any balloon that doesn't overlap with our current arrow position cannot possibly overlap with balloons we've already processed (due to the sorted order)

---

## Solution

### Algorithm: Greedy + Sorting

```python
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        # Step 1: Sort balloons by their end position (xend)
        points.sort(key=lambda x: (x[1], x[0]))
        
        n = len(points)
        removed = 0  # Count of balloons burst (not requiring new arrow)
        prev = points[0]  # Track the previous balloon (or last arrow position)
        
        # Step 2: Iterate through remaining balloons
        for i in range(1, n):
            # If current balloon overlaps with previous balloon's end position
            if points[i][0] <= prev[1]:
                # This balloon can be burst by the same arrow
                removed += 1
            else:
                # No overlap, need a new arrow for this balloon
                prev = points[i]
        
        # Step 3: Return total arrows needed
        return n - removed
```

### Detailed Explanation

1. **Sorting** (Line 3):
   - Primary key: `x[1]` (end position) in ascending order
   - Secondary key: `x[0]` (start position) for stability
   - Result: Balloons ordered by when they end

2. **Initialization** (Lines 5-8):
   - `removed`: Counts balloons that can be burst with existing arrows
   - `prev`: Tracks the "reference point"—starts as the first balloon, which requires an arrow
   - Initial arrow is shot at `points[0][1]` (end of first balloon)

3. **Iteration** (Lines 10-16):
   - For each subsequent balloon at index `i`:
     - **Check overlap**: `points[i][0] <= prev[1]`
       - This balloon's start ≤ previous balloon's end
       - This means an arrow at `prev[1]` would burst it
       - Increment `removed`
     - **No overlap**: No arrow at `prev[1]` can burst this balloon
       - Update `prev` to this balloon (prepare to shoot arrow at `points[i][1]`)

4. **Return** (Line 18):
   - Total arrows = Total balloons - Balloons burst with existing arrows
   - Returns `n - removed`

### Time & Space Complexity

- **Time Complexity**: O(n log n)
  - Sorting: O(n log n)
  - Single pass through balloons: O(n)
  - Overall: O(n log n)

- **Space Complexity**: O(1)
  - Only using a few variables for tracking
  - Sorting space depends on implementation (typically O(log n) for in-place sort)

### Example Walkthrough

Using **Example 1**: `points = [[10,16],[2,8],[1,6],[7,12]]`

1. **After sorting by end position**:
   - `[[1,6], [2,8], [7,12], [10,16]]`

2. **Iteration**:
   - `prev = [1,6]` (shoot arrow at x=6) → `removed = 0`
   - `i=1`: `[2,8]` → `2 <= 6` ✓ (overlaps) → `removed = 1`
   - `i=2`: `[7,12]` → `7 <= 6` ✗ (no overlap) → `prev = [7,12]` (shoot arrow at x=12)
   - `i=3`: `[10,16]` → `10 <= 12` ✓ (overlaps) → `removed = 2`

3. **Result**: `n - removed = 4 - 2 = 2` ✓

---

## Key Takeaways

- **Greedy algorithms** work well when a problem exhibits optimal substructure and greedy choice property
- **Sorting** is often the first step to enable efficient greedy solutions
- **Activity Selection / Interval Scheduling**: This problem is a variation—we're selecting the minimum number of "arrows" to cover all "intervals"
- **Edge Case**: Integer overflow consideration with `sort(key=lambda x: x[1])` when comparing large integers (use `x[1]` directly as Python handles big integers naturally)

## Tags

- Greedy
- Sorting
- Interval Scheduling
- Array

## Observations

## Solution

# Tags

