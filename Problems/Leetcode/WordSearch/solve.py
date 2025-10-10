from typing import List, Dict

class TrieNode:
    def __init__(self):
        self.completed : bool = False
        self.children : Dict[str, TrieNode] = {}

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word: str) -> None:
        cur = self.root
        for ch in word:
            if ch not in cur.children:
                cur.children[ch] = TrieNode()
            cur = cur.children[ch]
        cur.completed = True

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        trie = Trie()
        trie.insert(word)

        m = len(board)
        n = len(board[0])
        def dfs(r, c, node: TrieNode, visited: List[List[bool]]) -> bool:
            if visited[r][c]:
                return False
            if board[r][c] not in node.children:
                return False
            if node.children[board[r][c]].completed:
                return True
            
            visited[r][c] = True
            
            neighbors = [(r-1,c), (r+1,c), (r,c-1), (r,c+1)]
            for neighbor in neighbors:
                next_r, next_c = neighbor
                if next_r >= 0 and next_r < m and next_c >= 0 and next_c < n:
                    if not visited[next_r][next_c]:
                        if dfs(next_r, next_c, node.children[board[r][c]], visited):
                            visited[r][c] = False
                            return True
            visited[r][c] = False
            return False
        
        for i in range(m):
            for j in range(n):
                visited = [[False for _ in range(n)] for _ in range(m)]
                if dfs(i, j, trie.root, visited):
                    return True
        return False