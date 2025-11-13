## Problem

https://leetcode.com/problems/last-visited-integers/description/

```
Given an integer array nums where nums[i] is either a positive integer or -1. We need to find for each -1 the respective positive integer, which we call the last visited integer.

To achieve this goal, let's define two empty arrays: seen and ans.

Start iterating from the beginning of the array nums.

If a positive integer is encountered, prepend it to the front of seen.
If -1 is encountered, let k be the number of consecutive -1s seen so far (including the current -1),
If k is less than or equal to the length of seen, append the k-th element of seen to ans.
If k is strictly greater than the length of seen, append -1 to ans.
Return the array ans.

Example 1:

Input: nums = [1,2,-1,-1,-1]

Output: [2,1,-1]

Explanation:

Start with seen = [] and ans = [].

Process nums[0]: The first element in nums is 1. We prepend it to the front of seen. Now, seen == [1].
Process nums[1]: The next element is 2. We prepend it to the front of seen. Now, seen == [2, 1].
Process nums[2]: The next element is -1. This is the first occurrence of -1, so k == 1. We look for the first element in seen. We append 2 to ans. Now, ans == [2].
Process nums[3]: Another -1. This is the second consecutive -1, so k == 2. The second element in seen is 1, so we append 1 to ans. Now, ans == [2, 1].
Process nums[4]: Another -1, the third in a row, making k = 3. However, seen only has two elements ([2, 1]). Since k is greater than the number of elements in seen, we append -1 to ans. Finally, ans == [2, 1, -1].

Example 2:

Input: nums = [1,-1,2,-1,-1]

Output: [1,2,1]

Explanation:

Start with seen = [] and ans = [].

Process nums[0]: The first element in nums is 1. We prepend it to the front of seen. Now, seen == [1].
Process nums[1]: The next element is -1. This is the first occurrence of -1, so k == 1. We look for the first element in seen, which is 1. Append 1 to ans. Now, ans == [1].
Process nums[2]: The next element is 2. Prepend this to the front of seen. Now, seen == [2, 1].
Process nums[3]: The next element is -1. This -1 is not consecutive to the first -1 since 2 was in between. Thus, k resets to 1. The first element in seen is 2, so append 2 to ans. Now, ans == [1, 2].
Process nums[4]: Another -1. This is consecutive to the previous -1, so k == 2. The second element in seen is 1, append 1 to ans. Finally, ans == [1, 2, 1].

Constraints:

1 <= nums.length <= 100
nums[i] == -1 or 1 <= nums[i] <= 100
```

## Observations

1. **Two main operations**: We need to handle positive integers and -1s differently
   - Positive integers: Add to the front of a "seen" collection
   - -1s: Retrieve the k-th element from "seen" where k is the consecutive count of -1s

2. **Data structure choice**: We need efficient prepending and indexed access
   - Deque allows O(1) prepending with `appendleft()`
   - Deque allows O(1) indexed access for small indices

3. **State tracking**: We need to track consecutive -1s
   - Reset counter when we encounter a positive number
   - Increment counter for each consecutive -1

4. **Edge cases**: 
   - When consecutive -1 count exceeds the length of seen array, return -1
   - The "seen" array grows as we encounter more positive integers

5. **Key insight**: The problem asks for k-th element where k starts from 1, but array indexing starts from 0, so we use `neg_idx` which starts from 0 and gets incremented after each -1.

## Solution

1. **Initialize**: 
   - `q` (deque): Stores positive integers in reverse chronological order (most recent first)
   - `ans`: Result array
   - `neg_idx`: Counter for consecutive -1s (0-indexed)

2. **For each element in nums**:
   - **If positive**: Add to front of deque using `appendleft()`, reset `neg_idx` to 0
   - **If -1**: 
     - Check if `neg_idx < len(q)` (enough elements in seen)
     - If yes: append `q[neg_idx]` to answer
     - If no: append -1 to answer
     - Increment `neg_idx`

**Time Complexity**: O(n) where n is the length of nums
**Space Complexity**: O(k) where k is the number of unique positive integers

**Why deque works perfectly**:
- `appendleft()` is O(1) for adding new positive integers to the front
- Index access `q[i]` is O(1) for small indices (which is our case)
- The deque maintains the order where `q[0]` is the most recent, `q[1]` is second most recent, etc.

# Tags

- Array
- Deque
- Simulation
- Two Pointers

