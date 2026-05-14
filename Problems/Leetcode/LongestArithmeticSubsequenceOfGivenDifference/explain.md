## Problem

https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/description

Given an integer array `arr` and an integer `difference`, return the length of the longest subsequence in `arr` which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals `difference`.

A subsequence is a sequence that can be derived from `arr` by deleting some or no elements without changing the order of the remaining elements.

### Examples

**Example 1:**
```
Input: arr = [1,2,3,4], difference = 1
Output: 4
Explanation: The longest arithmetic subsequence is [1,2,3,4].
```

**Example 2:**
```
Input: arr = [1,3,5,7], difference = 1
Output: 1
Explanation: The longest arithmetic subsequence is any single element.
```

**Example 3:**
```
Input: arr = [1,5,7,8,5,3,4,2,1], difference = -2
Output: 4
Explanation: The longest arithmetic subsequence is [7,5,3,1].
```

### Constraints

- $1 \leq \text{arr.length} \leq 10^5$
- $-10^4 \leq \text{arr[i]}, \text{difference} \leq 10^4$

## Observations

1. **Arithmetic Subsequence Property**: For an arithmetic subsequence with difference `diff`, if we pick element at index `i`, the previous element must be `arr[i] - diff`. We need to find how long the sequence can be if we end at index `i`.

2. **Subsequence vs Subarray**: Since we're looking for subsequences (not subarrays), elements don't need to be contiguous. We can skip elements in between.

3. **Greedy Selection**: At each position, we want to extend the longest arithmetic sequence that could come before the current element. If we've seen value `(arr[i] - diff)` before, we can extend the sequence ending at that value.

4. **Optimal Substructure**: 
   - `dp[i]` = length of longest arithmetic subsequence **ending at index `i`** with the given difference
   - To compute `dp[i]`, we need to know the length of the longest sequence ending at any index `j < i` where `arr[i] - arr[j] = diff`

5. **Key Insight - Hash Map Optimization**: Instead of checking all previous indices (O(n²)), we can use a hash map to track: "What's the longest sequence ending with value `v`?"
   - For current element with value `val`, previous element would have value `val - diff`
   - We can directly look up if we've seen `val - diff` and extend from there

## Solution

### Approach 1: Brute Force Recursion (Top-down DP)
```python
# Time: O(n²), Space: O(n)
def longestSubsequence(arr, diff):
    n = len(arr)
    mem = {}
    
    def F(i):
        # Length of longest arithmetic subsequence ending at index i
        if i < 0:
            return 0
        if i in mem:
            return mem[i]
        res = 1
        for j in range(i):
            if arr[i] - arr[j] == diff:
                res = max(res, 1 + F(j))
        mem[i] = res
        return res
    
    res = 1
    for i in range(n):
        res = max(res, F(i))
    return res
```

**Analysis:**
- For each index `i`, we check all previous indices `j` to see if `arr[i] - arr[j] = diff`
- If yes, we can extend the sequence ending at `j` by 1
- We take the maximum across all possible extensions

### Approach 2: Bottom-up DP with Array
```python
# Time: O(n²), Space: O(n)
def longestSubsequence(arr, diff):
    n = len(arr)
    dp = [1] * n  # Each element is at least a sequence of length 1
    res = 1
    
    for i in range(n):
        for j in range(i):
            if arr[i] - arr[j] == diff:
                dp[i] = max(dp[i], 1 + dp[j])
                res = max(res, dp[i])
    
    return res
```

**Analysis:**
- `dp[i]` = length of longest arithmetic subsequence ending at index `i`
- For each position `i`, we look back at all previous positions `j`
- If `arr[i] - arr[j] = diff`, we can extend the sequence ending at `j`
- Still O(n²) because we need to check all pairs

### Approach 3: Optimized DP with Hash Map (Optimal)
```python
# Time: O(n), Space: O(n)
from collections import defaultdict

def longestSubsequence(arr, diff):
    res = 1
    dp = defaultdict(int)  # dp[val] = length of sequence ending with value 'val'
    
    for val in arr:
        prev = val - diff
        dp[val] = 1 + dp[prev]
        res = max(res, dp[val])
    
    return res
```

**Why This Works:**
- Instead of storing by index, store by value: `dp[val]` = longest arithmetic subsequence **ending with value `val`**
- For current element with value `val`:
  - The previous element in the sequence must be `val - diff`
  - If we've seen `val - diff` before, we can extend that sequence: `dp[val] = 1 + dp[val - diff]`
  - If we haven't seen `val - diff`, then `dp[val - diff]` returns 0 (defaultdict), so `dp[val] = 1` (start new sequence)

**Example Trace: arr = [1,5,7,8,5,3,4,2,1], difference = -2**

```
val=1: prev=3,   dp[1] = 1 + dp[3] = 1 + 0 = 1,   res=1,   dp={1:1}
val=5: prev=7,   dp[5] = 1 + dp[7] = 1 + 0 = 1,   res=1,   dp={1:1, 5:1}
val=7: prev=9,   dp[7] = 1 + dp[9] = 1 + 0 = 1,   res=1,   dp={1:1, 5:1, 7:1}
val=8: prev=10,  dp[8] = 1 + dp[10] = 1 + 0 = 1,  res=1,   dp={1:1, 5:1, 7:1, 8:1}
val=5: prev=7,   dp[5] = 1 + dp[7] = 1 + 1 = 2,   res=2,   dp={1:1, 5:2, 7:1, 8:1}
val=3: prev=5,   dp[3] = 1 + dp[5] = 1 + 2 = 3,   res=3,   dp={1:1, 5:2, 7:1, 8:1, 3:3}
val=4: prev=6,   dp[4] = 1 + dp[6] = 1 + 0 = 1,   res=3,   dp={..., 4:1}
val=2: prev=4,   dp[2] = 1 + dp[4] = 1 + 1 = 2,   res=3,   dp={..., 2:2}
val=1: prev=3,   dp[1] = 1 + dp[3] = 1 + 3 = 4,   res=4,   dp={1:4, ...}

Result: 4 (corresponding to subsequence [7,5,3,1])
```

**Key Optimization:**
- We don't care which index had the previous value, only its value
- Using value as key instead of index reduces time complexity from O(n²) to O(n)
- Space complexity is O(n) for the hash map storing unique values

## Tags

- Dynamic Programming
- Hash Map
- Subsequence
- Arithmetic Sequence

