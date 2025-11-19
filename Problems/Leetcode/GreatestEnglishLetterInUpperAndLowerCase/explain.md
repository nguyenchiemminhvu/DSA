## Problem

https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/

```
Given a string of English letters s, return the greatest English letter which occurs as both a lowercase and uppercase letter in s. The returned letter should be in uppercase. If no such letter exists, return an empty string.

An English letter b is greater than another letter a if b appears after a in the English alphabet.

Example 1:

Input: s = "lEeTcOdE"
Output: "E"
Explanation:
The letter 'E' is the only letter to appear in both lower and upper case.

Example 2:

Input: s = "arRAzFif"
Output: "R"
Explanation:
The letter 'R' is the greatest letter to appear in both lower and upper case.
Note that 'A' and 'F' also appear in both lower and upper case, but 'R' is greater than 'F' or 'A'.

Example 3:

Input: s = "AbCdEfGhIjK"
Output: ""
Explanation:
There is no letter that appears in both lower and upper case.

Constraints:

1 <= s.length <= 1000
s consists of lowercase and uppercase English letters.
```

## Observations

1. **Problem Requirements:**
   - Find the greatest English letter that appears in both lowercase and uppercase forms
   - Return the uppercase version of that letter
   - If no such letter exists, return empty string
   - "Greatest" means closest to 'Z' in the alphabet

2. **Key Insights:**
   - We need to check for pairs: (a,A), (b,B), (c,C), etc.
   - Since we want the greatest letter, we should iterate from 'z' to 'a' (reverse order)
   - Using a set for O(1) lookup time is efficient
   - Stop at the first match since we're going in reverse alphabetical order

3. **Algorithm Approach:**
   - Convert string to set for fast lookups
   - Iterate through lowercase letters in reverse order ('z' to 'a')
   - For each letter, check if both lowercase and uppercase versions exist in the set
   - Return the first match (which will be the greatest due to reverse iteration)

## Solution

1. **Create Character Set:** Convert the input string to a set `ss` for O(1) character lookups
2. **Reverse Iteration:** Use `string.ascii_lowercase[::-1]` to iterate from 'z' to 'a'
3. **Pair Check:** For each lowercase letter `c`, check if both `c` and `c.upper()` exist in the set
4. **Early Return:** Return the uppercase version of the first matching pair found
5. **Default Case:** If no pairs are found, return empty string

**Time Complexity:** O(n) where n is the length of the string
- Creating the set: O(n)
- Checking all 26 letters: O(1) since it's constant
- Set lookups: O(1) each

**Space Complexity:** O(k) where k is the number of unique characters in the string (at most 52 for English letters)

**Example Walkthrough:**
- Input: `s = "arRAzFif"`
- Set: `{'a', 'r', 'R', 'A', 'z', 'F', 'i', 'f'}`
- Check 'z': 'z' ✓, 'Z' ✗
- Check 'y': 'y' ✗
- ...
- Check 'r': 'r' ✓, 'R' ✓ → Return 'R'

# Tags

- **Hash Table/Set**
- **String Processing**
- **Greedy Algorithm**

