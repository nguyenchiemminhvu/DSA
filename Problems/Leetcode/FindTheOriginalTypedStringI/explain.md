## Problem

https://leetcode.com/problems/find-the-original-typed-string-i/description/

```
Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.

Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.

You are given a string word, which represents the final output displayed on Alice's screen.

Return the total number of possible original strings that Alice might have intended to type.

Example 1:

Input: word = "abbcccc"

Output: 5

Explanation:

The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".

Example 2:

Input: word = "abcd"

Output: 1

Explanation:

The only possible string is "abcd".

Example 3:

Input: word = "aaaa"

Output: 4

Constraints:

1 <= word.length <= 100
word consists only of lowercase English letters.
```

## Observations

- Alice may have held down a key too long, causing consecutive repeated characters
- We need to count all possible original strings she might have intended to type
- For each run of consecutive identical characters, we can reduce the count by removing any number of the repeated characters (but keeping at least one)
- If we have a run of `n` consecutive identical characters, there are `n` possible ways to interpret it (keep 1, keep 2, ..., keep n characters)
- The total number of possibilities is the product of all possible interpretations for each run of repeated characters

## Solution

1. **Initialize**: Start with `res = 1` (base case - the original string itself)
2. **Track consecutive characters**: Use `prev` to store the previous character and `count` to track the length of current run
3. **Process each character**:
   - If current character `c` is different from `prev`, reset `count = 1` (start new run)
   - If current character `c` is same as `prev`, increment `count`
   - When `count > 1` (we have a repeat), increment `res` by 1
4. **Update**: Set `prev = c` for next iteration

### Why this works

- For each run of repeated characters of length `n`, we have `n` choices (keep 1, 2, ..., n characters)
- But since we start with `res = 1`, we only need to add `(n-1)` additional possibilities for each run
- Each time we encounter an additional repeat in a run, we increment `res` by 1

### Example Walkthrough

For `word = "abbcccc"`:
- 'a': count = 1, res = 1
- 'b': count = 1, res = 1  
- 'b': count = 2, res = 2 (can have "ab" or "abb")
- 'c': count = 1, res = 2
- 'c': count = 2, res = 3 (add "abbc" vs "abbcc")
- 'c': count = 3, res = 4 (add "abbccc")
- 'c': count = 4, res = 5 (add "abbcccc")

Result: 5 possible strings

### Time Complexity: O(n)
### Space Complexity: O(1)

# Tags

- String
- Two Pointers
- Counting

