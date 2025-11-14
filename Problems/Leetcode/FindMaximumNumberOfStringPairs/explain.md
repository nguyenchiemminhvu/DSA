## Problem

https://leetcode.com/problems/find-maximum-number-of-string-pairs/description/

```
You are given a 0-indexed array words consisting of distinct strings.

The string words[i] can be paired with the string words[j] if:

The string words[i] is equal to the reversed string of words[j].
0 <= i < j < words.length.
Return the maximum number of pairs that can be formed from the array words.

Note that each string can belong in at most one pair.

Example 1:

Input: words = ["cd","ac","dc","ca","zz"]
Output: 2
Explanation: In this example, we can form 2 pair of strings in the following way:
- We pair the 0th string with the 2nd string, as the reversed string of word[0] is "dc" and is equal to words[2].
- We pair the 1st string with the 3rd string, as the reversed string of word[1] is "ca" and is equal to words[3].
It can be proven that 2 is the maximum number of pairs that can be formed.

Example 2:

Input: words = ["ab","ba","cc"]
Output: 1
Explanation: In this example, we can form 1 pair of strings in the following way:
- We pair the 0th string with the 1st string, as the reversed string of words[1] is "ab" and is equal to words[0].
It can be proven that 1 is the maximum number of pairs that can be formed.

Example 3:

Input: words = ["aa","ab"]
Output: 0
Explanation: In this example, we are unable to form any pair of strings.

Constraints:

1 <= words.length <= 50
words[i].length == 2
words consists of distinct strings.
words[i] contains only lowercase English letters.
```

## Observations

1. **String Length**: All strings have exactly 2 characters, making reversal operations simple and efficient.

2. **Distinct Strings**: The array contains distinct strings, so we don't need to worry about duplicate strings affecting our count.

3. **Pairing Condition**: A string can be paired with another if one is the reverse of the other (e.g., "ab" pairs with "ba").

4. **One-to-One Mapping**: Each string can belong to at most one pair, so once a string is used in a pair, it cannot be used again.

5. **Self-Palindromes**: Strings like "aa" cannot be paired with themselves since we need `i < j` and all strings are distinct.

6. **Greedy Approach**: We can use a greedy approach - when we find a match, we should immediately count it as a pair.

## Solution

1. **Initialize**: Create an empty frequency map `f` and result counter `res = 0`.

2. **Iterate Through Words**: For each word in the input array:
   - Calculate its reverse using slicing `word[::-1]`
   - Check if the reverse exists in our frequency map
   - If it exists, we found a pair! Add the frequency count to our result
   - Add the current word to our frequency map (or increment its count)

3. **Return Result**: The total number of pairs found.

**Why This Works:**
- When we encounter a word, we check if its reverse has been seen before
- If yes, we can form pairs equal to the frequency of the reverse
- We then add the current word to our map for future reverse lookups
- This ensures we count each valid pair exactly once

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(n) - storing words in the frequency map

**Example Walkthrough:**
For `words = ["cd","ac","dc","ca","zz"]`:
- "cd": rev="dc", not in map, add "cd" to map
- "ac": rev="ca", not in map, add "ac" to map  
- "dc": rev="cd", found in map! res += 1, add "dc" to map
- "ca": rev="ac", found in map! res += 1, add "ca" to map
- "zz": rev="zz", not in map, add "zz" to map
- Result: 2 pairs

# Tags

- Hash Table
- String
- Greedy
- Frequency Map

