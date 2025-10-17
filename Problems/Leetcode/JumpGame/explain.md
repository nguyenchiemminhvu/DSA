## Problem

https://leetcode.com/problems/jump-game/

```
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:

Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:

Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

Constraints:

1 <= nums.length <= 104
0 <= nums[i] <= 105
```

## Observations

1. **Problem Understanding**: We need to determine if we can reach the last index starting from index 0, where each element represents the maximum jump length from that position.

2. **Key Insight**: Instead of thinking forward (from start to end), we can think backward (from end to start). If we can reach the last index, then we need to find if there's a path from index 0 to the last index.

3. **Greedy Approach**: We can use a greedy strategy working backwards:
   - Start from the last index as our target
   - For each position going backwards, check if we can reach the current target
   - If yes, update the target to this closer position
   - Continue until we reach the beginning

4. **Why Greedy Works**: If we can reach position `i` from position `j` (where `j < i`), and we can reach the target from position `i`, then we can definitely reach the target from position `j`. So we always want to find the leftmost position that can reach our current target.

5. **Edge Cases**:
   - Single element array: Always true (already at target)
   - Array with zeros: A zero at any position (except last) might block the path

## Solution

1. **Initialize**: Set `target` to the last index (`n-1`)

2. **Iterate Backwards**: From `n-2` down to `0`:
   - Check if position `i` can reach the current `target`
   - Condition: `target - i <= nums[i]` means the distance to target is within jump range
   - If true, update `target = i` (we found a closer position that can reach the original target)

3. **Final Check**: Return `target <= 0`, which means we can reach index 0 (or even before it)

**Example Walkthrough**:

For `nums = [2,3,1,1,4]`:
- `target = 4` (last index)
- `i = 3`: Can position 3 reach 4? `4-3 = 1 <= nums[3] = 1` ✓ → `target = 3`
- `i = 2`: Can position 2 reach 3? `3-2 = 1 <= nums[2] = 1` ✓ → `target = 2`  
- `i = 1`: Can position 1 reach 2? `2-1 = 1 <= nums[1] = 3` ✓ → `target = 1`
- `i = 0`: Can position 0 reach 1? `1-0 = 1 <= nums[0] = 2` ✓ → `target = 0`
- Return `target <= 0` → `0 <= 0` → `True`

For `nums = [3,2,1,0,4]`:
- `target = 4`
- `i = 3`: Can position 3 reach 4? `4-3 = 1 <= nums[3] = 0` ✗ → `target = 4`
- `i = 2`: Can position 2 reach 4? `4-2 = 2 <= nums[2] = 1` ✗ → `target = 4`
- `i = 1`: Can position 1 reach 4? `4-1 = 3 <= nums[1] = 2` ✗ → `target = 4`
- `i = 0`: Can position 0 reach 4? `4-0 = 4 <= nums[0] = 3` ✗ → `target = 4`
- Return `target <= 0` → `4 <= 0` → `False`

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Alternative Approaches**:
1. **Forward Greedy**: Track the farthest reachable position
2. **Dynamic Programming**: Use memoization (less efficient)
3. **BFS/DFS**: Explore all possible paths (inefficient)

## Tags

array, greedy