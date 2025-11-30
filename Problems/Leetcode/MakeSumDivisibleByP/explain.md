## Problem

https://leetcode.com/problems/make-sum-divisible-by-p/description/

```
Given an array of positive integers nums, remove the smallest subarray (possibly empty) 
such that the sum of the remaining elements is divisible by p. It is not allowed to remove 
the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

Example 1:
Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. 
We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.

Example 2:
Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. 
The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.

Example 3:
Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6, which is already divisible by 3. Thus we do not need to remove anything.

Constraints:
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^9
- 1 <= p <= 10^9
```

## Observations

1. **Key Insight**: We need to find the smallest subarray whose removal makes the remaining sum divisible by `p`.

2. **Modular Arithmetic**: If `total_sum % p = remainder`, we need to find a subarray with sum that also has `remainder` when divided by `p`. Removing this subarray will make the remaining sum divisible by `p`.

3. **Prefix Sum with HashMap**: We can use prefix sums combined with a hashmap to efficiently find subarrays with a specific modulo value.

4. **Mathematical Relationship**: 
   - Let `total_mod = total_sum % p` (the remainder we need to remove)
   - For any position `i` with `prefix_sum[i] % p = current_mod`
   - We need to find a previous position `j` where `prefix_sum[j] % p = (current_mod - total_mod) % p`
   - This ensures the subarray `[j+1, i]` has sum with modulo `total_mod`

5. **Edge Cases**:
   - If `total_sum % p == 0`, no removal needed (return 0)
   - If the only valid subarray is the entire array, return -1
   - Handle negative modulo values by adding `p`

## Solution

1. **Calculate Target Remainder**: 
   - Compute `total_mod = sum(nums) % p`
   - This is the remainder we need to eliminate
   - If already 0, return 0 (no removal needed)

2. **Initialize HashMap**:
   - Store `{prefix_mod: index}` mappings
   - Start with `{0: -1}` to handle subarrays starting from index 0

3. **Iterate Through Array**:
   - Maintain running `prefix` sum modulo `p`
   - Calculate `target_mod = (prefix - total_mod) % p`
   - This is the modulo value we need to find in our previous prefix sums
   
4. **Find Matching Prefix**:
   - If `target_mod` exists in hashmap at position `j`
   - Subarray from `j+1` to `i` has the exact remainder we need to remove
   - Update minimum length: `min(res, i - j)`

5. **Update HashMap**:
   - Store current `prefix` modulo at index `i`
   - This overwrites previous occurrences (we want the latest for minimum length)

6. **Return Result**:
   - If `res >= n`, we'd have to remove the entire array (invalid)
   - Otherwise return `res`

### Time Complexity: O(n)
- Single pass through the array
- HashMap operations are O(1) average

### Space Complexity: O(min(n, p))
- HashMap stores at most `n` entries
- But modulo values are bounded by `p`, so at most `min(n, p)` unique entries

### Why It Works:

The key mathematical insight is:
- `prefix_sum[i] = sum(nums[0...i])`
- `prefix_sum[j] = sum(nums[0...j])`
- `subarray_sum[j+1...i] = prefix_sum[i] - prefix_sum[j]`

For the remaining sum to be divisible by `p`:
- `(total_sum - subarray_sum) % p = 0`
- `(total_sum - (prefix_sum[i] - prefix_sum[j])) % p = 0`
- `(prefix_sum[j] - prefix_sum[i] + total_sum) % p = 0`
- `prefix_sum[j] % p = (prefix_sum[i] - total_sum) % p`
- `prefix_sum[j] % p = (prefix_sum[i] - total_mod) % p`

# Tags
#array #prefix-sum #hashmap #modular-arithmetic #subarray #medium

