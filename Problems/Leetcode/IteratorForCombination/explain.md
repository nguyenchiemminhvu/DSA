## Problem

https://leetcode.com/problems/iterator-for-combination/description/

Design the `CombinationIterator` class that generates all combinations of length `k` from a string of distinct characters in lexicographical order.

**Class Methods:**
- `CombinationIterator(string characters, int combinationLength)`: Initializes the object with sorted distinct lowercase English letters and combination length
- `next()`: Returns the next combination of specified length in lexicographical order
- `hasNext()`: Returns true if there exists a next combination

**Example:**
```
Input: ["CombinationIterator", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
       [["abc", 2], [], [], [], [], [], []]
Output: [null, "ab", true, "ac", true, "bc", false]

Explanation:
CombinationIterator itr = new CombinationIterator("abc", 2);
itr.next();    // return "ab"
itr.hasNext(); // return True
itr.next();    // return "ac"
itr.hasNext(); // return True
itr.next();    // return "bc"
itr.hasNext(); // return False
```

**Constraints:**
- `1 <= combinationLength <= characters.length <= 15`
- All characters are unique
- At most 10^4 calls to `next` and `hasNext`
- All calls to `next` are valid

## Observations

1. **Combination Generation**: Need to generate all combinations of k characters from n characters, which is C(n, k)
2. **Lexicographical Order**: Combinations must be returned in sorted order
3. **Iterator Pattern**: Must support lazy evaluation with `next()` and `hasNext()` methods
4. **Constraint Analysis**: With max 15 characters, worst case is C(15, 7) ≈ 6,435 combinations - manageable to precompute
5. **Bit Manipulation Insight**: Each combination can be represented as a bitmask where set bits indicate selected characters

## Solution

### Approach: Bit Manipulation with Precomputation

**Core Idea:**
- Use bitmasks to represent all possible subsets of the input string
- Filter subsets to keep only those with exactly k set bits (k characters)
- Sort combinations lexicographically
- Iterate through precomputed results

**Algorithm:**

1. **Initialization (Constructor):**
   - Iterate through all possible bitmasks from 0 to 2^n - 1
   - For each mask, count the number of set bits using Brian Kernighan's algorithm
   - If bit count equals k, construct the combination by selecting characters at positions with set bits
   - Store all valid combinations in a list
   - Sort the list lexicographically
   - Initialize index to 0

2. **next():**
   - Return the combination at current index
   - Increment index

3. **hasNext():**
   - Check if index is less than the total number of combinations

**Time Complexity:**
- Constructor: O(2^n × n) for generating all subsets, O(C(n,k) × k × log(C(n,k))) for sorting
  - For n=15: O(32,768 × 15) + O(6,435 × 7 × log(6,435)) - acceptable for one-time cost
- `next()`: O(1)
- `hasNext()`: O(1)

**Space Complexity:**
- O(C(n,k) × k) to store all combinations
- For n=15, k=7: O(6,435 × 7) ≈ 45KB - very manageable

**Key Technique - Bit Counting:**
```python
def count_bit(val: int) -> int:
    count = 0
    while val:
        val = val & (val - 1)  # Brian Kernighan's algorithm
        count += 1
    return count
```
This efficiently counts set bits by repeatedly clearing the rightmost set bit.

## Alternatives

### Alternative 1: Backtracking with On-Demand Generation
Instead of precomputing all combinations, generate them on-the-fly using backtracking.

**Pros:**
- Better space complexity: O(k) for recursion stack
- No upfront computation cost
- More memory efficient for large n or when not all combinations are needed

**Cons:**
- Each `next()` call is O(k) instead of O(1)
- More complex state management
- Need to maintain partial combination state between calls

**Implementation Sketch:**
```python
class CombinationIterator:
    def __init__(self, s: str, k: int):
        self.s = s
        self.k = k
        self.indices = list(range(k))
        self.done = False
    
    def next(self) -> str:
        result = ''.join(self.s[i] for i in self.indices)
        # Advance to next combination
        self._advance()
        return result
    
    def _advance(self):
        # Find rightmost index that can be incremented
        i = self.k - 1
        while i >= 0 and self.indices[i] == len(self.s) - self.k + i:
            i -= 1
        if i < 0:
            self.done = True
        else:
            self.indices[i] += 1
            for j in range(i + 1, self.k):
                self.indices[j] = self.indices[j - 1] + 1
```

### Alternative 2: Itertools-Based Approach (Python)
Use Python's built-in `itertools.combinations` generator.

**Implementation:**
```python
from itertools import combinations

class CombinationIterator:
    def __init__(self, s: str, k: int):
        self.iterator = combinations(s, k)
        self.current = None
        self._fetch_next()
    
    def _fetch_next(self):
        try:
            self.current = ''.join(next(self.iterator))
        except StopIteration:
            self.current = None
    
    def next(self) -> str:
        result = self.current
        self._fetch_next()
        return result
    
    def hasNext(self) -> bool:
        return self.current is not None
```

**Pros:**
- Clean, concise code
- Battle-tested library implementation
- Memory efficient (generator-based)

**Cons:**
- Language-specific (Python only)
- Less educational value
- Hidden implementation details

### Alternative 3: Recursive Generation with Memoization
Generate combinations recursively with caching.

**Trade-offs:**
- Similar to precomputation but with recursive structure
- May be easier to understand for some developers
- Stack overhead for recursion

### Comparison Summary

| Approach | Space | next() Time | Constructor Time | Pros |
|----------|-------|-------------|------------------|------|
| Bit Manipulation (Current) | O(C(n,k)×k) | O(1) | O(2^n×n) | Simple, fast queries |
| On-Demand Backtracking | O(k) | O(k) | O(1) | Memory efficient |
| Itertools | O(1) | O(k) | O(1) | Pythonic, clean |
| Recursive | O(C(n,k)×k) | O(1) | O(C(n,k)×k) | Cleaner generation |

**Recommendation:** The current bit manipulation approach is optimal for this problem given:
- Small constraint (n ≤ 15)
- Multiple queries expected (up to 10^4 calls)
- O(1) query time is valuable
- Precomputation cost is acceptable

# Tags
#iterator #combinations #bit-manipulation #backtracking #design #precomputation #lexicographical-order

