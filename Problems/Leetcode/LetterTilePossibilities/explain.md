## Problem

https://leetcode.com/problems/letter-tile-possibilities/description/

You have `n` tiles, where each tile has one letter `tiles[i]` printed on it. Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.

**Example 1:**
```
Input: tiles = "AAB"
Output: 8
Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
```

**Example 2:**
```
Input: tiles = "AAABBC"
Output: 188
```

**Example 3:**
```
Input: tiles = "V"
Output: 1
```

**Constraints:**
- `1 <= tiles.length <= 7`
- `tiles` consists of uppercase English letters

## Observations

1. **Permutations with Duplicates**: This is a permutation problem where we need to count all possible non-empty sequences of different lengths (from 1 to n).

2. **Duplicate Letters**: The input may contain duplicate letters. We need to avoid counting duplicate sequences. For example, with "AAB", we should count "AA" only once, not twice.

3. **Different Lengths**: Unlike standard permutation problems, we need to consider sequences of all possible lengths from 1 to n.

4. **Small Input Size**: The constraint `tiles.length <= 7` suggests that an exponential solution is acceptable. The maximum number of sequences is bounded by:
   - For length 1: at most 7 sequences
   - For length 2: at most 7 × 6 = 42 sequences
   - ...
   - For length 7: at most 7! = 5040 sequences
   - Total: bounded by O(n! × n)

5. **Two Main Approaches**:
   - **Set-based**: Generate all permutations and use a set to filter duplicates
   - **Frequency-based**: Use character frequencies to avoid generating duplicates in the first place

## Solution

### Approach 1: Backtracking with Set (Given Solution)

The provided solution uses backtracking to generate all permutations of different lengths and stores them in a set to handle duplicates.

**Algorithm:**
1. For each length `l` from 1 to n:
   - Use backtracking to generate all l-length permutations
   - Track visited positions with a `visited` array
   - Add each generated sequence to a set (automatically handles duplicates)
2. Return the size of the set

**Code:**
```python
class Solution:
    def numTilePossibilities(self, s: str) -> int:
        n = len(s)
        ss = set()
        tmp = []
        visited = [False] * n
        
        def generating(k: int, idx: int) -> None:
            if idx >= k:
                ss.add("".join(tmp))
                return
            
            for i in range(n):
                if not visited[i]:
                    tmp.append(s[i])
                    visited[i] = True
                    generating(k, idx + 1)
                    visited[i] = False
                    tmp.pop()
        
        for l in range(1, n + 1):
            generating(l, 0)
        return len(ss)
```

**Complexity:**
- **Time**: O(n! × n) - generates all permutations of all lengths
- **Space**: O(n! × n) - stores all unique sequences in the set

**Pros:**
- Simple and straightforward
- Easy to understand

**Cons:**
- Generates duplicate sequences that get filtered by the set
- Uses extra space for the set
- Not optimal for larger inputs

### Approach 2: Backtracking with Frequency Map (Optimal)

Instead of tracking visited positions, we can use a frequency map to track available characters. This avoids generating duplicate sequences altogether.

**Algorithm:**
1. Count the frequency of each character
2. Use backtracking:
   - At each step, try adding each available character
   - Decrement its frequency, recurse, then restore the frequency
   - Count each non-empty sequence (increment counter before recursing)
3. Return the total count

**Code:**
```python
class Solution:
    def numTilePossibilities(self, tiles: str) -> int:
        from collections import Counter
        freq = Counter(tiles)
        
        def backtrack():
            count = 0
            for char in freq:
                if freq[char] > 0:
                    freq[char] -= 1
                    count += 1 + backtrack()  # Count current sequence + subsequences
                    freq[char] += 1
            return count
        
        return backtrack()
```

**Complexity:**
- **Time**: O(n!) - in the worst case with all unique characters
- **Space**: O(n) - recursion depth and frequency map

**Pros:**
- More efficient - avoids generating duplicates
- Cleaner code
- Less memory usage (no set needed)

**Cons:**
- Slightly less intuitive at first

### Approach 3: Mathematical Formula (For Understanding)

For a string with character frequencies, the number of permutations of length k is:
$$\frac{k!}{f_1! \times f_2! \times ... \times f_m!}$$

where $f_i$ is the frequency of character $i$ used in that permutation.

However, implementing this directly is complex because we need to enumerate all possible ways to select characters for each length.

## Alternatives

1. **Iterative DFS with Stack**: Convert the recursive backtracking to iterative using a stack
   
2. **Trie-based Approach**: Build a trie of all possible sequences while avoiding duplicates

3. **Dynamic Programming**: Use bitmask DP where state is (selected_indices_mask), but this doesn't handle duplicate characters efficiently

4. **BFS Approach**: Use BFS to explore all sequences level by level

**Recommendation**: The frequency-based backtracking (Approach 2) is the most elegant and efficient solution for this problem.

# Tags

`Backtracking` `Permutations` `Hash Table` `String` `Combinatorics`

