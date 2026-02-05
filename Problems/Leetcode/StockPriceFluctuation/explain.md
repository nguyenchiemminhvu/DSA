## Problem

https://leetcode.com/problems/stock-price-fluctuation/description/

```
You are given a stream of records about a particular stock. Each record contains a timestamp and the corresponding price of the stock at that timestamp.

Unfortunately due to the volatile nature of the stock market, the records do not come in order. Even worse, some records may be incorrect. Another record with the same timestamp may appear later in the stream correcting the price of the previous wrong record.

Design an algorithm that:
- Updates the price of the stock at a particular timestamp, correcting the price from any previous records at the timestamp.
- Finds the latest price of the stock based on the current records. The latest price is the price at the latest timestamp recorded.
- Finds the maximum price the stock has been based on the current records.
- Finds the minimum price the stock has been based on the current records.

Implement the StockPrice class:
- StockPrice() Initializes the object with no price records.
- void update(int timestamp, int price) Updates the price of the stock at the given timestamp.
- int current() Returns the latest price of the stock.
- int maximum() Returns the maximum price of the stock.
- int minimum() Returns the minimum price of the stock.

Example 1:
Input
["StockPrice", "update", "update", "current", "maximum", "update", "maximum", "update", "minimum"]
[[], [1, 10], [2, 5], [], [], [1, 3], [], [4, 2], []]
Output
[null, null, null, 5, 10, null, 5, null, 2]

Explanation
StockPrice stockPrice = new StockPrice();
stockPrice.update(1, 10); // Timestamps are [1] with corresponding prices [10].
stockPrice.update(2, 5);  // Timestamps are [1,2] with corresponding prices [10,5].
stockPrice.current();     // return 5, the latest timestamp is 2 with the price being 5.
stockPrice.maximum();     // return 10, the maximum price is 10 at timestamp 1.
stockPrice.update(1, 3);  // The previous timestamp 1 had the wrong price, so it is updated to 3.
                          // Timestamps are [1,2] with corresponding prices [3,5].
stockPrice.maximum();     // return 5, the maximum price is 5 after the correction.
stockPrice.update(4, 2);  // Timestamps are [1,2,4] with corresponding prices [3,5,2].
stockPrice.minimum();     // return 2, the minimum price is 2 at timestamp 4.

Constraints:
- 1 <= timestamp, price <= 10^9
- At most 10^5 calls will be made in total to update, current, maximum, and minimum.
- current, maximum, and minimum will be called only after update has been called at least once.
```

## Observations

1. **Out-of-order updates**: Records can arrive in any order, not necessarily sorted by timestamp
2. **Price corrections**: The same timestamp can be updated multiple times with different prices
3. **Three query types**: Need to efficiently support current(), maximum(), and minimum() operations
4. **Latest timestamp tracking**: Must keep track of which timestamp is the most recent
5. **Stale data in heaps**: After price corrections, heaps may contain outdated (price, timestamp) pairs

## Solution

### Approach: Lazy Deletion with Heaps

The key insight is to use **two heaps** (min-heap and max-heap) along with a **hash map** to track the true current prices:

1. **Data Structures**:
   - `real_price`: Dictionary mapping timestamp → current price (source of truth)
   - `min_heap`: Min-heap of (price, timestamp) pairs for finding minimum
   - `max_heap`: Max-heap of (-price, timestamp) pairs for finding maximum
   - `latest_time`: Tracks the most recent timestamp seen

2. **Update Operation**: O(log n)
   - Update `latest_time` to track the maximum timestamp
   - Store/overwrite the price in `real_price[timestamp]`
   - Push (price, timestamp) to both heaps (even if it's an update)
   - Old entries remain in heaps but will be filtered out later

3. **Current Operation**: O(1)
   - Simply return `real_price[latest_time]`

4. **Maximum/Minimum Operations**: O(log n) amortized
   - **Lazy deletion**: Peek at the top of the heap
   - If the top's price doesn't match `real_price` for that timestamp, it's stale → pop it
   - Repeat until we find a valid entry
   - Return the price from the valid top entry

### Why This Works

- **Correctness**: The `real_price` dictionary always holds the truth. Heaps may contain stale entries, but we validate them lazily.
- **Efficiency**: We avoid expensive heap removal operations (O(n)). Instead, we let stale entries accumulate and only remove them when they reach the top.
- **Amortized complexity**: Each entry is pushed once and popped at most once, giving O(log n) amortized time per operation.

### Implementation

```python
import heapq

class StockPrice:

    def __init__(self):
        self.latest_time = 0
        self.min_heap = []
        self.max_heap = []
        self.real_price = {}  # timestamp -> price

    def update(self, timestamp: int, price: int) -> None:
        self.latest_time = max(self.latest_time, timestamp)
        self.real_price[timestamp] = price
        heapq.heappush(self.min_heap, (price, timestamp))
        heapq.heappush(self.max_heap, (-price, timestamp))

    def current(self) -> int:
        return self.real_price[self.latest_time]

    def maximum(self) -> int:
        # Lazy deletion: remove stale entries from top
        while self.max_heap and -self.max_heap[0][0] != self.real_price[self.max_heap[0][1]]:
            heapq.heappop(self.max_heap)
        return -self.max_heap[0][0]

    def minimum(self) -> int:
        # Lazy deletion: remove stale entries from top
        while self.min_heap and self.min_heap[0][0] != self.real_price[self.min_heap[0][1]]:
            heapq.heappop(self.min_heap)
        return self.min_heap[0][0]
```

### Complexity Analysis

- **Time Complexity**:
  - `update()`: O(log n) - two heap pushes
  - `current()`: O(1) - dictionary lookup
  - `maximum()`: O(log n) amortized - lazy deletion of stale entries
  - `minimum()`: O(log n) amortized - lazy deletion of stale entries

- **Space Complexity**: O(n) where n is the total number of updates (including corrections)
  - Each update adds an entry to both heaps
  - Dictionary stores one entry per unique timestamp

### Example Walkthrough

```
update(1, 10):
  latest_time = 1
  real_price = {1: 10}
  min_heap = [(10, 1)]
  max_heap = [(-10, 1)]

update(2, 5):
  latest_time = 2
  real_price = {1: 10, 2: 5}
  min_heap = [(5, 2), (10, 1)]
  max_heap = [(-10, 1), (-5, 2)]

current() → real_price[2] = 5

maximum() → -max_heap[0][0] = 10

update(1, 3):  // Correction!
  latest_time = 2 (unchanged)
  real_price = {1: 3, 2: 5}  // Updated timestamp 1
  min_heap = [(3, 1), (5, 2), (10, 1)]
  max_heap = [(-10, 1), (-5, 2), (-3, 1)]

maximum():
  Check top: -(-10) = 10, but real_price[1] = 3 (stale!) → pop
  Check new top: -(-5) = 5, real_price[2] = 5 ✓
  Return 5
```

# Tags
`heap` `hash-table` `design` `lazy-deletion` `data-stream`

