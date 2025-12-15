## Problem

https://leetcode.com/problems/non-decreasing-subsequences/description/

```
Given an integer array nums, return all the different possible non-decreasing 
subsequences of the given array with at least two elements. You may return the 
answer in any order.

Example 1:
Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

Example 2:
Input: nums = [4,4,3,2,1]
Output: [[4,4]]

Constraints:
- 1 <= nums.length <= 15
- -100 <= nums[i] <= 100
```

## Observations

1. **Subsequence Definition**: We need to find subsequences (not subarrays), meaning we can skip elements but must maintain the relative order of selected elements.

2. **Non-decreasing Constraint**: Each subsequence must be non-decreasing, i.e., `nums[i] <= nums[i+1]` for all consecutive elements in the subsequence.

3. **Minimum Length**: Each valid subsequence must have at least 2 elements.

4. **Uniqueness**: The result should contain unique subsequences only. For example, with `[4,6,7,7]`, we shouldn't have duplicate `[4,7]` subsequences.

5. **Small Input Size**: With `n <= 15`, we can afford exponential time complexity like backtracking/DFS (worst case: $2^{15}$ = 32,768 possible subsequences).

6. **Duplicate Handling**: The input array can contain duplicates, and we need to avoid generating duplicate subsequences. Using a `set` with tuples is an effective approach.

## Solution

### Approach: DFS/Backtracking with Set Deduplication

The solution uses **depth-first search (DFS)** with backtracking to explore all possible subsequences, filtering for non-decreasing ones.

**Key Components:**

1. **Set for Deduplication**: 
   - Use `res = set()` to store results as tuples
   - This automatically handles duplicate subsequences
   - Convert back to list of lists at the end

2. **Temporary Array (`tmp`)**:
   - Tracks the current subsequence being built
   - Elements are added during exploration and removed during backtracking

3. **DFS Function**:
   - **Base Case**: If `tmp` has more than 1 element, add it to results
   - **Termination**: If index `i >= n`, return
   - **Iteration**: For each position `j` from `i` to `n-1`:
     - Only append `nums[j]` if `tmp` is empty OR `tmp[-1] <= nums[j]` (maintains non-decreasing property)
     - Recursively explore from `j+1`
     - Backtrack by removing the last element

**Algorithm Walkthrough** (Example: `nums = [4,6,7,7]`):

```
Start: tmp=[], i=0
├─ Add 4: tmp=[4]
│  ├─ Add 6: tmp=[4,6] → Save (4,6)
│  │  ├─ Add 7: tmp=[4,6,7] → Save (4,6,7)
│  │  │  └─ Add 7: tmp=[4,6,7,7] → Save (4,6,7,7)
│  │  └─ Add 7: tmp=[4,6,7] → Save (4,6,7) [duplicate, set handles]
│  ├─ Add 7: tmp=[4,7] → Save (4,7)
│  │  └─ Add 7: tmp=[4,7,7] → Save (4,7,7)
│  └─ Add 7: tmp=[4,7] → Save (4,7) [duplicate]
├─ Add 6: tmp=[6]
│  ├─ Add 7: tmp=[6,7] → Save (6,7)
│  │  └─ Add 7: tmp=[6,7,7] → Save (6,7,7)
│  └─ Add 7: tmp=[6,7] → Save (6,7) [duplicate]
└─ Add 7: tmp=[7]
   └─ Add 7: tmp=[7,7] → Save (7,7)
```

**Code Explanation:**

```python
class Solution:
    def findSubsequences(self, nums: List[int]) -> List[List[int]]:
        res = set()  # Use set to avoid duplicates
        tmp = []     # Current subsequence being built
        n = len(nums)
        
        def dfs(i: int) -> None:
            # If current subsequence has at least 2 elements, add to results
            if len(tmp) > 1:
                res.add(tuple(tmp))  # Convert to tuple for set storage
            
            # Base case: reached end of array
            if i >= n:
                return
            
            # Try adding each element from position i onwards
            for j in range(i, n):
                # Only add if it maintains non-decreasing property
                if not tmp or tmp[-1] <= nums[j]:
                    tmp.append(nums[j])  # Choose
                    dfs(j + 1)           # Explore
                    tmp.pop()            # Unchoose (backtrack)
        
        dfs(0)
        return [list(arr) for arr in res]  # Convert tuples back to lists
```

**Complexity Analysis:**

- **Time Complexity**: $O(2^n \cdot n)$
  - In worst case, we explore all $2^n$ possible subsequences
  - For each subsequence, we may perform $O(n)$ operations (tuple creation, set insertion)
  - With $n \leq 15$, this is acceptable
  
- **Space Complexity**: $O(2^n \cdot n)$
  - Set can store up to $2^n$ subsequences
  - Each subsequence can have up to $n$ elements
  - Recursion depth is at most $n$

# Tags

