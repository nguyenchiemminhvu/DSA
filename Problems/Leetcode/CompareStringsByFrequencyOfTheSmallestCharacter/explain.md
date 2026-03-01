## Problem

https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/description/

Define `f(s)` as the frequency of the lexicographically smallest character in string `s`.  
Given arrays `queries` and `words`, for each `queries[i]` count how many words `W` in `words` satisfy `f(queries[i]) < f(W)`.  
Return an integer array `answer` where `answer[i]` is the result for the i-th query.

**Example:**
- `queries = ["bbb","cc"]`, `words = ["a","aa","aaa","aaaa"]`
- f values: queries → [3, 2], words → [1, 2, 3, 4]
- "bbb" (f=3): only "aaaa" (f=4) qualifies → 1
- "cc"  (f=2): "aaa" (f=3) and "aaaa" (f=4) qualify → 2
- Output: `[1, 2]`

**Constraints:**
- `1 <= queries.length, words.length <= 2000`
- `1 <= queries[i].length, words[i].length <= 10`

## Observations

1. **Reduce to numbers:** For every string we only care about `f(s)` — a single integer in `[1, 10]`. The actual characters don't matter beyond computing `f`.
2. **Brute force is O(Q × W):** Compare each query's f-value against every word's f-value. With Q, W ≤ 2000 this is 4 million operations and would pass, but we can do better.
3. **Sort + binary search:** If we pre-sort the f-values of all words, for a query with value `f_q` we need the count of words where `f_w > f_q`. A single binary search gives us the first index where values exceed `f_q`, and the answer is `len(arr) - that_index`.
4. **Naming note:** The helper is called `lower_bound` but actually finds the **last index whose value ≤ target** (rightmost ≤). Everything to its right is strictly greater than `f_q`.

## Solution

**Step 1 — Precompute and sort word f-values:**
```
arr = [f(w) for w in words],  then sort arr
```

**Step 2 — For each query, binary search `arr`:**

The helper `lower_bound(arr, target)` returns the index `idx` of the rightmost element ≤ `target` (or `-1` if none exists):

```
left=0, right=n-1, idx=-1
while left <= right:
    mid = (left+right)/2
    if arr[mid] <= target:
        idx = mid          # this could still be the answer, try going right
        left = mid + 1
    else:
        right = mid - 1
return idx
```

After the binary search, elements in `arr[idx+1 ... n-1]` are all `> f_q`.  
Count = `len(arr) - idx - 1`.

Edge case: if every word's f-value > f_q, then `idx = -1`, so count = `len(arr) - (-1) - 1 = len(arr)`. Correct.

**Complexity:** O((Q + W) log W) time, O(W) extra space.

```python
class Solution:
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:
        def lower_bound(arr: List[int], target: int) -> int:
            n = len(arr)
            left, right = 0, n - 1
            idx = -1
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid] <= target:
                    idx = mid
                    left = mid + 1
                else:
                    right = mid - 1
            return idx
        
        arr = []
        for word in words:
            f = word.count(min(word))
            arr.append(f)
        arr.sort()

        res = []
        for query in queries:
            f = query.count(min(query))
            lower = lower_bound(arr, f)
            res.append(len(arr) - lower - 1)
        return res
```

# Tags
`Binary Search` `String` `Sorting` `Array`

