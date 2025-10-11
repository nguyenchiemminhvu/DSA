## Problem

https://leetcode.com/problems/maximum-total-damage-with-spell-casting/

```
A magician has various spells.

You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.

It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.

Each spell can be cast only once.

Return the maximum possible total damage that a magician can cast.

Example 1:

Input: power = [1,1,3,4]

Output: 6

Explanation:

The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.

Example 2:

Input: power = [7,1,6,6]

Output: 13

Explanation:

The maximum possible damage of 13 is produced by casting spells 1, 2, 3 with damage 1, 6, 6.

Constraints:

1 <= power.length <= 105
1 <= power[i] <= 109
```

## Observations

1. **Constraint Analysis**: If we cast a spell with damage `x`, we cannot cast spells with damage `x-2, x-1, x+1, x+2`. This creates a "forbidden zone" of `±2` around each chosen spell.

2. **Frequency Matters**: Multiple spells can have the same damage value, and we can cast all spells with the same damage (since they don't conflict with each other).

3. **Greedy Won't Work**: We can't simply pick the highest damage spells because they might block many other valuable spells.

4. **DP Structure**: This is a classic "House Robber" variant where we need to decide whether to include each unique damage value or skip it.

5. **Sorting Helps**: By sorting unique damage values, we can use dynamic programming more efficiently and find the last valid previous state.

6. **State Definition**: For each unique damage value, we have two choices:
   - Skip it: Take the maximum damage from the previous index
   - Take it: Add all instances of this damage + maximum damage from the last valid previous index

## Solution

The solution uses **Dynamic Programming with Memoization** to solve this variant of the "House Robber" problem.

### Algorithm Steps:

1. **Frequency Mapping**: First, count the frequency of each damage value since we can cast all spells with the same damage.

2. **Sorting**: Sort unique damage values to enable efficient DP transition finding.

3. **DP State**: `F(i)` represents the maximum damage we can achieve using damage values from index 0 to i in the sorted array.

4. **Recurrence Relation**:
   ```
   F(i) = max(
       F(i-1),                    // Skip current damage
       current_damage * freq + F(j)  // Take current damage + best from valid previous
   )
   ```
   where `j` is the largest index such that `sorted_power[j] < sorted_power[i] - 2`

5. **Finding Valid Previous State**: For each damage value `x`, we need to find the rightmost damage value that's `< x - 2` (to avoid the forbidden zone).

### Key Optimizations:

- **Memoization**: Cache results to avoid recomputing subproblems
- **Frequency Counting**: Handle duplicate damages efficiently
- **Binary Search Alternative**: The solution uses linear search, but binary search could optimize finding the valid previous index

### Time Complexity: 
- O(n²) in worst case due to linear search for previous valid index
- Could be optimized to O(n log n) with binary search

### Space Complexity: 
- O(n) for memoization and frequency map

### Example Walkthrough:
For `power = [1,1,3,4]`:
- `freq = {1: 2, 3: 1, 4: 1}`
- `sorted_power = [1, 3, 4]`
- `F(2)` (damage `4`): `max(F(1), 4*1 + F(-1)) = max(3, 4) = 4`
- But we can also take damage `1`: `max(skip, 1*2 + F(-1)) = 2`
- Total: We can take damage `1` (freq=2) and damage `4` `(freq=1) = 2 + 4 = 6`

## Tags

array, hash table, dynamic programming