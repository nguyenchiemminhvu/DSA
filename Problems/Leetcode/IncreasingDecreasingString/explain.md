## Problem

https://leetcode.com/problems/increasing-decreasing-string/description/

```
You are given a string s. Reorder the string using the following algorithm:

Remove the smallest character from s and append it to the result.
Remove the smallest character from s that is greater than the last appended character, and append it to the result.
Repeat step 2 until no more characters can be removed.
Remove the largest character from s and append it to the result.
Remove the largest character from s that is smaller than the last appended character, and append it to the result.
Repeat step 5 until no more characters can be removed.
Repeat steps 1 through 6 until all characters from s have been removed.
If the smallest or largest character appears more than once, you may choose any occurrence to append to the result.

Return the resulting string after reordering s using this algorithm.

Example 1:

Input: s = "aaaabbbbcccc"
Output: "abccbaabccba"
Explanation: After steps 1, 2 and 3 of the first iteration, result = "abc"
After steps 4, 5 and 6 of the first iteration, result = "abccba"
First iteration is done. Now s = "aabbcc" and we go back to step 1
After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"

Example 2:

Input: s = "rat"
Output: "art"
Explanation: The word "rat" becomes "art" after re-ordering it with the mentioned algorithm.

Constraints:

1 <= s.length <= 500
s consists of only lowercase English letters.
```

## Observations

1. **Pattern Recognition**: The algorithm follows a specific pattern:
   - Phase 1: Pick characters in ascending order (a→b→c→...)
   - Phase 2: Pick characters in descending order (z→y→x→...)
   - Repeat until all characters are used

2. **Character Frequency Tracking**: We need to track how many times each character appears to know when we've used all occurrences.

3. **Alternating Directions**: The solution alternates between two directions:
   - Forward pass: iterate through `a` to `z`
   - Backward pass: iterate through `z` to `a`

4. **Greedy Approach**: At each step, we greedily pick the next available character in the current direction.

5. **String Building**: We build the result string character by character, ensuring we don't exceed the available count of each character.

## Solution

1. **Frequency Counting**: Create a frequency map `f` to track how many times each character appears in the input string.

2. **Two-Phase Loop**: Continue until all characters are processed (`len(res) < n`):
   - **Ascending Phase**: Iterate through characters `a` to `z`, adding each available character once
   - **Descending Phase**: Iterate through characters `z` to `a`, adding each available character once

3. **Character Selection**: For each character in the current direction:
   - Check if the character exists in our frequency map and has remaining occurrences
   - If yes, append it to result and decrement its frequency count

**Time Complexity**: O(n) where n is the length of string s
- We visit each character exactly once during the frequency counting
- The while loop runs at most 26 iterations (since we process at least one character per iteration in worst case)
- Each iteration processes at most 26 characters (a-z), so the inner loops are O(26) = O(1)

**Space Complexity**: O(1) 
- The frequency map stores at most 26 entries (lowercase letters)
- All other variables use constant space

**Example Walkthrough** with `s = "aaaabbbbcccc"`:

Initial: `f = {'a': 4, 'b': 4, 'c': 4}`

**Iteration 1:**
- Ascending: a→b→c → result = "abc", `f = {'a': 3, 'b': 3, 'c': 3}`  
- Descending: c→b→a → result = "abccba", `f = {'a': 2, 'b': 2, 'c': 2}`

**Iteration 2:**
- Ascending: a→b→c → result = "abccbaabc", `f = {'a': 1, 'b': 1, 'c': 1}`
- Descending: c→b→a → result = "abccbaabccba", `f = {'a': 0, 'b': 0, 'c': 0}`

Final result: "abccbaabccba"

# Tags

- String Manipulation
- Frequency Counting
- Hash Map
- Greedy Algorithm
- Two Pointers (Conceptual)

