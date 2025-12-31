## Problem

https://leetcode.com/problems/minimum-additions-to-make-valid-string/description/

```
Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, 
return the minimum number of letters that must be inserted so that word becomes valid.

A string is called valid if it can be formed by concatenating the string "abc" several times.

Example 1:
Input: word = "b"
Output: 2
Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain 
the valid string "abc".

Example 2:
Input: word = "aaa"
Output: 6
Explanation: Insert letters "b" and "c" next to each "a" to obtain the valid string "abcabcabc".

Example 3:
Input: word = "abc"
Output: 0
Explanation: word is already valid. No modifications are needed.

Constraints:
- 1 <= word.length <= 50
- word consists of letters "a", "b" and "c" only.
```

## Observations

1. **Valid String Pattern**: A valid string is composed of repeated "abc" patterns concatenated together.

2. **Substring Analysis**: We can break down any input string into subsequences that match parts of "abc":
   - "abc" → complete pattern, needs 0 additions
   - "ab" → needs 1 addition (c)
   - "bc" → needs 1 addition (a)
   - "ac" → needs 1 addition (b)
   - "a", "b", or "c" → single character, needs 2 additions

3. **Greedy Approach**: We can greedily match the longest possible subsequences from the "abc" pattern and count how many characters need to be inserted.

4. **String Replacement Strategy**: By replacing matched patterns with their "cost" (number of insertions needed), we can calculate the total insertions:
   - Replace "abc" with "0" (0 insertions needed)
   - Replace "ab", "bc", "ac" with "1" (1 insertion needed)
   - Replace "a", "b", "c" with "2" (2 insertions needed)

5. **Order Matters**: We must replace longer patterns first to avoid incorrect matches (e.g., replace "abc" before "ab" to avoid breaking valid complete patterns).

## Solution

### Approach: Greedy Pattern Replacement

**Algorithm:**
1. Replace all occurrences of complete "abc" patterns with "0" (no insertions needed)
2. Replace remaining two-character patterns ("ab", "bc", "ac") with "1" (one insertion needed)
3. Replace remaining single characters ("a", "b", "c") with "2" (two insertions needed)
4. Sum all the numeric values in the resulting string

**Why This Works:**
- The replacement order ensures we maximize the use of existing characters
- Complete "abc" patterns are preserved first (best case - 0 additions)
- Two-character subsequences are then identified (1 addition each)
- Isolated characters require the most additions (2 each)

**Time Complexity:** O(n) where n is the length of the string
- Each replacement operation scans the string once
- We perform a constant number (7) of replacement operations

**Space Complexity:** O(n) for the string manipulations

**Example Walkthrough:**

For `word = "aaa"`:
1. After "abc" replacement: "aaa" (no change)
2. After "ab", "bc", "ac" replacements: "aaa" (no change)
3. After single character replacements: "222"
4. Sum: 2 + 2 + 2 = 6

For `word = "abac"`:
1. After "abc" replacement: "abac" (no change, "abc" not present consecutively)
2. After "ab" replacement: "1ac"
3. After "ac" replacement: "11"
4. Sum: 1 + 1 = 2

**Python Implementation:**
```python
class Solution:
    def addMinimum(self, s: str) -> int:
        # Replace complete patterns (0 insertions needed)
        s = s.replace('abc', '0')
        
        # Replace two-character patterns (1 insertion needed)
        s = s.replace('ab', '1')
        s = s.replace('bc', '1')
        s = s.replace('ac', '1')
        
        # Replace single characters (2 insertions needed)
        s = s.replace('a', '2')
        s = s.replace('b', '2')
        s = s.replace('c', '2')
        
        # Sum all insertion counts
        return sum(int(c) for c in s)
```

### Alternative Approach: State Machine

Another way to solve this is using a state machine that tracks the expected next character in the "abc" pattern:

```python
class Solution:
    def addMinimum(self, s: str) -> int:
        additions = 0
        expected = 'a'  # Start expecting 'a'
        
        for char in s:
            # Add missing characters until we reach the current character
            while expected != char:
                additions += 1
                if expected == 'a':
                    expected = 'b'
                elif expected == 'b':
                    expected = 'c'
                else:
                    expected = 'a'
            
            # Move to next expected character
            if expected == 'a':
                expected = 'b'
            elif expected == 'b':
                expected = 'c'
            else:
                expected = 'a'
        
        # Complete the final pattern if needed
        while expected != 'a':
            additions += 1
            if expected == 'b':
                expected = 'c'
            else:
                expected = 'a'
        
        return additions
```

Time Complexity: O(n)
Space Complexity: O(1)

# Tags

- String
- Greedy
- Pattern Matching
- String Manipulation