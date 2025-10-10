## Problem

https://leetcode.com/problems/implement-trie-prefix-tree/

```
A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently store and retrieve keys in a dataset of strings. There are various applications of this data structure, such as autocomplete and spellchecker.

Implement the Trie class:

Trie() Initializes the trie object.
void insert(String word) Inserts the string word into the trie.
boolean search(String word) Returns true if the string word is in the trie (i.e., was inserted before), and false otherwise.
boolean startsWith(String prefix) Returns true if there is a previously inserted string word that has the prefix prefix, and false otherwise.

Example 1:

Input
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
Output
[null, null, true, false, true, null, true]

Explanation
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // return True
trie.search("app");     // return False
trie.startsWith("app"); // return True
trie.insert("app");
trie.search("app");     // return True

Constraints:

1 <= word.length, prefix.length <= 2000
word and prefix consist only of lowercase English letters.
At most 3 * 104 calls in total will be made to insert, search, and startsWith.
```

## Observations

### Key Concepts
1. **Trie Structure**: A tree-like data structure where each node represents a character, and paths from root to nodes represent prefixes or complete words.

2. **Node Design**: Each TrieNode contains:
   - A boolean flag (`completed`) to mark if a word ends at this node
   - A dictionary/map (`children`) to store child nodes for each character

### Implementation Details
3. **Insert Operation**: 
   - Traverse the trie character by character
   - Create new nodes if they don't exist
   - Mark the final node as `completed = True` to indicate a word ends here
   - Time Complexity: O(m) where m is the length of the word
   - Space Complexity: O(m) in worst case (when inserting a completely new branch)

4. **Search Operation**:
   - Traverse the trie following the word's characters
   - Return `False` if any character path doesn't exist
   - Return `True` only if we reach the end AND the node is marked as completed
   - Time Complexity: O(m) where m is the length of the word
   - Space Complexity: O(1)

5. **StartsWith Operation**:
   - Similar to search but doesn't require the final node to be marked as completed
   - Only checks if the prefix path exists in the trie
   - Time Complexity: O(m) where m is the length of the prefix
   - Space Complexity: O(1)

### Edge Cases & Important Notes
6. **Prefix vs Complete Word**: The key difference between `search()` and `startsWith()` is that search requires `completed = True` at the final node, while startsWith only requires the path to exist.

7. **Character Set**: Problem constraints specify only lowercase English letters (a-z), which limits the branching factor to 26 per node.

8. **Memory Efficiency**: Using a dictionary for children is space-efficient as it only stores existing characters, unlike a fixed array approach.

9. **Example Walkthrough**:
   - After inserting "apple": search("apple") = True, search("app") = False, startsWith("app") = True
   - After inserting "app": search("app") = True (now the node at 'p' is marked completed)

### Use Cases
10. **Autocomplete Systems**: Efficient prefix matching for suggestion systems
11. **Spell Checkers**: Quick word validation and prefix-based corrections
12. **IP Routing**: Longest prefix matching in network routing tables
13. **Dictionary Lookups**: Fast word existence checking

## Tags

trie