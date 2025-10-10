## Problem

https://leetcode.com/problems/word-search-ii/

```
Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:

Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:

Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

Constraints:

m == board.length
n == board[i].length
1 <= m, n <= 12
board[i][j] is a lowercase English letter.
1 <= words.length <= 3 * 104
1 <= words[i].length <= 10
words[i] consists of lowercase English letters.
All the strings of words are unique.
```

## Observations

1. **Problem Type**: This is a combination of Trie data structure and DFS (Depth-First Search) on a `2D` grid.

2. **Key Constraints**:
   - Words must be formed from sequentially adjacent cells (horizontally or vertically)
   - Same cell cannot be used more than once in a single word
   - Need to find ALL words from the given list that exist on the board

3. **Brute Force Approach Issues**: 
   - Checking each word individually using DFS would be inefficient
   - Time complexity would be `O(words × m × n × 4^(max_word_length))`
   - Many redundant path explorations for words with common prefixes

4. **Optimization Strategy**:
   - Use a Trie to store all words - this allows sharing common prefixes
   - Perform DFS while traversing the Trie simultaneously
   - Prune paths early when current path doesn't match any word prefix in Trie

5. **Edge Cases**:
   - Empty board or empty words list
   - Words longer than possible paths on board
   - Duplicate words in result (handled by using set)

## Solution

### Approach: Trie + DFS with Backtracking

**Algorithm Steps**:

1. **Build Trie**: Insert all words into a Trie data structure
2. **DFS Exploration**: For each cell on the board, start DFS while traversing Trie
3. **Path Tracking**: Keep track of visited cells and current word being formed
4. **Word Detection**: When reaching a completed word in Trie, add to results
5. **Backtracking**: Unmark visited cells when returning from DFS

**Data Structures**:
- `TrieNode`: Contains `completed` flag and `children` dictionary
- `Trie`: Root-based structure for efficient word prefix matching
- `visited`: `2D` boolean array to track used cells in current path

**Key Implementation Details**:

1. **Trie Construction**:
   ```python
   trie = Trie()
   for word in words:
       trie.insert(word)
   ```

2. **DFS with Trie Traversal**:
   ```python
   def dfs(r, c, node: TrieNode, visited, cur_word):
       # Check bounds and visited status
       # Check if current character exists in Trie
       # Add character to current word
       # Check if word is completed
       # Mark as visited and explore neighbors
       # Backtrack by unmarking visited
   ```

3. **Optimization Techniques**:
   - **Early Termination**: Stop DFS if current character not in Trie children
   - **Visited Tracking**: Prevent cycles within same word path
   - **Set for Results**: Automatically handle duplicate words

**Time Complexity**: `O(m × n × 4^L)` where L is maximum word length
- We start DFS from each cell: `O(m × n)`
- For each DFS, worst case explores `4^L` paths

**Space Complexity**: `O(W × L + m × n)` where W is number of words
- Trie storage: `O(W × L)`
- Visited array: `O(m × n)`
- Recursion stack: `O(L)`

**Why This Approach Works**:
- Trie allows efficient prefix matching and early pruning
- DFS with backtracking explores all possible paths
- Combining both eliminates redundant work for words with common prefixes

## Tags

trie, array, string, dfs