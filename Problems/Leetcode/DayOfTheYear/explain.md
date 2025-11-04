## Problem

https://leetcode.com/problems/day-of-the-year/description/

```
Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.

Example 1:

Input: date = "2019-01-09"
Output: 9
Explanation: Given date is the 9th day of the year in 2019.

Example 2:

Input: date = "2019-02-10"
Output: 41

Constraints:

date.length == 10
date[4] == date[7] == '-', and all other date[i]'s are digits
date represents a calendar date between Jan 1st, 1900 and Dec 31st, 2019.
```

## Observations

1. **Input Format**: The date is given as a string in "YYYY-MM-DD" format, so we need to parse it to extract year, month, and day components.

2. **Goal**: Find the day number of the year (1-366 depending on leap years).

3. **Approach Options**:
   - **Manual calculation**: Create arrays for days in each month, handle leap years manually
   - **Built-in date library**: Use Python's `datetime` module to handle date arithmetic automatically

4. **Key Insights**:
   - The day of the year is essentially the difference between the given date and January 1st of the same year, plus 1
   - Python's `date` objects support subtraction, returning a `timedelta` object
   - The `timedelta.days` attribute gives us the number of days difference

## Solution

The provided solution uses Python's built-in `date` class for elegant date arithmetic:

```python
from datetime import date

class Solution:
    def dayOfYear(self, date: str) -> int:
        # Parse the date string to extract components
        y = int(date[0:4])  # Year: characters 0-3
        m = int(date[5:7])  # Month: characters 5-6  
        d = int(date[8:10]) # Day: characters 8-9
        
        # Create date objects
        ymd = date(y, m, d)        # The given date
        start = date(y, 1, 1)      # January 1st of the same year
        
        # Calculate difference and add 1
        diff = ymd - start         # Returns timedelta object
        return diff.days + 1       # Convert to days and add 1
```

**Time Complexity**: O(1) - All operations are constant time
**Space Complexity**: O(1) - Only using a few variables

**Why add 1?**
- January 1st - January 1st = 0 days difference
- But January 1st should return day 1 of the year
- Hence we add 1 to convert from 0-based to 1-based indexing

**Alternative Manual Approach**:
```python
def dayOfYear(self, date: str) -> int:
    y, m, d = int(date[:4]), int(date[5:7]), int(date[8:])
    
    # Days in each month (non-leap year)
    days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    
    # Check if leap year
    if (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0):
        days[1] = 29
    
    # Sum days in previous months + current day
    return sum(days[:m-1]) + d
```

The built-in approach is cleaner and handles leap years automatically.

# Tags

- **Date/Time Manipulation**
- **String Parsing**  
- **Mathematical Calculation**
- **Easy Difficulty**

