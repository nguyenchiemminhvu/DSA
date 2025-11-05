## Problem

https://leetcode.com/problems/distribute-candies-to-people/description/

```
We distribute some number of candies, to a row of n = num_people people in the following way:

We then give 1 candy to the first person, 2 candies to the second person, and so on until we give n candies to the last person.

Then, we go back to the start of the row, giving n + 1 candies to the first person, n + 2 candies to the second person, and so on until we give 2 * n candies to the last person.

This process repeats (with us giving one more candy each time, and moving to the start of the row after we reach the end) until we run out of candies.  The last person will receive all of our remaining candies (not necessarily one more than the previous gift).

Return an array (of length num_people and sum candies) that represents the final distribution of candies.

Example 1:

Input: candies = 7, num_people = 4
Output: [1,2,3,1]
Explanation:
On the first turn, ans[0] += 1, and the array is [1,0,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0,0].
On the third turn, ans[2] += 3, and the array is [1,2,3,0].
On the fourth turn, ans[3] += 1 (because there is only one candy left), and the final array is [1,2,3,1].

Example 2:

Input: candies = 10, num_people = 3
Output: [5,2,3]
Explanation: 
On the first turn, ans[0] += 1, and the array is [1,0,0].
On the second turn, ans[1] += 2, and the array is [1,2,0].
On the third turn, ans[2] += 3, and the array is [1,2,3].
On the fourth turn, ans[0] += 4, and the final array is [5,2,3].

Constraints:

1 <= candies <= 10^9
1 <= num_people <= 1000
```

## Observations

1. **Distribution Pattern**: We give candies in increasing amounts: 1, 2, 3, 4, ... until we run out.

2. **Cyclic Distribution**: After reaching the last person, we wrap around to the first person and continue with the next increment.

3. **Sequential Process**: 
   - Person 0 gets: 1, n+1, 2n+1, 3n+1, ... candies in each round
   - Person 1 gets: 2, n+2, 2n+2, 3n+2, ... candies in each round
   - Person i gets: i+1, n+i+1, 2n+i+1, 3n+i+1, ... candies in each round

4. **Final Distribution**: The last person to receive candies gets all remaining candies, even if it's less than the expected increment.

5. **Key Variables**:
   - `ir`: Current person index (cycles from 0 to n-1)
   - `cur`: Current number of candies to give (increments each turn)
   - `total`: Total candies distributed so far

## Solution

The solution uses a **simulation approach** to distribute candies step by step:

### Algorithm Steps:

1. **Initialize**:
   - `res`: Result array to track candies for each person
   - `ir = 0`: Index of current person (starts with first person)
   - `cur = 1`: Current candy amount to distribute
   - `total = 0`: Total candies distributed so far

2. **Main Loop** (`while total < candies`):
   - Use `ir %= n` to ensure cyclic distribution (wrap around after last person)
   - **Check if we can give full amount**: If `total + cur >= candies`
     - Give remaining candies: `res[ir] += (candies - total)`
     - Break the loop (we're done)
   - **Otherwise, give full amount**:
     - Add current amount: `res[ir] += cur`
     - Update total: `total += cur`
     - Increment for next turn: `cur += 1`
   - Move to next person: `ir += 1`

3. **Return** the final distribution array

### Example Walkthrough:
For `candies = 7, num_people = 4`:

| Turn | Person (ir) | Give (cur) | Person gets | Total distributed | Array state |
|------|-------------|------------|-------------|-------------------|-------------|
| 1    | 0           | 1          | 1           | 1                 | [1,0,0,0]   |
| 2    | 1           | 2          | 2           | 3                 | [1,2,0,0]   |
| 3    | 2           | 3          | 3           | 6                 | [1,2,3,0]   |
| 4    | 3           | 4          | 1 (remaining)| 7                | [1,2,3,1]   |

### Time & Space Complexity:
- **Time**: O(√candies) - We distribute candies in increasing amounts, so the number of iterations is roughly √(2×candies)
- **Space**: O(n) - For the result array

# Tags

simulation, array, math

