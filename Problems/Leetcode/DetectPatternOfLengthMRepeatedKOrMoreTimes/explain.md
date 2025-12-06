## Problem

https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/description/

```
Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.

A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.

Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false.

Example 1:
Input: arr = [1,2,4,4,4,4], m = 1, k = 3
Output: true
Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.

Example 2:
Input: arr = [1,2,1,2,1,1,1,3], m = 2, k = 2
Output: true
Explanation: The pattern (1,2) of length 2 is repeated 2 consecutive times. Another valid pattern (2,1) is also repeated 2 times.

Example 3:
Input: arr = [1,2,1,2,1,3], m = 2, k = 3
Output: false
Explanation: The pattern (1,2) is of length 2 but is repeated only 2 times. There is no pattern of length 2 that is repeated 3 or more times.

Constraints:
- 2 <= arr.length <= 100
- 1 <= arr[i] <= 100
- 1 <= m <= 100
- 2 <= k <= 100
```

## Observations

1. **Pattern Definition**: We need to find a subarray of length `m` that repeats consecutively `k` times (or more).

2. **Search Space**: We need to check all possible starting positions in the array. Since the pattern has length `m` and must repeat `k` times, we need at least `m * k` elements from position `i`.

3. **Boundary Condition**: The last valid starting position is `n - m * k` (where `n` is the array length), because we need `m * k` elements to form `k` repetitions of a pattern of length `m`.

4. **Pattern Matching**: For each starting position `i`, we extract a pattern of length `m` and check if it repeats `k` times consecutively.

5. **Array Slicing Trick**: Python's list multiplication (`list * k`) creates a list repeated `k` times, which is perfect for comparing against the actual subarray.

## Solution

1. **Iterate through possible starting positions**: `for i in range(n - m + 1)`
   - We iterate up to `n - m + 1` to ensure we can always extract at least one pattern of length `m`
   - This gives us every possible position where a pattern could start

2. **Create the expected pattern**: `sub = arr[i:i+m] * k`
   - Extract a subarray of length `m` starting at position `i`
   - Multiply it by `k` to create what the pattern should look like if it repeats `k` times
   - Example: If `arr[i:i+m] = [1,2]` and `k = 3`, then `sub = [1,2,1,2,1,2]`

3. **Compare with actual subarray**: `if arr[i:i + m * k] == sub`
   - Extract the actual subarray from position `i` with length `m * k`
   - Compare it with our expected pattern
   - If they match, we've found a pattern that repeats `k` times consecutively

4. **Return result**: Return `True` if found, otherwise `False` after checking all positions

**Time Complexity**: O(n × m × k)
- We iterate through `n` positions
- For each position, we create and compare subarrays of length `m × k`
- Array slicing and comparison take O(m × k) time

**Space Complexity**: O(m × k)
- We create temporary subarrays of size `m × k` for comparison

**Example Walkthrough** (arr = [1,2,4,4,4,4], m = 1, k = 3):

- i = 0: sub = [1] * 3 = [1,1,1], arr[0:3] = [1,2,4] ❌
- i = 1: sub = [2] * 3 = [2,2,2], arr[1:4] = [2,4,4] ❌
- i = 2: sub = [4] * 3 = [4,4,4], arr[2:5] = [4,4,4] ✅ **Return True**

# Tags

`Array` `Sliding Window` `Pattern Matching` `String Matching`

