## Problem

https://leetcode.com/problems/find-minimum-log-transportation-cost/description/

You are given integers `n`, `m`, and `k`.

There are two logs of lengths `n` and `m` units, which need to be transported in three trucks where each truck can carry one log with length at most `k` units.

You may cut the logs into smaller pieces, where the cost of cutting a log of length `x` into logs of length `len1` and `len2` is `cost = len1 * len2` such that `len1 + len2 = x`.

Return the minimum total cost to distribute the logs onto the trucks. If the logs don't need to be cut, the total cost is 0.

**Example 1:**
- Input: `n = 6, m = 5, k = 5`
- Output: `5`
- Explanation: Cut the log with length 6 into logs with length 1 and 5, at a cost equal to `1 * 5 == 5`. Now the three logs of length 1, 5, and 5 can fit in one truck each.

**Example 2:**
- Input: `n = 4, m = 4, k = 6`
- Output: `0`
- Explanation: The two logs can fit in the trucks already, hence we don't need to cut the logs.

**Constraints:**
- `2 <= k <= 10^5`
- `1 <= n, m <= 2 * k`
- The input is generated such that it is always possible to transport the logs.

## Observations

1. **Three trucks available**: We have 3 trucks, each can hold a log of at most `k` units.

2. **Two logs to transport**: We need to fit logs of length `n` and `m` into these trucks.

3. **Cutting cost formula**: When cutting a log of length `x` into two pieces of lengths `len1` and `len2`:
   - Cost = `len1 * len2`
   - Constraint: `len1 + len2 = x`

4. **Key insight - Greedy strategy**: 
   - Process the longer log first (sort in descending order)
   - If a log fits in a truck (`length <= k`), no cutting needed
   - If a log is too long (`length > k`), we must cut it

5. **Optimal cutting strategy**:
   - When we must cut a log of length `x > k`, we want to minimize the cost
   - Since we have a truck that can hold `k` units, the optimal first cut is to separate `k` units
   - This gives us: `len1 = k` and `len2 = x - k`
   - Cost = `k * (x - k)`
   - The piece of length `k` fits in one truck
   - The remaining piece `(x - k)` needs further processing

6. **Iterative cutting**:
   - If the remaining piece is still `> k`, we cut again using the same strategy
   - Each cut creates a piece of size `k` (which fits in a truck) and a remainder
   - Continue until the remainder is `<= k`

7. **Mathematical insight**:
   - For a log of length `x` where `x > k`, cutting it optimally:
   - First cut: `k` and `(x - k)`, cost = `k * (x - k)`
   - If `(x - k) > k`, second cut: `k` and `(x - 2k)`, cost = `k * (x - 2k)`
   - Total cost = `k * (x - k) + k * (x - 2k) + ... `
   - This simplifies to: `k * (x - k)` for the first cut since we're always separating `k` from the remainder

8. **Why this greedy approach works**:
   - We have 3 trucks and 2 logs, so at least one truck will be empty or we can distribute pieces
   - Cutting the longer log first minimizes total cost because we can fit more pieces optimally
   - Each cut of size `k` uses one truck, and we continue until all pieces fit

## Solution

1. **Sort logs**: `arr = sorted([m, n], reverse=True)` - Process longer log first

2. **Iterate through logs**:
   - If `val <= k`: The log fits in a truck, no cutting needed. Since we sorted in descending order, all remaining logs will also fit.
   - If `val > k`: We need to cut this log
     - Optimal cut: Separate `k` units (fits in one truck)
     - Remaining: `val - k` units
     - Cost: `k * (val - k)`

3. **Why this works**:
   - When we cut a log of length `val > k`, we separate exactly `k` units
   - The piece of size `k` goes into one truck
   - The remainder `(val - k)` either:
     - Fits in another truck if `<= k` (done)
     - Needs another cut if `> k` (but we only cut once per log in this problem)

4. **Time Complexity**: O(1) - Only sorting 2 elements and iterating at most 2 times
5. **Space Complexity**: O(1) - Only using constant extra space

**Example Walkthrough:**

Example 1: `n = 6, m = 5, k = 5`
- `arr = [6, 5]`
- Process `6`: Since `6 > 5`, cut it: `cost += (6 - 5) * 5 = 5`
- Process `5`: Since `5 <= 5`, break
- Total cost: `5`

Example 2: `n = 4, m = 4, k = 6`
- `arr = [4, 4]`
- Process `4`: Since `4 <= 6`, break
- Total cost: `0`

# Tags

`Greedy`, `Math`, `Optimization`

