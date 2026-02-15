## Problem

https://leetcode.com/problems/weighted-word-mapping/

```
You are given an array of strings words, where each string represents a word containing lowercase English letters.

You are also given an integer array weights of length 26, where weights[i] represents the weight of the ith lowercase English letter.

The weight of a word is defined as the sum of the weights of its characters.

For each word, take its weight modulo 26 and map the result to a lowercase English letter using reverse alphabetical order (0 -> 'z', 1 -> 'y', ..., 25 -> 'a').

Return a string formed by concatenating the mapped characters for all words in order.

Example 1:
Input: words = ["abcd","def","xyz"], weights = [5,3,12,14,1,2,3,2,10,6,6,9,7,8,7,10,8,9,6,9,9,8,3,7,7,2]
Output: "rij"
Explanation:
- The weight of "abcd" is 5 + 3 + 12 + 14 = 34. The result modulo 26 is 34 % 26 = 8, which maps to 'r'.
- The weight of "def" is 14 + 1 + 2 = 17. The result modulo 26 is 17 % 26 = 17, which maps to 'i'.
- The weight of "xyz" is 7 + 7 + 2 = 16. The result modulo 26 is 16 % 26 = 16, which maps to 'j'.
Thus, the string formed by concatenating the mapped characters is "rij".

Example 2:
Input: words = ["a","b","c"], weights = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
Output: "yyy"
Explanation: Each word has weight 1. The result modulo 26 is 1 % 26 = 1, which maps to 'y'.

Example 3:
Input: words = ["abcd"], weights = [7,5,3,4,3,5,4,9,4,2,2,7,10,2,5,10,6,1,2,2,4,1,3,4,4,5]
Output: "g"
Explanation: The weight of "abcd" is 7 + 5 + 3 + 4 = 19. The result modulo 26 is 19 % 26 = 19, which maps to 'g'.

Constraints:
- 1 <= words.length <= 100
- 1 <= words[i].length <= 10
- weights.length == 26
- 1 <= weights[i] <= 100
- words[i] consists of lowercase English letters.
```

## Observations

1. **Character Weight Mapping**: Each lowercase letter 'a' to 'z' has a corresponding weight in the `weights` array at indices 0 to 25.

2. **Word Weight Calculation**: For each word, we sum up the weights of all its characters. The character 'a' maps to `weights[0]`, 'b' to `weights[1]`, and so on.

3. **Modulo Operation**: The total weight is taken modulo 26 to get a value in the range [0, 25].

4. **Reverse Alphabetical Mapping**: The modulo result is mapped to a character in reverse alphabetical order:
   - 0 → 'z'
   - 1 → 'y'
   - 2 → 'x'
   - ...
   - 25 → 'a'
   
   This can be computed as: `chr((25 - modulo_result) + ord('a'))`

5. **Result Construction**: Concatenate all mapped characters in order to form the final string.

## Solution

```python
class Solution:
    def mapWordWeights(self, words: List[str], weights: List[int]) -> str:
        sums = [(sum(weights[ord(c) - ord('a')] for c in word) % 26) for word in words]
        res = [chr((25 - val) + ord('a')) for val in sums]
        return "".join(res)
```

**Explanation:**

1. **Calculate weighted sums**: For each word in `words`:
   - For each character `c` in the word, convert it to an index using `ord(c) - ord('a')` (e.g., 'a' → 0, 'b' → 1, etc.)
   - Look up the weight at that index: `weights[ord(c) - ord('a')]`
   - Sum all character weights for the word
   - Take modulo 26 to get a value in [0, 25]

2. **Map to reverse alphabet**: For each modulo result `val`:
   - Calculate `25 - val` to reverse the mapping (0 becomes 25, 1 becomes 24, etc.)
   - Convert to a character: `chr((25 - val) + ord('a'))`
   - This gives us: 0 → 'z', 1 → 'y', ..., 25 → 'a'

3. **Join results**: Concatenate all mapped characters into a single string.

**Complexity Analysis:**
- **Time Complexity**: O(n × m), where n is the number of words and m is the average length of each word. We iterate through each character of each word once.
- **Space Complexity**: O(n) for storing the intermediate results (sums and res arrays).

# Tags
`Array` `String` `Hash Table` `Math`

