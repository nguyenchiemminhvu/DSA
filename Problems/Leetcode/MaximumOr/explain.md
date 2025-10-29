## Problem

https://leetcode.com/problems/maximum-or/

```
You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you can choose an element and multiply it by 2.

Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained after applying the operation on nums at most k times.

Note that a | b denotes the bitwise or between two integers a and b.

Example 1:

Input: nums = [12,9], k = 1
Output: 30
Explanation: If we apply the operation to index 1, our new array nums will be equal to [12,18]. Thus, we return the bitwise or of 12 and 18, which is 30.

Example 2:

Input: nums = [8,1,2], k = 2
Output: 35
Explanation: If we apply the operation twice on index 0, we yield a new array of [32,1,2]. Thus, we return 32|1|2 = 35.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= 15
```

## Observations

1. **Operation Effect**: Multiplying by 2 is equivalent to left-shifting bits by 1 position (`nums[i] * 2 = nums[i] << 1`)
2. **Key Insight**: To maximize the OR result, we should apply all k operations to a single element rather than distributing them across multiple elements
   - This is because OR operation preserves all set bits, and concentrating operations creates higher-order bits
   - `nums[i] * 2^k = nums[i] << k` gives us the maximum possible contribution from element i
3. **Greedy Strategy**: For each element, calculate what the total OR would be if we apply all k operations to that element
4. **Efficient Calculation**: Use prefix and suffix OR arrays to avoid recalculating the OR of all other elements repeatedly

## Solution

**Algorithm:**
1. **Precompute Prefix OR**: `prefix[i+1]` stores OR of elements `nums[0]` to `nums[i]`
2. **Precompute Suffix OR**: `suffix[i]` stores OR of elements `nums[i]` to `nums[n-1]`
3. **Try Each Element**: For each element `nums[i]`:
   - Calculate OR of all other elements: `prefix[i] | suffix[i+1]`
   - Apply all k operations to current element: `nums[i] << k`
   - Calculate total OR: `others | (nums[i] << k)`
4. **Return Maximum**: Track and return the maximum OR value achieved

**Time Complexity**: O(n) - Single pass to build prefix/suffix arrays, single pass to try each element
**Space Complexity**: O(n) - For prefix and suffix arrays

**Why This Works:**
- The OR operation is monotonic (adding more set bits never decreases the result)
- Applying all operations to one element maximizes the highest-order bits
- Prefix/suffix arrays let us efficiently compute OR of "all elements except current one"

**Example Walkthrough** (nums = [8,1,2], k = 2):
- Try element 8: others = 1|2 = 3, enhanced = 8<<2 = 32, total = 3|32 = 35
- Try element 1: others = 8|2 = 10, enhanced = 1<<2 = 4, total = 10|4 = 14  
- Try element 2: others = 8|1 = 9, enhanced = 2<<2 = 8, total = 9|8 = 9
- Maximum = 35

## Tags

array, bit manipulation, greedy