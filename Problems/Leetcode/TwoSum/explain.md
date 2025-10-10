## Problem Description

https://leetcode.com/problems/two-sum/

```
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].

Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]

Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
```

## Observations

1. **Brute Force Approach**  
	- Try every possible pair of numbers.
	- For each pair, check if their sum equals `target`.
	- Time Complexity: $O(n^2)$ (slow for large arrays).

2. **Can We Do Better?**  
	- The problem asks for a solution faster than $O(n^2)$.
	- We need a way to check for pairs quickly.

3. **Using a Hash Map (Dictionary)**  
	- As we go through the array, we can remember the numbers we've seen so far.
	- For each number, check if `target - number` is already in our memory.
	- If yes, we found the pair!
	- If not, add the current number to our memory.

### Step-by-Step Solution

1. **Create an empty hash map** (dictionary) to store numbers and their indices.
2. **Loop through the array**:
	- For each number `num` at index `i`:
	  - Calculate `complement = target - num`.
	  - If `complement` is in the hash map:
		 - Return `[hash_map[complement], i]` (the indices).
	  - Otherwise, add `num` and its index to the hash map.
3. **Done!**  
	- This approach only needs one pass through the array.

### Example

Let’s walk through `nums = [2, 7, 11, 15], target = 9`:

- Start with an empty hash map: `{}`.
- Index 0, num = 2. Complement = 7. 7 not in map. Add 2: `{2: 0}`.
- Index 1, num = 7. Complement = 2. 2 is in map!  
  Return `[0, 1]`.

## Tags

array