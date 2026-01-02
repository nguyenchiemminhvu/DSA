# Minimum Deletions To Make Array Beautiful

## Problem

https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/description/

You are given a 0-indexed integer array `nums`. The array `nums` is **beautiful** if:
- `nums.length` is even.
- `nums[i] != nums[i + 1]` for all `i % 2 == 0`.

Note that an empty array is considered beautiful.

You can delete any number of elements from `nums`. When you delete an element, all the elements to the right of the deleted element will be shifted one unit to the left to fill the gap created and all the elements to the left of the deleted element will remain unchanged.

Return the minimum number of elements to delete from `nums` to make it beautiful.

### Examples

**Example 1:**
```
Input: nums = [1,1,2,3,5]
Output: 1
Explanation: You can delete either nums[0] or nums[1] to make nums = [1,2,3,5] which is beautiful. 
It can be proven you need at least 1 deletion to make nums beautiful.
```

**Example 2:**
```
Input: nums = [1,1,2,2,3,3]
Output: 2
Explanation: You can delete nums[0] and nums[5] to make nums = [1,2,2,3] which is beautiful. 
It can be proven you need at least 2 deletions to make nums beautiful.
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^5`

---

## Observations

1. **Beautiful Array Requirements:**
   - The array must have an even length
   - Adjacent pairs at even indices must have different values: `nums[0] != nums[1]`, `nums[2] != nums[3]`, `nums[4] != nums[5]`, etc.

2. **Key Insight:**
   - We can think of this as building a valid array by processing elements one by one
   - At even positions (0, 2, 4, ...), we can always add an element
   - At odd positions (1, 3, 5, ...), we can only add an element if it's different from the previous element

3. **Greedy Approach:**
   - Try to keep as many elements as possible while maintaining the beautiful property
   - Skip elements that would violate the beautiful property
   - If the final array has odd length, remove one more element

4. **Stack-based Simulation:**
   - Use a stack to simulate building the beautiful array
   - The stack length tells us the position we're trying to fill
   - Even positions: always accept the element
   - Odd positions: only accept if different from the previous element

---

## Solution

### Algorithm

The solution uses a **greedy approach with a stack** to simulate building the beautiful array:

```python
class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        n = len(nums)
        st = []
        for val in nums:
            if not st or len(st) % 2 == 0:
                st.append(val)
            else:
                if st[-1] != val:
                    st.append(val)
        if len(st) & 1:
            st.pop()
        return n - len(st)
```

### Step-by-Step Breakdown

1. **Initialize:**
   - `n = len(nums)`: Store the original array length
   - `st = []`: Create an empty stack to build the beautiful array

2. **Process Each Element:**
   ```python
   for val in nums:
       if not st or len(st) % 2 == 0:
           st.append(val)
   ```
   - If the stack is empty OR has even length, we're at an even position (0, 2, 4, ...)
   - Always add the element (even positions can have any value)

   ```python
   else:
       if st[-1] != val:
           st.append(val)
   ```
   - If the stack has odd length, we're at an odd position (1, 3, 5, ...)
   - Only add the element if it's different from the previous element
   - Otherwise, skip it (implicitly delete it)

3. **Handle Odd Length:**
   ```python
   if len(st) & 1:
       st.pop()
   ```
   - If the final stack has odd length, remove one element to make it even
   - `len(st) & 1` is equivalent to `len(st) % 2 == 1`

4. **Return Result:**
   ```python
   return n - len(st)
   ```
   - The minimum deletions = original length - final beautiful array length

### Example Walkthrough

**Example 1: nums = [1,1,2,3,5]**

| Step | val | st length | Position | Action | st after |
|------|-----|-----------|----------|--------|----------|
| 1 | 1 | 0 | even (0) | Add | [1] |
| 2 | 1 | 1 | odd (1) | 1 == 1, Skip | [1] |
| 3 | 2 | 1 | odd (1) | 1 != 2, Add | [1,2] |
| 4 | 3 | 2 | even (2) | Add | [1,2,3] |
| 5 | 5 | 3 | odd (3) | 3 != 5, Add | [1,2,3,5] |

- Final stack length: 4 (even, no adjustment needed)
- Result: 5 - 4 = **1 deletion**

**Example 2: nums = [1,1,2,2,3,3]**

| Step | val | st length | Position | Action | st after |
|------|-----|-----------|----------|--------|----------|
| 1 | 1 | 0 | even (0) | Add | [1] |
| 2 | 1 | 1 | odd (1) | 1 == 1, Skip | [1] |
| 3 | 2 | 1 | odd (1) | 1 != 2, Add | [1,2] |
| 4 | 2 | 2 | even (2) | Add | [1,2,2] |
| 5 | 3 | 3 | odd (3) | 2 != 3, Add | [1,2,2,3] |
| 6 | 3 | 4 | even (4) | Add | [1,2,2,3,3] |

- Final stack length: 5 (odd, pop one element) → 4
- Result: 6 - 4 = **2 deletions**

### Complexity Analysis

**Time Complexity: O(n)**
- Single pass through the array
- Each element is processed once
- Stack operations (append, pop) are O(1)

**Space Complexity: O(n)**
- Stack can store up to n elements in the worst case
- Could be optimized to O(1) by just tracking the count instead of building the actual array

### Optimized Space Solution

We can reduce space complexity to O(1) by just counting elements instead of building the array:

```python
class Solution:
    def minDeletion(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        prev = -1
        
        for val in nums:
            if count % 2 == 0:
                prev = val
                count += 1
            else:
                if prev != val:
                    prev = val
                    count += 1
        
        if count & 1:
            count -= 1
        
        return n - count
```

This achieves the same result with O(1) space complexity.

---

# Tags

`Array` `Greedy` `Stack` `Two Pointers`

