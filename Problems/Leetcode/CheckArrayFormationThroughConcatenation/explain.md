## Problem

https://leetcode.com/problems/check-array-formation-through-concatenation/description/

You are given an array of distinct integers `arr` and an array of integer arrays `pieces`, where the integers in `pieces` are distinct. Your goal is to form `arr` by concatenating the arrays in `pieces` in any order. However, you are not allowed to reorder the integers in each array `pieces[i]`.

Return `true` if it is possible to form the array `arr` from `pieces`. Otherwise, return `false`.

**Example 1:**
```
Input: arr = [15,88], pieces = [[88],[15]]
Output: true
Explanation: Concatenate [15] then [88]
```

**Example 2:**
```
Input: arr = [49,18,16], pieces = [[16,18,49]]
Output: false
Explanation: Even though the numbers match, we cannot reorder pieces[0].
```

**Example 3:**
```
Input: arr = [91,4,64,78], pieces = [[78],[4,64],[91]]
Output: true
Explanation: Concatenate [91] then [4,64] then [78]
```

**Constraints:**
- `1 <= pieces.length <= arr.length <= 100`
- `sum(pieces[i].length) == arr.length`
- `1 <= pieces[i].length <= arr.length`
- `1 <= arr[i], pieces[i][j] <= 100`
- The integers in `arr` are distinct
- The integers in `pieces` are distinct (i.e., if we flatten pieces in a 1D array, all the integers are distinct)

## Observations

1. **Order within pieces must be preserved**: Each piece array must appear in `arr` as a contiguous subsequence in the exact same order. We can't rearrange elements within a piece.

2. **Pieces can be arranged in any order**: We can concatenate pieces in any order to form `arr`, but the internal order of each piece is fixed.

3. **All integers are distinct**: This is crucial! Since all values are unique, each piece can only match at most one position in `arr`. We can use the first element of each piece as a unique identifier to find where it should start.

4. **Matching strategy**: For each piece, find where its first element appears in `arr`, then verify that all subsequent elements of that piece match consecutively in `arr`.

5. **Early termination**: If any piece's first element doesn't exist in `arr`, or if the piece doesn't match the consecutive elements in `arr`, we can immediately return `false`.

## Solution

1. **Iterate through each piece** in the `pieces` array
2. **Find the starting position**: Use `arr.index(row[0])` to find where the first element of the current piece appears in `arr`
   - If the first element doesn't exist in `arr`, return `false` (caught by try-except)
3. **Validate the entire piece**: Starting from the found position, verify that all elements of the piece match consecutively in `arr`
   - Check bounds: `start >= len(arr)` prevents index out of bounds
   - Check value match: `val != arr[start]` ensures elements match exactly
   - If any mismatch occurs, return `false`
4. **Success**: If all pieces are validated, return `true`

**Why this works:**

- Since all integers are distinct, `arr.index(row[0])` finds the unique position where each piece must start
- We don't need to track used positions because the problem guarantees that if we can form `arr` from `pieces`, each piece will occupy a unique, non-overlapping segment
- The algorithm implicitly checks that all pieces together cover the entire `arr` because if any element is missing or duplicated, the matching will fail

**Time Complexity:** $O(n \times m)$ where $n$ is the length of `arr` and $m$ is the number of pieces
- Each `arr.index()` call is $O(n)$
- We do this for each piece in the worst case

**Space Complexity:** $O(1)$ - only using a few variables for indexing

**Alternative approach** (more efficient):

```python
class Solution:
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:
        # Create a mapping from first element to the piece
        piece_map = {piece[0]: piece for piece in pieces}
        
        i = 0
        while i < len(arr):
            if arr[i] not in piece_map:
                return False
            
            piece = piece_map[arr[i]]
            for val in piece:
                if i >= len(arr) or arr[i] != val:
                    return False
                i += 1
        
        return True
```

This approach uses a hash map to avoid repeated `index()` calls, reducing time complexity to $O(n)$.

# Tags
#array #hash-map #greedy #string-matching

