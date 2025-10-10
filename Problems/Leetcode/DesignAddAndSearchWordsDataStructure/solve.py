from typing import Dict

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
    
    def match(self, word: str) -> bool:
        return self.__match(self.root, word, 0)
    
    def __match(self, root: TrieNode, word: str, index: int) -> bool:
        if root == None:
            return False
        
        if index == len(word):
            return root.completed
        
        if word[index] == '.':
            for child in root.children.values():
                if self.__match(child, word, index + 1):
                    return True
            return False
        else:
            if word[index] not in root.children:
                return False
            return self.__match(root.children[word[index]], word, index + 1)

class WordDictionary:

    def __init__(self):
        self.trie = Trie()

    def addWord(self, word: str) -> None:
        self.trie.insert(word)

    def search(self, word: str) -> bool:
        return self.trie.match(word)


# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)