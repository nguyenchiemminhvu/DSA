from typing import List, Dict

class TrieNode:
    def __init__(self):
        self.completed: bool = False
        self.children: Dict[str, TrieNode] = {}

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

    def search(self, word: str) -> bool:
        cur = self.root
        for ch in word:
            if ch not in cur.children:
                return False
            cur = cur.children[ch]
        return cur.completed

    def startsWith(self, prefix: str) -> bool:
        cur = self.root
        for ch in prefix:
            if ch not in cur.children:
                return False
            cur = cur.children[ch]
        return True
    
    def getShortestPrefix(self, word: str) -> str:
        cur = self.root
        i = 0
        while i < len(word):
            if word[i] in cur.children:
                cur = cur.children[word[i]]
                i += 1
                if cur.completed:
                    break
            else:
                return None
        return word[:i] if cur.completed else None

class Solution:
    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        trie = Trie()
        for d in dictionary:
            trie.insert(d)

        words = sentence.split()
        for i in range(len(words)):
            prefix = trie.getShortestPrefix(words[i])
            if prefix != None:
                words[i] = prefix
        return " ".join(words)