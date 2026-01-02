## Problem

https://leetcode.com/problems/maximum-width-ramp/description/

A **ramp** in an integer array `nums` is a pair `(i, j)` for which `i < j` and `nums[i] <= nums[j]`. The **width** of such a ramp is `j - i`.

Given an integer array `nums`, return the maximum width of a ramp in `nums`. If there is no ramp in `nums`, return 0.

**Example 1:**
```
Input: nums = [6,0,8,2,1,5]
Output: 4
Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
```

**Example 2:**
```
Input: nums = [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2] = 1 and nums[9] = 1.
```

**Constraints:**
- `2 <= nums.length <= 5 * 10^4`
- `0 <= nums[i] <= 5 * 10^4`

## Observations

1. **Brute Force Approach**: Check all pairs (i, j) where i < j and nums[i] <= nums[j], then find the maximum width. This would be O(n²) time complexity - not efficient for large arrays.

2. **Key Insight**: To maximize the width (j - i), we want:
   - `i` to be as **small** as possible (leftmost position)
   - `j` to be as **large** as possible (rightmost position)

3. **Decreasing Stack Pattern**: 
   - If we have indices where values are **strictly decreasing**, these are the only candidates for potential starting points (i) of maximum ramps
   - Why? If nums[a] > nums[b] and a < b, then any ramp starting at index `a` can also start at index `b` with a potentially larger width

4. **Two-Pass Strategy**:
   - **First pass (left to right)**: Build a stack of indices with strictly decreasing values
   - **Second pass (right to left)**: For each position j, try to match it with the leftmost possible i from our stack

5. **Why traverse backwards in second pass?**: 
   - We want to maximize j (rightmost position)
   - By going right to left, we ensure we're considering the largest possible j values first
   - Once we pop an index from the stack, we know we've found the best (rightmost) match for it

## Solution

### Approach: Monotonic Decreasing Stack

**Algorithm:**

1. **Build decreasing stack** (First Pass):
   - Traverse the array from left to right
   - Push index `i` onto stack if stack is empty OR `nums[i]` is strictly less than the value at the top of the stack
   - This creates a stack of indices where values are strictly decreasing

2. **Find maximum width** (Second Pass):
   - Traverse the array from right to left
   - For each index `j`:
     - While stack is not empty AND `nums[stack.top()] <= nums[j]`:
       - Calculate width: `j - stack.top()`
       - Update maximum width
       - Pop from stack (we've found the best match for this index)
   - Return the maximum width found

**Why this works:**
- The stack contains all potential left boundaries (i) in decreasing order
- For any j, we greedily match with the leftmost possible i (smallest index) that satisfies nums[i] <= nums[j]
- Since we traverse j from right to left, we ensure we're maximizing the right boundary
- Once we pop an index from the stack, we've found its optimal pair and don't need to consider it again

**Time Complexity:** O(n)
- First pass: O(n) to build the stack
- Second pass: O(n) - each element is pushed and popped at most once
- Overall: O(n)

**Space Complexity:** O(n)
- Stack can contain up to n indices in the worst case (strictly decreasing array)

**Implementation:**

```python
class Solution:
    def maxWidthRamp(self, nums: List[int]) -> int:
        n = len(nums)
        
        # Step 1: Build a decreasing stack of indices
        st = []
        for i in range(n):
            if not st or nums[st[-1]] > nums[i]:
                st.append(i)
        
        # Step 2: Traverse from right to left to find max width
        max_ramp = 0
        for i in range(n - 1, -1, -1):
            while st and nums[st[-1]] <= nums[i]:
                max_ramp = max(max_ramp, i - st[-1])
                st.pop()
        
        return max_ramp
```

**Example Walkthrough:**

For `nums = [6,0,8,2,1,5]`:

*Step 1: Build decreasing stack*
- i=0: stack=[], nums[0]=6 → push 0 → stack=[0]
- i=1: nums[1]=0 < nums[0]=6 → push 1 → stack=[0,1]
- i=2: nums[2]=8 >= nums[1]=0 → skip
- i=3: nums[3]=2 >= nums[1]=0 → skip
- i=4: nums[4]=1 >= nums[1]=0 → skip
- i=5: nums[5]=5 >= nums[1]=0 → skip
- Final stack: [0, 1] (indices with values [6, 0])

*Step 2: Find max width (right to left)*
- i=5: nums[5]=5, stack=[0,1]
  - nums[1]=0 <= 5 → width = 5-1=4, pop 1 → stack=[0]
  - nums[0]=6 > 5 → stop
  - max_ramp = 4
- i=4: nums[4]=1, stack=[0]
  - nums[0]=6 > 1 → stop
- i=3,2: similar, no updates
- i=1,0: stack already processed

Result: **4**

# Tags

`Array` `Stack` `Monotonic Stack` `Two Pointers` `Greedy`
