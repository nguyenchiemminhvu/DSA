## Problem

https://leetcode.com/problems/ransom-note/description/

```
Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.

Each letter in magazine can only be used once in ransomNote.

Example 1:

Input: ransomNote = "a", magazine = "b"
Output: false

Example 2:

Input: ransomNote = "aa", magazine = "ab"
Output: false

Example 3:

Input: ransomNote = "aa", magazine = "aab"
Output: true

Constraints:

1 <= ransomNote.length, magazine.length <= 105
ransomNote and magazine consist of lowercase English letters.
```

## Observations

1. **Character Frequency Problem**: This is fundamentally a character frequency counting problem where we need to check if the ransom note can be formed using available characters from the magazine.

2. **One-time Use Constraint**: Each character in the magazine can only be used once, meaning we need to track how many times each character appears and ensure we don't exceed the available count.

3. **ASCII Character Set**: The solution uses an array of size 128 to cover the entire ASCII character set, though the problem states only lowercase English letters are used (could optimize to size 26).

4. **Two-Pass Approach**: The algorithm processes the magazine first to count available characters, then processes the ransom note to "consume" characters and check availability.

5. **Early Termination**: The solution can return `False` immediately when a character is needed but not available, providing efficient early termination.

## Solution

1. **Initialize Frequency Array**: Create an array `f` of size 128 to store character frequencies, initialized to 0.

2. **Count Magazine Characters**: Iterate through the magazine string `t` and increment the count for each character using `ord(c)` as the index.

3. **Process Ransom Note**: For each character in the ransom note string `s`:
   - Decrement the count in the frequency array
   - If the count becomes negative, it means we need more of this character than available in the magazine
   - Return `False` immediately if any character count goes negative

4. **Success Case**: If we successfully process all characters in the ransom note without any count going negative, return `True`.

**Time Complexity**: O(n + m) where n is the length of the ransom note and m is the length of the magazine.

**Space Complexity**: O(1) - constant space for the fixed-size frequency array (128 elements).

**Key Insights:**
- The frequency array acts as a "bank" of available characters
- Decrementing and checking for negative values efficiently handles the "use once" constraint
- Using ASCII values as array indices provides O(1) character lookup and update

## Tags

string, hash table