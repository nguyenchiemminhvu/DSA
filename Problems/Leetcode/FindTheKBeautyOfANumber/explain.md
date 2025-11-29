## Problem

https://leetcode.com/problems/find-the-k-beauty-of-a-number/

```
The k-beauty of an integer num is defined as the number of substrings of num when it is read as a string that meet the following conditions:
- It has a length of k.
- It is a divisor of num.

Given integers num and k, return the k-beauty of num.

Note:
- Leading zeros are allowed.
- 0 is not a divisor of any value.
- A substring is a contiguous sequence of characters in a string.

Example 1:
Input: num = 240, k = 2
Output: 2
Explanation: The following are the substrings of num of length k:
- "24" from "240": 24 is a divisor of 240.
- "40" from "240": 40 is a divisor of 240.
Therefore, the k-beauty is 2.

Example 2:
Input: num = 430043, k = 2
Output: 2
Explanation: The following are the substrings of num of length k:
- "43" from "430043": 43 is a divisor of 430043.
- "30" from "430043": 30 is not a divisor of 430043.
- "00" from "430043": 0 is not a divisor of 430043.
- "04" from "430043": 4 is not a divisor of 430043.
- "43" from "430043": 43 is a divisor of 430043.
Therefore, the k-beauty is 2.

Constraints:
- 1 <= num <= 10^9
- 1 <= k <= num.length (taking num as a string)
```

## Observations

1. **String Conversion**: Converting the number to a string makes it easy to extract substrings of length k.

2. **Sliding Window**: We need to check all consecutive substrings of length k, which is a classic sliding window pattern with window size k.

3. **Division by Zero**: We must handle the case where a substring represents 0 (e.g., "00", "000"), as division by zero is undefined and 0 is explicitly not a divisor.

4. **Leading Zeros**: Substrings like "04" are valid and represent the number 4. Python's `int()` function naturally handles this.

5. **Edge Cases**:
   - If k equals the length of num, there's only one substring to check
   - If k = 1, we're checking individual digits
   - Substrings with leading zeros need to be converted correctly (e.g., "04" → 4)

## Solution

1. **Convert to String**: Convert `num` to a string `s` to easily extract substrings.

2. **Sliding Window Iteration**: Loop through all possible starting positions from index 0 to `len(s) - k` (inclusive). This ensures we get all substrings of exactly length k.

3. **Extract and Convert**: For each position `i`, extract the substring `s[i:i+k]` and convert it to an integer `val`.

4. **Check Divisibility**: 
   - First check `if val` to ensure the value is not 0 (avoiding division by zero)
   - Then check `num % val == 0` to verify if `val` is a divisor of `num`
   - If both conditions are true, increment the count

5. **Return Count**: Return the total count of valid k-beauty substrings.

**Time Complexity**: O(n) where n is the number of digits in num. We iterate through all possible substrings once.

**Space Complexity**: O(n) for storing the string representation of num.

**Key Insight**: The condition `if val and num % val == 0` is elegant because:
- `val` is falsy when it's 0, preventing division by zero
- The short-circuit evaluation means `num % val` is only computed when `val != 0`

# Tags
#sliding-window #string #math #easy

