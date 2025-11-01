## Problem

https://leetcode.com/problems/decode-the-message/description/

```
You are given the strings key and message, which represent a cipher key and a secret message, respectively. The steps to decode message are as follows:

Use the first appearance of all 26 lowercase English letters in key as the order of the substitution table.
Align the substitution table with the regular English alphabet.
Each letter in message is then substituted using the table.
Spaces ' ' are transformed to themselves.
For example, given key = "happy boy" (actual key would have at least one instance of each letter in the alphabet), we have the partial substitution table of ('h' -> 'a', 'a' -> 'b', 'p' -> 'c', 'y' -> 'd', 'b' -> 'e', 'o' -> 'f').
Return the decoded message.

Example 1:

Input: key = "the quick brown fox jumps over the lazy dog", message = "vkbs bs t suepuv"
Output: "this is a secret"
Explanation: The diagram above shows the substitution table.
It is obtained by taking the first appearance of each letter in "the quick brown fox jumps over the lazy dog".

Example 2:

Input: key = "eljuxhpwnyrdgtqkviszcfmabo", message = "zwx hnfx lqantp mnoeius ycgk vcnjrdb"
Output: "the five boxing wizards jump quickly"
Explanation: The diagram above shows the substitution table.
It is obtained by taking the first appearance of each letter in "eljuxhpwnyrdgtqkviszcfmabo".

Constraints:

26 <= key.length <= 2000
key consists of lowercase English letters and ' '.
key contains every letter in the English alphabet ('a' to 'z') at least once.
1 <= message.length <= 2000
message consists of lowercase English letters and ' '.
```

## Observations

1. **Cipher Creation**: We need to create a substitution cipher by mapping each unique letter in the key to the alphabet in order (a, b, c, ..., z).

2. **Key Processing**: The key contains spaces that should be removed, and we only care about the first appearance of each letter.

3. **Alphabet Mapping**: The first unique letter maps to 'a', second unique letter to 'b', and so on.

4. **Space Handling**: Spaces in the message remain as spaces in the decoded message.

5. **Sequential Mapping**: We iterate through the key and build our mapping dictionary as we encounter new characters.

## Solution

The solution uses a **hash map (dictionary)** approach to create and apply the substitution cipher:

### Algorithm Steps:

1. **Remove Spaces from Key**: 
   ```python
   key = "".join(key.split(' '))
   ```
   This eliminates all spaces from the key string.

2. **Build Substitution Map**:
   - Use a set `skey` to track characters we've already seen
   - Use a dictionary `d` to store the character mappings
   - Use counter `i` to track which alphabet letter to map to
   - For each character in the key:
     - If it's the first time seeing this character, map it to `chr(ord('a') + i)`
     - Increment the counter for the next mapping

3. **Handle Space Character**:
   ```python
   d[' '] = ' '
   ```
   Spaces map to themselves.

4. **Decode the Message**:
   - Convert message to a list for easy character replacement
   - Replace each character using the mapping dictionary
   - Join back into a string

### Time Complexity: O(n + m)
- O(n) to process the key and build the mapping
- O(m) to decode the message
- Where n = length of key, m = length of message

### Space Complexity: O(1)
- The dictionary will have at most 27 entries (26 letters + space)
- The set will have at most 26 entries
- Both are constant space relative to input size

### Key Insights:
- **First Appearance Only**: Using a set ensures we only map each character once
- **Sequential Alphabet**: Using `chr(ord('a') + i)` generates alphabet letters in order
- **In-Place Decoding**: Converting message to list allows efficient character replacement

## Tags

- Hash Map / Dictionary
- String Manipulation
- Substitution Cipher
- Character Mapping

