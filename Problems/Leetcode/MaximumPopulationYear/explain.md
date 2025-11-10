## Problem

https://leetcode.com/problems/maximum-population-year/

```
You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.

The population of some year x is the number of people alive during that year. The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the person is not counted in the year that they die.

Return the earliest year with the maximum population.

Example 1:

Input: logs = [[1993,1999],[2000,2010]]
Output: 1993
Explanation: The maximum population is 1, and 1993 is the earliest year with this population.

Example 2:

Input: logs = [[1950,1961],[1960,1971],[1970,1981]]
Output: 1960
Explanation: 
The maximum population is 2, and it had happened in years 1960 and 1970.
The earlier year between them is 1960.

Constraints:

1 <= logs.length <= 100
1950 <= birthi < deathi <= 2050
```

## Observations

1. **Range of Years**: The problem is constrained to years 1950-2050, which gives us a manageable range of only 101 years.

2. **Population Counting**: A person contributes to the population from their birth year (inclusive) until their death year (exclusive). This means if someone is born in 1993 and dies in 1999, they are alive during years 1993, 1994, 1995, 1996, 1997, 1998.

3. **Event-based Approach**: Each person's life can be viewed as two events:
   - Birth year: population increases by 1
   - Death year: population decreases by 1

4. **Prefix Sum Pattern**: This is a classic "range update" problem that can be efficiently solved using difference arrays and prefix sums.

5. **Early Year Priority**: If multiple years have the same maximum population, we need to return the earliest year.

## Solution

The solution uses a **difference array** combined with **prefix sum** technique:

### Algorithm Steps:

1. **Initialize Difference Array**: Create an array `prefix` of size 105 (2050-1950+5 for safety) to represent years 1950-2054.

2. **Mark Events**: For each person's log [birth, death]:
   - Increment `prefix[birth - 1950]` (population increases at birth)
   - Decrement `prefix[death - 1950]` (population decreases at death)

3. **Calculate Actual Population**: Convert the difference array to actual population counts using prefix sum:
   ```python
   for i in range(1, len(prefix)):
       prefix[i] += prefix[i - 1]
   ```

4. **Find Maximum**: Find the maximum population and return the earliest year with that population.

### Why This Works:

- **Difference Array**: Instead of updating ranges [birth, death-1] for each person (which would be O(n²)), we mark only the start and end points.
- **Prefix Sum**: Transforms the difference array into actual population counts in O(n) time.
- **Time Complexity**: O(n + k) where n is number of people and k is the year range (≤ 101).
- **Space Complexity**: O(k) for the difference array.

### Example Walkthrough:
For `logs = [[1993,1999],[2000,2010]]`:
1. After marking events: `prefix[43] = 1, prefix[49] = -1, prefix[50] = 1, prefix[60] = -1`
2. After prefix sum: Years 1993-1998 have population 1, year 1999 has 0, years 2000-2009 have 1
3. Maximum population is 1, earliest year is 1993

# Tags

- Array
- Prefix Sum
- Difference Array
- Simulation

