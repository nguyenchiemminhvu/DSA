## Problem

https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/description/

```
Alice and Bob are playing a game. Initially, Alice has a string word = "a".

You are given a positive integer k.

Now Bob will ask Alice to perform the following operation forever:

Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".

Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.

Example 1:

Input: k = 5

Output: "b"

Explanation:

Initially, word = "a". We need to do the operation three times:

Generated string is "b", word becomes "ab".
Generated string is "bc", word becomes "abbc".
Generated string is "bccd", word becomes "abbcbccd".

Example 2:

Input: k = 10

Output: "c"

Constraints:

1 <= k <= 500
```

## Observations

1. **Pattern Recognition**: The problem follows a specific pattern where we start with "a" and in each operation:
   - Double the string by appending a transformed version
   - Each character in the appended part is the next character in the alphabet

2. **String Growth**: The string grows exponentially:
   - Initially: "a" (length 1)
   - After 1st operation: "ab" (length 2)
   - After 2nd operation: "abbc" (length 4)
   - After 3rd operation: "abbcbccd" (length 8)
   - Pattern: length becomes 2^n after n operations

3. **Character Transformation**: When appending, each character advances by 1 in the alphabet:
   - 'a' → 'b', 'b' → 'c', 'c' → 'd', etc.
   - 'z' wraps around to 'a' (modulo 26)

4. **Efficiency Consideration**: We don't need to build the actual string - we only need to track character values numerically and find the k-th position.

## Solution

1. **Initialization**: 
   - `word = [0]` represents the initial string "a" (0 = 'a')
   - `n = 1` tracks the current length

2. **Iterative Doubling**:
   - While we don't have enough characters (k >= len(word)):
   - `word.extend(word)` doubles the array size
   - Update `n *= 2` to track new length

3. **Character Transformation**:
   - For the second half of the array (indices n//2 to n-1):
   - Increment each value by 1 with modulo 26 to handle wrap-around
   - This simulates advancing each character to the next letter

4. **Result**: 
   - Return the character at position k-1 (0-indexed)
   - Convert numeric value back to character using `chr(ord('a') + value)`

**Time Complexity**: O(k) - In the worst case, we need to generate up to k characters
**Space Complexity**: O(k) - We store at most k character values

**Example Walkthrough** (k = 5):
- Start: word = [0] ("a")
- Iteration 1: word = [0, 1] ("ab")
- Iteration 2: word = [0, 1, 1, 2] ("abbc") 
- Iteration 3: word = [0, 1, 1, 2, 1, 2, 2, 3] ("abbcbccd")
- Return word[4] = 1 → 'b'

# Tags

- String Manipulation
- Simulation
- Array
- Pattern Recognition
- Mathematical

