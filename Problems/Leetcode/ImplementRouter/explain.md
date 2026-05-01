## Problem

https://leetcode.com/problems/implement-router/description/

Design a data structure to efficiently manage network packets in a router with the following requirements:

**Packet Attributes:**
- `source`: Unique identifier for the sending machine
- `destination`: Unique identifier for the target machine
- `timestamp`: Time when the packet arrived at the router

**Router Operations:**

1. **`Router(int memoryLimit)`**: Initialize with a fixed memory limit (max packets storable)
   - When a new packet would exceed the limit, remove the oldest packet

2. **`bool addPacket(source, destination, timestamp)`**: Add a packet to the router
   - Return `true` if successfully added; `false` if it's a duplicate
   - A duplicate has identical source, destination, and timestamp

3. **`int[] forwardPacket()`**: Forward the next packet in FIFO order
   - Remove and return the oldest packet as `[source, destination, timestamp]`
   - Return empty array if no packets exist

4. **`int getCount(destination, startTime, endTime)`**: Count stored packets
   - Return count of packets with matching destination and timestamp in range `[startTime, endTime]`

**Constraints:**
- Memory limit: 2 to 10⁵
- Source/destination IDs: 1 to 2×10⁵
- Timestamps: 1 to 10⁹ (queries in non-decreasing order)
- Up to 10⁵ total method calls

## Observations

1. **FIFO Forwarding**: Packets must be forwarded in the order they arrived. A `deque` naturally maintains this order.

2. **Duplicate Detection**: Need O(1) lookup to check if `(timestamp, source, destination)` tuple already exists. A `set` is ideal for this.

3. **Memory Eviction**: When full, remove the oldest packet (leftmost in deque). Since we track all packets in the set and deque together, removal is straightforward.

4. **Range Queries**: The `getCount` operation requires counting packets with:
   - Specific destination
   - Timestamp in range `[startTime, endTime]`
   
   Since **addPacket calls are in non-decreasing timestamp order**, the timestamps stored for each destination are naturally sorted. This enables **binary search** for efficient range counting.

5. **Data Structure Strategy**:
   - `deque`: Maintains FIFO order for forwarding
   - `set`: O(1) duplicate detection
   - `defaultdict(list)`: Maps each destination to its sorted list of timestamps
   - Binary search on timestamp lists: O(log n) per query

## Solution

```python
from collections import deque, defaultdict
from typing import List

class Router:
    def __init__(self, memoryLimit: int):
        self.n = memoryLimit
        self.s_packets = set()           # (timestamp, source, destination) tuples
        self.packets = deque()           # FIFO queue of (timestamp, source, destination)
        self.dest_map = defaultdict(list)  # destination -> sorted list of timestamps

    def addPacket(self, source: int, destination: int, timestamp: int) -> bool:
        """
        Add a packet if not a duplicate and within memory limit.
        Time: O(1) average | Space: O(1) for this operation
        """
        packet = (timestamp, source, destination)
        
        # Check if duplicate
        if packet in self.s_packets:
            return False
        
        # Evict oldest packet if at memory limit
        if len(self.packets) == self.n:
            old_timestamp, old_source, old_destination = self.packets.popleft()
            self.s_packets.remove((old_timestamp, old_source, old_destination))
            self.dest_map[old_destination].pop(0)  # Remove first (oldest) timestamp
        
        # Add new packet
        self.packets.append(packet)
        self.s_packets.add(packet)
        self.dest_map[destination].append(timestamp)
        return True

    def forwardPacket(self) -> List[int]:
        """
        Forward the oldest packet in FIFO order.
        Time: O(1) | Space: O(1)
        """
        if not self.packets:
            return []
        
        timestamp, source, destination = self.packets.popleft()
        self.s_packets.remove((timestamp, source, destination))
        self.dest_map[destination].pop(0)  # Remove first timestamp
        return [source, destination, timestamp]

    def _lower_bound(self, arr: List[int], target: int) -> int:
        """
        Find the leftmost position where arr[pos] >= target (binary search).
        Time: O(log n)
        """
        left, right = 0, len(arr)
        while left < right:
            mid = (left + right) // 2
            if arr[mid] < target:
                left = mid + 1
            else:
                right = mid
        return left

    def getCount(self, destination: int, startTime: int, endTime: int) -> int:
        """
        Count packets with matching destination and timestamp in range [startTime, endTime].
        Time: O(log n) where n is number of packets with this destination
        """
        timestamps = self.dest_map[destination]
        if not timestamps:
            return 0
        
        # Find leftmost timestamp >= startTime
        left = self._lower_bound(timestamps, startTime)
        # Find leftmost timestamp > endTime (i.e., >= endTime + 1)
        right = self._lower_bound(timestamps, endTime + 1)
        
        return right - left
```

## Complexity Analysis

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| `addPacket` | O(1) | O(1) | Set lookup/insert is O(1) average; deque operations are O(1) |
| `forwardPacket` | O(1) | O(1) | Deque popleft and set remove are O(1) |
| `getCount` | O(log n) | O(1) | Binary search on sorted timestamp list; n = packets with destination |
| **Total Space** | - | O(m) | m = memory limit; store up to m packets |

## Key Design Insights

1. **Tuple as unique identifier**: Using `(timestamp, source, destination)` as the packet identity ensures all three fields matter for duplicate detection.

2. **Synchronized removal**: When removing packets:
   - Remove from `deque` (FIFO order)
   - Remove from `set` (duplicate tracking)
   - Remove from `dest_map[destination]` (range query support)
   
   All three structures must stay synchronized.

3. **Sorted timestamp lists**: Because addPacket calls arrive in non-decreasing timestamp order, each destination's timestamp list is automatically sorted. This naturally supports efficient binary search without explicit sorting.

4. **Binary search technique**: The `_lower_bound` method finds the insertion point—two calls efficiently narrow the range:
   - `left = _lower_bound(timestamps, startTime)`: First timestamp ≥ startTime
   - `right = _lower_bound(timestamps, endTime + 1)`: First timestamp > endTime
   - Count = `right - left`

## Example Walkthrough

```
Router(3)  // memoryLimit = 3

addPacket(1, 4, 90):    packets=[(90,1,4)], dest_map[4]=[90] → true
addPacket(2, 5, 90):    packets=[(90,1,4), (90,2,5)], dest_map[5]=[90] → true
addPacket(1, 4, 90):    Duplicate (90,1,4) → false
addPacket(3, 5, 95):    packets=[(90,1,4), (90,2,5), (95,3,5)], dest_map[5]=[90,95] → true
addPacket(4, 5, 105):   At limit; evict (90,1,4)
                        packets=[(90,2,5), (95,3,5), (105,4,5)], dest_map[5]=[90,95,105] → true

forwardPacket():        Remove (90,2,5) from front → [2, 5, 90]
                        packets=[(95,3,5), (105,4,5)], dest_map[5]=[95,105]

addPacket(5, 2, 110):   packets=[(95,3,5), (105,4,5), (110,5,2)] → true

getCount(5, 100, 110):  dest_map[5]=[95,105]
                        left = lower_bound([95,105], 100) = 1
                        right = lower_bound([95,105], 111) = 2
                        count = 2 - 1 = 1  (packet [105,4,5])
```

# Tags
#deque #set #binary-search #range-query #duplicate-detection

