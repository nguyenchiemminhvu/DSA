## Problem

https://leetcode.com/problems/132-pattern/description/

```
Given an array of n integers nums, a 132 pattern is a subsequence of three integers 
nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].

Return true if there is a 132 pattern in nums, otherwise, return false.

Example 1:
Input: nums = [1,2,3,4]
Output: false
Explanation: There is no 132 pattern in the sequence.

Example 2:
Input: nums = [3,1,4,2]
Output: true
Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
Input: nums = [-1,3,2,0]
Output: true
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

Constraints:
- n == nums.length
- 1 <= n <= 2 * 10^5
- -10^9 <= nums[i] <= 10^9
```

## Observations

1. **Pattern Definition**: We need to find three indices i < j < k where:
   - nums[i] < nums[k] < nums[j]
   - This means nums[j] is the largest (the "3" in 132)
   - nums[i] is the smallest (the "1" in 132)
   - nums[k] is in the middle (the "2" in 132)

2. **Brute Force Challenge**: A naive O(n³) approach checking all triplets is too slow for n up to 2×10⁵.

3. **Key Insights**:
   - For each position k (the "2" position), we need to find:
     - A position j > k where nums[j] > nums[k] (the "3")
     - A position i < j where nums[i] < nums[k] (the "1")
   - We can optimize by precomputing useful information

4. **Data Structures Needed**:
   - **left_min[i]**: The minimum value from index 0 to i (helps find the "1")
   - **left_gt[i]**: The nearest index to the left where the value is greater than nums[i] (helps find the "3")
   - **Monotonic Stack**: To efficiently compute left_gt array

## Solution

### Approach: Precomputation with Monotonic Stack

The solution uses two key precomputed arrays:

1. **left_min[i]**: Tracks the minimum value from the start up to index i
2. **left_gt[i]**: For each position i, stores the nearest left index where the value is greater than nums[i]

### Algorithm Steps:

**Step 1: Build Helper Arrays (Single Pass)**
```python
for i, val in enumerate(nums):
    # Track minimum value seen so far
    if val < cur_min:
        cur_min = val
    left_min[i] = cur_min
    
    # Use monotonic decreasing stack to find left greater element
    while st and nums[st[-1]] <= val:
        st.pop()
    if st:
        left_gt[i] = st[-1]
    st.append(i)
```

**Stack Logic**: The stack maintains indices in decreasing order of their values:
- Pop elements ≤ current value (they can't be the "3" for current element)
- Top of stack (if exists) is the nearest left element greater than current
- Push current index

**Step 2: Search for 132 Pattern**
```python
for i in range(2, n):
    if left_gt[i] != -1:
        pivot_3 = left_gt[i]  # This is our "3" position (j)
        # Check if there's a "1" before pivot_3 that's less than nums[i]
        if pivot_3 > 0 and left_min[pivot_3 - 1] < nums[i]:
            return True
```

### Example Walkthrough: nums = [3, 1, 4, 2]

**Building Arrays:**
```
Index:     0   1   2   3
nums:      3   1   4   2
left_min:  3   1   1   1
left_gt:  -1  -1   0   2
```

**Explanation:**
- i=0: min=3, stack=[0]
- i=1: min=1, pop 0 (3>1), stack=[1]
- i=2: min=1, stack=[1,2] (4>1, so left_gt[2]=1)
- i=3: min=1, pop 2 (4>2), left_gt[3]=1, stack=[1,3]

**Finding Pattern:**
- i=2: left_gt[2]=0, check left_min[0-1] → invalid (pivot_3=0)
- i=3: left_gt[3]=2 (pivot_3=2)
  - Check: left_min[2-1]=1 < nums[3]=2 ✓
  - Pattern found: [1, 4, 2] at indices [1, 2, 3]

### Complexity Analysis

- **Time Complexity**: O(n)
  - First loop: O(n) with amortized O(1) stack operations
  - Second loop: O(n)
- **Space Complexity**: O(n)
  - left_min array: O(n)
  - left_gt array: O(n)
  - Stack: O(n) worst case

### Why This Works

For a valid 132 pattern with positions (i, j, k):
- **Position k (the "2")**: We iterate through possible k values
- **Position j (the "3")**: left_gt[k] gives us the nearest left position with a larger value
- **Position i (the "1")**: left_min[j-1] gives us the minimum value before j
- If left_min[j-1] < nums[k], we have: left_min[j-1] < nums[k] < nums[j] → 132 pattern!

# Tags

`Array` `Stack` `Monotonic Stack` `Greedy` `Precomputation` `Medium`

