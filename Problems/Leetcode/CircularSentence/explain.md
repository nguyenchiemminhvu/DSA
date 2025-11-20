## Problem

https://leetcode.com/problems/circular-sentence/description/

```
A sentence is a list of words that are separated by a single space with no leading or trailing spaces.

For example, "Hello World", "HELLO", "hello world hello world" are all sentences.
Words consist of only uppercase and lowercase English letters. Uppercase and lowercase English letters are considered different.

A sentence is circular if:

The last character of each word in the sentence is equal to the first character of its next word.
The last character of the last word is equal to the first character of the first word.
For example, "leetcode exercises sound delightful", "eetcode", "leetcode eats soul" are all circular sentences. However, "Leetcode is cool", "happy Leetcode", "Leetcode" and "I like Leetcode" are not circular sentences.

Given a string sentence, return true if it is circular. Otherwise, return false.

Example 1:

Input: sentence = "leetcode exercises sound delightful"
Output: true
Explanation: The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
- leetcode's last character is equal to exercises's first character.
- exercises's last character is equal to sound's first character.
- sound's last character is equal to delightful's first character.
- delightful's last character is equal to leetcode's first character.
The sentence is circular.

Example 2:

Input: sentence = "eetcode"
Output: true
Explanation: The words in sentence are ["eetcode"].
- eetcode's last character is equal to eetcode's first character.
The sentence is circular.

Example 3:

Input: sentence = "Leetcode is cool"
Output: false
Explanation: The words in sentence are ["Leetcode", "is", "cool"].
- Leetcode's last character is not equal to is's first character.
The sentence is not circular.

Constraints:

1 <= sentence.length <= 500
sentence consist of only lowercase and uppercase English letters and spaces.
The words in sentence are separated by a single space.
There are no leading or trailing spaces.
```

## Observations

1. **Circular Property**: A sentence is circular if it forms a "chain" where each word's last character matches the next word's first character, and the last word's last character matches the first word's first character.

2. **Two Key Conditions**:
   - **Adjacent Word Connection**: For each consecutive pair of words `words[i]` and `words[i+1]`, we need `words[i][-1] == words[i+1][0]`
   - **Circular Connection**: The last word must connect back to the first word: `words[last][-1] == words[first][0]`

3. **Single Word Edge Case**: If there's only one word, it's circular if its first and last characters are the same.

4. **Case Sensitivity**: The problem explicitly states that uppercase and lowercase letters are considered different, so we need exact character matching.

5. **Input Constraints**: 
   - No leading/trailing spaces
   - Words separated by single spaces
   - Only English letters and spaces
   - Length between 1-500 characters

6. **Algorithmic Insight**: Instead of handling the circular connection separately, we can append the first word to the end of the word list and then check all consecutive pairs in a single loop.

## Solution

The provided solution uses an **elegant circular array technique** to simplify the validation process:

### Algorithm Breakdown:

1. **Smart Circular Handling**: By appending `words[0]` to the end, we convert the circular validation into a linear check. This eliminates the need for special case handling of the last-to-first word connection.

2. **Single Loop**: After the modification, we only need one loop checking `words[i-1][-1] != words[i][0]` for all consecutive pairs, including the crucial last-to-first connection.

3. **Character Access**: 
   - `words[i-1][-1]`: Last character of previous word
   - `words[i][0]`: First character of current word

### Step-by-Step Example:

For `sentence = "leetcode exercises sound delightful"`:

1. `words = ["leetcode", "exercises", "sound", "delightful"]`
2. `words.append(words[0])` → `["leetcode", "exercises", "sound", "delightful", "leetcode"]`
3. Check pairs:
   - `"leetcode"[-1] == "exercises"[0]` → `'e' == 'e'` ✓
   - `"exercises"[-1] == "sound"[0]` → `'s' == 's'` ✓  
   - `"sound"[-1] == "delightful"[0]` → `'d' == 'd'` ✓
   - `"delightful"[-1] == "leetcode"[0]` → `'l' == 'l'` ✓
4. All pairs match → Return `True`

### Time & Space Complexity:

- **Time Complexity**: O(n), where n is the number of words. We iterate through the words once.
- **Space Complexity**: O(n) for storing the word list after splitting.

### Alternative Approaches:

1. **Without Array Modification**: Check adjacent pairs normally, then separately check `words[-1][-1] == words[0][0]`
2. **Single Pass String Scanning**: Process the sentence character by character without splitting into words
3. **Modular Arithmetic**: Use `(i + 1) % len(words)` to handle circular indexing

The given solution is optimal for readability and simplicity while maintaining good performance.

## Tags

- String Processing
- Array Manipulation  
- Circular Array
- Pattern Matching
- Text Parsing

