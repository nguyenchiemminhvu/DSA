## Problem

https://leetcode.com/problems/find-if-digit-game-can-be-won/

```
You are given an array of positive integers nums.

Alice and Bob are playing a game. In the game, Alice can choose either all single-digit numbers or all double-digit numbers from nums, and the rest of the numbers are given to Bob. Alice wins if the sum of her numbers is strictly greater than the sum of Bob's numbers.

Return true if Alice can win this game, otherwise, return false.

Example 1:

Input: nums = [1,2,3,4,10]

Output: false

Explanation:

Alice cannot win by choosing either single-digit or double-digit numbers.

Example 2:

Input: nums = [1,2,3,4,5,14]

Output: true

Explanation:

Alice can win by choosing single-digit numbers which have a sum equal to 15.

Example 3:

Input: nums = [5,5,5,25]

Output: true

Explanation:

Alice can win by choosing double-digit numbers which have a sum equal to 25.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 99
```

## Observations

1. **Game Rules**: Alice can choose either ALL single-digit numbers (1-9) OR ALL double-digit numbers (10-99) from the array. Bob gets the remaining numbers.

2. **Win Condition**: Alice wins if her sum is strictly greater than Bob's sum.

3. **Key Insight**: Since Alice gets to choose which category (single or double digits), she will pick whichever gives her the maximum advantage.

4. **Mathematical Analysis**: 
   - Let `single_sum` = sum of all single-digit numbers
   - Let `double_sum` = sum of all double-digit numbers  
   - Let `total_sum` = `single_sum + double_sum`
   
   If Alice chooses single digits:
   - Alice gets: `single_sum`
   - Bob gets: `double_sum = total_sum - single_sum`
   - Alice wins if: `single_sum > total_sum - single_sum`
   - This simplifies to: `single_sum > total_sum/2`
   
   If Alice chooses double digits:
   - Alice gets: `double_sum`  
   - Bob gets: `single_sum = total_sum - double_sum`
   - Alice wins if: `double_sum > total_sum - double_sum`
   - This simplifies to: `double_sum > total_sum/2`

5. **Crucial Observation**: Alice can win if and only if `single_sum ≠ double_sum`. 
   - If `single_sum > double_sum`, Alice chooses single digits
   - If `double_sum > single_sum`, Alice chooses double digits
   - If `single_sum = double_sum`, then both equal `total_sum/2`, so Alice cannot get strictly more than Bob

## Solution

1. **Partition the array**: Iterate through all numbers and separate them into:
   - `a`: Sum of single-digit numbers (< 10)
   - `b`: Sum of double-digit numbers (≥ 10)

2. **Apply the key insight**: Alice can win if and only if the two sums are different (`a != b`)

3. **Why this works**:
   - If `a > b`: Alice chooses single digits, gets sum `a`, Bob gets sum `b`. Alice wins since `a > b`.
   - If `b > a`: Alice chooses double digits, gets sum `b`, Bob gets sum `a`. Alice wins since `b > a`.
   - If `a = b`: No matter what Alice chooses, she gets the same sum as Bob, so she cannot win (needs strictly greater).

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using two variables to store sums

**Example Walkthrough**:
- `nums = [1,2,3,4,10]`
- Single digits: 1+2+3+4 = 10, Double digits: 10
- Since 10 = 10, Alice cannot win → `false`

- `nums = [1,2,3,4,5,14]`  
- Single digits: 1+2+3+4+5 = 15, Double digits: 14
- Since 15 ≠ 14, Alice can win (chooses single digits) → `true`

# Tags

- Array
- Math
- Game Theory
- Greedy

