## Problem

https://leetcode.com/problems/number-of-longest-increasing-subsequence/description

# Number of Longest Increasing Subsequence

## Problem

**LeetCode**: https://leetcode.com/problems/number-of-longest-increasing-subsequence/description

Given an integer array `nums`, return the **number of longest increasing subsequences**.

**Notice**: The sequence has to be **strictly increasing**.

### Examples

**Example 1:**
- Input: `nums = [1,3,5,4,7]`
- Output: `2`
- Explanation: The two longest increasing subsequences are `[1, 3, 4, 7]` and `[1, 3, 5, 7]`.

**Example 2:**
- Input: `nums = [2,2,2,2,2]`
- Output: `5`
- Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.

### Constraints

- `1 <= nums.length <= 2000`
- `-10^6 <= nums[i] <= 10^6`
- The answer is guaranteed to fit inside a 32-bit integer.

---

## Observations

1. **Two Pieces of Information**: For each position `i`, we need to track:
   - The **length** of the longest increasing subsequence (LIS) ending at index `i`
   - The **count** of such LIS sequences

2. **Dynamic Programming State**: We can use a DP array where `dp[i] = (max_len, max_count)` to store both pieces of information.

3. **Transition Logic**: For each position `i`:
   - Look at all previous positions `j < i` where `nums[j] < nums[i]` (strictly increasing)
   - If extending from position `j` gives us a longer sequence, update both length and count to match position `j`'s count
   - If extending from position `j` gives the same length, accumulate the counts (add them together)

4. **Final Answer**: Scan all positions and find the maximum LIS length. Sum up the counts for all positions that have this maximum length.

5. **Time Complexity**: $O(n^2)$ - for each position, we check all previous positions
6. **Space Complexity**: $O(n)$ - we store the DP table

---

## Solution

### Approach 1: Memoization (Top-Down DP)

```python
def findNumberOfLIS(self, nums: List[int]) -> int:
    n = len(nums)
    mem = {}
    
    def F(i: int) -> Tuple[int, int]:
        """
        Returns (LIS length ending at i, count of LIS ending at i)
        """
        if i in mem:
            return mem[i]
        
        max_len = 1
        max_count = 1
        
        # Check all previous elements
        for j in range(i):
            if nums[i] > nums[j]:
                prev_len, prev_count = F(j)
                # If we found a longer sequence, reset count
                if prev_len + 1 > max_len:
                    max_len = prev_len + 1
                    max_count = prev_count
                # If same length, accumulate counts
                elif prev_len + 1 == max_len:
                    max_count += prev_count
        
        mem[i] = (max_len, max_count)
        return mem[i]
    
    # Find global maximum length and sum counts
    global_max_len = 0
    res = 0
    for i in range(n):
        max_len, count = F(i)
        if global_max_len < max_len:
            global_max_len = max_len
            res = count
        elif global_max_len == max_len:
            res += count
    return res
```

### Approach 2: Tabulation (Bottom-Up DP)

```python
def findNumberOfLIS(self, nums: List[int]) -> int:
    n = len(nums)
    
    # dp[i] = (LIS length ending at i, count of LIS ending at i)
    dp = [(1, 1)] * n
    
    # Build DP table from left to right
    for i in range(n):
        max_len, max_count = 1, 1
        for j in range(i):
            if nums[i] > nums[j]:
                prev_len, prev_count = dp[j]
                # If extending gives longer sequence
                if prev_len + 1 > max_len:
                    max_len = prev_len + 1
                    max_count = prev_count
                # If extending gives same length
                elif prev_len + 1 == max_len:
                    max_count += prev_count
        dp[i] = (max_len, max_count)
    
    # Find global maximum and sum counts
    global_max_len = 0
    res = 0
    for i in range(n):
        l, c = dp[i]
        if global_max_len < l:
            global_max_len = l
            res = c
        elif global_max_len == l:
            res += c
    return res
```

### Key Insights in the Solution

1. **Tuple Storage**: Each DP entry stores `(length, count)` as a pair, allowing us to track both metrics simultaneously.

2. **Count Accumulation**: The critical logic is:
   - When `prev_len + 1 > max_len`: We found a longer sequence, so we **replace** the count with `prev_count`
   - When `prev_len + 1 == max_len`: We found another path of the same length, so we **add** to the count

3. **Final Pass**: After building the DP table, we scan through all entries and collect counts from positions with the maximum LIS length.

4. **Why This Works**: 
   - We ensure that each position correctly counts all distinct LIS sequences ending at that position
   - By summing counts from all positions with maximum length, we get the total count of all distinct LIS in the array

---

## Tags

- Dynamic Programming
- Longest Increasing Subsequence (LIS)
- Counting Subsequences
- O(n²) solution
