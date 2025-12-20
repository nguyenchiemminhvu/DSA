## Problem

https://leetcode.com/problems/pyramid-transition-matrix/

```
You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row of blocks contains one less block than the row beneath it and is centered on top.

To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks respectively, and the third character is the top block.

For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right) block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.

You start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.

Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular pattern in the pyramid is in allowed, or false otherwise.

Example 1:
Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
Output: true
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 3), we can build "CE" on level 2 and then build "A" on level 1.
There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.

Example 2:
Input: bottom = "AAAA", allowed = ["AAB","AAC","BCD","BBE","DEF"]
Output: false
Explanation: The allowed triangular patterns are shown on the right.
Starting from the bottom (level 4), there are multiple ways to build level 3, but trying all the possibilites, you will get always stuck before building level 1.

Constraints:
- 2 <= bottom.length <= 6
- 0 <= allowed.length <= 216
- allowed[i].length == 3
- The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
- All the values of allowed are unique.
```

## Observations

1. **Problem Structure**: This is a constraint satisfaction problem where we need to build a pyramid from bottom to top, following specific rules about which blocks can be stacked together.

2. **Key Insights**:
   - Each row has one less block than the row below it
   - For a row of length n, the next row will have length n-1
   - We need to reach a single block at the top (row of length 1)
   - Each adjacent pair of blocks in a row determines the possible blocks that can be placed above them

3. **Decision Tree**: For each row, we need to:
   - Consider all adjacent pairs of blocks
   - For each pair, find all valid blocks that can be placed on top (from allowed patterns)
   - Generate all possible combinations for the upper row
   - This creates a tree of possibilities that we need to explore

4. **Optimization Opportunities**:
   - **Preprocessing**: Build a map from (left, right) pairs to possible top blocks for O(1) lookup
   - **Memoization**: Cache results for rows we've already computed to avoid redundant calculations
   - **Pruning**: If we can't build even one valid upper row, we can stop immediately

5. **Complexity Considerations**:
   - Small constraint (bottom.length <= 6) makes exhaustive search feasible
   - At most 6 letters (A-F) means limited branching factor
   - Memoization significantly reduces repeated work

## Solution

### Approach: DFS with Backtracking and Memoization

The solution uses a depth-first search approach with backtracking to explore all possible pyramid constructions:

**Step 1: Preprocessing**
```python
check = {}
for s in allowed:
    left, right, up = s[0], s[1], s[2]
    if (left, right) not in check:
        check[(left, right)] = []
    check[(left, right)].append(up)
```
- Build a dictionary mapping each (left, right) pair to a list of possible top blocks
- This allows O(1) lookup instead of scanning through allowed list each time
- Example: If allowed = ["ABC", "ABD"], then check[('A', 'B')] = ['C', 'D']

**Step 2: Generate All Possible Upper Rows**
```python
def build_upper_row(row: str) -> List[str]:
    res = []
    n = len(row)
    def backtrack(i: int, tmp: List[str]) -> None:
        if i == n - 1:  # Processed all adjacent pairs
            res.append("".join(tmp))
            return
        
        pair = (row[i], row[i + 1])  # Current adjacent pair
        if pair not in check:  # No valid pattern for this pair
            return
        
        for ch in check[pair]:  # Try each possible top block
            tmp.append(ch)
            backtrack(i + 1, tmp)  # Move to next pair
            tmp.pop()  # Backtrack
    
    backtrack(0, [])
    return res
```
- For a row like "BCD", we have pairs: (B,C) and (C,D)
- For each pair, try all possible blocks that can go on top
- Use backtracking to generate all combinations
- Example: "BCD" with pairs (B,C)→['C'] and (C,D)→['E'] produces "CE"

**Step 3: DFS to Explore All Pyramid Paths**
```python
def dfs(row: str) -> bool:
    if len(row) == 1:  # Reached the top
        return True
    
    if row in memo:  # Already computed this row
        return memo[row]
    
    upper = build_upper_row(row)  # Get all possible upper rows
    for up in upper:
        if dfs(up):  # Recursively check if we can build from this upper row
            return True
    
    memo[row] = False  # Cache failure
    return False
```
- Base case: If we reach a single block, we've successfully built the pyramid
- For each possible upper row, recursively try to build the rest of the pyramid
- Use memoization to avoid recomputing the same row
- Return true as soon as we find one valid path to the top

**Time Complexity**: O(k^n × n) where:
- n is the length of bottom (max 6)
- k is the average branching factor (number of choices per pair)
- We potentially explore k^n different paths
- For each row, we spend O(n) to generate the upper row
- Memoization reduces this significantly in practice

**Space Complexity**: O(k^n × n) for:
- Memoization cache storing different row strings
- Recursion stack depth is at most n (pyramid height)
- Temporary lists in backtracking

**Example Walkthrough** (bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]):
1. check = {('B','C'): ['C'], ('C','D'): ['E'], ('C','E'): ['A'], ('F','F'): ['F']}
2. dfs("BCD"):
   - build_upper_row("BCD") → pairs (B,C) and (C,D) → generates ["CE"]
   - dfs("CE"):
     - build_upper_row("CE") → pair (C,E) → generates ["A"]
     - dfs("A"): len=1, return True ✓
3. Result: True

# Tags

- Backtracking
- Depth-First Search (DFS)
- Memoization
- Hash Map
- String Manipulation
- Constraint Satisfaction

