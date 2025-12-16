## Problem

https://leetcode.com/problems/partition-to-k-equal-sum-subsets/description/

Given an integer array `nums` and an integer `k`, return `true` if it is possible to divide this array into `k` non-empty subsets whose sums are all equal.

**Example 1:**
```
Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
```

**Example 2:**
```
Input: nums = [1,2,3,4], k = 3
Output: false
```

**Constraints:**
- `1 <= k <= nums.length <= 16`
- `1 <= nums[i] <= 10^4`
- The frequency of each element is in the range `[1, 4]`

## Observations

1. **Target Sum**: Each subset must have a sum equal to `total_sum / k`. If `total_sum % k != 0`, it's impossible to partition.

2. **Early Termination**: If any element is greater than `target`, partitioning is impossible.

3. **Greedy Sorting**: Sorting the array in descending order helps us fail fast - larger numbers are harder to fit, so we try them first.

4. **Backtracking Nature**: This is a combinatorial problem where we need to try different combinations of elements for each subset.

5. **State Space**: We need to track:
   - Which elements have been used
   - Current sum being built
   - How many complete subsets we've formed

6. **Base Cases**:
   - If we've formed `k-1` complete subsets, the remaining elements automatically form the last subset
   - When current sum equals target, start building the next subset from the beginning

## Solution

### Approach: Backtracking with DFS

The solution uses **backtracking with depth-first search** to explore all possible ways to partition the array.

### Algorithm Steps:

1. **Validation**:
   - Calculate total sum and check if divisible by `k`
   - Calculate target sum per subset: `target = sum(nums) / k`
   - Sort array in descending order (optimization)
   - Check if largest element exceeds target

2. **DFS Backtracking**:
   - **Parameters**:
     - `i`: Starting index for the current search
     - `cur_sum`: Current sum of the subset being built
     - `segments`: Number of remaining subsets to form
   
   - **Base Case**: If only 1 segment remains, return `True` (all others are complete, so the last one must be valid)
   
   - **Recursive Case**:
     - If `cur_sum == target`: We've completed one subset, start the next one from index 0
     - Otherwise, try adding each unused element from index `i` onwards:
       - Skip if element is already used or would exceed target
       - Mark element as used
       - Recursively continue building
       - Backtrack if unsuccessful

3. **Optimizations**:
   - **Descending sort**: Larger numbers constrain choices more, helping us fail faster
   - **Start from 0 on new subset**: When starting a new subset, we can use any remaining element
   - **Start from i+1 within subset**: Avoid revisiting elements in the same subset (maintains ordering)

### Time Complexity:
- Worst case: $O(k \cdot 2^n)$ where $n$ is the length of nums
- We try each element in up to $k$ subsets, and for each configuration, we have exponential possibilities
- Sorting: $O(n \log n)$ is dominated by the backtracking

### Space Complexity:
- $O(n)$ for the `used` array and recursion stack depth

### Key Insights:

1. **Why start from 0 when beginning new subset?** 
   - Once we complete a subset, any remaining unused element can be the first element of the next subset

2. **Why start from i+1 within the same subset?**
   - This prevents duplicates and ensures we don't revisit elements already considered for the current subset

3. **Why sort in descending order?**
   - Larger elements have fewer placement options, so trying them first prunes the search space earlier

4. **Why check segments == 1?**
   - If we've successfully formed `k-1` subsets with the target sum, the remaining elements must sum to target (since total is divisible by k)

# Tags

`Array` `Backtracking` `Depth-First Search` `Dynamic Programming` `Bit Manipulation` `Memoization` `Bitmask`

