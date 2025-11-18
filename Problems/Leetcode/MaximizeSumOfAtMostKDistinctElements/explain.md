## Problem

https://leetcode.com/problems/maximize-sum-of-at-most-k-distinct-elements/description/

```
You are given a positive integer array nums and an integer k.

Choose at most k elements from nums so that their sum is maximized. However, the chosen numbers must be distinct.

Return an array containing the chosen numbers in strictly descending order.

Example 1:

Input: nums = [84,93,100,77,90], k = 3

Output: [100,93,90]

Explanation:

The maximum sum is 283, which is attained by choosing 93, 100 and 90. We rearrange them in strictly descending order as [100, 93, 90].

Example 2:

Input: nums = [84,93,100,77,93], k = 3

Output: [100,93,84]

Explanation:

The maximum sum is 277, which is attained by choosing 84, 93 and 100. We rearrange them in strictly descending order as [100, 93, 84]. We cannot choose 93, 100 and 93 because the chosen numbers must be distinct.

Example 3:

Input: nums = [1,1,1,2,2,2], k = 6

Output: [2,1]

Explanation:

The maximum sum is 3, which is attained by choosing 1 and 2. We rearrange them in strictly descending order as [2, 1].

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 109
1 <= k <= nums.length
```

## Observations

1. **Distinct Elements Requirement**: We can only choose distinct numbers from the array, meaning duplicates are not allowed in our selection.

2. **Maximize Sum**: To maximize the sum with distinct elements, we should choose the largest possible distinct values.

3. **At Most K Elements**: We need to choose at most k elements, not exactly k. If there are fewer than k distinct elements, we choose all of them.

4. **Output Format**: The result should be in strictly descending order.

5. **Key Insight**: Since we want to maximize the sum and can only use distinct elements, the optimal strategy is to:
   - Remove duplicates from the array
   - Sort the unique elements in descending order
   - Take the first k elements (or all if fewer than k exist)

## Solution

```python
class Solution:
    def maxKDistinct(self, nums: List[int], k: int) -> List[int]:
        return sorted(list(set(nums)), reverse=True)[0:k]
```

**Explanation:**

1. **`set(nums)`**: Creates a set from the input array, automatically removing all duplicate elements. This ensures we only work with distinct values.

2. **`list(set(nums))`**: Converts the set back to a list so we can perform sorting and indexing operations.

3. **`sorted(..., reverse=True)`**: Sorts the unique elements in descending order. This puts the largest elements first, which is exactly what we need to maximize the sum.

4. **`[0:k]`**: Takes the first k elements from the sorted list. If there are fewer than k distinct elements, this will simply return all available elements.

**Time Complexity:** O(n log n) where n is the length of nums
- Creating the set: O(n)
- Converting to list: O(n)  
- Sorting: O(n log n)
- Slicing: O(k)

**Space Complexity:** O(n) for storing the unique elements

**Example Walkthrough:**
- Input: `nums = [84,93,100,77,93], k = 3`
- After `set(nums)`: `{84, 93, 100, 77}` (duplicates removed)
- After `sorted(..., reverse=True)`: `[100, 93, 84, 77]`
- After `[0:3]`: `[100, 93, 84]`

This solution elegantly handles all the requirements in a single line by leveraging Python's built-in data structures and functions.

# Tags

**Array, Sorting, Hash Set, Greedy**

