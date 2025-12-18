## Problem

https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

```
You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.

Return the maximum possible length of s.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Example 1:
Input: arr = ["un","iq","ue"]
Output: 4
Explanation: All the valid concatenations are:
- ""
- "un"
- "iq"
- "ue"
- "uniq" ("un" + "iq")
- "ique" ("iq" + "ue")
Maximum length is 4.

Example 2:
Input: arr = ["cha","r","act","ers"]
Output: 6
Explanation: Possible longest valid concatenations are "chaers" ("cha" + "ers") and "acters" ("act" + "ers").

Example 3:
Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
Output: 26
Explanation: The only string in arr has all 26 characters.

Constraints:
- 1 <= arr.length <= 16
- 1 <= arr[i].length <= 26
- arr[i] contains only lowercase English letters.
```

## Observations

1. **Unique Characters Constraint**: We need to form a concatenated string where all characters are unique (no duplicates).

2. **Subsequence Selection**: We can select any subsequence of the array (not necessarily contiguous), which means we can skip strings.

3. **Small Array Size**: The constraint `arr.length <= 16` is a huge hint - this suggests we can try all possible combinations (2^16 = 65,536 combinations at most).

4. **Invalid Strings**: Some strings in the input array might already have duplicate characters within themselves (like "aa"). These strings can never be part of a valid concatenation.

5. **Character Conflicts**: When trying to add a new string to our current concatenation, we must ensure none of its characters are already present in our accumulated set of characters.

6. **Backtracking Approach**: This is a classic backtracking problem where we explore all possible combinations and track the maximum length.

## Solution

The solution uses **backtracking** (DFS) to explore all valid combinations:

### Approach:
1. Use a set `ss` to track characters already used in the current concatenation
2. Use a list `tmp` to track indices of strings we've selected
3. For each position, try to add each remaining string if:
   - The string itself has no duplicate characters
   - None of its characters conflict with already selected characters
4. Recursively explore further selections
5. Backtrack by removing the string and its characters from our tracking structures
6. Keep track of the maximum length found

### Code:
```python
class Solution:
    def maxLength(self, arr: List[str]) -> int:
        n = len(arr)
        res = [0]  # Using list to allow modification in nested function
        ss = set()  # Set to track used characters
        tmp = []    # List to track selected string indices
        
        def dfs(i: int) -> None:
            # Update maximum length with current selection
            res[0] = max(res[0], sum(len(arr[idx]) for idx in tmp))
            
            # Try adding each remaining string
            for j in range(i, n):
                word = arr[j]
                
                # Skip if word has duplicate characters within itself
                if len(set(word)) != len(word):
                    continue
                
                # Skip if word has characters already in our set
                if any(c in ss for c in word):
                    continue
                
                # Add word to current combination
                for c in word:
                    ss.add(c)
                tmp.append(j)
                
                # Explore with this word included
                dfs(j + 1)
                
                # Backtrack: remove word from current combination
                tmp.pop()
                for c in word:
                    ss.remove(c)
        
        dfs(0)
        return res[0]
```

### Time Complexity:
- **O(2^n × m)** where n is the length of arr and m is the average string length
  - We explore up to 2^n combinations (each string can be included or excluded)
  - For each combination, we check characters which takes O(m) time
  - With n ≤ 16, this is 2^16 = 65,536 combinations at most

### Space Complexity:
- **O(n + 26)** = **O(n)**
  - Recursion depth: O(n) for the call stack
  - `ss` set: O(26) at most (only lowercase English letters)
  - `tmp` list: O(n) at most

### Key Points:
- Using `res[0]` instead of a simple variable allows the nested function to modify the result
- The set `ss` efficiently tracks which characters are currently used
- Early pruning (checking for duplicates in the string itself) improves performance
- The backtracking ensures we explore all valid combinations systematically

# Tags
Backtracking, DFS, Set, String, Recursion

