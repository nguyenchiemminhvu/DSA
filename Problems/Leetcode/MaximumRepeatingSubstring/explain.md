## Problem

https://leetcode.com/problems/maximum-repeating-substring/description/

```
For a string sequence, a string word is k-repeating if word concatenated k times is a substring of sequence. The word's maximum k-repeating value is the highest value k where word is k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value is 0.

Given strings sequence and word, return the maximum k-repeating value of word in sequence.

Example 1:

Input: sequence = "ababc", word = "ab"
Output: 2
Explanation: "abab" is a substring in "ababc".

Example 2:

Input: sequence = "ababc", word = "ba"
Output: 1
Explanation: "ba" is a substring in "ababc". "baba" is not a substring in "ababc".

Example 3:

Input: sequence = "ababc", word = "ac"
Output: 0
Explanation: "ac" is not a substring in "ababc". 

Constraints:

1 <= sequence.length <= 100
1 <= word.length <= 100
sequence and word contains only lowercase English letters.
```

## Observations

1. **Problem Understanding**: We need to find the maximum number of times we can concatenate `word` such that the result is still a substring of `sequence`.

2. **Key Insights**:
   - If `word` itself is not in `sequence`, the answer is 0
   - The maximum possible k-value is `len(sequence) // len(word)` (when the entire sequence is made of repeated words)
   - We need to check if `word * k` (word repeated k times) is a substring of sequence

3. **Examples Analysis**:
   - Example 1: `sequence = "ababc"`, `word = "ab"`
     - "ab" (k=1): ✓ exists in "ababc" at position 0
     - "abab" (k=2): ✓ exists in "ababc" at position 0
     - "ababab" (k=3): ✗ doesn't exist (length exceeds sequence)
     - Answer: 2
   
   - Example 2: `sequence = "ababc"`, `word = "ba"`
     - "ba" (k=1): ✓ exists in "ababc" at position 1
     - "baba" (k=2): ✗ doesn't exist as substring
     - Answer: 1

4. **Edge Cases**:
   - Word longer than sequence → return 0
   - Word not present in sequence → return 0
   - Word equals sequence → return 1

5. **Optimization Opportunity**: Since we're looking for the maximum k, we can use binary search on the possible k values instead of checking sequentially.

## Solution

### Approach 1: Brute Force (Simple)
```python
def maxRepeating(self, sequence: str, word: str) -> int:
    max_k = len(sequence) // len(word)
    
    for k in range(max_k, 0, -1):
        if word * k in sequence:
            return k
    
    return 0
```

**Time Complexity**: O(n²) where n is length of sequence
**Space Complexity**: O(k * m) where k is the result and m is length of word

### Approach 2: Binary Search (Optimal)
```python
def maxRepeating(self, sequence: str, word: str) -> int:
    ns = len(sequence)
    nw = len(word)
    left = 1
    right = ns // nw
    res = 0
    
    while left <= right:
        mid = left + (right - left) // 2
        if sequence.find(word * mid) != -1:
            res = mid
            left = mid + 1  # Try larger k
        else:
            right = mid - 1  # Try smaller k
    
    return res
```

**Time Complexity**: O(n * log(n/m)) where n is length of sequence, m is length of word
**Space Complexity**: O(k * m) for string concatenation

### Algorithm Explanation:

1. **Binary Search Setup**: 
   - Search space: [1, len(sequence) // len(word)]
   - This represents all possible k values

2. **Binary Search Logic**:
   - For each mid value, create `word * mid` and check if it's in sequence
   - If found: update result and search for larger k (left = mid + 1)
   - If not found: search for smaller k (right = mid - 1)

3. **Why Binary Search Works**:
   - If `word * k` is not a substring, then `word * (k+1)`, `word * (k+2)`, etc. won't be substrings either
   - This monotonic property allows binary search

### Alternative Approach: Dynamic Programming
```python
def maxRepeating(self, sequence: str, word: str) -> int:
    n, m = len(sequence), len(word)
    if m > n:
        return 0
    
    # dp[i] = max repeating ending at position i
    dp = [0] * n
    max_repeat = 0
    
    for i in range(m - 1, n):
        if sequence[i - m + 1:i + 1] == word:
            dp[i] = 1 if i < m else dp[i - m] + 1
            max_repeat = max(max_repeat, dp[i])
    
    return max_repeat
```

**Time Complexity**: O(n * m)
**Space Complexity**: O(n)

# Tags

- String
- Binary Search
- Dynamic Programming
- Substring Search
- String Matching
- Two Pointers (alternative approach)

**Difficulty**: Easy-Medium
**Companies**: Amazon, Microsoft, Google
**Similar Problems**: 
- Repeated Substring Pattern (LeetCode 459)
- Longest Repeating Character Replacement (LeetCode 424)

