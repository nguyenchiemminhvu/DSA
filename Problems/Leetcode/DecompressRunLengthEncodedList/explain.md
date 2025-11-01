## Problem

https://leetcode.com/problems/decompress-run-length-encoded-list/

```
We are given a list nums of integers representing a list compressed with run-length encoding.

Consider each adjacent pair of elements [freq, val] = [nums[2*i], nums[2*i+1]] (with i >= 0).  For each such pair, there are freq elements with value val concatenated in a sublist. Concatenate all the sublists from left to right to generate the decompressed list.

Return the decompressed list.

Example 1:

Input: nums = [1,2,3,4]
Output: [2,4,4,4]
Explanation: The first pair [1,2] means we have freq = 1 and val = 2 so we generate the array [2].
The second pair [3,4] means we have freq = 3 and val = 4 so we generate [4,4,4].
At the end the concatenation [2] + [4,4,4] is [2,4,4,4].

Example 2:

Input: nums = [1,1,2,3]
Output: [1,3,3]

Constraints:

2 <= nums.length <= 100
nums.length % 2 == 0
1 <= nums[i] <= 100
```

## Observations

1. **Run-Length Encoding Pattern**: The input array follows a specific pattern where every pair of adjacent elements `[nums[2*i], nums[2*i+1]]` represents `[frequency, value]`.

2. **Array Structure**: 
   - The array length is always even (guaranteed by constraints)
   - Elements at even indices (0, 2, 4, ...) represent frequencies
   - Elements at odd indices (1, 3, 5, ...) represent values to repeat

3. **Processing Pattern**: We need to iterate through the array with a step of 2 to process each frequency-value pair.

4. **Output Construction**: For each pair, we append `frequency` number of `value` elements to our result.

5. **Edge Cases**: The constraints guarantee valid input, so no need to handle empty arrays or odd-length arrays.

## Solution

1. **Initialize**: Create an empty result list `res` to store the decompressed elements.

2. **Iterate through pairs**: Use `range(0, n, 2)` to iterate through even indices (0, 2, 4, ...).
   - `i` represents the index of the frequency
   - `i + 1` represents the index of the value

3. **Extract frequency and value**: 
   - `nums[i]` is the frequency (how many times to repeat)
   - `nums[i + 1]` is the value to repeat

4. **Generate repeated elements**: Use list multiplication `[nums[i + 1]] * nums[i]` to create a list with the value repeated frequency times.

5. **Extend result**: Use `extend()` to add all elements from the repeated list to the result.

**Time Complexity**: O(k) where k is the sum of all frequencies (total number of elements in the output)
**Space Complexity**: O(k) for the result array

**Example Walkthrough:**
- Input: `[1,2,3,4]`
- i=0: frequency=1, value=2 → add [2] → res=[2]
- i=2: frequency=3, value=4 → add [4,4,4] → res=[2,4,4,4]
- Output: `[2,4,4,4]`

## Tags

- Array
- Simulation
- Run-Length Encoding

