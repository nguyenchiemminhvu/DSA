## Problem

https://leetcode.com/problems/strong-password-checker-ii/description/

A password is said to be **strong** if it satisfies all the following criteria:

1. It has at least **8 characters**.
2. It contains at least **one lowercase letter**.
3. It contains at least **one uppercase letter**.
4. It contains at least **one digit**.
5. It contains at least **one special character**. The special characters are: `"!@#$%^&*()-+"`.
6. It does **not** contain 2 of the same character in adjacent positions (e.g., `"aab"` violates this, but `"aba"` does not).

Given a string `password`, return `true` if it is a strong password. Otherwise, return `false`.

**Example 1:**
```
Input: password = "IloveLe3tcode!"
Output: true
Explanation: The password meets all the requirements.
```

**Example 2:**
```
Input: password = "Me+You--IsMyDream"
Output: false
Explanation: The password does not contain a digit and also contains 2 of the same character in adjacent positions (--).
```

**Example 3:**
```
Input: password = "1aB!"
Output: false
Explanation: The password does not meet the length requirement (only 4 characters).
```

**Constraints:**
- `1 <= password.length <= 100`
- `password` consists of letters, digits, and special characters: `"!@#$%^&*()-+"`.

## Observations

1. **Multiple Conditions to Check**: This is a validation problem where we need to verify 6 different criteria. All must be satisfied for the password to be strong.

2. **Early Exit Opportunity**: We can return `false` immediately if:
   - Length is less than 8
   - Two adjacent characters are the same

3. **Character Classification**: We need to identify and count:
   - Lowercase letters (`a-z`)
   - Uppercase letters (`A-Z`)
   - Digits (`0-9`)
   - Special characters from the specific set

4. **Single Pass Solution**: All checks can be performed in one iteration through the password string.

5. **Adjacent Character Check**: We need to track the previous character to detect consecutive duplicates. Using a sentinel value (like `'~'`) that won't appear in the password ensures the first character comparison doesn't cause issues.

## Solution

### Approach: Single Pass with Multiple Counters

**Algorithm:**
1. **Length Check**: First, validate that the password has at least 8 characters. If not, return `false` immediately.

2. **Initialize Counters**: Set up counters for each character type:
   - `count_low`: lowercase letters
   - `count_up`: uppercase letters
   - `count_d`: digits
   - `count_spec`: special characters

3. **Single Pass Iteration**: Traverse the password once, and for each character:
   - **Check Adjacent Duplicates**: Compare with the previous character. If they match, return `false` immediately.
   - **Classify and Count**: Increment the appropriate counter based on character type.
   - **Update Previous**: Store current character as `prev` for next iteration.

4. **Final Validation**: After the loop, verify that all counters are at least 1. If any is 0, return `false`.

5. **Return Success**: If all checks pass, return `true`.

**Complexity Analysis:**

- **Time Complexity**: $O(n)$ where $n$ is the length of the password
  - We iterate through the password exactly once
  - Each character check (using `in` operator) is $O(1)$ since we're checking against small constant-size sets

- **Space Complexity**: $O(1)$
  - We only use a fixed number of integer counters and one character variable
  - The `string` module constants don't count as they're predefined

**Why This Works:**

- **Complete Coverage**: By checking length upfront and then validating each criterion during the single pass, we ensure no condition is missed.
  
- **Efficient Early Exit**: The adjacent duplicate check returns `false` immediately when violated, avoiding unnecessary further processing.

- **Clear Character Classification**: Using Python's `string` module provides readable and reliable character set checking.

**Alternative Optimizations:**

Instead of counters, we could use boolean flags since we only need to know if at least one of each type exists:

```python
has_low = has_up = has_digit = has_spec = False
```

This doesn't significantly improve performance but can be slightly more memory-efficient (though both are $O(1)$).

# Tags
`String` `Validation` `Linear Scan` `Character Classification`

