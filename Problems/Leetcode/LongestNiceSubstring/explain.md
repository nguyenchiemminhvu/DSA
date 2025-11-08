## Problem

https://leetcode.com/problems/longest-nice-substring/description/

```
A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.

Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.

Example 1:

Input: s = "YazaAay"
Output: "aAa"
Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
"aAa" is the longest nice substring.

Example 2:

Input: s = "Bb"
Output: "Bb"
Explanation: "Bb" is a nice string because both 'B' and 'b' appear. The whole string is a substring.

Example 3:

Input: s = "c"
Output: ""
Explanation: There are no nice substrings.

Constraints:

1 <= s.length <= 100
s consists of uppercase and lowercase English letters.
```

## Observations

1. **Definition of "Nice" String**: A string is nice if for every letter that appears in the string, both its lowercase and uppercase versions are present.

2. **Key Insights**:
   - We need to check all possible substrings to find the longest nice one
   - For a substring to be nice, every character that appears must have its case counterpart
   - If multiple nice substrings have the same length, return the earliest occurrence
   - If no nice substring exists, return empty string

3. **Examples Analysis**:
   - `"YazaAay"` → `"aAa"`: Contains 'a' and 'A', both cases present
   - `"Bb"` → `"Bb"`: Contains 'b' and 'B', both cases present
   - `"c"` → `""`: Only lowercase 'c', no uppercase 'C'

4. **Edge Cases**:
   - Single character strings are never nice (need both cases)
   - Strings with only one case of letters are not nice
   - Empty or very short strings

## Solution

### Approach: Brute Force with Helper Function

The solution uses a brute force approach that checks all possible substrings:

#### Algorithm Steps:

1. **Helper Function `is_nice(s)`**:
   - Creates two sets: one for lowercase letters, one for uppercase letters
   - Iterates through the string and populates both sets
   - Checks if every lowercase letter has its uppercase counterpart
   - Checks if every uppercase letter has its lowercase counterpart
   - Returns `True` only if both conditions are satisfied

2. **Main Logic**:
   - Generate all possible substrings using nested loops
   - For each substring, check if it's nice using the helper function
   - Track the longest nice substring found
   - Return the longest nice substring (earliest occurrence in case of ties)

#### Code Walkthrough:

```python
def is_nice(s: str) -> bool:
    s_lower = set()  # Store unique lowercase letters
    s_upper = set()  # Store unique uppercase letters
    
    # Populate sets with letters from string
    for c in s:
        if c.islower():
            s_lower.add(c)
        else:
            s_upper.add(c)
    
    # Check if every lowercase has uppercase counterpart
    for c in s_lower:
        if c.upper() not in s_upper:
            return False
    
    # Check if every uppercase has lowercase counterpart        
    for c in s_upper:
        if c.lower() not in s_lower:
            return False
    
    return True

# Main function generates all substrings
for i in range(n):
    for j in range(i + 1, n):  # j starts from i+1 to avoid single chars
        if is_nice(s[i:j+1]):
            if max_len < j - i + 1:
                max_len = j - i + 1
                selected = s[i:j + 1]
```

#### Time Complexity: O(n³)
- O(n²) to generate all substrings
- O(n) to check if each substring is nice
- Total: O(n²) × O(n) = O(n³)

#### Space Complexity: O(1)
- The sets store at most 26 characters each (English alphabet)
- Constant space regardless of input size

#### Alternative Approaches:

1. **Divide and Conquer**: O(n log n) average case
   - If a character appears without its counterpart, split the string at that character
   - Recursively find nice substrings in each part

2. **Sliding Window**: More complex but potentially more efficient for certain cases

This brute force solution is acceptable given the constraint that string length ≤ 100.

# Tags

- String
- Brute Force
- Two Pointers
- Hash Set

