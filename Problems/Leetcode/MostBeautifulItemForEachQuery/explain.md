## Problem

https://leetcode.com/problems/most-beautiful-item-for-each-query/description/

````markdown
## Problem

https://leetcode.com/problems/most-beautiful-item-for-each-query/description/

Given a 2D integer array `items` where `items[i] = [price_i, beauty_i]` denotes the price and beauty of an item, and a 0-indexed integer array `queries`, for each `queries[j]` determine the **maximum beauty** of an item whose price is **less than or equal to** `queries[j]`. If no such item exists, the answer is `0`.

Return an array `answer` of the same length as `queries` where `answer[j]` is the answer to the j-th query.

**Constraints:**
- `1 <= items.length, queries.length <= 10^5`
- `1 <= price_i, beauty_i, queries[j] <= 10^9`

## Observations

1. **Queries are independent:** Each query asks for the best beauty among all items with price ≤ query value. There is no dependency between queries.

2. **Brute force is too slow:** Iterating over all items for every query is O(n × m), which is up to 10^10 operations — too slow given the constraints.

3. **Sorting unlocks binary search:** If we sort items by price, for a given query we only care about items up to some index (the rightmost item whose price ≤ query). We can find this index with binary search in O(log n).

4. **Prefix maximum of beauty:** After sorting by price, the answer for a query is not just `items[idx][1]` — it's the **maximum beauty among all items from index 0 to idx**. We can precompute this as a running maximum in O(n), so each query becomes a simple O(1) lookup after the binary search.

5. **Binary search pattern (upper bound):** We want the last index where `price <= query`. Equivalently, we find the first index where `price > query` (upper bound), then subtract 1. If that result is -1, no valid item exists → answer is `0`.

## Solution

**Step 1 — Sort items by price:**  
This lets us process items in price order and enables binary search.

**Step 2 — Build prefix maximum of beauty:**  
Traverse the sorted items and replace each `beauty` with the running maximum up to that index. Now `items[i][1]` represents the best beauty achievable among all items with price ≤ `items[i][0]`.

**Step 3 — Answer each query with binary search:**  
For each query value, use binary search to find the rightmost item whose price ≤ query (upper bound - 1). The answer is `items[idx][1]` (already the prefix max beauty), or `0` if no such item exists.

**Time Complexity:** O(n log n + m log n) — sorting + one binary search per query  
**Space Complexity:** O(1) extra (modifying items in-place, result array excluded)

```python
class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        # Step 1: Sort items by price ascending
        items.sort(key=lambda x: x[0])
        n = len(items)

        # Step 2: Replace each beauty with the prefix maximum beauty up to that index
        cur_max = 0
        for i in range(n):
            cur_max = max(cur_max, items[i][1])
            items[i][1] = cur_max

        res = []
        for query in queries:
            # Step 3: Binary search for the rightmost item with price <= query
            # We find the first index where price > query (upper bound), then subtract 1
            left, right = 0, n - 1
            idx = n  # default: all items have price <= query
            while left <= right:
                mid = left + (right - left) // 2
                if items[mid][0] > query:
                    idx = mid        # mid might be the upper bound, search left
                    right = mid - 1
                else:
                    left = mid + 1   # price <= query, search right for a tighter bound
            idx -= 1  # convert upper_bound index to last valid index
            res.append(0 if idx < 0 else items[idx][1])
        return res
```

**Walkthrough with Example 1:**  
`items = [[1,2],[3,2],[2,4],[5,6],[3,5]]`, `queries = [1,2,3,4,5,6]`

After sorting by price:  
`[[1,2],[2,4],[3,2],[3,5],[5,6]]`

After prefix max of beauty:  
`[[1,2],[2,4],[3,4],[3,5],[5,6]]`

| query | binary search finds idx | answer |
|-------|------------------------|--------|
| 1     | 0                       | 2      |
| 2     | 1                       | 4      |
| 3     | 3                       | 5      |
| 4     | 3                       | 5      |
| 5     | 4                       | 6      |
| 6     | 4                       | 6      |

Output: `[2, 4, 5, 5, 6, 6]` ✓

# Tags

`Array` `Binary Search` `Sorting` `Prefix Maximum`
````

## Observations

## Solution

# Tags

