## Problem

https://leetcode.com/problems/longest-alternating-subarray/description/

```
You are given a 0-indexed integer array nums. A subarray s of length m is called alternating if:

- m is greater than 1.
- s[1] = s[0] + 1.
- The 0-indexed subarray s looks like [s[0], s[1], s[0], s[1],...,s[(m-1) % 2]].
  In other words, s[1] - s[0] = 1, s[2] - s[1] = -1, s[3] - s[2] = 1, 
  s[4] - s[3] = -1, and so on up to s[m - 1] - s[m - 2] = (-1)^m.

Return the maximum length of all alternating subarrays present in nums 
or -1 if no such subarray exists.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:
Input: nums = [2,3,4,3,4]
Output: 4
Explanation: The alternating subarrays are [2,3], [3,4], [3,4,3], and [3,4,3,4].
The longest is [3,4,3,4] with length 4.

Example 2:
Input: nums = [4,5,6]
Output: 2
Explanation: [4,5] and [5,6] are the only two alternating subarrays, both with length 2.

Constraints:
- 2 <= nums.length <= 100
- 1 <= nums[i] <= 10^4
```

## Observations

1. **Pattern Recognition**: An alternating subarray must start with a difference of +1, then alternate between -1 and +1:
   - First difference: `nums[i+1] - nums[i] = +1`
   - Second difference: `nums[i+2] - nums[i+1] = -1`
   - Third difference: `nums[i+3] - nums[i+2] = +1`
   - And so on...

2. **Minimum Length**: Valid alternating subarrays must have length ≥ 2 (as stated in the problem)

3. **Greedy Approach**: We can check every possible starting position and extend as far as the alternating pattern holds

4. **Sign Flipping**: The difference alternates between +1 and -1, which we can track by multiplying the expected sign by -1 after each step

5. **Edge Cases**:
   - If no alternating subarray of length ≥ 2 exists, return -1
   - Arrays with only 2 elements need special consideration

## Solution

### Algorithm Overview

The solution uses a **brute force approach** with optimization:

1. Try every index as a potential starting point for an alternating subarray
2. For each starting point, check how far we can extend the alternating pattern
3. Keep track of the maximum length found
4. Return -1 if the maximum length is less than 2

### Helper Function: `check(start, sign)`

This function determines the length of an alternating subarray starting at index `start` with initial difference `sign`:

```python
def check(start: int, sign: int) -> int:
    count = 1  # Start with the first element
    for i in range(start + 1, n):
        if nums[i] - nums[i - 1] == sign:
            count += 1
        else:
            break  # Pattern broken, stop extending
        sign *= -1  # Flip the expected difference for next iteration
    return count
```

**Parameters:**
- `start`: Starting index of the subarray
- `sign`: Expected difference for the first step (+1 for alternating subarrays)

**Logic:**
- Starts with count = 1 (the starting element)
- Iterates through subsequent elements
- Checks if the difference matches the expected sign
- If yes, increments count and flips the sign for next iteration
- If no, breaks out of the loop
- Returns the total count

### Main Logic

```python
res = 0
for i in range(n):
    res = max(res, check(i, 1))
return -1 if res < 2 else res
```

- Tries every index as a starting point
- Calls `check(i, 1)` because all valid alternating subarrays must start with difference +1
- Keeps track of the maximum length found
- Returns -1 if no valid alternating subarray exists (length < 2)

### Time & Space Complexity

- **Time Complexity**: O(n²)
  - Outer loop: O(n) iterations
  - Inner loop (check function): O(n) in worst case
  - Overall: O(n × n) = O(n²)

- **Space Complexity**: O(1)
  - Only uses a few variables regardless of input size

### Example Walkthrough

For `nums = [2,3,4,3,4]`:

1. **Start at index 0 (value 2):**
   - Check difference: 3 - 2 = 1 ✓ (count = 2)
   - Check difference: 4 - 3 = 1 ✗ (expected -1)
   - Length = 2

2. **Start at index 1 (value 3):**
   - Check difference: 4 - 3 = 1 ✓ (count = 2)
   - Check difference: 3 - 4 = -1 ✓ (count = 3)
   - Check difference: 4 - 3 = 1 ✓ (count = 4)
   - Length = 4 ← Maximum!

3. **Start at index 2 (value 4):**
   - Check difference: 3 - 4 = -1 ✗ (expected 1)
   - Length = 1

4. **Start at index 3 (value 3):**
   - Check difference: 4 - 3 = 1 ✓ (count = 2)
   - Length = 2

5. **Start at index 4:** No elements after, length = 1

**Result:** Maximum length = 4

### Key Insights

- The solution ensures we only consider subarrays that start with difference +1 (as required)
- By checking every possible starting position, we guarantee finding the longest alternating subarray
- The sign-flipping mechanism elegantly handles the alternating pattern
- Early termination in the `check` function prevents unnecessary iterations

# Tags

#array #sliding-window #brute-force #pattern-matching

