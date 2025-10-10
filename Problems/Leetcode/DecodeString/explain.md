## Problem

https://leetcode.com/problems/decode-string/

```
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 105.

Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Constraints:

1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].
```

## Observations

1. **Pattern Recognition**: The problem involves nested structures with brackets `k[encoded_string]` where we need to repeat the content inside brackets `k` times.

2. **Stack-based Approach**: Due to the nested nature of the encoding (like `3[a2[c]]`), we need to handle the innermost brackets first, making this a perfect candidate for stack-based processing.

3. **Two Types of Data**: We need to track both numbers (repetition count) and strings (content to repeat), suggesting we need two separate stacks or data structures.

4. **Processing Order**: When we encounter a closing bracket `]`, we need to:
   - Collect all characters back to the matching opening bracket `[`
   - Get the corresponding number
   - Repeat the collected string that many times
   - Push the result back for further processing

5. **Edge Cases**: 
   - Plain strings without brackets (like `"ef"` in `"2[abc]3[cd]ef"`)
   - Multiple consecutive brackets
   - Nested brackets of varying depths

## Solution

The solution uses a **two-stack approach** with deques to handle the nested bracket structure:

### Key Data Structures:
- `st_str`: Stack to store strings and bracket markers
- `st_num`: Stack to store repetition numbers
- `cur_str`: Current string being built
- `cur_num`: Current number being parsed

### Algorithm Walkthrough:

1. **Character Processing**:
   - **Digits**: Build the repetition number and push to `st_num`
   - **'['**: Mark the start of a new encoded section
   - **Letters**: Accumulate into current string
   - **']'**: Process the encoded section

2. **Closing Bracket Logic** (`']'`):
   ```python
   # Save current string and collect all strings back to '['
   st_str.append(cur_str)
   temp_str = ""
   while st_str[-1] != '[':
       temp_str = st_str[-1] + temp_str  # Prepend to maintain order
       st_str.pop()
   st_str.pop()  # Remove the '[' marker
   
   # Get repetition count and create repeated string
   temp_num = st_num.pop()
   st_str.append(temp_str * temp_num)
   ```

3. **Opening Bracket Logic** (`'['`):
   - Save current string to stack
   - Reset current string and number
   - Push bracket marker

4. **Final Assembly**: Join all remaining strings in the stack

### Example Trace (`"3[a2[c]]"`):

| Step | Character | Action | st_str | st_num | cur_str |
|------|-----------|--------|--------|--------|---------|
| 1 | '3' | Push number | [] | [3] | "" |
| 2 | '[' | Push bracket | ["", "["] | [3] | "" |
| 3 | 'a' | Build string | ["", "["] | [3] | "a" |
| 4 | '2' | Push number | ["", "[", "a"] | [3, 2] | "" |
| 5 | '[' | Push bracket | ["", "[", "a", "", "["] | [3, 2] | "" |
| 6 | 'c' | Build string | ["", "[", "a", "", "["] | [3, 2] | "c" |
| 7 | ']' | Process inner | ["", "[", "a", "cc"] | [3] | "" |
| 8 | ']' | Process outer | ["accaccacc"] | [] | "" |

### Time & Space Complexity:
- **Time**: O(n × m) where n is input length and m is the maximum expansion factor
- **Space**: O(n) for the stacks and temporary strings

The solution elegantly handles nested structures by using the stack's LIFO nature to process innermost brackets first, building up the decoded string layer by layer.

## Tags

array, string, stack