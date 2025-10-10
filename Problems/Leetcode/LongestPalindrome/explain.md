## Problem

https://leetcode.com/problems/longest-palindrome/

```
Given a string s which consists of lowercase or uppercase letters, return the length of the longest palindrome that can be built with those letters.

Letters are case sensitive, for example, "Aa" is not considered a palindrome.

Example 1:

Input: s = "abccccdd"
Output: 7
Explanation: One longest palindrome that can be built is "dccaccd", whose length is 7.

Example 2:

Input: s = "a"
Output: 1
Explanation: The longest palindrome that can be built is "a", whose length is 1.

Constraints:

1 <= s.length <= 2000
s consists of lowercase and/or uppercase English letters only.
```

## Observations

1. **Palindrome Structure**: A palindrome can have at most one character with an odd frequency (which would be placed in the center). All other characters must appear an even number of times.

2. **Character Frequency**: We need to count the frequency of each character in the string. For building the longest palindrome:
   - For characters with even frequency: use all occurrences
   - For characters with odd frequency: use (frequency - 1) occurrences, saving one character for potential center

3. **Case Sensitivity**: The problem states that uppercase and lowercase letters are different (e.g., 'A' ≠ 'a').

4. **Greedy Approach**: To maximize palindrome length, we should use as many characters as possible while maintaining the palindrome property.

5. **Center Character**: If there are any characters with odd frequencies, we can place one character in the center to increase the palindrome length by 1.

## Solution

**Algorithm Explanation:**

1. **Frequency Counting**: 
   - Create a frequency array of size 128 (covers all ASCII characters)
   - Count frequency of each character in the input string

2. **Sort Frequencies**: 
   - Sort frequencies in descending order to process higher frequencies first
   - This doesn't affect correctness but makes the algorithm more intuitive

3. **Calculate Palindrome Length**:
   - For each frequency, add `(val - (val & 1))` to the result
   - `val & 1` extracts the least significant bit, which is 1 for odd numbers and 0 for even numbers
   - `val - (val & 1)` gives us the largest even number ≤ val
   - This represents the maximum number of characters we can use from this frequency while maintaining palindrome property

4. **Add Center Character**:
   - If `s > longest`, it means there are characters with odd frequencies
   - We can place one character in the center, so add 1 to the result

**Time Complexity**: O(n + k log k) where n is the length of string and k is the number of unique characters (at most 128)

**Space Complexity**: O(k) for the frequency array

**Key Insight**: The bit manipulation `val & 1` is an efficient way to check if a number is odd, and `val - (val & 1)` gives us the largest even number less than or equal to val, which represents the maximum usable characters for palindrome construction.

## Tags

string