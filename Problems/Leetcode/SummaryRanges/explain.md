## Problem

https://leetcode.com/problems/summary-ranges/

```
You are given a sorted unique integer array nums.

A range [a,b] is the set of all integers from a to b (inclusive).

Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.

Each range [a,b] in the list should be output as:

"a->b" if a != b
"a" if a == b

Example 1:

Input: nums = [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: The ranges are:
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"

Example 2:

Input: nums = [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: The ranges are:
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"

Constraints:

0 <= nums.length <= 20
-231 <= nums[i] <= 231 - 1
All the values of nums are unique.
nums is sorted in ascending order.
```

## Observations

The problem asks us to find consecutive ranges in a sorted array and represent them in a specific format:
- Single element ranges: `"a"` if `a == b`
- Multi-element ranges: `"a->b"` if `a != b`

Key insights:
1. **Array is already sorted**: We can traverse once from left to right
2. **Need to track range boundaries**: Keep track of the start (`left`) and current end (`right`) of each range
3. **Consecutive detection**: Two numbers are consecutive if `nums[i+1] == nums[i] + 1`
4. **Range completion**: When we find a non-consecutive number, the current range is complete

The main challenge is handling the **last range** - since we only detect range completion when we encounter a non-consecutive element, we need a way to process the final range.

## Solution

**Algorithm Overview:**
The solution uses a **two-pointer approach** with a clever sentinel value trick:

1. **Sentinel Addition**: Add `0xFFFFFFFF` (a very large number) to the end of the array to ensure the last range gets processed
2. **Range Tracking**: Use `left` and `right` pointers to track the current range boundaries
3. **Consecutive Check**: For each element, check if it extends the current range (`nums[i] == right + 1`)
4. **Range Completion**: When a gap is found, add the completed range to results and start a new range

**Step-by-step walkthrough:**
```python
nums = [0,1,2,4,5,7]
nums.append(0xFFFFFFFF)  # [0,1,2,4,5,7,4294967295]
left = 0, right = 0

i=1: nums[1]=1, right+1=1 → consecutive, right=1
i=2: nums[2]=2, right+1=2 → consecutive, right=2  
i=3: nums[3]=4, right+1=3 → gap! Add "0->2", left=4, right=4
i=4: nums[4]=5, right+1=5 → consecutive, right=5
i=5: nums[5]=7, right+1=6 → gap! Add "4->5", left=7, right=7  
i=6: nums[6]=4294967295, right+1=8 → gap! Add "7"
```

**Key Design Decisions:**
- **Sentinel value `0xFFFFFFFF`**: Ensures the final range gets processed without special case handling
- **Range format logic**: `left == right` → single element, otherwise → range format
- **In-place modification**: The algorithm modifies the input array by appending the sentinel

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - only uses constant extra space (excluding output array)

## Tags

array, string