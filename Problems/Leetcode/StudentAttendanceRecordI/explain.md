## Problem

https://leetcode.com/problems/student-attendance-record-i/description/

```
You are given a string s representing an attendance record for a student where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

'A': Absent.
'L': Late.
'P': Present.
The student is eligible for an attendance award if they meet both of the following criteria:

The student was absent ('A') for strictly fewer than 2 days total.
The student was never late ('L') for 3 or more consecutive days.
Return true if the student is eligible for an attendance award, or false otherwise.

Example 1:

Input: s = "PPALLP"
Output: true
Explanation: The student has fewer than 2 absences and was never late 3 or more consecutive days.

Example 2:

Input: s = "PPALLL"
Output: false
Explanation: The student was late 3 consecutive days in the last 3 days, so is not eligible for the award.

Constraints:

1 <= s.length <= 1000
s[i] is either 'A', 'L', or 'P'.
```

## Observations

1. **Two main conditions to check:**
   - Student must have fewer than 2 absences ('A') in total
   - Student must never be late ('L') for 3 or more consecutive days

2. **Simple string analysis problem:**
   - We need to count occurrences of 'A' characters
   - We need to detect if "LLL" (3 consecutive L's) exists anywhere in the string

3. **Edge cases to consider:**
   - Empty string (but constraints say length >= 1)
   - String with only one character
   - All same characters
   - Maximum length string (1000 characters)

4. **Time complexity considerations:**
   - Both `count()` and `in` operations are O(n) where n is string length
   - Overall time complexity: O(n)
   - Space complexity: O(1) - no extra space needed

## Solution

1. **Check absence condition:** `s.count('A') >= 2`
   - Count all occurrences of 'A' in the string
   - If there are 2 or more absences, student is not eligible
   - Return `False` immediately (early termination)

2. **Check consecutive late condition:** `s.count('LLL') > 0`
   - Look for the substring "LLL" (3 consecutive L's)
   - `count('LLL')` returns how many times this pattern appears
   - If it appears even once (`> 0`), student is not eligible
   - Return `False` immediately

3. **Return True if both conditions pass**
   - If we reach this point, both conditions are satisfied
   - Student is eligible for the award

**Alternative approaches:**

1. **Single pass solution:**
```python
def checkRecord(self, s: str) -> bool:
    absent_count = 0
    consecutive_late = 0
    
    for char in s:
        if char == 'A':
            absent_count += 1
            if absent_count >= 2:
                return False
            consecutive_late = 0
        elif char == 'L':
            consecutive_late += 1
            if consecutive_late >= 3:
                return False
        else:  # char == 'P'
            consecutive_late = 0
    
    return True
```

2. **Using regular expressions:**
```python
import re
def checkRecord(self, s: str) -> bool:
    return s.count('A') < 2 and not re.search('LLL', s)
```

**Why the given solution is good:**
- **Readable:** Very clear and concise
- **Efficient:** Early termination on first violation
- **Simple:** Uses Python's built-in string methods effectively
- **Correct:** Handles all edge cases properly

**Time Complexity:** O(n) where n is the length of the string
**Space Complexity:** O(1) - only uses constant extra space

# Tags

`String` `Simulation` `Easy`

