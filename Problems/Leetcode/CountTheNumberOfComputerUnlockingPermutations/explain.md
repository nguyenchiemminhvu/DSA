## Problem

https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/description/

```
You are given an array complexity of length n.

There are n locked computers in a room with labels from 0 to n - 1, each with its own unique password. 
The password of the computer i has a complexity complexity[i].

The password for the computer labeled 0 is already decrypted and serves as the root. All other computers 
must be unlocked using it or another previously unlocked computer, following this information:

- You can decrypt the password for the computer i using the password for computer j, where j is any 
  integer less than i with a lower complexity. (i.e. j < i and complexity[j] < complexity[i])
- To decrypt the password for computer i, you must have already unlocked a computer j such that 
  j < i and complexity[j] < complexity[i].

Find the number of permutations of [0, 1, 2, ..., (n - 1)] that represent a valid order in which the 
computers can be unlocked, starting from computer 0 as the only initially unlocked one.

Since the answer may be large, return it modulo 10^9 + 7.

Example 1:
Input: complexity = [1,2,3]
Output: 2
Explanation:
The valid permutations are:
- [0, 1, 2]: Unlock 0 → 1 (complexity[0] < complexity[1]) → 2 (complexity[1] < complexity[2])
- [0, 2, 1]: Unlock 0 → 2 (complexity[0] < complexity[2]) → 1 (complexity[0] < complexity[1])

Example 2:
Input: complexity = [3,3,3,4,4,4]
Output: 0
Explanation: There are no possible permutations which can unlock all computers.

Constraints:
- 2 <= complexity.length <= 10^5
- 1 <= complexity[i] <= 10^9
```

## Observations

### Key Constraint Analysis

1. **Computer 0 Must Start**: Computer 0 is always unlocked first (the root)

2. **Ordering Constraint**: To unlock computer `i`, we need:
   - Some computer `j` where `j < i` (lower label)
   - `complexity[j] < complexity[i]` (lower complexity)
   - Computer `j` must already be unlocked

3. **Critical Insight**: For any computer `i > 0` to be unlockable at all:
   - There must exist at least one `j < i` with `complexity[j] < complexity[i]`
   - Since computer 0 is always unlocked first, if `complexity[0] < complexity[i]`, we can always unlock `i` (after unlocking 0)

4. **Impossibility Condition**: If ANY computer `i > 0` has `complexity[i] <= complexity[0]`:
   - We cannot unlock it because we need `complexity[j] < complexity[i]` where `j < i`
   - The only available computer before unlocking anything else is computer 0
   - If `complexity[0] >= complexity[i]`, there's no valid unlocking sequence
   - Result: **0 permutations**

5. **When All Computers Are Unlockable**: If `complexity[0] < complexity[i]` for all `i > 0`:
   - Computer 0 can unlock any other computer (since `0 < i` and `complexity[0] < complexity[i]`)
   - Once we have computers 0 and some other computer unlocked, we have more options
   - The key is counting valid orderings

### Counting Valid Permutations

When all computers can be unlocked (i.e., `complexity[0]` is minimum):

- **Position 0**: Must be computer 0 (given) — **1 choice**
- **Position 1**: Can be any of the remaining (n-1) computers — **(n-1) choices**
  - Any computer `i > 0` can be unlocked by computer 0
- **Position 2**: Can be any of the remaining (n-2) computers — **(n-2) choices**
  - At this point, we have computers 0 and one other unlocked
  - Any remaining computer can be unlocked by at least computer 0
- **Position k**: Can be any of the remaining (n-k) computers — **(n-k) choices**

The pattern shows that we can arrange the remaining (n-1) computers in any order after computer 0.

**Total permutations** = 1 × (n-1) × (n-2) × ... × 1 = **(n-1)!**

## Solution

1. **Check Feasibility**: 
   - Find minimum complexity among computers 1 to n-1
   - If `min(complexity[1:]) <= complexity[0]`, return 0
   - This ensures all computers can be unlocked by computer 0

2. **Calculate Factorial**:
   - If feasible, answer is `(n-1)!`
   - Compute `1 × 2 × 3 × ... × (n-1)` with modulo arithmetic
   - Use modulo at each step to prevent overflow

### Complexity Analysis

- **Time Complexity**: O(n)
  - O(n) to find minimum in `arr[1:]`
  - O(n) to calculate factorial
  - Total: O(n)

- **Space Complexity**: O(1)
  - Only using constant extra space for variables

### Why This Works

The solution leverages the fact that if `complexity[0]` is the minimum:
- Computer 0 acts as a universal unlocker for all other computers
- Once we have 2 or more computers unlocked, we have even more flexibility
- The constraint `j < i` in the problem refers to **computer labels**, not positions in the permutation
- After placing computer 0 first, we can arrange the remaining computers in any order because:
  - At any step, we have at least computer 0 unlocked (which can unlock any remaining computer)
  - The label constraint is automatically satisfied in the permutation

# Tags
`#math` `#combinatorics` `#factorial` `#greedy` `#array`

