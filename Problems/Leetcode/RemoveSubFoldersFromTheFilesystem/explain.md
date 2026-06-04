## Problem

https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/description/

Given a list of folders in a filesystem, remove all **sub-folders** from the list and return only the top-level folders.

A folder `b` is a sub-folder of folder `a` if `b` starts with `a` followed by a `/`. For example, `/a/b` is a sub-folder of `/a`, but `/ab` is not.

**Example:**
- Input: `["/a", "/a/b", "/c/d", "/c/d/e", "/c/f"]`
- Output: `["/a", "/c/d", "/c/f"]`

---

## Observations

1. **Path as a sequence of parts:** Any folder path like `/a/b/c` can be split on `/` into parts `["a", "b", "c"]`. A sub-folder relationship is simply one path being a **prefix** (in terms of parts) of another.

2. **Trie is a natural fit:** A Trie (prefix tree) where each node represents one path component naturally captures the prefix structure of folder paths. Inserting a path and checking for an ancestor is $O(L)$ where $L$ is the path depth.

3. **Early termination on valid prefix:** When inserting a path, if we reach a node already marked `valid`, the current path is a sub-folder of an already-inserted folder — we can stop immediately and discard it.

4. **Pruning deeper paths after insert:** When a node is marked `valid` (a top-level folder is confirmed), all its children are irrelevant — clearing `leaves` ensures no deeper path is ever returned.

5. **Collecting results via DFS:** A DFS that only collects paths at nodes where `valid=True` and `leaves` is empty (leaf nodes after pruning) gives exactly the top-level folders.

---

## Solution Explanation

```python
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
```

**Step-by-step walkthrough:**

1. **`Solution.removeSubfolders`**
   - Each folder string (e.g. `"/a/b"`) is split by `'/'`, yielding `['', 'a', 'b']`. The leading empty string from the root `/` is dropped via `path[1:]`, giving `['a', 'b']`.
   - Each cleaned path is inserted into the Trie.
   - After all insertions, `get_paths()` collects the surviving top-level folders.

2. **`Trie.insert(s)`**
   - Traverses the Trie one path component at a time.
   - **If a node along the way is already `valid`**, the current path is deeper than a folder already recorded — it is a sub-folder, so we **break early** and discard it.
   - **At the end node**, mark it `valid = True` and **clear its `leaves`**. This prunes any previously inserted sub-folders of the current path in one shot.

3. **`Trie.get_paths`**
   - DFS from the root, rebuilding the path string as it descends.
   - A node with `valid=True` and no `leaves` (because they were cleared) is a surviving top-level folder — its reconstructed path is added to the result.

**Complexity:**
- Let $N$ = number of folders, $L$ = average path depth.
- **Time:** $O(N \cdot L)$ for insertions + $O(N \cdot L)$ for DFS = $O(N \cdot L)$.
- **Space:** $O(N \cdot L)$ for the Trie nodes.
