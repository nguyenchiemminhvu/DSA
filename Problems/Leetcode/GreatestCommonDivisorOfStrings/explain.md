## Problem

https://leetcode.com/problems/greatest-common-divisor-of-strings/description/

For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).

Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.

**Example 1:**
- Input: str1 = "ABCABC", str2 = "ABC"
- Output: "ABC"

**Example 2:**
- Input: str1 = "ABABAB", str2 = "ABAB"
- Output: "AB"

**Example 3:**
- Input: str1 = "LEET", str2 = "CODE"
- Output: ""

**Constraints:**
- 1 <= str1.length, str2.length <= 1000
- str1 and str2 consist of English uppercase letters.

## Observations

1. **Common prefix approach**: The GCD string must be a prefix of both strings since it needs to divide both.

2. **Length constraint**: The length of the GCD string must be a divisor of both string lengths. If a string of length `p` divides a string of length `n`, then `n % p == 0`.

3. **Greedy reduction**: We can start with the longest possible common prefix and reduce it character by character until we find a valid GCD string.

4. **Validation**: For a candidate prefix to be the GCD, when repeated appropriately, it should reconstruct both original strings exactly.

## Solution

1. **Find common prefix**: First, we identify the longest common prefix between the two strings by comparing characters from the beginning.

2. **Iterative validation**: Starting with the full common prefix, we check if it can be a valid GCD string:
   - The prefix length must divide both string lengths evenly (`na % np == 0` and `nb % np == 0`)
   - When the prefix is repeated the appropriate number of times, it should reconstruct both original strings

3. **Greedy reduction**: If the current prefix doesn't work, we remove the last character and try again with a shorter prefix.

4. **Return result**: Once we find a valid prefix (or exhaust all possibilities), we return the result.

**Time Complexity:** O(min(m,n) × (m+n)) where m and n are the lengths of the two strings. In the worst case, we might check each prefix length and for each, we reconstruct both strings.

**Space Complexity:** O(min(m,n)) for storing the prefix array.

**Key Insight:** The GCD of two strings must be a common prefix, and its length must be a divisor of both string lengths. This constraint significantly reduces the search space.

# Tags
- String Manipulation
- Greatest Common Divisor (GCD)
- Prefix Matching
- Mathematical Properties

