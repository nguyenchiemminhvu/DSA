## Problem

https://leetcode.com/problems/replace-words/

```
In English, we have a concept called root, which can be followed by some other word to form another longer word - let's call this word derivative. For example, when the root "help" is followed by the word "ful", we can form a derivative "helpful".

Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces, replace all the derivatives in the sentence with the root forming it. If a derivative can be replaced by more than one root, replace it with the root that has the shortest length.

Return the sentence after the replacement.

Example 1:

Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"

Example 2:

Input: dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
Output: "a a b c"

Constraints:

1 <= dictionary.length <= 1000
1 <= dictionary[i].length <= 100
dictionary[i] consists of only lower-case letters.
1 <= sentence.length <= 106
sentence consists of only lower-case letters and spaces.
The number of words in sentence is in the range [1, 1000]
The length of each word in sentence is in the range [1, 1000]
Every two consecutive words in sentence will be separated by exactly one space.
sentence does not have leading or trailing spaces.
```

## Observations

1. **Core Problem**: We need to replace longer words (derivatives) with their shortest root words from a dictionary.

2. **Key Insight**: This is a perfect use case for a **Trie (Prefix Tree)** because:
   - We need to find the shortest prefix of a word that exists in our dictionary
   - Trie allows efficient prefix matching by traversing character by character
   - We can stop as soon as we find a complete root word (shortest prefix)

3. **Algorithm Strategy**:
   - Build a Trie from all dictionary words
   - For each word in the sentence, find its shortest root using the Trie
   - Replace the word with its root if found

4. **Time Complexity**: 
   - Building Trie: `O(N × M)` where `N` is number of dictionary words, `M` is average length
   - Processing sentence: `O(K × L)` where K is number of words in sentence, L is average word length
   - Overall: `O(N × M + K × L)`

5. **Space Complexity**: `O(N × M)` for the Trie structure

## Solution

The solution uses a custom Trie implementation with an additional method `getShortestPrefix()`:

### Key Components:

1. **TrieNode Class**: 
   - `completed`: boolean flag indicating if this node represents the end of a dictionary word
   - `children`: dictionary mapping characters to child TrieNode objects

2. **Trie Class**:
   - `insert()`: Standard trie insertion
   - `getShortestPrefix()`: **Custom method** that finds the shortest prefix of a given word that exists as a complete word in the trie

3. **getShortestPrefix() Logic**:
   ```python
   def getShortestPrefix(self, word: str) -> str:
       cur = self.root
       i = 0
       while i < len(word):
           if word[i] in cur.children:
               cur = cur.children[word[i]]
               i += 1
               if cur.completed:  # Found complete root word
                   break
           else:
               return None  # No matching prefix found
       return word[:i] if cur.completed else None
   ```
   - Traverses the trie character by character
   - **Stops immediately** when it finds the first complete word (shortest root)
   - Returns `None` if no valid prefix is found

4. **Main Algorithm**:
   - Insert all dictionary words into the trie
   - Split the sentence into individual words
   - For each word, attempt to find its shortest root
   - Replace the word with its root if found
   - Join all words back into a sentence

### Example Walkthrough:
Given `dictionary = ["cat","bat","rat"]` and `sentence = "the cattle was rattled by the battery"`:

1. Build trie with "cat", "bat", "rat"
2. Process each word:
   - "the" → no root found → remains "the"
   - "cattle" → finds "cat" (stops at 'c'-'a'-'t' since it's complete) → becomes "cat"
   - "was" → no root found → remains "was"
   - "rattled" → finds "rat" → becomes "rat"
   - "by" → no root found → remains "by"
   - "the" → no root found → remains "the"
   - "battery" → finds "bat" → becomes "bat"

3. Result: "the cat was rat by the bat"

The elegance of this solution lies in the `getShortestPrefix()` method that efficiently finds the shortest matching root by leveraging the trie's prefix-matching capabilities.

## Tags

trie, bfs, string