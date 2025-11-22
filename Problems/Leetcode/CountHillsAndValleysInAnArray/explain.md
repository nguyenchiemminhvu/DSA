## Problem

https://leetcode.com/problems/count-hills-and-valleys-in-an-array/description/

```
You are given a 0-indexed integer array nums. An index i is part of a hill in nums if the closest non-equal neighbors of i are smaller than nums[i]. Similarly, an index i is part of a valley in nums if the closest non-equal neighbors of i are larger than nums[i]. Adjacent indices i and j are part of the same hill or valley if nums[i] == nums[j].

Note that for an index to be part of a hill or valley, it must have a non-equal neighbor on both the left and right of the index.

Return the number of hills and valleys in nums.

Example 1:

Input: nums = [2,4,1,1,6,5]
Output: 3
Explanation:
At index 0: There is no non-equal neighbor of 2 on the left, so index 0 is neither a hill nor a valley.
At index 1: The closest non-equal neighbors of 4 are 2 and 1. Since 4 > 2 and 4 > 1, index 1 is a hill. 
At index 2: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 2 is a valley.
At index 3: The closest non-equal neighbors of 1 are 4 and 6. Since 1 < 4 and 1 < 6, index 3 is a valley, but note that it is part of the same valley as index 2.
At index 4: The closest non-equal neighbors of 6 are 1 and 5. Since 6 > 1 and 6 > 5, index 4 is a hill.
At index 5: There is no non-equal neighbor of 5 on the right, so index 5 is neither a hill nor a valley. 
There are 3 hills and valleys so we return 3.

Example 2:

Input: nums = [6,6,5,5,4,1]
Output: 0
Explanation:
At index 0: There is no non-equal neighbor of 6 on the left, so index 0 is neither a hill nor a valley.
At index 1: There is no non-equal neighbor of 6 on the left, so index 1 is neither a hill nor a valley.
At index 2: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4, index 2 is neither a hill nor a valley.
At index 3: The closest non-equal neighbors of 5 are 6 and 4. Since 5 < 6 and 5 > 4, index 3 is neither a hill nor a valley.
At index 4: The closest non-equal neighbors of 4 are 5 and 1. Since 4 < 5 and 4 > 1, index 4 is neither a hill nor a valley.
At index 5: There is no non-equal neighbor of 1 on the right, so index 5 is neither a hill nor a valley.
There are 0 hills and valleys so we return 0.

Constraints:

3 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Key insight**: Adjacent equal elements are part of the same hill or valley, so we need to remove consecutive duplicates first.

2. **Hill condition**: An element is a hill if both closest non-equal neighbors are smaller than it.
   - Pattern: `left < current > right`

3. **Valley condition**: An element is a valley if both closest non-equal neighbors are larger than it.
   - Pattern: `left > current < right`

4. **Edge cases**: 
   - First and last elements can never be hills or valleys (no neighbors on one side)
   - After removing duplicates, array length must be at least 3

5. **Example walkthrough** (nums = [2,4,1,1,6,5]):
   - After removing duplicates: [2,4,1,6,5]
   - Index 1 (value 4): 2 < 4 > 1 → Hill
   - Index 2 (value 1): 4 > 1 < 6 → Valley  
   - Index 3 (value 6): 1 < 6 > 5 → Hill
   - Total: 3 hills and valleys

## Solution

1. **Preprocessing**: Remove consecutive duplicates using two-pointer technique
   - Keep track of unique elements and overwrite the array in-place
   - Use sentinel value (max int) to handle first element comparison

2. **Main Logic**: Iterate through middle elements (indices 1 to n-2)
   - For each element, check if it forms a hill or valley with its neighbors
   - Hill: `nums[i-1] < nums[i] > nums[i+1]`
   - Valley: `nums[i-1] > nums[i] < nums[i+1]`

**Time Complexity**: O(n) - Single pass for deduplication + single pass for counting
**Space Complexity**: O(1) - In-place modification, no extra space needed

**Key Benefits of This Approach:**
- Handles the "same hill/valley" requirement by preprocessing
- Simple and clean logic after deduplication
- Efficient in-place operation

# Tags

array