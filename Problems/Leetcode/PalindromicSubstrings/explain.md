## Problem

https://leetcode.com/problems/palindromic-substrings/description/

Given a string `s`, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

**Example 1:**
```
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
```

**Example 2:**
```
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
```

**Constraints:**
- `1 <= s.length <= 1000`
- `s` consists of lowercase English letters.

## Observations

1. **Every single character is a palindrome**: For a string of length `n`, we always have at least `n` palindromic substrings (the individual characters themselves).

2. **Palindromes have a center**: Every palindrome has a center. The center can be:
   - A single character (for odd-length palindromes like "aba")
   - Between two characters (for even-length palindromes like "abba")

3. **Expandability property**: Once we identify a center, we can expand outward while characters match. The moment characters don't match, we stop.

4. **Brute force approach**: We could check every substring to see if it's a palindrome, but this would be O(n³) - O(n²) substrings × O(n) to check each.

5. **Expand-around-center optimization**: By leveraging the palindrome center property, we reduce complexity to O(n²) - O(n) possible centers × O(n) expansion per center in worst case.

6. **No memorization benefit for recursive approach**: The recursive memoization approach in the commented code has overlapping subproblems but the memoization table doesn't provide significant savings compared to the expand-around approach because we still must compute expansion at each position.

## Solution

### Approach: Expand Around Center (Active Solution)

**Core Idea**: For each possible palindrome center, expand outward as long as characters match.

```python
def countSubstrings(self, s: str) -> int:
    n = len(s)
    res = 0
    
    def count_palin(l: int, r: int) -> int:
        count = 0
        while l >= 0 and r < n and s[l] == s[r]:
            count += 1
            l -= 1
            r += 1
        return count
    
    for i in range(n):
        res += count_palin(i, i)          # Odd-length palindromes (center at i)
        if i + 1 < n:
            res += count_palin(i, i + 1)  # Even-length palindromes (center between i and i+1)
    return res
```

**Step-by-step walkthrough with "aaa":**

1. i=0: 
   - count_palin(0, 0): "a" matches → count=1, expand to (-1,1) → stop. Total: 1
   - count_palin(0, 1): "a"=="a" → count=1, expand to (-1,2) → stop. Total: 1
   - Subtotal: 2

2. i=1:
   - count_palin(1, 1): "a" matches → count=1, expand to (0,2) → "a"=="a" → count=2, expand to (-1,3) → stop. Total: 2
   - count_palin(1, 2): "a"=="a" → count=1, expand to (0,3) → stop. Total: 1
   - Subtotal: 3

3. i=2:
   - count_palin(2, 2): "a" matches → count=1, expand to (1,3) → stop. Total: 1
   - Skip count_palin(2, 3) as i+1=3 >= n
   - Subtotal: 1

**Total: 2 + 3 + 1 = 6** ✓

**Time Complexity**: O(n²)
- We have n possible centers (n for odd-length + n-1 for even-length = 2n-1 centers)
- For each center, expansion in the worst case (like "aaaa...") is O(n)
- Total: O(n) × O(n) = O(n²)

**Space Complexity**: O(1)
- Only using a counter and loop variables; no additional data structures

### Alternative Approach: Recursive Memoization (Commented Code)

The commented code uses a recursive function that returns the number of palindromes extending from a center:

```python
def F(l: int, r: int) -> int:
    if l < 0 or r >= n:
        return 0
    if (l, r) in mem:
        return mem[(l, r)]
    ways = 0
    if s[l] == s[r]:
        ways = 1 + F(l - 1, r + 1)
    mem[(l, r)] = ways
    return ways
```

This approach counts palindromes by recursively expanding while memoizing results. However:
- **Time Complexity**: Still O(n²) worst case, but with memoization overhead
- **Space Complexity**: O(n²) for the memoization table + O(n) for recursion stack
- **Verdict**: More complex and uses more space for similar performance

**Why expand-around-center is better:**
- Cleaner iterative code
- Better space efficiency (O(1) vs O(n²))
- No recursion overhead
- Same time complexity with better practical performance

# Tags

#strings #palindromes #two-pointers #expand-around-center

