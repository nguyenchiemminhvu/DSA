## Problem

https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description

Given an integer array `nums` sorted in non-decreasing order, remove duplicates in-place such that each unique element appears **at most twice**. The relative order of elements must be preserved.

### Key Constraints:
- **In-place modification**: Must modify the input array directly
- **O(1) extra space**: Only constant extra memory allowed
- **Array is sorted**: Elements are in non-decreasing order
- **Return value**: Return `k` where the first `k` elements contain the valid result
- **Size constraint**: 1 ≤ nums.length ≤ 3 × 10⁴

### Examples:

**Example 1:**
```
Input: nums = [1,1,1,2,2,3]
Output: k = 5, nums = [1,1,2,2,3,_]
Explanation: The first 5 elements are [1,1,2,2,3]
```

**Example 2:**
```
Input: nums = [0,0,1,1,1,1,2,3,3]
Output: k = 7, nums = [0,0,1,1,2,3,3,_,_]
Explanation: The first 7 elements are [0,0,1,1,2,3,3]
```

## Observations

1. **Sorted Array Property**: Since the array is sorted, duplicate elements are adjacent. This allows us to process elements sequentially.

2. **Two-Pointer Technique**: We need a pointer (`it`) to track where the next valid element should be placed, and another pointer (`i`) to iterate through the array.

3. **Counting Approach**: We need to track how many times each element has appeared. Once an element appears more than twice, we skip it.

4. **In-place Constraint**: We cannot use additional arrays, but can use a small constant-space structure (like a dictionary with bounded size since each element can only appear 0-2 times in the result).

5. **No Deletion**: We don't actually "delete" elements; we overwrite them at position `it`, shifting the valid elements forward.

## Solution

```python
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        it = 0  # pointer for placement position
        s = defaultdict(int)  # frequency map for counting occurrences
        
        for i, val in enumerate(nums):
            # Skip if this element has already appeared twice
            if s[val] > 1:
                continue
            
            # Place current element at position it
            nums[it] = nums[i]
            it += 1
            
            # Increment the count for this element
            s[val] += 1
        
        return it
```

### Algorithm Walkthrough:

**Example: nums = [1,1,1,2,2,3]**

| Iteration | i | val | s[val] | Action | nums | it |
|-----------|---|-----|--------|--------|------|-----|
| Start | - | - | - | - | [1,1,1,2,2,3] | 0 |
| 1 | 0 | 1 | 0 | Place nums[0] at it=0 | [1,1,1,2,2,3] | 1 |
| 2 | 1 | 1 | 1 | Place nums[1] at it=1 | [1,1,1,2,2,3] | 2 |
| 3 | 2 | 1 | 2 | Skip (s[1] > 1) | [1,1,1,2,2,3] | 2 |
| 4 | 3 | 2 | 0 | Place nums[3] at it=2 | [1,1,2,2,2,3] | 3 |
| 5 | 4 | 2 | 1 | Place nums[4] at it=3 | [1,1,2,2,2,3] | 4 |
| 6 | 5 | 3 | 0 | Place nums[5] at it=4 | [1,1,2,2,3,3] | 5 |

**Result: k = 5, nums = [1,1,2,2,3,...]**

### Complexity Analysis:

- **Time Complexity**: $O(n)$ - We iterate through the array once where $n$ is the length of `nums`
- **Space Complexity**: $O(1)$ amortized - The frequency map can store at most unique elements, but since each unique value only needs to track counts 0-2, it's bounded by the number of unique elements. However, in the worst case with many unique elements, this could be $O(n)$, which violates the strict O(1) requirement.

### ⚠️ Space Complexity Note:

The provided solution uses a `defaultdict`, which theoretically violates the O(1) space constraint if there are many unique elements. A truly O(1) space solution would use a **two-pointer approach without a frequency map**:

```python
class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        it = 1
        count = 1
        
        for i in range(1, len(nums)):
            if nums[i] == nums[i-1]:
                count += 1
            else:
                count = 1
            
            if count <= 2:
                nums[it] = nums[i]
                it += 1
        
        return it
```

This optimized version:
- Uses only two variables (`it` and `count`) → **True O(1) space**
- Compares with the previous element instead of using a dictionary
- Resets the counter when a new element is encountered

### Key Insights:

1. **Frequency Tracking**: We track how many times we've seen each element
2. **Conditional Placement**: Only place elements if they haven't appeared more than twice
3. **Two-Pointer Strategy**: Separation of read pointer (i) and write pointer (it) is crucial
4. **Sorted Property Usage**: Adjacency of duplicates makes counting efficient

# Tags
#two-pointers #in-place #array #sorting

