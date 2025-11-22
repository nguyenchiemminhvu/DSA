## Problem

https://leetcode.com/problems/reformat-phone-number/

```
You are given a phone number as a string number. number consists of digits, spaces ' ', and/or dashes '-'.

You would like to reformat the phone number in a certain manner. Firstly, remove all spaces and dashes. Then, group the digits from left to right into blocks of length 3 until there are 4 or fewer digits. The final digits are then grouped as follows:

2 digits: A single block of length 2.
3 digits: A single block of length 3.
4 digits: Two blocks of length 2 each.
The blocks are then joined by dashes. Notice that the reformatting process should never produce any blocks of length 1 and produce at most two blocks of length 2.

Return the phone number after formatting.

Example 1:

Input: number = "1-23-45 6"
Output: "123-456"
Explanation: The digits are "123456".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 3 digits remaining, so put them in a single block of length 3. The 2nd block is "456".
Joining the blocks gives "123-456".

Example 2:

Input: number = "123 4-567"
Output: "123-45-67"
Explanation: The digits are "1234567".
Step 1: There are more than 4 digits, so group the next 3 digits. The 1st block is "123".
Step 2: There are 4 digits left, so split them into two blocks of length 2. The blocks are "45" and "67".
Joining the blocks gives "123-45-67".

Example 3:

Input: number = "123 4-5678"
Output: "123-456-78"
Explanation: The digits are "12345678".
Step 1: The 1st block is "123".
Step 2: The 2nd block is "456".
Step 3: There are 2 digits left, so put them in a single block of length 2. The 3rd block is "78".
Joining the blocks gives "123-456-78".

Constraints:

2 <= number.length <= 100
number consists of digits and the characters '-' and ' '.
There are at least two digits in number.
```

## Observations

1. **Input Cleanup**: First, we need to remove all spaces and dashes from the input string to get only digits.

2. **Grouping Strategy**: We group digits into chunks of 3 from left to right, but need special handling for the end.

3. **Edge Case Handling**: The tricky part is handling the last group(s):
   - If we end up with exactly 4 digits in the last two groups combined, we need to redistribute them as 2+2 instead of 3+1 (to avoid single-digit blocks).
   - This happens when the second-to-last group has 3 digits and the last group has 1 digit.

4. **No Single Blocks**: The problem explicitly states we should never produce blocks of length 1, which is why we redistribute 3+1 → 2+2.

## Solution

1. **Regex Cleanup**: `re.split(r"[\s-]+", number)` splits on one or more spaces or dashes, then `"".join()` removes them.

2. **List Comprehension**: Creates groups of 3 digits efficiently using slicing `[i:i+3]`.

3. **Edge Case Detection**: Checks if `len(number[-2]) + len(number[-1]) == 4` to identify when we have a 3+1 situation that needs redistribution.

4. **Redistribution Logic**: 
   - Takes the last character from the second-to-last group: `number[-2][-1]`
   - Prepends it to the last group: `number[-2][-1] + number[-1]`
   - Removes it from the second-to-last group: `number[-2][:-1]`

**Example Walkthrough** (Input: "123 4-567"):
- After cleanup: "1234567"
- After grouping: ["123", "4567"] → but "4567" is too long!
- Actually groups of 3: ["123", "456", "7"]
- Edge case detected: len("456") + len("7") = 4
- Redistribute: ["123", "45", "67"]
- Final result: "123-45-67"

# Tags

