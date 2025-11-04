## Problem

https://leetcode.com/problems/longest-continuous-increasing-subsequence/description/

```
Given an unsorted array of integers nums, return the length of the longest continuous increasing subsequence (i.e. subarray). The subsequence must be strictly increasing.

A continuous increasing subsequence is defined by two indices l and r (l < r) such that it is [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] and for each l <= i < r, nums[i] < nums[i + 1].

Example 1:

Input: nums = [1,3,5,4,7]
Output: 3
Explanation: The longest continuous increasing subsequence is [1,3,5] with length 3.
Even though [1,3,5,7] is an increasing subsequence, it is not continuous as elements 5 and 7 are separated by element
4.

Example 2:

Input: nums = [2,2,2,2,2]
Output: 1
Explanation: The longest continuous increasing subsequence is [2] with length 1. Note that it must be strictly
increasing.

Constraints:

1 <= nums.length <= 104
-109 <= nums[i] <= 109
```

## Observations

1. **Continuous vs Subsequence**: The problem asks for a **continuous** increasing subsequence, which means it must be a subarray (contiguous elements), not just any subsequence.

2. **Strictly Increasing**: Each element must be strictly greater than the previous one (nums[i] < nums[i+1]), so equal elements break the sequence.

3. **Single Pass Opportunity**: Since we only care about continuous sequences, we can solve this in a single pass by tracking the current sequence length.

4. **Dynamic Programming Pattern**: We can use the prefix array approach where `prefix[i]` represents the length of the longest continuous increasing subsequence ending at index `i`.

5. **Edge Cases**: 
   - Single element array: minimum length is 1
   - All equal elements: each has length 1
   - Strictly decreasing array: each element forms its own sequence of length 1

## Solution

### Approach: Dynamic Programming with Prefix Array

The solution uses a prefix array where `prefix[i]` stores the length of the longest continuous increasing subsequence ending at index `i`.

**Algorithm:**
1. Initialize `prefix` array with all 1's (each element forms a sequence of length 1)
2. Iterate from index 1 to n-1
3. If `nums[i] > nums[i-1]`, extend the previous sequence: `prefix[i] = prefix[i-1] + 1`
4. Otherwise, `prefix[i]` remains 1 (start new sequence)
5. Return the maximum value in the prefix array

**Example Walkthrough:**
```
nums = [1, 3, 5, 4, 7]

Initial: prefix = [1, 1, 1, 1, 1]

i=1: nums[1]=3 > nums[0]=1 → prefix[1] = prefix[0] + 1 = 2
     prefix = [1, 2, 1, 1, 1]

i=2: nums[2]=5 > nums[1]=3 → prefix[2] = prefix[1] + 1 = 3  
     prefix = [1, 2, 3, 1, 1]

i=3: nums[3]=4 < nums[2]=5 → prefix[3] remains 1
     prefix = [1, 2, 3, 1, 1]

i=4: nums[4]=7 > nums[3]=4 → prefix[4] = prefix[3] + 1 = 2
     prefix = [1, 2, 3, 1, 2]

Result: max(prefix) = 3
```

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(n) - for the prefix array

### Alternative O(1) Space Solution:
```python
def findLengthOfLCIS(self, nums: List[int]) -> int:
    max_length = current_length = 1
    
    for i in range(1, len(nums)):
        if nums[i] > nums[i-1]:
            current_length += 1
            max_length = max(max_length, current_length)
        else:
            current_length = 1
    
    return max_length
```

# Tags

- **Array**
- **Dynamic Programming** 
- **Sliding Window**
- **Two Pointers**

