## Problem

https://leetcode.com/problems/next-greater-element-ii/description/

Given a **circular integer array** `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return the next greater number for every element in `nums`.

The **next greater number** of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1` for this number.

**Example 1:**
```
Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: 
- The first 1's next greater number is 2
- The number 2 can't find next greater number
- The second 1's next greater number needs to search circularly, which is also 2
```

**Example 2:**
```
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]
```

**Constraints:**
- `1 <= nums.length <= 10^4`
- `-10^9 <= nums[i] <= 10^9`

## Observations

1. **Circular Array Property**: Since the array is circular, after reaching the end, we need to continue searching from the beginning. This means for any element, we might need to look at all elements in the array (except itself).

2. **Next Greater Element Pattern**: This is a classic stack-based problem. The key insight is that we can use a monotonic stack to efficiently find the next greater element.

3. **Handling Circularity**: To handle the circular nature, we can simulate it by either:
   - Iterating through the array twice (using index modulo)
   - Duplicating the array (concatenating it with itself)

4. **Right-to-Left Traversal**: By traversing from right to left and maintaining a monotonic decreasing stack (storing indices), we can efficiently find the next greater element for each position.

5. **Stack Invariant**: The stack maintains indices of elements in decreasing order of their values. This ensures that the top of the stack is always a candidate for the next greater element.

## Solution

### Approach: Monotonic Stack with Array Duplication

**Time Complexity**: O(n) where n is the length of the array  
**Space Complexity**: O(n) for the stack and duplicated array

### Algorithm:

1. **Duplicate the Array**: Extend `nums` by concatenating it with itself. This simulates the circular property.
   ```
   [1,2,1] → [1,2,1,1,2,1]
   ```

2. **Initialize**:
   - Create a result array `next_gt` of size `2n` initialized with `-1`
   - Create an empty stack to store indices

3. **Traverse from Right to Left**:
   - For each element at index `i` from `nn-1` to `0`:
     - Pop all indices from the stack whose values are `<=` current value
     - If the stack is not empty, the element at `stack[-1]` is the next greater element
     - Push current index onto the stack

4. **Extract Result**: Return the first `n` elements from `next_gt` (corresponding to the original array).

### Why This Works:

- **Monotonic Stack**: By maintaining a stack where elements are in decreasing order of their values, we ensure that the first element we find that's greater than the current element is indeed the next greater element.

- **Right-to-Left Traversal**: This allows us to build up knowledge of elements to the right (and circularly, to the left) as we process each element.

- **Circular Handling**: By duplicating the array, an element at position `i` in the original array can "see" elements at positions `i+1, i+2, ..., n-1, 0, 1, ..., i-1` naturally.

### Code:

```python
class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        # Duplicate array to handle circular nature
        nums.extend(nums[:])
        nn = len(nums)
        next_gt = [-1] * nn
        st = []
        
        # Traverse from right to left
        for i in range(nn - 1, -1, -1):
            val = nums[i]
            
            # Pop elements that are not greater than current
            while st and nums[st[-1]] <= val:
                st.pop()
            
            # If stack is not empty, top element is next greater
            if st:
                next_gt[i] = nums[st[-1]]
            
            # Push current index onto stack
            st.append(i)
        
        # Return only first half (original array size)
        return next_gt[0:nn // 2]
```

### Example Walkthrough:

For `nums = [1,2,1]`, after duplication: `[1,2,1,1,2,1]`

```
Index:  5    4    3    2    1    0
Value:  1    2    1    1    2    1
Stack: [] → [5] → [4] → [4,3] → [4] → [1] → [1,0]

i=5: val=1, stack=[], next_gt[5]=-1, push 5 → stack=[5]
i=4: val=2, pop 5 (1<=2), stack=[], next_gt[4]=-1, push 4 → stack=[4]
i=3: val=1, stack=[4], next_gt[3]=nums[4]=2, push 3 → stack=[4,3]
i=2: val=1, stack=[4,3], next_gt[2]=nums[3]=1? No! Pop 3, next_gt[2]=nums[4]=2, push 2 → stack=[4,2]
i=1: val=2, pop 2 (1<=2), stack=[4], next_gt[1]=nums[4]=2? No! Pop 4, next_gt[1]=-1, push 1 → stack=[1]
i=0: val=1, stack=[1], next_gt[0]=nums[1]=2, push 0 → stack=[1,0]
```

Result: `next_gt[0:3] = [2,-1,2]` ✓

# Tags
`Array` `Stack` `Monotonic Stack` `Circular Array`

