## Problem

https://leetcode.com/problems/top-k-frequent-words/description/

```
Given an array of strings words and an integer k, return the k most frequent strings.

Return the answer sorted by:
1. Frequency from highest to lowest
2. Lexicographical order for words with the same frequency

Constraints:
- 1 <= words.length <= 500
- 1 <= words[i].length <= 10
- words[i] consists of lowercase English letters
- k is in the range [1, number of unique words]

Example 1:
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]

Example 2:
Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
```

## Observations

1. **Frequency Counting**: We need to count how many times each word appears in the input array.

2. **Two-Level Sorting**:
   - Primary sort: By frequency (descending - most frequent first)
   - Secondary sort: By lexicographical order (ascending - alphabetically)

3. **Key Insight**: Words with the same frequency must be ordered alphabetically. For example, if "is" and "sunny" both appear 3 times, we need "is" before "sunny".

4. **Efficient Approach**: 
   - Use a hash map to count frequencies: O(n)
   - Sort unique words with custom comparator: O(m log m) where m is number of unique words
   - Return first k elements: O(k)

5. **Follow-up Challenge**: The problem asks if we can solve it in O(n log k) time using a heap/priority queue of size k instead of sorting all unique words.

## Solution

### Approach: Hash Map + Sorting

```python
from typing import List
from collections import defaultdict

class Solution:
    def topKFrequent(self, words: List[str], top: int) -> List[str]:
        # Step 1: Count frequency of each word
        f = defaultdict(int)
        for word in words:
            f[word] += 1
        
        # Step 2: Get unique words and sort by custom key
        words = list(set(words))
        words.sort(key=lambda x: (-f[x], x))
        
        # Step 3: Return top k words
        return words[:top]
```

### Explanation

1. **Frequency Map** (`f`):
   - Use `defaultdict(int)` to count occurrences
   - Iterate through all words: O(n) time
   - Space: O(m) where m is number of unique words

2. **Custom Sorting Key**:
   ```python
   key=lambda x: (-f[x], x)
   ```
   - `-f[x]`: Negative frequency for descending order (higher frequency first)
   - `x`: Lexicographical order for ascending alphabetical sort
   - Python's tuple comparison: compares first element, then second if tied

3. **Example Walkthrough** (Example 1):
   ```
   Input: ["i","love","leetcode","i","love","coding"], k = 2
   
   After counting:
   f = {"i": 2, "love": 2, "leetcode": 1, "coding": 1}
   
   After sorting by (-frequency, word):
   - "i": (-2, "i")
   - "love": (-2, "love")
   - "coding": (-1, "coding")
   - "leetcode": (-1, "leetcode")
   
   Result: ["i", "love"]
   ```

### Complexity Analysis

- **Time Complexity**: O(n + m log m)
  - O(n): Count frequencies (n = total number of words)
  - O(m): Convert to unique words (m = unique words)
  - O(m log m): Sort unique words
  - O(k): Slice top k elements
  - Total: O(n + m log m)

- **Space Complexity**: O(m)
  - O(m): Frequency map
  - O(m): List of unique words
  - O(1): Sorting is in-place (Python's Timsort)

### Alternative: Min-Heap Approach (O(n log k))

For the follow-up challenge, we can use a min-heap of size k:

```python
import heapq
from collections import Counter

class Solution:
    def topKFrequent(self, words: List[str], k: int) -> List[str]:
        count = Counter(words)
        
        # Min-heap of size k
        # Note: Use (-freq, word) for max-freq but min-lexical
        heap = []
        for word, freq in count.items():
            heapq.heappush(heap, (freq, word))
            if len(heap) > k:
                heapq.heappop(heap)
        
        # Extract and reverse to get descending order
        result = []
        while heap:
            result.append(heapq.heappop(heap)[1])
        
        return result[::-1]
```

**Note**: The heap approach requires careful handling of the comparison to ensure correct ordering for both frequency and lexicographical requirements.

# Tags

#hash-map #sorting #heap #priority-queue #string #frequency-counting #top-k

