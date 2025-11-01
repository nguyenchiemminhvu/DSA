## Problem

https://leetcode.com/problems/sum-of-variable-length-subarrays/

```
You are given an integer array nums of size n. For each index i where 0 <= i < n, define a subarray nums[start ... i] where start = max(0, i - nums[i]).

Return the total sum of all elements from the subarray defined for each index in the array.

Example 1:

Input: nums = [2,3,1]

Output: 11

Explanation:

i	Subarray	Sum
0	nums[0] = [2]	2
1	nums[0 ... 1] = [2, 3]	5
2	nums[1 ... 2] = [3, 1]	4
Total Sum	 	11
The total sum is 11. Hence, 11 is the output.

Example 2:

Input: nums = [3,1,1,2]

Output: 13

Explanation:

i	Subarray	Sum
0	nums[0] = [3]	3
1	nums[0 ... 1] = [3, 1]	4
2	nums[1 ... 2] = [1, 1]	2
3	nums[1 ... 3] = [1, 1, 2]	4
Total Sum	 	13
The total sum is 13. Hence, 13 is the output.

Constraints:

1 <= n == nums.length <= 100
1 <= nums[i] <= 1000
```

## Observations

1. **Variable Length Subarrays**: For each index `i`, we need to consider a subarray that ends at index `i` and starts at `max(0, i - nums[i])`. This means:
   - If `nums[i]` is large enough, the subarray starts from index `i - nums[i]`
   - If `i - nums[i] < 0`, the subarray starts from index `0` (beginning of array)

2. **Pattern Analysis**: Looking at the examples:
   - Index 0: Always uses subarray `[0...0]` since `max(0, 0 - nums[0]) = 0`
   - Index 1: Uses subarray starting from `max(0, 1 - nums[1])`
   - The length of each subarray is determined by the value at that index

3. **Efficient Computation**: Instead of calculating each subarray sum individually (which would be O(n²)), we can use prefix sums to calculate any subarray sum in O(1) time.

4. **Prefix Sum Application**: If we have prefix sums, then `sum(nums[start...end]) = prefix[end+1] - prefix[start]`

## Solution

1. **Build Prefix Sum Array**: 
   - Create `prefix` array where `prefix[i]` represents sum of elements from index 0 to i-1
   - `prefix[0] = 0`, `prefix[1] = nums[0]`, `prefix[2] = nums[0] + nums[1]`, etc.

2. **Calculate Each Subarray Sum**:
   - For each index `i`, determine the start position: `start = max(0, i - nums[i])`
   - The subarray is `nums[start...i]`
   - Using prefix sums: `sum(nums[start...i]) = prefix[i+1] - prefix[start]`

3. **Accumulate Results**: Add each subarray sum to the total result

**Time Complexity**: O(n) - single pass to build prefix array + single pass to calculate sums  
**Space Complexity**: O(n) - for the prefix sum array

**Example Walkthrough** (nums = [2,3,1]):
- Prefix array: [0, 2, 5, 6]
- i=0: start=max(0,0-2)=0, sum=prefix[1]-prefix[0]=2-0=2
- i=1: start=max(0,1-3)=0, sum=prefix[2]-prefix[0]=5-0=5  
- i=2: start=max(0,2-1)=1, sum=prefix[3]-prefix[1]=6-2=4
- Total: 2+5+4=11

## Tags

- Array
- Prefix Sum
- Mathematical
- Medium

