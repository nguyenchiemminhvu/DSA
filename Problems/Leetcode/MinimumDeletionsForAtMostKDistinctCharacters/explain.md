## Problem

https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/

```
You are given a string s consisting of lowercase English letters, and an integer k.

Your task is to delete some (possibly none) of the characters in the string so that the number of distinct characters in the resulting string is at most k.

Return the minimum number of deletions required to achieve this.

Example 1:

Input: s = "abc", k = 2

Output: 1

Explanation:

s has three distinct characters: 'a', 'b' and 'c', each with a frequency of 1.
Since we can have at most k = 2 distinct characters, remove all occurrences of any one character from the string.
For example, removing all occurrences of 'c' results in at most k distinct characters. Thus, the answer is 1.

Example 2:

Input: s = "aabb", k = 2

Output: 0

Explanation:

s has two distinct characters ('a' and 'b') with frequencies of 2 and 2, respectively.
Since we can have at most k = 2 distinct characters, no deletions are required. Thus, the answer is 0.

Example 3:

Input: s = "yyyzz", k = 1

Output: 2

Explanation:

s has two distinct characters ('y' and 'z') with frequencies of 3 and 2, respectively.
Since we can have at most k = 1 distinct character, remove all occurrences of any one character from the string.
Removing all 'z' results in at most k distinct characters. Thus, the answer is 2.

Constraints:

1 <= s.length <= 16
1 <= k <= 16
s consists only of lowercase English letters.
```

## Observations

1. **Core Problem**: We need to reduce the number of distinct characters in a string to at most `k` by deleting characters.

2. **Key Insight**: To minimize deletions, we should completely remove the characters with the lowest frequencies first, rather than partially removing characters.

3. **Greedy Strategy**: 
   - Count the frequency of each character
   - If we have more than `k` distinct characters, we need to eliminate some characters entirely
   - Always eliminate the characters with the smallest frequencies first to minimize total deletions

4. **Min-Heap Approach**: 
   - Use a min-heap to efficiently get characters with minimum frequencies
   - Keep popping characters with minimum frequencies until we have at most `k` distinct characters

5. **Edge Cases**:
   - If the number of distinct characters is already ≤ `k`, no deletions needed
   - We must eliminate entire character types, not partial occurrences

## Solution

**Algorithm**: Greedy approach using min-heap

**Time Complexity**: O(n log n) where n is the number of distinct characters
**Space Complexity**: O(n) for the frequency counter and heap

**Why this works**:
1. We count frequencies of all characters using `Counter`
2. We create a min-heap where the smallest frequency is at the top
3. We keep removing entire character types (with their full frequency) starting from the least frequent ones
4. We continue until we have at most `k` distinct characters remaining
5. The sum of frequencies of removed characters gives us the minimum deletions needed

**Example walkthrough** (`s = "yyyzz"`, `k = 1`):
- Frequencies: `{'y': 3, 'z': 2}`
- Min-heap: `[(2, 'z'), (3, 'y')]`
- We have 2 distinct characters but need at most 1
- Pop `(2, 'z')`: add 2 to result, heap becomes `[(3, 'y')]`
- Now we have 1 distinct character (≤ k), so we stop
- Return 2 deletions

# Tags

- **Greedy Algorithm**: We greedily choose to remove characters with minimum frequencies
- **Hash Map / Counter**: Used to count character frequencies
- **Heap / Priority Queue**: Min-heap to efficiently get characters with minimum frequencies
- **String Manipulation**: Processing string characters and deletions
- **Frequency Analysis**: Core technique involves analyzing character frequencies

