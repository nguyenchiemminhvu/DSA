## Problem

https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/

```
You are given a string word containing lowercase English letters.

Telephone keypads have keys mapped with distinct collections of lowercase English letters, which can be used to form words by pushing them. For example, the key 2 is mapped with ["a","b","c"], we need to push the key one time to type "a", two times to type "b", and three times to type "c" .

It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters. The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key. You need to find the minimum number of times the keys will be pushed to type the string word.

Return the minimum number of pushes needed to type word after remapping the keys.

An example mapping of letters to keys on a telephone keypad is given below. Note that 1, *, #, and 0 do not map to any letters.

Example 1:

Input: word = "abcde"
Output: 5
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
Total cost is 1 + 1 + 1 + 1 + 1 = 5.
It can be shown that no other mapping can provide a lower cost.

Example 2:

Input: word = "xyzxyzxyzxyz"
Output: 12
Explanation: The remapped keypad given in the image provides the minimum cost.
"x" -> one push on key 2
"y" -> one push on key 3
"z" -> one push on key 4
Total cost is 1 * 4 + 1 * 4 + 1 * 4 = 12
It can be shown that no other mapping can provide a lower cost.
Note that the key 9 is not mapped to any letter: it is not necessary to map letters to every key, but to map all the letters.

Example 3:

Input: word = "aabbccddeeffgghhiiiiii"
Output: 24
Explanation: The remapped keypad given in the image provides the minimum cost.
"a" -> one push on key 2
"b" -> one push on key 3
"c" -> one push on key 4
"d" -> one push on key 5
"e" -> one push on key 6
"f" -> one push on key 7
"g" -> one push on key 8
"h" -> two pushes on key 9
"i" -> one push on key 9
Total cost is 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 2 * 2 + 6 * 1 = 24.
It can be shown that no other mapping can provide a lower cost.

Constraints:

1 <= word.length <= 105
word consists of lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to map 26 letters to 8 keys (2-9) on a phone keypad to minimize total button pushes for typing a given word.

2. **Key Constraints**: 
   - We have 8 keys available (2-9)
   - Each letter must be mapped to exactly one key
   - The cost of typing a letter is its position on the key + 1 (1st position = 1 push, 2nd position = 2 pushes, etc.)

3. **Greedy Strategy**: To minimize total pushes, we should:
   - Assign the most frequent letters to the first positions (1 push each)
   - Distribute letters across keys to balance the load
   - Use a round-robin approach to fill keys evenly

4. **Key Capacity**: Traditional phone keypads have different capacities:
   - Keys 2, 3, 4, 6, 8, 9: 3 letters each
   - Keys 5, 7: 4 letters each (PQRS and WXYZ)
   - Total capacity: 3×6 + 4×2 = 26 letters (perfect fit)

5. **Algorithm Insight**: The solution counts character frequencies, sorts them in descending order, then distributes characters across keys using round-robin to ensure most frequent characters get the lowest push counts.

## Solution

**Time Complexity**: O(n + 26 log 26) = O(n) where n is the length of the word
**Space Complexity**: O(1) since we only use fixed-size arrays for 26 letters

**Key Points**:
1. **Frequency-based assignment**: Most frequent characters get priority for lower-cost positions
2. **Round-robin distribution**: Ensures balanced load across all 8 keys
3. **Traditional keypad layout**: Respects the standard 3-4 letter distribution per key
4. **Optimal greedy approach**: Since all letters are distinct, frequency-based greedy assignment is optimal

## Tags

array, string, greedy