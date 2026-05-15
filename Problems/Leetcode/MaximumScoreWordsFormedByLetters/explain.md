## Problem

https://leetcode.com/problems/maximum-score-words-formed-by-letters/description/

Given a list of **words**, a list of single **letters** (possibly repeating), and a **score** array for each character ('a' to 'z'):
- Find the maximum score of any valid set of words formed using the given letters
- Each word can be used **at most once**
- Each letter can be used **at most once** (based on available count)
- Score of a word = sum of scores of its characters
- Not all letters need to be used

**Constraints:**
- 1 ≤ words.length ≤ 14
- 1 ≤ words[i].length ≤ 15
- 1 ≤ letters.length ≤ 100
- score.length = 26
- 0 ≤ score[i] ≤ 10

**Example 1:**
```
Input: 
  words = ["dog","cat","dad","good"]
  letters = ["a","a","c","d","d","d","g","o","o"]
  score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]

Output: 23

Explanation:
  Score mapping: a=1, c=9, d=5, g=3, o=2
  Select "dad" (5+1+5=11) and "good" (3+2+2+5=12) → Total = 23
```

**Example 2:**
```
Input:
  words = ["xxxz","ax","bx","cx"]
  letters = ["z","a","b","c","x","x","x"]
  score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]

Output: 27

Explanation:
  Score mapping: a=4, b=4, c=4, x=5, z=10
  Select "ax" (4+5=9), "bx" (4+5=9), "cx" (4+5=9) → Total = 27
```

## Observations

1. **Constraint on words.length ≤ 14**: This is the key hint! With at most 14 words, we can enumerate all possible subsets using bitmask (2^14 = 16,384 subsets) or use backtracking/recursion.

2. **Letter counting is critical**: Each word requires specific letters. We must track:
   - Available letter counts (from the `letters` list)
   - Required letter counts for each word (frequency array)
   - We can only select a word if all its required letters are available

3. **Two main approaches**:
   - **Bitmask DP**: Iterate all 2^14 subsets of words, check validity, calculate score
   - **Backtracking with Memoization**: Build subsets recursively, memoize based on (word_index, remaining_letters)

4. **Letter representation**: Use a frequency array of size 26 for lowercase letters, where `freq[i]` represents count of character `chr(ord('a') + i)`

5. **Score calculation**: Pre-compute word scores and letter requirements beforehand to optimize

## Solution

### Approach: Backtracking with Memoization

The solution uses **top-down dynamic programming** (memoized recursion):

```python
def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
    # Step 1: Pre-compute word frequencies and scores
    word_counts = []
    word_scores = []
    for word in words:
        freq = [0] * 26
        s = 0
        for c in word:
            idx = ord(c) - ord('a')
            freq[idx] += 1
            s += score[idx]
        word_counts.append(freq)
        word_scores.append(s)
    
    # Step 2: Count available letters
    available = [0] * 26
    for letter in letters:
        idx = ord(letter) - ord('a')
        available[idx] += 1
    
    # Step 3: Backtracking with memoization
    mem = {}
    
    def F(i: int, remain: tuple[int]) -> int:
        """
        i: current word index (0 to len(words)-1)
        remain: tuple of remaining letter counts (size 26)
        returns: maximum score from word i onwards with remaining letters
        """
        if i >= len(words):
            return 0
        
        if (i, remain) in mem:
            return mem[(i, remain)]
        
        # Option 1: Skip current word
        res = F(i + 1, remain)
        
        # Option 2: Try to use current word (if we have enough letters)
        temp_rem = list(remain)
        enough = True
        
        # Check if we have enough letters for word i
        for j in range(26):
            if word_counts[i][j] > temp_rem[j]:
                enough = False
                break
        
        if enough:
            # Subtract word's letter requirements
            for j in range(26):
                temp_rem[j] -= word_counts[i][j]
            # Take current word and continue
            res = max(res, word_scores[i] + F(i + 1, tuple(temp_rem)))
        
        mem[(i, remain)] = res
        return res
    
    return F(0, tuple(available))
```

### Time Complexity Analysis

- **Word preprocessing**: O(W × L) where W = number of words, L = average word length
- **Letter preprocessing**: O(N) where N = number of letters
- **Backtracking**: 
  - Number of states: O(2^W) (each word either selected or not, but memoization may reduce this)
  - Each state does O(26) work (checking and updating letter frequencies)
  - Total: O(2^W × 26) in worst case, but typically much better with pruning
- **Overall**: O(W × L + N + 2^W × 26) ≈ O(2^W) since W ≤ 14

### Space Complexity

- O(2^W × 26) for memoization table (each state stores a tuple of 26 values)
- O(W) for recursion depth

### Key Insights

1. **Pre-computation**: Compute word frequencies and scores once instead of repeatedly
2. **Tuple as state**: Using `tuple` for remaining letters allows it to be used as dictionary key
3. **Early termination**: Check letter availability before recursing (pruning)
4. **Top-down vs Bottom-up**: Top-down makes sense here because not all states are reachable
5. **Memoization cutoff**: Once we've processed all words, return 0 (base case)

### Alternative: Bitmask Approach

```python
def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
    n = len(words)
    available = [0] * 26
    for letter in letters:
        available[ord(letter) - ord('a')] += 1
    
    max_score = 0
    
    # Iterate all 2^n subsets
    for mask in range(1 << n):
        letter_count = [0] * 26
        current_score = 0
        valid = True
        
        # Check if this subset is valid
        for i in range(n):
            if mask & (1 << i):
                for c in words[i]:
                    idx = ord(c) - ord('a')
                    letter_count[idx] += 1
                    if letter_count[idx] > available[idx]:
                        valid = False
                        break
                if not valid:
                    break
                current_score += sum(score[ord(c) - ord('a')] for c in words[i])
        
        if valid:
            max_score = max(max_score, current_score)
    
    return max_score
```

This is simpler but slightly less efficient due to re-checking states.

# Tags

#backtracking #memoization #dp #bitmask #greedy-pruning #state-compression

