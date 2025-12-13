## Problem

https://leetcode.com/problems/combination-sum/description/

```
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
7 is a candidate, and 7 = 7.
These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8
Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1
Output: []

Constraints:
- 1 <= candidates.length <= 30
- 2 <= candidates[i] <= 40
- All elements of candidates are distinct.
- 1 <= target <= 40
```

## Observations

1. **Unlimited Reuse**: Each candidate can be used unlimited times, which means we can include the same number multiple times in a combination.

2. **Unique Combinations**: We need to find all unique combinations, not permutations. For example, [2,3,2] and [2,2,3] should be considered the same combination.

3. **Backtracking Approach**: This is a classic backtracking problem where we explore all possible combinations by:
   - Including a candidate (possibly multiple times)
   - Moving to the next candidate
   - Backtracking when the sum exceeds target or we've explored all possibilities

4. **Sorting Optimization**: Sorting the array helps us:
   - Prune branches early when sum exceeds target
   - Avoid duplicate combinations by maintaining order

5. **Index Management**: To avoid duplicate combinations, we pass the current index to the recursive function. This ensures we only consider candidates from the current index onwards, maintaining the order and preventing permutations like [2,3] and [3,2].

## Solution

1. **Initialization**:
   - Sort the candidates array for optimization
   - Initialize result list `res` to store all valid combinations

2. **Recursive Function `generating(idx, tmp, s)`**:
   - `idx`: Current index in candidates array
   - `tmp`: Current combination being built
   - `s`: Current sum of numbers in `tmp`

3. **Base Cases**:
   - If `s > target`: Current path won't lead to a valid solution, prune it
   - If `s == target`: Found a valid combination, add copy to results
   - If `idx >= n`: No more candidates to explore

4. **Recursive Exploration**:
   - Iterate through candidates from `idx` to end
   - For each candidate at index `i`:
     - Add it to current combination: `tmp + [nums[i]]`
     - Update sum: `s + nums[i]`
     - Recursively call with index `i` (not `i+1`) to allow reusing same number
     - This automatically backtracks when function returns

5. **Avoiding Duplicates**:
   - By always starting from current index `i` and never going backwards
   - We ensure combinations are in non-decreasing order
   - This prevents counting [2,3,2] and [2,2,3] as different combinations

### Time Complexity:
- **O(N^(T/M))** where:
  - N = number of candidates
  - T = target value
  - M = minimal value among candidates
- In worst case, we might explore all possible combinations

### Space Complexity:
- **O(T/M)** for recursion stack depth
- The maximum depth is bounded by target/minimum_candidate

### Example Walkthrough:

For `candidates = [2,3,6,7]`, `target = 7`:

```
Start: generating(0, [], 0)
├─ Try nums[0]=2: generating(0, [2], 2)
│  ├─ Try nums[0]=2: generating(0, [2,2], 4)
│  │  ├─ Try nums[0]=2: generating(0, [2,2,2], 6)
│  │  │  ├─ Try nums[0]=2: generating(0, [2,2,2,2], 8) → s > 7, return
│  │  │  ├─ Try nums[1]=3: generating(1, [2,2,2,3], 9) → s > 7, return
│  │  │  └─ ...
│  │  ├─ Try nums[1]=3: generating(1, [2,2,3], 7) → s == 7, add [2,2,3] ✓
│  │  └─ ...
│  └─ ...
├─ Try nums[1]=3: generating(1, [3], 3)
│  └─ ...
├─ Try nums[2]=6: generating(2, [6], 6)
│  └─ ...
└─ Try nums[3]=7: generating(3, [7], 7) → s == 7, add [7] ✓

Result: [[2,2,3], [7]]
```

# Tags

`Backtracking` `Recursion` `Array` `Depth-First Search` `Combination`

