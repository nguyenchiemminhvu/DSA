## Problem

https://leetcode.com/problems/count-days-spent-together/

Alice and Bob are traveling to Rome for separate business meetings.

You are given 4 strings `arriveAlice`, `leaveAlice`, `arriveBob`, and `leaveBob`. Alice will be in the city from the dates `arriveAlice` to `leaveAlice` (inclusive), while Bob will be in the city from the dates `arriveBob` to `leaveBob` (inclusive). Each will be a 5-character string in the format `"MM-DD"`, corresponding to the month and day of the date.

Return the total number of days that Alice and Bob are in Rome together.

You can assume that all dates occur in the same calendar year, which is not a leap year. Note that the number of days per month can be represented as: `[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]`.

**Example 1:**
```
Input: arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
Output: 3
Explanation: Alice will be in Rome from August 15 to August 18. Bob will be in Rome from August 16 to August 19. 
They are both in Rome together on August 16th, 17th, and 18th, so the answer is 3.
```

**Example 2:**
```
Input: arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
Output: 0
Explanation: There is no day when Alice and Bob are in Rome together, so we return 0.
```

**Constraints:**
- All dates are provided in the format `"MM-DD"`
- Alice and Bob's arrival dates are earlier than or equal to their leaving dates
- The given dates are valid dates of a non-leap year

## Observations

1. **Interval Overlap Problem**: This is fundamentally a problem of finding the overlap between two date ranges (intervals).

2. **Date Representation**: Working with `"MM-DD"` format directly is cumbersome. Converting to a simpler representation (day of year) makes calculations easier.

3. **Day of Year Conversion**: We can convert any date to a "day of year" number (1-365):
   - January 1 = day 1
   - December 31 = day 365
   - This transforms the problem into finding overlap between two numeric ranges.

4. **Overlap Calculation**: For two intervals `[a_start, a_end]` and `[b_start, b_end]`:
   - Overlap starts at: `max(a_start, b_start)`
   - Overlap ends at: `min(a_end, b_end)`
   - If overlap_start > overlap_end, there's no overlap

5. **Edge Cases**:
   - No overlap (disjoint intervals)
   - One interval completely contains the other
   - Partial overlap
   - Same dates (complete overlap)

## Solution

#### Helper Function: `get_day_of_year(month, day)`

This function converts a date (month, day) to the day number of the year:
- **Input**: month (1-12) and day (1-31)
- **Process**: 
  - Sum all days in months before the current month: `sum(days_in_months[:month - 1])`
  - Add the current day: `+ day`
- **Example**: March 15
  - Months before March: January (31) + February (28) = 59 days
  - Day 15 of March: 59 + 15 = 74th day of year

#### Main Algorithm

**Step 1: Parse and convert all dates**
```python
a_start = get_day_of_year(int(a_arrived[0:2]), int(a_arrived[3:5]))
a_end   = get_day_of_year(int(a_leave[0:2]),   int(a_leave[3:5]))
b_start = get_day_of_year(int(b_arrived[0:2]), int(b_arrived[3:5]))
b_end   = get_day_of_year(int(b_leave[0:2]),   int(b_leave[3:5]))
```
- Extract month: `a_arrived[0:2]` (first 2 characters)
- Extract day: `a_arrived[3:5]` (characters after the hyphen)
- Convert to integers and then to day-of-year

**Step 2: Find overlap interval**
```python
overlap_start = max(a_start, b_start)  # Latest arrival
overlap_end = min(a_end, b_end)        # Earliest departure
```
- The overlap can only start when **both** have arrived (latest arrival)
- The overlap must end when **either** leaves (earliest departure)

**Step 3: Calculate overlap duration**
```python
return max(0, overlap_end - overlap_start + 1)
```
- Duration = end - start + 1 (inclusive count)
- Use `max(0, ...)` to handle no-overlap case (when overlap_end < overlap_start)

### Visual Example (Example 1)

```
Timeline (August):
Day of month:  15  16  17  18  19
Alice:         [===============]
Bob:               [===============]
Overlap:           [===========]
                   16  17  18
```

- Alice: days 227-230 (Aug 15-18)
- Bob: days 228-231 (Aug 16-19)
- overlap_start = max(227, 228) = 228
- overlap_end = min(230, 231) = 230
- Days together = 230 - 228 + 1 = 3

### Complexity Analysis

- **Time Complexity**: O(1)
  - Converting dates: O(12) = O(1) for summing days in months
  - All other operations are constant time
  
- **Space Complexity**: O(1)
  - Only using a fixed-size array and a few variables

### Why This Solution Works

1. **Simplification**: Converting to day-of-year reduces the problem to simple numeric range overlap
2. **No Date Arithmetic**: Avoids complex calendar logic by preprocessing dates
3. **Clean Interval Logic**: The max/min pattern for overlap is a standard technique
4. **Handles All Cases**: The `max(0, ...)` naturally handles disjoint intervals

# Tags

`Interval Overlap` `Date Conversion` `Math` `String Parsing`

