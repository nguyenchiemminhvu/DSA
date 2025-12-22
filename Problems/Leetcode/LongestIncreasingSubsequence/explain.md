## Problem

https://leetcode.com/problems/longest-increasing-subsequence/description/

Given an integer array `nums`, return the length of the longest **strictly increasing subsequence**.

**Example 1:**
```
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
```

**Example 2:**
```
Input: nums = [0,1,0,3,2,3]
Output: 4
```

**Example 3:**
```
Input: nums = [7,7,7,7,7,7,7]
Output: 1
```

**Constraints:**
- `1 <= nums.length <= 2500`
- `-10^4 <= nums[i] <= 10^4`

**Follow up:** Can you come up with an algorithm that runs in O(n log(n)) time complexity?

## Observations

1. **Subsequence vs Subarray**: A subsequence doesn't need to be contiguous. We can skip elements but must maintain the relative order.

2. **Strictly Increasing**: Each element in the subsequence must be strictly greater than the previous one (no equal values allowed).

3. **Overlapping Subproblems**: The problem exhibits optimal substructure - the LIS ending at position `i` depends on the LIS ending at all positions `j < i`.

4. **Dynamic Programming Approach**: 
   - For each position `i`, we need to know the length of the longest increasing subsequence ending at that position
   - This can be computed by looking at all previous positions `j < i` where `nums[j] < nums[i]`

5. **Time Complexity Trade-offs**:
   - DP approach: O(n²) time, O(n) space
   - Binary search + patience sorting: O(n log n) time, O(n) space

## Solution

### Approach 1: Dynamic Programming (O(n²))

**Core Idea:**
- `dp[i]` = length of the longest increasing subsequence ending at index `i`
- For each position `i`, check all previous positions `j < i`
- If `nums[i] > nums[j]`, we can extend the LIS ending at `j` by including `nums[i]`

**Algorithm:**
```python
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [1] * n  # Every element is an LIS of length 1 by itself
        
        for i in range(1, n):
            for j in range(0, i):
                if nums[i] > nums[j]:
                    # Can extend LIS ending at j
                    dp[i] = max(dp[i], dp[j] + 1)
        
        return max(dp)  # Maximum length among all positions
```

**Step-by-Step Example:** `nums = [10,9,2,5,3,7,101,18]`

```
Initial: dp = [1, 1, 1, 1, 1, 1, 1, 1]

i=1, nums[1]=9:
  j=0: 9 < 10? No
  dp = [1, 1, 1, 1, 1, 1, 1, 1]

i=2, nums[2]=2:
  j=0: 2 < 10? Yes, but dp[2]=1 already
  j=1: 2 < 9? Yes, but dp[2]=1 already
  dp = [1, 1, 1, 1, 1, 1, 1, 1]

i=3, nums[3]=5:
  j=0: 5 < 10? No
  j=1: 5 < 9? No
  j=2: 5 > 2? Yes → dp[3] = max(1, dp[2]+1) = 2
  dp = [1, 1, 1, 2, 1, 1, 1, 1]

i=4, nums[4]=3:
  j=0,1: No
  j=2: 3 > 2? Yes → dp[4] = max(1, dp[2]+1) = 2
  j=3: 3 < 5? No
  dp = [1, 1, 1, 2, 2, 1, 1, 1]

i=5, nums[5]=7:
  j=0,1: No
  j=2: 7 > 2? Yes → dp[5] = max(1, 1+1) = 2
  j=3: 7 > 5? Yes → dp[5] = max(2, 2+1) = 3
  j=4: 7 > 3? Yes → dp[5] = max(3, 2+1) = 3
  dp = [1, 1, 1, 2, 2, 3, 1, 1]

i=6, nums[6]=101:
  Best: extends from nums[5]=7 → dp[6] = 4
  dp = [1, 1, 1, 2, 2, 3, 4, 1]

i=7, nums[7]=18:
  Best: extends from nums[5]=7 → dp[7] = 4
  dp = [1, 1, 1, 2, 2, 3, 4, 4]

Answer: max(dp) = 4
LIS: [2, 5, 7, 101] or [2, 3, 7, 101] or [2, 5, 7, 18] or [2, 3, 7, 18]
```

**Complexity:**
- **Time:** O(n²) - nested loops over all elements
- **Space:** O(n) - DP array

**Why This Works:**
- **Optimal Substructure**: If the LIS ending at `j` has length `k`, then the LIS ending at `i` (where `nums[i] > nums[j]`) has at least length `k+1`
- **Correctness**: By checking all previous positions, we guarantee we find the maximum possible length at each position

### Approach 2: Binary Search + Patience Sorting (O(n log n))

For the follow-up, we can use a different approach:

**Core Idea:**
- Maintain an array `tail` where `tail[i]` is the smallest tail element of all increasing subsequences of length `i+1`
- For each element, use binary search to find where it can extend or replace

```python
class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        from bisect import bisect_left
        
        tail = []
        
        for num in nums:
            pos = bisect_left(tail, num)
            if pos == len(tail):
                tail.append(num)
            else:
                tail[pos] = num
        
        return len(tail)
```

**Complexity:**
- **Time:** O(n log n) - n elements, binary search for each
- **Space:** O(n) - tail array

# Tags

`Dynamic Programming` `Binary Search` `Array` `Subsequence` `Patience Sorting`

