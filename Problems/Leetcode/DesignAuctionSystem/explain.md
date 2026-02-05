## Problem

https://leetcode.com/problems/design-auction-system/description/

```
Design an auction system that manages bids from multiple users in real time.

Each bid is associated with a userId, an itemId, and a bidAmount.

Implement the AuctionSystem class:
- AuctionSystem(): Initializes the AuctionSystem object.
- void addBid(int userId, int itemId, int bidAmount): Adds a new bid for itemId by userId with bidAmount. 
  If the same userId already has a bid on itemId, replace it with the new bidAmount.
- void updateBid(int userId, int itemId, int newAmount): Updates the existing bid of userId for itemId to newAmount. 
  It is guaranteed that this bid exists.
- void removeBid(int userId, int itemId): Removes the bid of userId for itemId. 
  It is guaranteed that this bid exists.
- int getHighestBidder(int itemId): Returns the userId of the highest bidder for itemId. 
  If multiple users have the same highest bidAmount, return the user with the highest userId. 
  If no bids exist for the item, return -1.

Constraints:
- 1 <= userId, itemId <= 5 * 10^4
- 1 <= bidAmount, newAmount <= 10^9
- At most 5 * 10^4 total calls to addBid, updateBid, removeBid, and getHighestBidder.
- The input is generated such that for updateBid and removeBid, the bid from the given userId for the given itemId will be valid.
```

## Observations

1. **Multiple Data Structures Needed**: We need to track both the current valid bids and efficiently find the highest bidder.

2. **Lazy Deletion Problem**: When a bid is updated or removed, we can't efficiently remove old entries from the heap in O(log n) time. Instead, we use a "lazy deletion" approach where stale entries remain in the heap but are filtered out when queried.

3. **Heap for Maximum Queries**: A max heap is ideal for finding the highest bidder. We use negative values to simulate a max heap in Python (since heapq is a min heap).

4. **Tie-Breaking Rule**: When multiple users have the same highest bid, we must return the user with the highest userId. This is achieved by storing (-bidAmount, -userId) in the heap.

5. **Validation Required**: In `getHighestBidder`, we need to validate that the top of the heap represents a current valid bid by checking:
   - The userId exists in the real_bid dictionary for that item
   - The bidAmount in the heap matches the current bidAmount in real_bid

## Solution

### Approach: Max Heap with Lazy Deletion

**Data Structures:**
- `real_bid`: A nested dictionary `{itemId: {userId: bidAmount}}` that stores the current valid bids
- `max_heaps`: A dictionary `{itemId: heap}` where each heap stores tuples `(-bidAmount, -userId)` for that item

**Key Operations:**

1. **addBid(userId, itemId, bidAmount)**:
   - Update or add the bid in `real_bid[itemId][userId]`
   - Push `(-bidAmount, -userId)` to the heap for that item
   - Time: O(log n) where n is the number of bids for the item

2. **updateBid(userId, itemId, newAmount)**:
   - Update `real_bid[itemId][userId]` with the new amount
   - Push the new bid to the heap (old entry becomes stale)
   - Time: O(log n)

3. **removeBid(userId, itemId)**:
   - Remove userId from `real_bid[itemId]`
   - The heap entry becomes stale and will be cleaned up during getHighestBidder
   - Time: O(1)

4. **getHighestBidder(itemId)**:
   - Check if any valid bids exist for the item
   - Pop stale entries from the heap until we find a valid bid:
     - Stale entry = userId not in real_bid OR bidAmount doesn't match
   - Return the userId of the valid highest bid, or -1 if none exist
   - Time: O(k) where k is the number of stale entries at the top of the heap (amortized O(log n))

**Why This Works:**

The lazy deletion approach avoids expensive heap removal operations. Stale entries naturally accumulate at various positions in the heap, but we only care about the top element. When querying for the highest bidder, we clean up stale entries at the top until we find a valid one.

The space trade-off is acceptable because:
- Each update/remove creates at most one stale entry
- Total operations are bounded by 5 × 10^4
- Stale entries are eventually cleaned up during getHighestBidder calls

**Time Complexity:**
- addBid: O(log n)
- updateBid: O(log n)
- removeBid: O(1)
- getHighestBidder: O(k log n) where k is stale entries, amortized O(log n)

**Space Complexity:** O(m × n) where m is the number of items and n is the average number of bids (including stale entries) per item.

# Tags
#design #heap #hash-table #lazy-deletion #data-structures

