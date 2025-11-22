## Problem

https://leetcode.com/problems/reformat-date/description/

```
Given a date string in the form Day Month Year, where:

Day is in the set {"1st", "2nd", "3rd", "4th", ..., "30th", "31st"}.
Month is in the set {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}.
Year is in the range [1900, 2100].
Convert the date string to the format YYYY-MM-DD, where:

YYYY denotes the 4 digit year.
MM denotes the 2 digit month.
DD denotes the 2 digit day.

Example 1:

Input: date = "20th Oct 2052"
Output: "2052-10-20"

Example 2:

Input: date = "6th Jun 1933"
Output: "1933-06-06"

Example 3:

Input: date = "26th May 1960"
Output: "1960-05-26"

Constraints:

The given dates are guaranteed to be valid, so no error handling is necessary.
```

## Observations

1. **Input Format**: The input date is in the format "Day Month Year" where:
   - Day includes ordinal suffixes ("st", "nd", "rd", "th")
   - Month is a 3-letter abbreviation
   - Year is a 4-digit number

2. **Output Format**: We need to convert to "YYYY-MM-DD" format where:
   - Year comes first (4 digits)
   - Month is 2 digits (01-12)
   - Day is 2 digits (01-31)

3. **Key Challenges**:
   - Need to map month abbreviations to numbers
   - Need to extract day number from ordinal format
   - Need to rearrange the order from "Day Month Year" to "Year Month Day"

4. **Data Mapping Required**:
   - Month names to 2-digit strings
   - Day ordinals to 2-digit strings

## Solution

1. **Create Mapping Dictionaries**:
   - `months`: Maps 3-letter month abbreviations to 2-digit month numbers
   - `days`: Maps ordinal day strings to 2-digit day numbers

2. **Parse and Rearrange**:
   - Split the input date by spaces: `["20th", "Oct", "2052"]`
   - Reverse the list to get year-first order: `["2052", "Oct", "20th"]`

3. **Convert Components**:
   - `words[0]` (year) stays as is: `"2052"`
   - `words[1]` (month) gets converted using months dict: `"Oct" → "10"`
   - `words[2]` (day) gets converted using days dict: `"20th" → "20"`

4. **Format Output**:
   - Join with hyphens: `"2052-10-20"`

**Time Complexity**: O(1) - All operations are constant time
**Space Complexity**: O(1) - Fixed-size dictionaries regardless of input

**Alternative Approach**: Instead of creating a full days dictionary, we could extract the numeric part from the day string using string slicing or regex, but the dictionary approach is clearer and handles all edge cases explicitly.

# Tags

