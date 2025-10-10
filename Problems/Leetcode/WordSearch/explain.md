## Problem

https://leetcode.com/problems/word-search/description/

```
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.

Follow up: Could you use search pruning to make your solution faster with a larger board?
```

## Observations

1. **Problem Type**: This is a classic graph traversal problem on a 2D grid where we need to find if a word can be formed by following adjacent cells.

2. **Key Constraints**:
   - Each cell can only be used once per path
   - Adjacent means horizontally or vertically neighboring (not diagonal)
   - We need to find a path that spells out the exact word

3. **Solution Approach Analysis**:
   - The provided solution uses a **Trie + DFS** approach, which is actually overkill for this single-word search
   - A simpler DFS without Trie would be more efficient for finding just one word
   - The Trie approach is better suited for multiple word searches (like Word Search II)

4. **Time Complexity**: O(M×N×4^L) where M×N is the board size and L is word length (4 directions at each step)
5. **Space Complexity**: O(L) for the recursion stack and visited array

6. **Edge Cases**:
   - Word longer than total board cells
   - Single character word
   - Word not present in board
   - Empty board or word

## Solution

The solution uses a combination of **Trie data structure** and **Depth-First Search (DFS)** with backtracking:

### Algorithm Steps:

1. **Build Trie**: Insert the target word into a Trie for efficient prefix matching
2. **Grid Traversal**: Try starting the search from each cell in the board
3. **DFS with Backtracking**: 
   - For each starting position, perform DFS to explore all possible paths
   - Use a visited array to track used cells in current path
   - Backtrack by unmarking visited cells when returning from recursion

### Key Components:

#### Trie Structure:
```python
class TrieNode:
    def __init__(self):
        self.completed : bool = False  # Marks end of a word
        self.children : Dict[str, TrieNode] = {}  # Child nodes for each character
```

#### DFS Logic:
- **Base Cases**: 
  - If current cell is already visited → return False
  - If current character not in Trie → return False  
  - If we've completed the word → return True

- **Recursive Case**:
  - Mark current cell as visited
  - Explore all 4 adjacent cells
  - If any path leads to success → return True
  - Backtrack by unmarking current cell

### Why This Approach Works:
- **Trie ensures prefix matching**: We only continue if current path could lead to the target word
- **Backtracking ensures correctness**: Each cell is only used once per path attempt
- **Exhaustive search**: We try all possible starting positions and paths

## Tags

trie, array, dfs, string