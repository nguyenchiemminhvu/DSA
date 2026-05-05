from typing import List

class TrieNode:
    def __init__(self):
        self.child = {}
        self.completed = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word: str):
        p = self.root
        for ch in word:
            if ch not in p.child:
                p.child[ch] = TrieNode()
            p = p.child[ch]
        p.completed = True
    
    def find(self, prefix: str) -> List[str]:
        p = self.root
        for ch in prefix:
            if ch not in p.child:
                return []
            p = p.child[ch]
        
        words = []
        def dfs(node, s: str):
            if node.completed:
                words.append(s)
            for ch, next_node in node.child.items():
                dfs(next_node, s + ch)
        
        dfs(p, prefix)
        return words

class Solution:
    def suggestedProducts(self, products: List[str], word: str) -> List[List[str]]:
        t = Trie()
        for product in products:
            t.insert(product)
        
        res = []
        cur = ''
        for ch in word:
            row = []
            cur += ch
            items = t.find(cur)
            items.sort()
            row.extend(items[:3])
            res.append(row)
        
        return res