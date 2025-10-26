## Problem

https://leetcode.com/problems/repeated-substring-pattern/description/

```
Given a string s, check if it can be constructed by taking a substring of it and appending multiple copies of the substring together.

Example 1:

Input: s = "abab"
Output: true
Explanation: It is the substring "ab" twice.

Example 2:

Input: s = "aba"
Output: false

Example 3:

Input: s = "abcabcabcabc"
Output: true
Explanation: It is the substring "abc" four times or the substring "abcabc" twice.

Constraints:

1 <= s.length <= 104
s consists of lowercase English letters.
```

## Observations

1. **Pattern Length Constraint**: If a string can be constructed by repeating a substring, the length of that substring must be a divisor of the total string length.
   - For example: "abab" (length 4) can be formed by "ab" (length 2), where 2 divides 4.

2. **Multiple Valid Patterns**: A string might have multiple valid repeating patterns of different lengths.
   - "abcabcabcabc" can be formed by "abc" (repeated 4 times) or "abcabc" (repeated 2 times).

3. **Minimum Repetitions**: For a valid pattern, it must be repeated at least twice (otherwise it's just the original string).

4. **Brute Force Approach**: We can check all possible substring lengths from 1 to n/2 (where n is string length).

5. **Smart Trick**: There's an elegant solution using string concatenation - if s is made of repeated patterns, then s should appear in (s + s) starting from index 1 to len(s)-1.

## Solution

### Approach 1: Brute Force
```cpp
bool repeatedSubstringPattern(string s) {
    int n = s.length();
    
    // Try all possible pattern lengths from 1 to n/2
    for (int len = 1; len <= n / 2; len++) {
        if (n % len == 0) {  // Pattern length must divide string length
            string pattern = s.substr(0, len);
            string constructed = "";
            
            // Build string by repeating the pattern
            for (int i = 0; i < n / len; i++) {
                constructed += pattern;
            }
            
            if (constructed == s) {
                return true;
            }
        }
    }
    return false;
}
```

**Time Complexity**: O(n²) - for each divisor, we construct and compare strings
**Space Complexity**: O(n) - for storing the constructed string

### Approach 2: Optimized Brute Force
```cpp
bool repeatedSubstringPattern(string s) {
    int n = s.length();
    
    for (int len = 1; len <= n / 2; len++) {
        if (n % len == 0) {
            bool isValid = true;
            
            // Check if every character matches the pattern
            for (int i = len; i < n; i++) {
                if (s[i] != s[i % len]) {
                    isValid = false;
                    break;
                }
            }
            
            if (isValid) return true;
        }
    }
    return false;
}
```

**Time Complexity**: O(n²) - worst case still checks all characters for each divisor
**Space Complexity**: O(1) - no extra space needed

### Approach 3: String Concatenation Trick
```cpp
bool repeatedSubstringPattern(string s) {
    string doubled = s + s;
    // Remove first and last character to avoid trivial matches
    string sub = doubled.substr(1, doubled.length() - 2);
    
    // If s is made of repeated patterns, it should appear in the middle
    return sub.find(s) != string::npos;
}
```

**Key Insight**: If string s is formed by repeating a pattern P, then:
- s = P + P + ... + P (k times)
- s + s = P + P + ... + P + P + P + ... + P (2k times)
- After removing first and last character from (s + s), if we can still find s, then s must be made of repeated patterns.

**Example**: 
- s = "abab" → s + s = "abababab"
- After removing first and last: "bababa"
- "abab" can be found at index 1 in "bababa" → return true

**Time Complexity**: O(n) - string search is typically O(n) with KMP or similar algorithms
**Space Complexity**: O(n) - for storing the doubled string

### Approach 4: Mathematical/KMP-based (Most Efficient)
The concatenation trick can be implemented more efficiently using the concept from KMP algorithm's failure function, but the above approaches are sufficient for most interview scenarios.

## Tags

array, string, greedy