## Problem

https://leetcode.com/problems/jump-game-ix/description

Given an integer array `nums`, from any index `i` you can jump to another index `j` following these rules:
- Jump to index `j` where `j > i` is allowed only if `nums[j] < nums[i]`
- Jump to index `j` where `j < i` is allowed only if `nums[j] > nums[i]`

For each index `i`, find the maximum value in `nums` that can be reached by following any sequence of valid jumps starting at `i`.

**Return** an array `ans` where `ans[i]` is the maximum value reachable starting from index `i`.

### Examples

**Example 1:**
```
Input: nums = [2,1,3]
Output: [2,2,3]

Explanation:
- i = 0: No valid jumps increase the value. Max = 2
- i = 1: Can jump to j = 0 (nums[0] = 2 > nums[1] = 1). Max = 2
- i = 2: Max value already, no jumps increase it. Max = 3
```

**Example 2:**
```
Input: nums = [2,3,1]
Output: [3,3,3]

Explanation:
- i = 0: Jump to j = 2 (nums[2] = 1 < nums[0] = 2)
          Then jump to j = 1 (nums[1] = 3 > nums[2] = 1). Max = 3
- i = 1: Max value already. Max = 3
- i = 2: Jump to j = 1 (nums[1] = 3 > nums[2] = 1). Max = 3
```

### Constraints
- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^9`

## Observations

1. **Key Insight - Monotonic Regions**: For any starting position, we can only jump within certain regions. The jump rules create a natural partitioning of the array:
   - From position `i`, we can jump forward only to smaller values (decreasing direction)
   - We can jump backward only to larger values (increasing direction)

2. **Monotonic Stacks Pattern**: The problem is essentially asking: from each position, what's the maximum value we can reach by alternating between:
   - Moving right to smaller values
   - Then moving left to larger values
   - And so on...

3. **Critical Observation - Pivot Points**: If we process the array, we can identify "pivot" positions where:
   - `left_max[i]` (max value to the left including i) is less than or equal to `right_min[i+1]` (min value to the right)
   - At these positions, no more jumps are possible beyond this point because any forward jump would require a smaller value (but we're already at the max seen so far)

4. **Segment Processing**: The array can be divided into segments where all positions in a segment will have the same maximum reachable value. These segments are determined by the pivot points.

5. **Time Optimization**: Instead of computing the result for each position independently (which would be expensive), we can:
   - Precompute `left_max` and `right_min` arrays
   - Find natural boundaries where the reachability "breaks"
   - Assign the same maximum value to entire segments at once

## Solution

### Approach: Monotonic Array Segmentation

The algorithm works by identifying segments of the array where all indices can reach the same maximum value.

```python
class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        res = nums[:]  # Start with original values
        
        n = len(nums)
        left_max = [0] * n  # Maximum value from index 0 to i
        right_min = [0] * n  # Minimum value from index i to n-1
        
        # Build left_max array
        left_max[0] = nums[0]
        for i in range(1, n):
            left_max[i] = max(left_max[i - 1], nums[i])
        
        # Build right_min array
        right_min[n - 1] = nums[-1]
        for i in range(n - 2, -1, -1):
            right_min[i] = min(right_min[i + 1], nums[i])
        
        # Process segments
        pivot_idx = 0
        pivot_max = nums[0]
        
        for i in range(n):
            pivot_max = max(pivot_max, nums[i])
            
            # Check if we've reached a boundary segment
            # If i is the last element OR left_max[i] <= right_min[i+1]
            if i == n - 1 or left_max[i] <= right_min[i + 1]:
                # All indices from pivot_idx to i can reach pivot_max
                for j in range(pivot_idx, i + 1):
                    res[j] = pivot_max
                
                # Start a new segment if not at the end
                if i < n - 1:
                    pivot_idx = i + 1
                    pivot_max = nums[pivot_idx]
        
        return res
```

### How It Works

1. **left_max[i]**: Stores the maximum value seen from start to position `i`. This represents what's the best we've seen "behind" us.

2. **right_min[i]**: Stores the minimum value seen from position `i` to end. This represents the smallest value we could jump to going forward.

3. **Segment Detection**: When `left_max[i] <= right_min[i+1]`:
   - The maximum value seen so far (left_max[i]) is less than or equal to the minimum value ahead (right_min[i+1])
   - This means from any position in the current segment [pivot_idx, i], we can:
     - Jump forward to any position with a smaller value (covered by left_max[i])
     - But then we hit the boundary where all remaining values are >= right_min[i+1]
   - So the maximum reachable is capped at pivot_max (the max in current segment)

4. **Why It Works**: 
   - For position `j` in segment [pivot_idx, i] with value `nums[j]`:
     - If `nums[j] < pivot_max`: We can jump backward to reach pivot_max
     - If `nums[j] == pivot_max`: It's already the maximum
     - We can't reach beyond the boundary to larger values in the next segment because the jump rules prevent it

### Complexity Analysis

- **Time**: `O(n)` - We build left_max and right_min in O(n), then process the array once
- **Space**: `O(n)` - For the left_max and right_min arrays, plus the result array

# Tags

- Array
- Monotonic Stack
- Dynamic Programming
- Greedy Segmentation
