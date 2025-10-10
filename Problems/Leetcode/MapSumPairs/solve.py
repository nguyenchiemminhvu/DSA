from typing import Dict

class TrieNode:
    def __init__(self):
        self.val: int = 0
        self.children: Dict[str, TrieNode] = {}

class Trie:

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str, val: int) -> None:
        cur = self.root
        for ch in word:
            if ch not in cur.children:
                cur.children[ch] = TrieNode()
            cur = cur.children[ch]
        cur.val = val
    
    def sumPrefix(self, prefix: str) -> int:
        cur = self.root
        for ch in prefix:
            if ch not in cur.children:
                return 0
            cur = cur.children[ch]
        
        s = cur.val
        for child in cur.children.values():
            s += self.__traversal(child)
        return s
    
    def __traversal(self, root: TrieNode) -> int:
        if root == None:
            return 0
        
        s = root.val
        for child in root.children.values():
            s += self.__traversal(child)
        return s

class MapSum:

    def __init__(self):
        self.trie = Trie()

    def insert(self, key: str, val: int) -> None:
        self.trie.insert(key, val)

    def sum(self, prefix: str) -> int:
        return self.trie.sumPrefix(prefix)


# Your MapSum object will be instantiated and called as such:
# obj = MapSum()
# obj.insert(key,val)
# param_2 = obj.sum(prefix)