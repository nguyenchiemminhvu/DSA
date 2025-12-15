## Problem

https://leetcode.com/problems/largest-time-for-given-digits/description/

```
Given an array arr of 4 digits, find the latest 24-hour time that can be made using each digit exactly once.

24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.

Return the latest 24-hour time in "HH:MM" format. If no valid time can be made, return an empty string.

Example 1:
Input: arr = [1,2,3,4]
Output: "23:41"
Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.

Example 2:
Input: arr = [5,5,5,5]
Output: ""
Explanation: There are no valid 24-hour times as "55:55" is not valid.

Constraints:
- arr.length == 4
- 0 <= arr[i] <= 9
```

## Observations

1. **Search Space**: We need to find the largest valid time from exactly 4 digits
   - Hours: 00-23 (24 possibilities)
   - Minutes: 00-59 (60 possibilities)
   - Each digit must be used exactly once

2. **Greedy Approach**: To find the latest time, we should:
   - Start from the largest possible hour (23) and work backwards
   - For each hour, start from the largest possible minute (59) and work backwards
   - Stop at the first valid combination found

3. **Digit Matching**: A time is valid if the frequency of digits in the time string matches the frequency of digits in the input array

4. **Edge Cases**:
   - No valid time possible (e.g., [5,5,5,5] - cannot form valid hours)
   - Multiple valid times possible - need to return the latest one
   - Duplicate digits in the array

## Solution

```python
from collections import Counter

class Solution:
    def largestTimeFromDigits(self, arr: List[int]) -> str:
        hours = [f"{val:02d}" for val in range(23, -1, -1)]
        minutes = [f"{val:02d}" for val in range(59, -1, -1)]

        f_arr = Counter(arr)
        for h in hours:
            for m in minutes:
                tmp = [int(c) for c in h + m]
                f_tmp = Counter(tmp)
                if f_tmp == f_arr:
                    return h + ":" + m
        return ""
```

### Algorithm Explanation

1. **Generate Candidate Times**:
   - Create list of hours from 23 down to 00 (descending order)
   - Create list of minutes from 59 down to 00 (descending order)
   - Format both with leading zeros using `f"{val:02d}"`

2. **Count Input Digits**:
   - Use `Counter(arr)` to get frequency map of input digits

3. **Iterate from Latest to Earliest**:
   - Outer loop: iterate hours from 23 to 00
   - Inner loop: iterate minutes from 59 to 00
   - This ensures we check times in descending order

4. **Match Digits**:
   - For each time candidate (h + m), convert to list of integers
   - Create Counter of these digits
   - Compare with input Counter
   - If they match exactly, we found the latest valid time

5. **Return Result**:
   - First match found is the latest time (due to descending iteration)
   - If no match found after all iterations, return empty string

### Time Complexity
- **O(24 × 60) = O(1440) = O(1)**: Fixed iterations regardless of input
- Creating Counter for each candidate: O(4) per candidate
- Overall: O(1) since the search space is constant

### Space Complexity
- **O(1)**: Fixed space for hours/minutes lists and Counter objects
- Hours list: 24 elements
- Minutes list: 60 elements
- Counter objects: at most 10 keys (digits 0-9)

### Why This Works
- By iterating from largest to smallest time, we guarantee the first match is the latest valid time
- Counter comparison ensures we use each digit exactly once
- Handles duplicate digits correctly (e.g., [1,1,2,3])

# Tags

#brute-force #greedy #string #hash-table #counter

