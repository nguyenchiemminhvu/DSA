## Problem

https://leetcode.com/problems/palindrome-partitioning/description/

```
Given a string s, partition s such that every substring of the partition is a palindrome. 
Return all possible palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]

Constraints:
- 1 <= s.length <= 16
- s contains only lowercase English letters.
```

## Observations

1. **Backtracking Problem**: We need to find all possible ways to partition the string, which suggests a backtracking approach.

2. **Palindrome Check**: For each partition, we need to verify if a substring is a palindrome. A simple way is to compare the substring with its reverse.

3. **Partitioning Strategy**: 
   - Start from index 0 and try all possible partitions
   - For each position i, try to create partitions ending at j (where j ranges from i to n-1)
   - If s[i:j+1] is a palindrome, include it in the current partition and recursively partition the rest

4. **Small Input Size**: With constraint `s.length <= 16`, exponential time complexity is acceptable.

5. **Complete Search**: We need to explore all possible partitioning combinations, making backtracking ideal.

## Solution

### Approach: Backtracking with DFS

**Algorithm:**
1. Use a DFS function that takes a starting index `i`
2. Base case: If `i >= n`, we've partitioned the entire string, so add the current partition to results
3. Recursive case: Try all possible substrings starting at index `i`:
   - For each ending position `j` from `i` to `n-1`:
     - Check if `s[i:j+1]` is a palindrome (compare with its reverse)
     - If yes, add it to current partition (`tmp`)
     - Recursively process the remaining string starting at `j+1`
     - Backtrack by removing the last added substring

**Code Explanation:**

```python
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        n = len(s)
        res = []           # Store all valid partitions
        tmp = []           # Current partition being built
        
        def dfs(i: int) -> None:
            # Base case: reached end of string
            if i >= n:
                res.append(tmp[:])  # Add a copy of current partition
                return
            
            # Try all possible partitions starting at index i
            for j in range(i, n):
                # Check if substring s[i:j+1] is a palindrome
                if s[i:j+1] == s[i:j+1][::-1]:
                    tmp.append(s[i:j+1])    # Choose
                    dfs(j + 1)               # Explore
                    tmp.pop()                # Backtrack
        
        dfs(0)
        return res
```

**Key Points:**

1. **Palindrome Check**: `s[i:j+1] == s[i:j+1][::-1]` - reverses the substring and compares
2. **Backtracking Template**: Choose → Explore → Unchoose
3. **Deep Copy**: `tmp[:]` creates a copy because `tmp` is modified during recursion
4. **State Space**: At each position, we try partitions of different lengths

**Complexity Analysis:**

- **Time Complexity**: $O(n \cdot 2^n)$
  - In the worst case, every substring is a palindrome (e.g., "aaa")
  - For a string of length n, there are $2^{n-1}$ ways to partition it
  - Each partition requires O(n) to check palindromes and copy to result
  
- **Space Complexity**: $O(n)$
  - Recursion depth is at most n (when each character is a separate partition)
  - `tmp` array stores at most n elements
  - Not counting the output space

**Example Walkthrough:**

For `s = "aab"`:
1. Start at index 0:
   - Try "a" (palindrome) → recurse from index 1
     - Try "a" (palindrome) → recurse from index 2
       - Try "b" (palindrome) → reached end → add ["a","a","b"]
     - Try "ab" (not palindrome) → skip
   - Try "aa" (palindrome) → recurse from index 2
     - Try "b" (palindrome) → reached end → add ["aa","b"]
   - Try "aab" (not palindrome) → skip

Result: `[["a","a","b"], ["aa","b"]]`

# Tags

`Backtracking` `String` `Dynamic Programming` `Depth-First Search`

