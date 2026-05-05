## Problem

https://leetcode.com/problems/search-suggestions-system/description

Given an array of strings `products` and a string `searchWord`, design a system that suggests at most three product names from `products` after each character of `searchWord` is typed. Suggested products should have a common prefix with `searchWord`. If there are more than three products with a common prefix, return the three lexicographically minimum products.

**Return** a list of lists of the suggested products after each character of `searchWord` is typed.

### Example 1:
```
Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
After typing 'm' and 'mo' all products match and we show user ["mobile","moneypot","monitor"].
After typing 'mou', 'mous' and 'mouse' the system suggests ["mouse","mousepad"].
```

### Example 2:
```
Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Explanation: The only word "havana" will be always suggested while typing the search word.
```

### Constraints:
- `1 <= products.length <= 1000`
- `1 <= products[i].length <= 3000`
- `1 <= sum(products[i].length) <= 2 * 10^4`
- All strings of `products` are unique
- `products[i]` consists of lowercase English letters
- `1 <= searchWord.length <= 1000`
- `searchWord` consists of lowercase English letters

## Observations

1. **Prefix Matching**: We need to find all products that share a common prefix with the current prefix of `searchWord` at each step.

2. **Lexicographic Order**: Products with the same prefix must be returned in lexicographically sorted order, and we only return the first three.

3. **Incremental Search**: For each character added to the search word, we're building on the previous prefix. This suggests we can use a **Trie** data structure to efficiently track prefixes.

4. **Trie Efficiency**: Using a Trie allows us to:
   - Insert all products in $O(N \cdot M)$ time where $N$ is the number of products and $M$ is the average length
   - Query for a prefix in $O(L)$ time where $L$ is the length of the prefix
   - Find all products with a given prefix using DFS

5. **Lexicographic Output**: Products need to be sorted lexicographically. We can sort the results from each DFS traversal or use a different approach like sorting products first and using binary search.

6. **Alternative Approaches**:
   - **Sorting + Linear Search**: Sort products first, then for each prefix, linearly search and collect matching products (less efficient for large datasets)
   - **Sorting + Binary Search**: Sort products, use binary search to find the range of products with the common prefix (more efficient)
   - **Trie + DFS**: Build a Trie, then for each prefix, traverse the Trie to find all matching products

## Solution

### Approach: Trie with DFS

The Trie-based solution is optimal for this problem:

**Data Structure**:
```python
class TrieNode:
    def __init__(self):
        self.child = {}          # Map from character to TrieNode
        self.completed = False   # Whether this node marks the end of a word
```

**Algorithm**:

1. **Build Trie**: Insert all products into the Trie
2. **For each character in searchWord**:
   - Append the character to current prefix
   - Navigate the Trie to the node representing this prefix
   - If the prefix doesn't exist in Trie, return empty list
   - Otherwise, perform DFS from this node to find all products with this prefix
   - Sort the results and take the first 3 (lexicographically minimum)

**Code**:
```python
class TrieNode:
    def __init__(self):
        self.child = {}
        self.completed = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word: str):
        """Insert a word into the Trie"""
        p = self.root
        for ch in word:
            if ch not in p.child:
                p.child[ch] = TrieNode()
            p = p.child[ch]
        p.completed = True
    
    def find(self, prefix: str) -> List[str]:
        """Find all words with the given prefix"""
        p = self.root
        # Navigate to the node representing the prefix
        for ch in prefix:
            if ch not in p.child:
                return []
            p = p.child[ch]
        
        # DFS to find all words starting with this prefix
        words = []
        def dfs(node, s: str):
            if node.completed:
                words.append(s)
            # Explore all children in lexicographic order
            for ch in sorted(node.child.keys()):
                dfs(node.child[ch], s + ch)
        
        dfs(p, prefix)
        return words

class Solution:
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        t = Trie()
        # Build the Trie with all products
        for product in products:
            t.insert(product)
        
        res = []
        cur = ''
        # Process each character of searchWord
        for ch in searchWord:
            cur += ch
            # Find all products with current prefix
            items = t.find(cur)
            # Take the first 3 (they're already sorted by DFS traversal order)
            res.append(items[:3])
        
        return res
```

### Complexity Analysis

**Time Complexity**:
- Insertion: $O(N \cdot M)$ where $N$ is number of products, $M$ is average product length
- For each character in searchWord (up to $L$ characters):
  - Navigating to the prefix node: $O(L)$
  - DFS to find all matching products: $O(N)$ in worst case
  - Overall: $O(L \cdot (L + N))$
- **Total**: $O(N \cdot M + L \cdot (L + N))$

**Space Complexity**:
- Trie storage: $O(N \cdot M)$ for all product characters
- Recursion stack: $O(M)$ for DFS depth
- Result storage: $O(L \cdot 3)$ for at most 3 results per character
- **Total**: $O(N \cdot M)$

### Why This Solution Works

1. **Prefix Efficiency**: The Trie naturally organizes words by prefixes, allowing quick navigation to all words sharing a common prefix.

2. **Lexicographic Ordering**: By using `sorted(node.child.keys())` in the DFS, we traverse child nodes in lexicographic order, ensuring results are naturally sorted.

3. **Optimal Prefix Handling**: Once we navigate to a prefix node, all words in that subtree have the required prefix.

4. **Scalability**: Even with large datasets, the Trie approach scales well because we limit results to 3 products and the DFS terminates early once 3 are found.

### Alternative: Sorting + Binary Search

For comparison, a simpler approach without Trie:
```python
class Solution:
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        products.sort()
        res = []
        cur = ''
        
        for ch in searchWord:
            cur += ch
            # Binary search to find the starting position
            left, right = 0, len(products)
            while left < right:
                mid = (left + right) // 2
                if products[mid] < cur:
                    left = mid + 1
                else:
                    right = mid
            
            # Collect up to 3 products starting from this position
            row = []
            for i in range(left, min(left + 3, len(products))):
                if products[i].startswith(cur):
                    row.append(products[i])
                else:
                    break
            
            res.append(row)
        
        return res
```

This approach has $O(N \log N + L \cdot \log N)$ time complexity and is simpler to implement.

# Tags

- Trie
- String
- Design
- Prefix Search
- Depth-First Search
- Binary Search (alternative)

