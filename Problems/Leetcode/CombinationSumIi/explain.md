## Problem

https://leetcode.com/problems/combination-sum-ii/description/

```
Given a collection of candidate numbers (candidates) and a target number (target), 
find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

Example 1:
Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6], [1,2,5], [1,7], [2,6]]

Example 2:
Input: candidates = [2,5,2,1,2], target = 5
Output: [[1,2,2], [5]]

Constraints:
- 1 <= candidates.length <= 100
- 1 <= candidates[i] <= 50
- 1 <= target <= 30
```

## Observations

1. **Key Difference from Combination Sum I**: Each number can only be used **once** per combination
   - In the recursion, we move to `i + 1` instead of `i`
   - This ensures each element is used at most once

2. **Duplicate Numbers in Input**: The array may contain duplicate numbers
   - Example: `[1,1,2,5,6,7,10]` has two 1's
   - We can use both 1's in a single combination: `[1,1,6]`

3. **Avoiding Duplicate Combinations**: The challenge is to avoid duplicate combinations in the result
   - If we have duplicates at the same recursion level, we need to skip them
   - Example: at the same level, if we already tried `nums[i]`, we skip `nums[i+1]` if they're equal

4. **Sorting is Crucial**:
   - Enables duplicate detection: adjacent duplicates can be easily skipped
   - Enables early termination: if `nums[i] > remain`, all subsequent numbers are also too large

5. **Pruning Opportunities**:
   - If current number exceeds remaining target, break (all subsequent numbers are larger)
   - Skip duplicates at the same recursion level to avoid duplicate combinations

## Solution

### Approach: Backtracking with Duplicate Handling

**Algorithm**:
1. **Sort** the input array to group duplicates together and enable pruning
2. Use **backtracking** to explore all possible combinations:
   - At each step, decide whether to include the current number
   - Recursively explore with the remaining target
3. **Base Case**: When `remain == 0`, we found a valid combination
4. **Duplicate Handling**: At each recursion level, skip duplicate numbers after the first occurrence
   - `if i > idx and nums[i] == nums[i-1]: continue`
   - This ensures we don't generate duplicate combinations
5. **Pruning**: If `nums[i] > remain`, break early (all subsequent numbers are larger)

**Why Skip Duplicates This Way?**

Consider `candidates = [1,1,2], target = 3`:
```
Level 0: Try first 1
  Level 1: Try second 1
    Level 2: Try 2 → [1,1,2] (invalid, sum=4)
  Level 1: Try 2 → [1,2] ✓
  
Level 0: Skip second 1 (i > idx and nums[i] == nums[i-1])
  ↑ This prevents duplicate [1,2] combination
  
Level 0: Try 2
  Level 1: ... (no valid combinations)
```

The condition `i > idx` ensures:
- At the **same recursion level** (same `idx`), we skip duplicates after the first
- At **different recursion levels**, we can still use duplicate values (e.g., both 1's in `[1,1,6]`)

**Code Walkthrough**:

```python
class Solution:
    def combinationSum2(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()  # Sort to group duplicates and enable pruning
        n = len(nums)
        res = []
        
        def generating(idx: int, tmp: List[int], remain: int) -> None:
            # Base case: found a valid combination
            if remain == 0:
                res.append(tmp[:])  # Make a copy of tmp
                return
            
            # Try each number from idx to end
            for i in range(idx, n):
                # Skip duplicates at the same recursion level
                # i > idx ensures this is not the first number at this level
                if i > idx and nums[i] == nums[i - 1]:
                    continue
                
                # Pruning: if current number exceeds remain, stop
                # (all subsequent numbers are >= current)
                if nums[i] > remain:
                    break
                
                # Choose: add current number to combination
                tmp.append(nums[i])
                # Explore: recurse with i+1 (each number used once)
                generating(i + 1, tmp, remain - nums[i])
                # Unchoose: backtrack
                tmp.pop()
        
        generating(0, [], target)
        return res
```

**Time Complexity**: $O(2^n)$ where $n$ is the length of candidates
- In the worst case, we explore all $2^n$ subsets
- Sorting takes $O(n \log n)$, but backtracking dominates

**Space Complexity**: $O(n)$
- Recursion depth is at most $n$ (each call moves to `i+1`)
- The `tmp` list can have at most $n$ elements
- Not counting output space

**Key Insights**:
1. **Sort first** to enable both duplicate detection and pruning
2. **`i > idx`** is the magic condition that prevents duplicate combinations while allowing duplicate values
3. **`i + 1`** in the recursive call ensures each element is used at most once
4. **Early break** when `nums[i] > remain` provides significant pruning

# Tags

`Backtracking` `Array` `Sorting` `Recursion` `Duplicate-Handling`

