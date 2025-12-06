## Problem

https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/description/

You are given a string `time` in the form of `hh:mm`, where some of the digits in the string are hidden (represented by `?`).

The valid times are those inclusively between `00:00` and `23:59`.

Return the **latest valid time** you can get from `time` by replacing the hidden digits.

### Examples

**Example 1:**
```
Input: time = "2?:?0"
Output: "23:50"
Explanation: The latest hour beginning with the digit '2' is 23 and the latest minute ending with the digit '0' is 50.
```

**Example 2:**
```
Input: time = "0?:3?"
Output: "09:39"
```

**Example 3:**
```
Input: time = "1?:22"
Output: "19:22"
```

### Constraints

- `time` is in the format `hh:mm`
- It is guaranteed that you can produce a valid time from the given string

## Observations

1. **Time Format Structure:**
   - Position 0-1: Hours (00-23)
   - Position 2: Colon separator (':')
   - Position 3-4: Minutes (00-59)

2. **Digit Constraints:**
   - **First hour digit (position 0):** Can be 0, 1, or 2
   - **Second hour digit (position 1):** 
     - If first digit is 2: can only be 0-3
     - If first digit is 0 or 1: can be 0-9
   - **First minute digit (position 3):** Can be 0-5
   - **Second minute digit (position 4):** Can be 0-9

3. **Greedy Approach:**
   - To get the **latest** time, we want to maximize digits from left to right
   - Start with hours: maximize the first digit, then the second
   - Then maximize minutes: first digit, then second

4. **Brute Force Approach (Given Solution):**
   - Generate all possible valid times in descending order
   - Check each time against the pattern to see if it matches
   - Return the first matching time (which will be the latest)

## Solution

1. **Generate Hours (23 down to 00):**
   ```python
   hours = list(reversed([f"{i:02d}" for i in range(24)]))
   # Result: ['23', '22', '21', ..., '01', '00']
   ```

2. **Generate Minutes (59 down to 00):**
   ```python
   minutes = list(reversed([f"{i:02d}" for i in range(60)]))
   # Result: ['59', '58', '57', ..., '01', '00']
   ```

3. **Iterate Through All Combinations:**
   - Start from the largest hour (23) and largest minute (59)
   - For each combination, create a full time string `"hh:mm"`

4. **Pattern Matching:**
   - Compare each character of the generated time with the input pattern
   - If input character is `'?'`, it matches anything
   - If input character is a digit, it must exactly match the generated time's character
   - If all positions match, this is our answer (and it's the latest possible)

5. **Return Result:**
   - The first valid match is the latest time because we iterate in descending order

#### Example Walkthrough: `time = "2?:?0"`

1. First iteration: `h = "23"`, `m = "59"` → `t = "23:59"`
   - Compare with `"2?:?0"`:
   - Position 0: `'2'` == `'2'` ✓
   - Position 1: `'?'` matches `'3'` ✓
   - Position 2: `':'` == `':'` ✓
   - Position 3: `'?'` matches `'5'` ✓
   - Position 4: `'0'` != `'9'` ✗

2. Continue with `h = "23"`, trying different minutes...
   - Eventually reach `m = "50"` → `t = "23:50"`
   - All positions match: `"23:50"` ✓

3. **Return `"23:50"`**

### Complexity Analysis

**Time Complexity:** O(24 × 60 × 5) = O(7,200) = **O(1)**
- Fixed number of hours (24) and minutes (60)
- For each combination, check 5 characters
- Constant time overall

**Space Complexity:** O(24 + 60) = **O(1)**
- Storage for hours and minutes lists
- Constant space

### Alternative Greedy Approach (More Efficient):

A more elegant solution would process each digit position independently:

```python
def maximumTime(self, time: str) -> str:
    result = list(time)
    
    # First hour digit
    if result[0] == '?':
        result[0] = '2' if result[1] == '?' or result[1] <= '3' else '1'
    
    # Second hour digit
    if result[1] == '?':
        result[1] = '3' if result[0] == '2' else '9'
    
    # First minute digit
    if result[3] == '?':
        result[3] = '5'
    
    # Second minute digit
    if result[4] == '?':
        result[4] = '9'
    
    return ''.join(result)
```

This greedy approach is O(1) time with only 4 conditional checks and uses O(5) = O(1) space.

# Tags

`string` `greedy` `brute-force` `pattern-matching`

