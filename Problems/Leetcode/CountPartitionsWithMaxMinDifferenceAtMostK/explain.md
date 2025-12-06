## Problem

https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/description

```
You are given an integer array nums and an integer k. Your task is to partition nums 
into one or more non-empty contiguous segments such that in each segment, the difference 
between its maximum and minimum elements is at most k.

Return the total number of ways to partition nums under this condition.

Since the answer may be too large, return it modulo 10^9 + 7.

Example 1:
Input: nums = [9,4,1,3,7], k = 4
Output: 6

Explanation:
There are 6 valid partitions where the difference between the maximum and minimum 
elements in each segment is at most k = 4:
[[9], [4], [1], [3], [7]]
[[9], [4], [1], [3, 7]]
[[9], [4], [1, 3], [7]]
[[9], [4, 1], [3], [7]]
[[9], [4, 1], [3, 7]]
[[9], [4, 1, 3], [7]]

Example 2:
Input: nums = [3,3,4], k = 0
Output: 2

Explanation:
There are 2 valid partitions:
[[3], [3], [4]]
[[3, 3], [4]]

Constraints:
- 2 <= nums.length <= 5 * 10^4
- 1 <= nums[i] <= 10^9
- 0 <= k <= 10^9
```

## Observations

1. **Contiguous Segments**: We must partition the array into contiguous subarrays, not arbitrary subsets.

2. **Valid Segment Condition**: A segment `[i..j]` is valid if `max(nums[i..j]) - min(nums[i..j]) <= k`.

3. **Counting Problem**: We need to count all possible ways to partition, not find the optimal partition.

4. **Greedy Won't Work**: We can't just greedily extend segments as far as possible because we need to count ALL valid partitions.

5. **Overlapping Subproblems**: The number of ways to partition `nums[i:]` depends on:
   - Where we place the first partition boundary
   - The number of ways to partition the remaining array

6. **Key Insight**: For each starting position `i`, we can try all possible ending positions `j` for the first segment. If `[i..j]` is valid, we add the number of ways to partition `nums[j+1:]`.

## Solution

### Approach: Dynamic Programming with Memoization

**State Definition:**
- `F(i)` = number of valid ways to partition `nums[i:]` (starting from index `i`)

**Base Case:**
- `F(n)` = 1 (reached the end, one valid empty partition)

**Recurrence Relation:**
```
F(i) = Σ F(j+1) for all j where [i..j] is a valid segment
```

For each position `i`, we try extending a segment from `i` to `j`:
- Track the minimum and maximum in the current segment `[i..j]`
- If `max - min <= k`, the segment is valid, so we add `F(j+1)` to our count
- If `max - min > k`, we can't extend further (and any longer segment will also be invalid)

**Why This Works:**

1. **Correctness**: Every valid partition of `nums[i:]` must start with some segment `[i..j]`, followed by a valid partition of `nums[j+1:]`. We enumerate all possibilities.

2. **Early Termination**: Once `max - min > k` for segment `[i..j]`, extending to `[i..j+1]` will only make the range worse (or equal), so we can stop.

3. **Memoization**: We cache results to avoid recomputing `F(i)` multiple times.

**Time Complexity:** O(n²)
- We have `n` states (one for each starting position)
- For each state, we might iterate through up to `n` ending positions
- With memoization, each state is computed once

**Space Complexity:** O(n)
- Memoization dictionary stores at most `n` entries
- Recursion depth is at most `n`

### Implementation Details

```python
class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:
        n = len(nums)
        mod = 10**9 + 7
        memo = {}
        
        # F(i) = number of valid ways to partition nums[i:]
        def F(i: int) -> int:
            # Base case: reached end → 1 valid partition
            if i == n:
                return 1
            
            if i in memo:
                return memo[i]

            ways = 0
            cur_min = float('inf')
            cur_max = float('-inf')

            # Try extending segment [i..j]
            for j in range(i, n):
                cur_min = min(cur_min, nums[j])
                cur_max = max(cur_max, nums[j])

                # If range exceeds k, stop extending
                if cur_max - cur_min > k:
                    break

                # Add ways to partition the rest
                ways += F(j + 1)

            memo[i] = ways % mod
            return ways % mod

        return F(0)
```

**Example Walkthrough (nums = [9,4,1,3,7], k = 4):**

- `F(0)`: Try segments starting at 0
  - `[9]` (valid, max-min=0): add `F(1)`
  - `[9,4]` (invalid, max-min=5): stop
  
- `F(1)`: Try segments starting at 1
  - `[4]` (valid): add `F(2)`
  - `[4,1]` (valid, max-min=3): add `F(3)`
  - `[4,1,3]` (valid, max-min=3): add `F(4)`
  - `[4,1,3,7]` (invalid, max-min=6): stop

And so on... Each path through the recursion tree represents one valid partition.

# Tags
Dynamic Programming, Memoization, Array, Sliding Window

