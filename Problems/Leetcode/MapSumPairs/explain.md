## Problem

https://leetcode.com/problems/map-sum-pairs/

```
Design a map that allows you to do the following:

Maps a string key to a given value.
Returns the sum of the values that have a key with a prefix equal to a given string.
Implement the MapSum class:

MapSum() Initializes the MapSum object.
void insert(String key, int val) Inserts the key-val pair into the map. If the key already existed, the original key-value pair will be overridden to the new one.
int sum(string prefix) Returns the sum of all the pairs' value whose key starts with the prefix.

Example 1:

Input
["MapSum", "insert", "sum", "insert", "sum"]
[[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
Output
[null, null, 3, null, 5]

Explanation
MapSum mapSum = new MapSum();
mapSum.insert("apple", 3);  
mapSum.sum("ap");           // return 3 (apple = 3)
mapSum.insert("app", 2);    
mapSum.sum("ap");           // return 5 (apple + app = 3 + 2 = 5)

Constraints:

1 <= key.length, prefix.length <= 50
key and prefix consist of only lowercase English letters.
1 <= val <= 1000
At most 50 calls will be made to insert and sum.
```

## Observations

1. **Problem Requirements**: We need to efficiently store key-value pairs and quickly find the sum of all values whose keys start with a given prefix.

2. **Data Structure Choice**: A Trie (prefix tree) is the ideal data structure for this problem because:
   - It naturally groups strings by their common prefixes
   - Allows efficient prefix-based searches
   - Each node can store a value for keys that end at that node

3. **Key Insights**:
   - Each TrieNode needs to store a value (for keys ending at that node) and children nodes
   - When inserting, we traverse the trie character by character and set the value at the final node
   - For prefix sum, we find the node corresponding to the prefix, then sum all values in the subtree rooted at that node

4. **Edge Cases**:
   - Prefix doesn't exist in the trie → return `0`
   - Empty prefix → sum all values in the entire trie
   - Overriding existing keys → the trie naturally handles this by updating the value at the existing node

5. **Time Complexity**:
   - Insert: `O(k)` where k is the length of the key
   - Sum: `O(k + n)` where k is the length of the prefix and n is the number of nodes in the subtree

## Solution

The solution uses a **Trie (Prefix Tree)** data structure with two main components:

### TrieNode Structure
```python
class TrieNode:
    def __init__(self):
        self.val: int = 0  # Value stored at this node (0 if no key ends here)
        self.children: Dict[str, TrieNode] = {}  # Child nodes for each character
```

### Algorithm Breakdown

**1. Insert Operation:**
- Traverse the trie character by character, creating nodes as needed
- Set the value at the final node representing the complete key
- If the key already exists, the value is naturally overridden

**2. Sum Operation:**
- First, navigate to the node representing the given prefix
- If prefix doesn't exist, return 0
- From the prefix node, perform a DFS traversal to sum all values in the subtree
- This includes the value at the prefix node itself (if a key ends there) plus all descendant values

**3. Helper Method (`__traversal`):**
- Recursively traverses all nodes in a subtree
- Accumulates the sum of all values found
- Uses DFS to ensure all nodes are visited exactly once

### Key Implementation Details

- **Trie Structure**: Each character in a string corresponds to an edge in the trie
- **Value Storage**: Only nodes where a key ends store non-zero values
- **Prefix Matching**: The trie's structure naturally supports efficient prefix operations
- **Recursion**: The traversal uses recursion to elegantly handle the tree structure

### Example Walkthrough
Given operations: `insert("apple", 3)`, `sum("ap")`, `insert("app", 2)`, `sum("ap")`

1. After `insert("apple", 3)`: Trie has path a→p→p→l→e with value 3 at 'e' node
2. `sum("ap")`: Navigate to 'p' node, traverse subtree, find only "apple" → return 3
3. After `insert("app", 2)`: Same path but value 2 stored at second 'p' node
4. `sum("ap")`: Navigate to 'p' node, traverse subtree, find "app"(2) + "apple"(3) → return `5`

## Tags

trie, bfs