## Problem

https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/description/

```
Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.

An array A is a zigzag array if either:

Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
Return the minimum number of moves to transform the given array nums into a zigzag array.

Example 1:

Input: nums = [1,2,3]
Output: 2
Explanation: We can decrease 2 to 0 or 3 to 1.

Example 2:

Input: nums = [9,6,1,6,2]
Output: 4

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 1000
```

## Observations

1. **Two zigzag patterns possible**: There are exactly two ways to make a zigzag array:
   - Pattern A: Even indices are peaks (greater than neighbors): `A[0] > A[1] < A[2] > A[3] < A[4] > ...`
   - Pattern B: Odd indices are peaks (greater than neighbors): `A[0] < A[1] > A[2] < A[3] > A[4] < ...`

2. **Only decrease operations allowed**: We can only decrease elements by 1, never increase them. This means:
   - If an element needs to be a peak, we can't make it higher, so we must lower its neighbors
   - If an element needs to be a valley, we can lower it directly

3. **Greedy approach works**: For each pattern, we can independently calculate the minimum moves needed:
   - For peaks: neighbors must be decreased to be strictly less than the peak
   - For valleys: the element itself must be decreased to be strictly less than both neighbors

4. **Key insight**: Since we're trying to minimize moves and can only decrease, for each valley position:
   - We need to make `nums[i]` strictly less than both `nums[i-1]` and `nums[i+1]`
   - The optimal target is `min(left_neighbor, right_neighbor) - 1`
   - Moves needed = `max(0, nums[i] - min(left_neighbor, right_neighbor) + 1)`

## Solution

1. **`build_zigzag_up(start)`**: Calculates moves needed to make indices starting from `start` (with step 2) into valleys
   - `start = 0`: Makes even indices (0, 2, 4, ...) valleys → odd indices become peaks
   - `start = 1`: Makes odd indices (1, 3, 5, ...) valleys → even indices become peaks

2. **For each valley position `i`**:
   - Get left neighbor (`nums[i-1]`) and right neighbor (`nums[i+1]`)
   - Use `float('inf')` for boundary cases (no left/right neighbor)
   - Calculate minimum neighbor value: `min(left, right)`
   - To make `nums[i]` a valley, it must be `< min(left, right)`
   - Moves needed: `max(0, nums[i] - min(left, right) + 1)`

3. **Return minimum**: `min(build_zigzag_up(0), build_zigzag_up(1))`

**Example walkthrough** with `nums = [9,6,1,6,2]`:

- **Pattern A** (even indices as peaks): `build_zigzag_up(1)` makes indices 1,3 valleys
  - `i=1`: `nums[1]=6`, neighbors: `9,1` → need `6 < min(9,1) = 1` → moves: `max(0, 6-1+1) = 6`
  - `i=3`: `nums[3]=6`, neighbors: `1,2` → need `6 < min(1,2) = 1` → moves: `max(0, 6-1+1) = 6`
  - Total: 12 moves

- **Pattern B** (odd indices as peaks): `build_zigzag_up(0)` makes indices 0,2,4 valleys  
  - `i=0`: `nums[0]=9`, neighbors: `∞,6` → need `9 < 6` → moves: `max(0, 9-6+1) = 4`
  - `i=2`: `nums[2]=1`, neighbors: `6,6` → need `1 < 6` → already satisfied → moves: `0`
  - `i=4`: `nums[4]=2`, neighbors: `6,∞` → need `2 < 6` → already satisfied → moves: `0`
  - Total: 4 moves

- **Answer**: `min(12, 4) = 4`

**Time Complexity**: O(n) - single pass through array
**Space Complexity**: O(1) - only using constant extra space

## Tags

array, greedy