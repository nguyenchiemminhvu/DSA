from typing import List

class TrieNode:
    def __init__(self):
        self.completed = False
        self.children = {}

class Trie:
    def __init__(self):
        self.root = TrieNode()
        self.root.completed = True
    
    def insert(self, word):
        p = self.root
        for c in word:
            if c not in p.children:
                p.children[c] = TrieNode()
            p = p.children[c]
        p.completed = True
    
    def get_longest_word(self):
        max_len = 0
        max_word = ''
        def dfs(p, length, temp):
            nonlocal max_len, max_word
            if not p.completed:
                return
            
            if max_len <= length:
                candidate = ''.join(temp)
                if max_len < length:
                    max_len = length
                    max_word = candidate
                else:
                    if max_word > candidate:
                        max_word = candidate
            
            for child in p.children.keys():
                dfs(p.children[child], length + 1, temp + [child])
        
        dfs(self.root, 0, [])
        return max_word

class Solution:
    def longestWord(self, words: List[str]) -> str:
        trie = Trie()
        for word in words:
            trie.insert(word)
        
        return trie.get_longest_word()