## Problem

https://leetcode.com/problems/distribute-candies/description/

```
Alice has n candies, where the ith candy is of type candyType[i]. Alice noticed that she started to gain weight, so she visited a doctor.

The doctor advised Alice to only eat n / 2 of the candies she has (n is always even). Alice likes her candies very much, and she wants to eat the maximum number of different types of candies while still following the doctor's advice.

Given the integer array candyType of length n, return the maximum number of different types of candies she can eat if she only eats n / 2 of them.

Example 1:

Input: candyType = [1,1,2,2,3,3]
Output: 3
Explanation: Alice can only eat 6 / 2 = 3 candies. Since there are only 3 types, she can eat one of each type.

Example 2:

Input: candyType = [1,1,2,3]
Output: 2
Explanation: Alice can only eat 4 / 2 = 2 candies. Whether she eats types [1,2], [1,3], or [2,3], she still can only eat 2 different types.

Example 3:

Input: candyType = [6,6,6,6]
Output: 1
Explanation: Alice can only eat 4 / 2 = 2 candies. Even though she can eat 2 candies, she only has 1 type.

Constraints:

n == candyType.length
2 <= n <= 104
n is even.
-105 <= candyType[i] <= 105
```

## Observations

1. **Constraint Analysis**: Alice can only eat `n/2` candies where `n` is the total number of candies.

2. **Goal**: Maximize the number of different candy types she can eat within the limit.

3. **Key Insight**: The maximum number of different types Alice can eat is limited by two factors:
   - The eating limit: `n/2` candies
   - The variety available: number of unique candy types

4. **Optimal Strategy**: Alice should eat at most one candy of each type to maximize variety, until she reaches her eating limit.

5. **Edge Cases**:
   - If unique types ≤ n/2: She can eat one of each type
   - If unique types > n/2: She's limited by her eating capacity

## Solution

The solution uses a **frequency counting + greedy approach**:

### Algorithm Steps:
1. **Count unique types**: Use a dictionary/map to count frequency of each candy type
2. **Calculate eating limit**: `threshold = n // 2`
3. **Apply constraint**: Return `min(threshold, number_of_unique_types)`

### Time & Space Complexity:
- **Time**: O(n) - single pass through the array
- **Space**: O(k) where k is the number of unique candy types (at most n)

### Example Analysis:
- `[1,1,2,2,3,3]`: 3 unique types, limit = 3 → min(3,3) = 3
- `[1,1,2,3]`: 3 unique types, limit = 2 → min(2,3) = 2  
- `[6,6,6,6]`: 1 unique type, limit = 2 → min(2,1) = 1

# Tags

`Hash Table` `Greedy` `Array` `Counting`

