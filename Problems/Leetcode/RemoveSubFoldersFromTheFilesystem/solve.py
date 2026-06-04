from typing import List, Dict

class TrieNode:
    def __init__(self):
        self.valid = False
        self.leaves : Dict[str, 'TrieNode'] = {}

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, s: List[str]):
        p = self.root
        for c in s:
            if p.valid: # stop at valid prefix
                break
            if c not in p.leaves:
                p.leaves[c] = TrieNode()
            p = p.leaves[c]
        p.valid = True
        p.leaves.clear() # keep prefix only
    
    def get_paths(self):
        paths = []
        def dfs(root: TrieNode, path: str):
            if not root.leaves and root.valid:
                paths.append(path)
                return
            
            for s in root.leaves.keys():
                dfs(root.leaves[s], path + '/' + s)
        dfs(self.root, '')
        return paths

class Solution:
    def removeSubfolders(self, folders: List[str]) -> List[str]:
        trie = Trie()
        for folder in folders:
            path = folder.split('/')
            trie.insert(path[1:])
        
        paths = trie.get_paths()
        return paths