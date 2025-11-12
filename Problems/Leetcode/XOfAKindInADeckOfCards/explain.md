## Problem

https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/

```
You are given an integer array deck where deck[i] represents the number written on the ith card.

Partition the cards into one or more groups such that:

Each group has exactly x cards where x > 1, and
All the cards in one group have the same integer written on them.
Return true if such partition is possible, or false otherwise.

Example 1:

Input: deck = [1,2,3,4,4,3,2,1]
Output: true
Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].

Example 2:

Input: deck = [1,1,1,2,2,2,3,3]
Output: false
Explanation: No possible partition.

Constraints:

1 <= deck.length <= 104
0 <= deck[i] < 104
```

## Observations

1. **Problem Requirements**:
   - We need to partition cards into groups where each group has exactly `x` cards (x > 1)
   - All cards in a group must have the same number
   - We need to find if such a partition is possible

2. **Key Insight**: 
   - For a valid partition to exist, the group size `x` must divide evenly into the count of each unique card
   - If card value `i` appears `count[i]` times, then `count[i] % x == 0` for all `i`

3. **Mathematical Approach**:
   - We need to find the largest possible `x > 1` that divides all counts
   - This is equivalent to finding the Greatest Common Divisor (GCD) of all counts
   - If GCD > 1, then we can partition with group size = GCD

4. **Example Analysis**:
   - `deck = [1,2,3,4,4,3,2,1]`: counts = [2,2,2,2], GCD = 2 → valid (x=2)
   - `deck = [1,1,1,2,2,2,3,3]`: counts = [3,3,2], GCD = 1 → invalid

## Solution

1. **Count Frequencies**: Use `Counter` to count occurrences of each card value
2. **Initialize GCD**: Start with the count of the first unique card
3. **Calculate GCD**: Iteratively compute GCD of current result with each count
4. **Check Validity**: Return `True` if final GCD > 1, `False` otherwise

**Why GCD Works**:
- If all counts share a common divisor `d > 1`, we can form groups of size `d`
- The GCD gives us the largest such divisor
- If GCD = 1, no common divisor > 1 exists, so no valid partition is possible

**Time Complexity**: O(n + k×log(max_count)) where n = deck size, k = unique cards  
**Space Complexity**: O(k) for the counter

# Tags

- Hash Table
- Math
- Number Theory
- Greatest Common Divisor (GCD)

