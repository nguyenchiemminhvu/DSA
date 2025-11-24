## Problem

https://leetcode.com/problems/count-the-number-of-special-characters-i/

```
You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.

Return the number of special letters in word.

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters in word are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

No character in word appears in uppercase.

Example 3:

Input: word = "abBCab"

Output: 1

Explanation:

The only special character in word is 'b'.

Constraints:

1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.
```

## Observations

1. **Definition of Special Character**: A character is special if it appears in both lowercase and uppercase forms in the string.

2. **Key Insight**: We need to check for pairs - for each lowercase letter, check if its uppercase counterpart exists (and vice versa).

3. **Duplicate Handling**: The same character can appear multiple times in the string, but we only care about its presence, not frequency.

4. **Efficient Approach**: Use a set to store unique characters, eliminating duplicates and enabling O(1) lookup time.

5. **One-way Check**: We only need to iterate through lowercase letters and check for their uppercase counterparts (or vice versa) to avoid double counting.

## Solution

1. **Create a Set**: Convert the string into a set of unique characters to eliminate duplicates and enable fast lookups.

2. **Iterate Through Unique Characters**: Loop through each character in the set.

3. **Check Lowercase Letters Only**: For each lowercase letter, check if its uppercase counterpart exists in the set. This prevents counting the same pair twice.

4. **Count Special Pairs**: Use `int(c.upper() in s)` which converts the boolean result to 1 (if uppercase exists) or 0 (if it doesn't), adding to our count.

**Time Complexity**: O(n) where n is the length of the word
- Creating the set: O(n)
- Iterating through unique characters: O(k) where k ≤ n
- Set lookup: O(1)

**Space Complexity**: O(1) since we can have at most 52 unique English letters (26 lowercase + 26 uppercase)

# Tags

