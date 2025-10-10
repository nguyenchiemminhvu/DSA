## Problem

https://leetcode.com/problems/design-add-and-search-words-data-structure/

```
Design a data structure that supports adding new words and finding if a string matches any previously added string.

Implement the WordDictionary class:

WordDictionary() Initializes the object.
void addWord(word) Adds word to the data structure, it can be matched later.
bool search(word) Returns true if there is any string in the data structure that matches word or false otherwise. word may contain dots '.' where dots can be matched with any letter.

Example:

Input
["WordDictionary","addWord","addWord","addWord","search","search","search","search"]
[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]
Output
[null,null,null,null,false,true,true,true]

Explanation
WordDictionary wordDictionary = new WordDictionary();
wordDictionary.addWord("bad");
wordDictionary.addWord("dad");
wordDictionary.addWord("mad");
wordDictionary.search("pad"); // return False
wordDictionary.search("bad"); // return True
wordDictionary.search(".ad"); // return True
wordDictionary.search("b.."); // return True

Constraints:

1 <= word.length <= 25
word in addWord consists of lowercase English letters.
word in search consist of '.' or lowercase English letters.
There will be at most 2 dots in word for search queries.
At most 104 calls will be made to addWord and search.
```

## Observations

1. **Data Structure Choice**: This problem requires efficient prefix-based storage and wildcard matching, making Trie (Prefix Tree) the optimal choice.

2. **Wildcard Handling**: The `'.'` character can match any letter, requiring recursive exploration of all possible paths in the Trie during search.

3. **Two Operations**: 
   - `addWord`: Standard Trie insertion - `O(m)` where m is word length
   - `search`: Modified Trie search with backtracking for wildcards - `O(n)` in worst case where `n` is number of nodes

4. **Edge Cases**:
   - Empty strings (handled by checking `index == len(word)`)
   - Words with only dots
   - Words longer than any stored word
   - Non-existent character paths

5. **Memory Efficiency**: Each TrieNode stores only necessary children, not a fixed 26-character array.

## Solution

The solution uses a **Trie (Prefix Tree)** data structure with **recursive backtracking** for wildcard matching:

### Core Components:

1. **TrieNode Class**:
   - `completed`: Boolean flag marking end of a valid word
   - `children`: Dictionary mapping characters to child nodes

2. **Trie Class**:
   - `insert()`: Standard Trie insertion, marking word completion
   - `match()`: Wrapper for recursive wildcard matching

3. **WordDictionary Class**:
   - Encapsulates Trie functionality for the required interface

### Algorithm Flow:

**Adding Words (`addWord`)**:
1. Traverse Trie character by character
2. Create new nodes if path doesn't exist  
3. Mark final node as `completed = True`

**Searching Words (`search`)**:
1. **Base Cases**:
   - If node is None `→` return False
   - If reached end of word `→` return `node.completed`

2. **Wildcard Case ('.')**: 
   - Try all possible children recursively
   - Return True if any path succeeds

3. **Regular Character**:
   - Check if character exists in children
   - Recursively search the corresponding child

### Time Complexity:
- **Insert**: `O(m)` where `m = word` length
- **Search**: `O(n)` worst case where `n = total nodes` (when many wildcards), `O(m)` average case

### Space Complexity:
- `O(ALPHABET_SIZE × N × M)` where `N = number of words, M = average word length
`
This solution efficiently handles both exact matches and wildcard patterns while maintaining good performance for the given constraints.

## Tags

trie, dfs, string