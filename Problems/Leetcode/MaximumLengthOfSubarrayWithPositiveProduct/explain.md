## Problem

https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/

```
Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.

A subarray of an array is a consecutive sequence of zero or more values taken out of that array.

Return the maximum length of a subarray with positive product.

Example 1:

Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.

Example 2:

Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.

Example 3:

Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
```

## Observations

1. **Product Rules**: 
   - A product is positive when we have an even number of negative values
   - A product is zero when any element is zero
   - A product is negative when we have an odd number of negative values

2. **Zero as Separator**: 
   - Zeros effectively split the array into independent chunks
   - Each chunk between zeros needs to be analyzed separately
   - We cannot include zeros in our subarray since that makes the product 0 (not positive)

3. **Handling Negative Numbers**:
   - If a chunk has an even number of negative values, the entire chunk has positive product
   - If a chunk has an odd number of negative values, we need to exclude one negative number to make the product positive
   - To maximize length, we should exclude either the first negative or the last negative number

4. **Key Insight**: 
   - For chunks with odd number of negatives, we have two options:
     - Take elements from start up to (but not including) the last negative
     - Take elements from (after) the first negative to the end
   - We choose the option that gives us maximum length

## Solution

The solution uses a two-step approach:

### Step 1: Split by Zeros
```python
def split_list_by_zeros(arr: List[int]) -> List[List[int]]:
    chunks = []
    chunk = []
    for val in nums:
        if val == 0:
            if chunk:
                chunks.append(chunk)
            chunk = []
        else:
            chunk.append(val)
    if chunk:
        chunks.append(chunk)
    return chunks
```

This function splits the input array into chunks separated by zeros. Each chunk contains only non-zero elements.

### Step 2: Find Maximum Length in Each Chunk
```python
def get_max_len_in_chunk(arr: List[int]) -> int:
    d = [] # index of negative values
    for i, val in enumerate(arr):
        if val < 0:
            d.append(i)
    if len(d) % 2 == 0:
        return len(arr)
    
    sub_left = d[-1]
    sub_right = len(arr) - d[0] - 1
    return max(sub_left, sub_right)
```

For each chunk:
1. **Track negative indices**: Store positions of all negative numbers
2. **Even negatives case**: If we have even number of negatives, entire chunk has positive product
3. **Odd negatives case**: If we have odd number of negatives, we must exclude one negative:
   - `sub_left = d[-1]`: Length from start to (before) last negative
   - `sub_right = len(arr) - d[0] - 1`: Length from (after) first negative to end
   - Return the maximum of these two options

### Algorithm Flow:
1. Split array into chunks separated by zeros
2. For each chunk, find the maximum length subarray with positive product
3. Return the overall maximum

### Time Complexity: O(n)
- Single pass to split by zeros
- Single pass through each element to find negatives
- Total: O(n)

### Space Complexity: O(k)
- Where k is the number of negative numbers (for storing indices)
- In worst case: O(n)

## Tags

array, greedy