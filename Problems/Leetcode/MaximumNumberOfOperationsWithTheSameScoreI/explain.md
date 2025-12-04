## Problem

https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/description/

You are given an array of integers `nums`. Consider the following operation:

- Delete the **first two elements** of `nums` and define the **score** of the operation as the sum of these two elements.

You can perform this operation until `nums` contains fewer than two elements. Additionally, the **same score** must be achieved in all operations.

Return the **maximum number of operations** you can perform.

**Example 1:**
```
Input: nums = [3,2,1,4,5]
Output: 2

Explanation:
- Operation 1: Remove 3 and 2, score = 3 + 2 = 5. nums = [1,4,5]
- Operation 2: Remove 1 and 4, score = 1 + 4 = 5. nums = [5]
- Cannot perform more operations (fewer than 2 elements)
```

**Example 2:**
```
Input: nums = [1,5,3,3,4,1,3,2,2,3]
Output: 2

Explanation:
- Operation 1: Remove 1 and 5, score = 1 + 5 = 6. nums = [3,3,4,1,3,2,2,3]
- Operation 2: Remove 3 and 3, score = 3 + 3 = 6. nums = [4,1,3,2,2,3]
- Cannot continue: 4 + 1 = 5 ≠ 6 (different from previous score)
```

**Example 3:**
```
Input: nums = [5,3]
Output: 1
```

**Constraints:**
- `2 <= nums.length <= 100`
- `1 <= nums[i] <= 1000`

## Observations

1. **Key Operation**: We always delete the first two elements, not any arbitrary pair
2. **Score Requirement**: The score (sum of first two elements) must remain constant across all operations
3. **Stopping Condition**: We stop when either:
   - Less than 2 elements remain, OR
   - The next pair's sum differs from the reference score
4. **Reference Score**: The first operation's score becomes the reference for all subsequent operations
5. **Greedy Approach**: We perform operations sequentially from the start until we can't continue

## Solution

### Approach: Simulation

The problem is straightforward - simulate the operation process:
1. Set the reference score as the sum of the first two elements
2. Keep removing the first two elements as long as their sum equals the reference score
3. Count the number of successful operations

### Algorithm

**Time Complexity: O(n)**
- We iterate through the array at most n/2 times (removing 2 elements each iteration)
- Each pop() operation is O(1) since we pop from the end
- Overall: O(n)

**Space Complexity: O(1)**
- We modify the input array in-place
- Only use a constant amount of extra space for variables

### Why Reverse?

The solution reverses the array to make `pop()` operations efficient:
- **Without reverse**: Removing from the front requires shifting all elements → O(n) per removal
- **With reverse**: Pop from the end is O(1)
- Trade-off: O(n) reversal once vs O(n²) total for all removals

### Alternative Approach (Index-based)

If modifying the input is not desired:

```python
class Solution:
    def maxOperations(self, nums: List[int]) -> int:
        ref = nums[0] + nums[1]  # Reference score
        count = 0
        i = 0
        
        while i + 1 < len(nums):
            if nums[i] + nums[i + 1] != ref:
                break
            count += 1
            i += 2  # Move to next pair
        
        return count
```

**Complexity:**
- Time: O(n)
- Space: O(1)
- Advantage: No modification of input array

# Tags

`Array` `Simulation` `Greedy`

