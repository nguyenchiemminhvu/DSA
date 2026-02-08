## Problem

https://leetcode.com/problems/count-dominant-indices/description/

```
Given an integer array nums of length n, an index i is dominant if
nums[i] is greater than the average of all elements to its right.
Return the count of dominant indices. The last element is never dominant.
```

## Observations

- For each index i, we need the average of nums[i+1..n-1].
- A running suffix sum lets us compute that average in O(1) per index.
- We can scan from right to left, keeping the sum of elements to the right
  and the count of those elements.

## Solution

Scan from right to left and maintain the sum of elements to the right.
For index i, the right subarray length is n - i - 1, so the average is
sum_right / (n - i - 1). If nums[i] is greater, increment the answer.
Then add nums[i] to sum_right and continue. Time is O(n), space is O(1).

```python
class Solution:
	def dominantIndices(self, nums: List[int]) -> int:
		n = len(nums)
		res = 0
		sum_right = nums[-1]
		for i in range(n - 2, -1, -1):
			if nums[i] > sum_right / (n - i - 1):
				res += 1
			sum_right += nums[i]
		return res
```

# Tags

- array
- prefix-sum
- math

