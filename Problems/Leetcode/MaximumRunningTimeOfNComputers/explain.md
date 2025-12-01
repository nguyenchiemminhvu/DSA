## Problem

https://leetcode.com/problems/maximum-running-time-of-n-computers/description/

```
You have n computers. You are given the integer n and a 0-indexed integer array batteries 
where the ith battery can run a computer for batteries[i] minutes. You are interested in 
running all n computers simultaneously using the given batteries.

Initially, you can insert at most one battery into each computer. After that and at any 
integer time moment, you can remove a battery from a computer and insert another battery 
any number of times. The inserted battery can be a totally new battery or a battery from 
another computer. You may assume that the removing and inserting processes take no time.

Note that the batteries cannot be recharged.

Return the maximum number of minutes you can run all the n computers simultaneously.

Example 1:
Input: n = 2, batteries = [3,3,3]
Output: 4

Example 2:
Input: n = 2, batteries = [1,1,1,1]
Output: 2

Constraints:
- 1 <= n <= batteries.length <= 10^5
- 1 <= batteries[i] <= 10^9
```

## Observations

1. **Key Insight**: We can freely swap batteries between computers at any time with no cost. This means we can distribute battery power optimally.

2. **Battery Usage**: A battery with capacity `b` can contribute at most `min(b, T)` minutes when running for `T` total minutes. If `b > T`, we only use `T` minutes from it. If `b <= T`, we use all of it.

3. **Feasibility Check**: For a target time `T`, all `n` computers can run simultaneously if:
   - Total usable battery power >= Total required power
   - `sum(min(battery[i], T)) >= n * T`

4. **Binary Search**: Since if we can run for `T` minutes, we can also run for any time `< T`, the answer space is monotonic. We can binary search on the answer.

5. **Search Bounds**: 
   - Minimum: 0 minutes
   - Maximum: `sum(batteries)` (if we could pool all battery power for 1 computer, but we have `n` computers)

## Solution

**Approach: Binary Search + Greedy Validation**

The solution uses binary search to find the maximum running time:

1. **Binary Search Space**: Search between `0` and `sum(batteries)`

2. **Validation Function** (`testing(T)`):
   - For a given time `T`, check if `n` computers can run simultaneously
   - For each battery `b`, it can contribute `min(b, T)` minutes
   - If total contribution `>= n * T`, then `T` is achievable
   
3. **Why `min(b, T)`?**
   - If a battery has more power than needed (`b > T`), we can only use `T` minutes from it
   - If a battery has less power (`b <= T`), we use all of it and can swap to another battery

4. **Example Walkthrough** (n=2, batteries=[3,3,3]):
   - Test T=4: sum(min(3,4) + min(3,4) + min(3,4)) = 9 >= 2*4 = 8 ✓
   - Test T=5: sum(min(3,5) + min(3,5) + min(3,5)) = 9 >= 2*5 = 10 ✗
   - Maximum is 4 minutes

**Time Complexity**: O(nb × log(sum(batteries))) where nb is the number of batteries
- Binary search: O(log(sum(batteries)))
- Each validation: O(nb)

**Space Complexity**: O(1)

# Tags
`Binary Search`, `Greedy`, `Array`, `Math`

