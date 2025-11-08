## Problem

https://leetcode.com/problems/maximum-number-of-words-you-can-type/description/

```
There is a malfunctioning keyboard where some letter keys do not work. All other keys on the keyboard work properly.

Given a string text of words separated by a single space (no leading or trailing spaces) and a string brokenLetters of all distinct letter keys that are broken, return the number of words in text you can fully type using this keyboard.

Example 1:

Input: text = "hello world", brokenLetters = "ad"
Output: 1
Explanation: We cannot type "world" because the 'd' key is broken.

Example 2:

Input: text = "leet code", brokenLetters = "lt"
Output: 1
Explanation: We cannot type "leet" because the 'l' and 't' keys are broken.

Example 3:

Input: text = "leet code", brokenLetters = "e"
Output: 0
Explanation: We cannot type either word because the 'e' key is broken.

Constraints:

1 <= text.length <= 104
0 <= brokenLetters.length <= 26
text consists of words separated by a single space without any leading or trailing spaces.
Each word only consists of lowercase English letters.
brokenLetters consists of distinct lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to count how many complete words can be typed when certain keys on the keyboard are broken.

2. **Key Constraints**: 
   - A word can only be counted if ALL its characters can be typed (no broken letters)
   - If even one character in a word uses a broken key, the entire word cannot be typed
   - We need to return the total count of fully typeable words

3. **Approach Strategy**:
   - Convert `brokenLetters` to a set for O(1) lookup time
   - Split the text into individual words
   - For each word, check if any character exists in the broken letters set
   - If no broken letters found in a word, increment the count

4. **Edge Cases**:
   - Empty `brokenLetters` → all words can be typed
   - All letters are broken → no words can be typed
   - Single character words with/without broken letters

5. **Time Complexity**: O(n × m) where n is the number of words and m is the average word length
6. **Space Complexity**: O(k) where k is the number of broken letters (for the set)

## Solution

The solution uses a straightforward greedy approach:

### Algorithm:
1. **Create broken letters set**: Convert `brokenLetters` string to a set for fast O(1) character lookup
2. **Split text into words**: Use `.split()` to get individual words from the input text
3. **Check each word**: For every word, iterate through its characters and check if any character is in the broken letters set
4. **Early termination**: As soon as we find a broken letter in a word, mark it as "not typeable" and break
5. **Count valid words**: Only increment counter if the word contains no broken letters

### Key Components:
- `banned_keys = set(brokenLetters)`: O(1) lookup for broken letters
- `good = True; for c in word: if c in banned_keys: good = False; break`: Early termination when broken letter found
- `count += int(good)`: Convert boolean to integer (True=1, False=0) for counting

### Example Walkthrough:
For `text = "hello world", brokenLetters = "ad"`:
1. `banned_keys = {'a', 'd'}`
2. `words = ["hello", "world"]`
3. Check "hello": h✓, e✓, l✓, l✓, o✓ → no broken letters → count = 1
4. Check "world": w✓, o✓, r✓, l✓, d✗ → contains 'd' (broken) → count remains 1
5. Return 1

### Time Complexity: O(n × m)
- n = number of words in text
- m = average length of words
- Each character lookup in set is O(1)

### Space Complexity: O(k)
- k = number of broken letters (for the set storage)
- The words list is temporary and doesn't count toward auxiliary space

# Tags

