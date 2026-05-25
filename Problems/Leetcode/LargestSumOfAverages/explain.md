## Problem

https://leetcode.com/problems/largest-sum-of-averages/description/

You are given an integer array `nums` and an integer `k`. You can partition the array into **at most** `k` non-empty adjacent subarrays. The score of a partition is the **sum of the averages** of each subarray.

**Constraints:**
- The partition must use every integer in `nums`
- The score is not necessarily an integer
- Return the maximum score you can achieve from all possible partitions
- Answers within 10⁻⁶ of the actual answer will be accepted

**Example 1:**
```
Input: nums = [9,1,2,3,9], k = 3
Output: 20.00000
Explanation: 
The best choice is to partition nums into [9], [1, 2, 3], [9]. 
The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
```

**Example 2:**
```
Input: nums = [1,2,3,4,5,6,7], k = 4
Output: 20.50000
```

**Constraints:**
- 1 ≤ nums.length ≤ 100
- 1 ≤ nums[i] ≤ 10⁴
- 1 ≤ k ≤ nums.length

## Observations

1. **Optimal Substructure**: This is a dynamic programming problem. If we partition starting at index `i` with `cnt` partitions remaining, the optimal solution depends on where we place the first partition boundary.

2. **State Definition**: We need to track:
   - Current position `i` in the array
   - Number of partitions `cnt` remaining to use
   - The maximum score we can achieve from position `i` to the end using exactly `cnt` partitions

3. **Overlapping Subproblems**: Many subproblems are recomputed. For instance, computing the optimal score from index 5 with 2 partitions may be needed multiple times.

4. **Prefix Sum Optimization**: Calculating the sum of elements in a range repeatedly is inefficient. A prefix sum array allows us to compute any segment sum in O(1) time:
   - `prefix_sum[i]` = sum of elements from index 0 to i-1
   - Sum from index l to r = `prefix_sum[r+1] - prefix_sum[l]`

5. **Greedy Doesn't Work**: We can't simply greedily pick the smallest or largest averages. We need to try all possible partitioning configurations because:
   - Taking one large element alone (high average) might prevent better partitions later
   - Taking multiple small elements together (lower average) might leave high elements grouped together

6. **Base Cases**:
   - If we reach the end of the array (`i >= n`), score is 0
   - If we have only 1 partition left (`cnt == 1`), we must take all remaining elements as one subarray

## Solution

**Approach: Dynamic Programming with Memoization (Top-Down)**

**Key Idea:**
- Use recursive function `F(i, cnt)` to compute the maximum score starting from index `i` with `cnt` partitions available
- For each position, try all possible ending points for the first partition
- Memoize results to avoid redundant calculations

**Algorithm:**

1. **Precompute Prefix Sums**: Build a prefix sum array for O(1) segment sum queries
   ```
   prefix_sum[i+1] = prefix_sum[i] + nums[i]
   ```

2. **Define Helper Function**: `segment_avg(l, r)` computes the average of elements from index l to r using prefix sums

3. **Define DP Function**: `F(i, cnt)` returns the maximum score from index i to n-1 using cnt partitions
   - **Base Case 1**: If `i >= n`, return 0 (no more elements)
   - **Base Case 2**: If `cnt == 1`, return the average of all remaining elements
   - **Recursive Case**: Try all possible end positions j for the first partition (from i+1 to n-cnt+1):
     - Current partition is from i to j-1
     - Recursively solve for remaining elements starting at j with cnt-1 partitions
     - Take the maximum across all choices

4. **Return**: `F(0, k)` gives the maximum score for the entire array with k partitions

**Time Complexity**: O(n² × k)
- State space: O(n × k) different (i, cnt) pairs
- Each state tries O(n) possible partition points
- Each partition point calculation is O(1)

**Space Complexity**: O(n × k)
- Memoization dictionary stores O(n × k) entries
- Recursion depth: O(n)

**Why This Works:**

The solution explores all valid partitioning strategies:
- It tries placing the first partition boundary at every valid position
- For each choice, it recursively finds the optimal partitioning of the remaining array
- The constraint that we need at least `cnt` elements remaining for `cnt` partitions is enforced by the loop condition: `j <= n - cnt + 1`

**Example Walkthrough** (nums = [9,1,2,3,9], k = 3):

```
F(0, 3) tries:
  - Partition [9], then solve F(1, 2):
    - F(1, 2) tries partition [1], then solve F(2, 1) → avg([2,3,9]) = 14/3
    - Best: 1 + 14/3 = 17/3
    - Or partition [1,2], then solve F(3, 1) → avg([3,9]) = 6
    - Best: 1.5 + 6 = 7.5
    - Or partition [1,2,3], then solve F(4, 1) → avg([9]) = 9
    - Best: 2 + 9 = 11
    - Maximum F(1, 2) = 11
  - Result: 9 + 11 = 20 ✓ (Optimal!)
```

# Tags

- Dynamic Programming
- Memoization (Top-Down)
- Prefix Sum Optimization
- Array Partitioning
- Optimization Problem

