## Problem

https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/description/

```
You are given an integer array nums. You need to ensure that the elements in the array are distinct. To achieve this, you can perform the following operation any number of times:

Remove 3 elements from the beginning of the array. If the array has fewer than 3 elements, remove all remaining elements.
Note that an empty array is considered to have distinct elements. Return the minimum number of operations needed to make the elements in the array distinct.

Example 1:

Input: nums = [1,2,3,4,2,3,3,5,7]

Output: 2

Explanation:

In the first operation, the first 3 elements are removed, resulting in the array [4, 2, 3, 3, 5, 7].
In the second operation, the next 3 elements are removed, resulting in the array [3, 5, 7], which has distinct elements.
Therefore, the answer is 2.

Example 2:

Input: nums = [4,5,6,4,4]

Output: 2

Explanation:

In the first operation, the first 3 elements are removed, resulting in the array [4, 4].
In the second operation, all remaining elements are removed, resulting in an empty array.
Therefore, the answer is 2.

Example 3:

Input: nums = [6,7,8,9]

Output: 0

Explanation:

The array already contains distinct elements. Therefore, the answer is 0.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Goal**: We need to make all elements in the array distinct by removing elements from the beginning of the array, 3 at a time.

2. **Operation Rules**: 
   - Each operation removes exactly 3 elements from the beginning
   - If fewer than 3 elements remain, remove all remaining elements
   - An empty array is considered to have distinct elements

3. **Key Strategy**: We need to find the minimum number of operations to eliminate all duplicates.

4. **Frequency Tracking**: We can use a frequency counter to track how many times each element appears in the array.

5. **Greedy Approach**: We simulate the operations by:
   - Checking if any element has frequency ≥ 2 (indicating duplicates)
   - If duplicates exist, remove 3 elements from the beginning
   - Continue until all elements are distinct

6. **Termination Condition**: The process stops when no element appears more than once (all frequencies < 2).

## Solution

**Algorithm Explanation:**

The solution uses a simulation approach with frequency tracking:

1. **Initialize Frequency Counter**: Use `Counter(nums)` to track the frequency of each element in the array.

2. **Check for Duplicates**: The condition `any(v >= 2 for k, v in f.items())` checks if any element appears 2 or more times.

3. **Simulate Operations**: While duplicates exist:
   - Remove up to 3 elements from the beginning of the array (indices `i`, `i+1`, `i+2`)
   - Decrement their frequencies in the counter
   - Move the pointer `i` by 3 positions
   - Increment the operation count

4. **Boundary Handling**: The loop `for offset in range(3)` with condition `if i + offset < n` ensures we don't go out of bounds when fewer than 3 elements remain.

**Time Complexity**: O(n) where n is the length of the array
- We process each element at most once during the simulation
- The frequency counter operations are O(1) on average

**Space Complexity**: O(n) for the frequency counter

**Example Walkthrough** with `nums = [1,2,3,4,2,3,3,5,7]`:

- Initial frequencies: {1:1, 2:2, 3:3, 4:1, 5:1, 7:1}
- Duplicates exist (2 appears 2 times, 3 appears 3 times)
- **Operation 1**: Remove [1,2,3], frequencies become {1:0, 2:1, 3:2, 4:1, 5:1, 7:1}
- Still have duplicates (3 appears 2 times)
- **Operation 2**: Remove [4,2,3], frequencies become {1:0, 2:0, 3:1, 4:0, 5:1, 7:1}
- No more duplicates, array becomes [3,5,7] which has distinct elements
- **Result**: 2 operations

# Tags

Array, Hash Table, Simulation, Greedy

