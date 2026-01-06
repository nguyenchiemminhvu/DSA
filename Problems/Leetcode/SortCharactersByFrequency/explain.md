## Problem

https://leetcode.com/problems/sort-characters-by-frequency/description/

Given a string `s`, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

**Example 1:**
```
Input: s = "tree"
Output: "eert"
Explanation: 'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
```

**Example 2:**
```
Input: s = "cccaaa"
Output: "aaaccc"
Explanation: Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
Note that "cacaca" is incorrect, as the same characters must be together.
```

**Example 3:**
```
Input: s = "Aabb"
Output: "bbAa"
Explanation: "bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
```

**Constraints:**
- `1 <= s.length <= 5 * 10^5`
- `s` consists of uppercase and lowercase English letters and digits.

## Observations

1. **Frequency Counting**: We need to count how many times each character appears in the string.

2. **Sorting by Frequency**: Characters must be sorted in decreasing order of their frequency. Characters with higher frequency should appear first.

3. **Same Characters Together**: All occurrences of the same character must be grouped together in the output.

4. **Case Sensitivity**: Uppercase and lowercase letters are treated as different characters (e.g., 'A' and 'a' are different).

5. **Multiple Valid Answers**: When characters have the same frequency, they can appear in any order relative to each other.

## Solution

### Approach: Heap-based Sorting

This solution uses a **max heap** (priority queue) to efficiently sort characters by frequency.

**Algorithm Steps:**
1. **Count Frequencies**: Use `Counter` to count the frequency of each character in the string
2. **Build Max Heap**: Create a max heap where elements are ordered by frequency (use negative values since Python's heapq is a min heap)
3. **Extract and Build Result**: Pop elements from the heap and append each character multiplied by its count to the result string

### Implementation

```python
from collections import Counter
import heapq

class Solution:
    def frequencySort(self, s: str) -> str:
        # Step 1: Count frequency of each character
        f = Counter(s)
        
        # Step 2: Build a max heap based on frequency
        # Use negative frequency for max heap (Python heapq is min heap)
        pq = []
        for k, v in f.items():
            heapq.heappush(pq, (-v, k))
        
        # Step 3: Extract characters from heap and build result
        res = ""
        while pq:
            count, ch = heapq.heappop(pq)
            count *= -1  # Convert back to positive
            res += ch * count  # Append character 'count' times
        return res
```

### Complexity Analysis

**Time Complexity: O(n log k)**
- Counting frequencies: O(n) where n is the length of string
- Building the heap: O(k log k) where k is the number of unique characters
- Extracting from heap: O(k log k)
- Overall: O(n + k log k) = O(n log k) since k ≤ n

**Space Complexity: O(n)**
- Counter storage: O(k) for unique characters
- Heap storage: O(k)
- Result string: O(n)
- Overall: O(n)

### Key Insights

1. **Max Heap Trick**: Since Python's `heapq` implements a min heap, we use negative frequencies (`-v`) to simulate a max heap behavior.

2. **String Multiplication**: Python allows `ch * count` to repeat a character multiple times efficiently.

3. **Counter Utility**: The `Counter` class from collections module provides an elegant way to count character frequencies.

### Alternative Approaches

1. **Sorting**: Count frequencies, then sort by frequency in descending order - O(n + k log k)
2. **Bucket Sort**: Use frequency as bucket index for O(n) time but requires more space
3. **Custom Sorting with Dictionary**: Similar to heap approach but using sorted() function

# Tags

`Hash Table` `String` `Sorting` `Heap (Priority Queue)` `Counting`

