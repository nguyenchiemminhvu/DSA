## Problem

https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/description

Given a **0-indexed integer array** `nums`, partition it into one or more **contiguous subarrays**. A partition is valid if each subarray satisfies **one** of these conditions:

1. The subarray consists of exactly **2 equal elements** (e.g., `[2,2]`)
2. The subarray consists of exactly **3 equal elements** (e.g., `[4,4,4]`)
3. The subarray consists of exactly **3 consecutive increasing elements** with difference 1 between adjacent elements (e.g., `[3,4,5]`)

**Return** `true` if the array has at least one valid partition; otherwise, return `false`.

**Examples:**
- Input: `[4,4,4,5,6]` → Output: `true` (partition: `[4,4]` and `[4,5,6]`)
- Input: `[1,1,1,2]` → Output: `false` (no valid partition exists)

**Constraints:**
- `2 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^6`

## Observations

1. **Partition Decision Point**: At each position, we decide whether to include it in a 2-element, 3-element equal, or 3-element consecutive group ending at that position.

2. **Dependency Pattern**: Whether position `i` can be validly partitioned depends on whether the subarray **before** the current group can be validly partitioned.

3. **Three Mutually Exclusive Options**:
   - **Option 1 (2-equal)**: If `nums[i] == nums[i-1]`, we can form a valid 2-element partition if `dp[i-2]` is true (subarray `[0...i-2]` is valid)
   - **Option 2 (3-equal)**: If `nums[i] == nums[i-1] == nums[i-2]`, we can form a valid 3-equal partition if `dp[i-3]` is true
   - **Option 3 (3-consecutive)**: If `nums[i] == nums[i-1] + 1 == nums[i-2] + 2` (consecutive increasing), we can partition if `dp[i-3]` is true

4. **State Definition**: `dp[i]` = `true` if elements from index `0` to `i` (inclusive) can be validly partitioned.

5. **Base Case Issue**: Initializing `dp = [True] * n` is **problematic** because it assumes all single elements and isolated subarrays are valid, but they're not. The correct approach is to initialize as `[False] * n` and handle base cases carefully, or validate during the DP loop.

## Solution

### Approach: Dynamic Programming (Bottom-Up)

**Time Complexity**: O(n) - single pass through array
**Space Complexity**: O(n) - DP array

```python
class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = [False] * (n + 1)  # dp[i] = can first i elements be validly partitioned
        dp[0] = True  # Empty array is valid (base case)
        
        for i in range(1, n + 1):
            # Option 1: 2 equal elements ending at position i-1
            if i >= 2 and nums[i-1] == nums[i-2]:
                dp[i] = dp[i] or dp[i-2]
            
            # Option 2: 3 equal elements ending at position i-1
            if i >= 3 and nums[i-1] == nums[i-2] and nums[i-2] == nums[i-3]:
                dp[i] = dp[i] or dp[i-3]
            
            # Option 3: 3 consecutive increasing elements ending at position i-1
            if i >= 3 and nums[i-1] == nums[i-2] + 1 and nums[i-2] == nums[i-3] + 1:
                dp[i] = dp[i] or dp[i-3]
        
        return dp[n]
```

**Key Insights:**

1. **Index Mapping**: Using 1-based indexing in DP (`dp[0]` for empty, `dp[i]` for first `i` elements) is cleaner. When checking position `i` in the DP array, we access elements at indices `i-1`, `i-2`, `i-3` in the original array.

2. **Why `dp[0] = True`**: If we successfully partition up to some position, it means the remaining subarray forms a valid group. The base case represents "no elements remain to partition," which is valid.

3. **State Transitions**: At each position, we try all three options and take OR:
   - If any option succeeds, `dp[i] = true`
   - All three options must be checked because they're mutually exclusive ways to form the ending partition

4. **Example Trace** (`nums = [4,4,4,5,6]`):
   ```
   dp = [T, F, F, F, F, F]  (indices 0-5)
   
   i=1: nums[0]=4
     - Check i>=2: No
     - Result: dp[1] = False
   
   i=2: nums[0:2]=[4,4]
     - Check 2-equal: nums[1]==nums[0]? Yes → dp[2] = dp[0] = True
     - Result: dp[2] = True
   
   i=3: nums[0:3]=[4,4,4]
     - Check 3-equal: nums[2]==nums[1]==nums[0]? Yes → dp[3] = dp[0] = True
     - Result: dp[3] = True
   
   i=4: nums[0:4]=[4,4,4,5]
     - Check 2-equal: nums[3]==nums[2]? No
     - Check 3-equal: No
     - Check 3-consec: nums[3]==nums[2]+1? 5==5? Yes → dp[4] = dp[1] = False
     - Result: dp[4] = False
   
   i=5: nums[0:5]=[4,4,4,5,6]
     - Check 3-consec: nums[4]==nums[3]+1? 6==6? Yes → dp[5] = dp[2] = True
     - Result: dp[5] = True ✓
   ```

### Alternative: Top-Down Memoization

The commented-out recursive solution works similarly but uses memoization:
- `F(i)` = can elements from index `0` to `i` be validly partitioned?
- Returns `True` if index is -1 (all elements processed)
- Recursively tries all three options and returns their OR

Both approaches have identical time and space complexity.

# Tags

#dynamic-programming #array-partition #memoization #greedy-validation

