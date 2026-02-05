import heapq

class AuctionSystem:

    def __init__(self):
        self.real_bid = {} # { item : {user: price}}
        self.max_heaps = {} # { item: [order by (-price, -user)] }

    def addBid(self, userId: int, itemId: int, bidAmount: int) -> None:
        if itemId not in self.real_bid:
            self.real_bid[itemId] = {}
        self.real_bid[itemId][userId] = bidAmount
        if itemId not in self.max_heaps:
            self.max_heaps[itemId] = []
        heapq.heappush(self.max_heaps[itemId], (-bidAmount, -userId))

    def updateBid(self, userId: int, itemId: int, newAmount: int) -> None:
        self.real_bid[itemId][userId] = newAmount
        heapq.heappush(self.max_heaps[itemId], (-newAmount, -userId))

    def removeBid(self, userId: int, itemId: int) -> None:
        self.real_bid[itemId].pop(userId)

    def getHighestBidder(self, itemId: int) -> int:
        if itemId not in self.real_bid or not self.real_bid[itemId]:
            return -1
        
        d_bid = self.real_bid[itemId]
        max_heap = self.max_heaps[itemId]
        while max_heap and -max_heap[0][1] not in d_bid or -max_heap[0][0] != d_bid[-max_heap[0][1]]:
            heapq.heappop(max_heap)
        if not max_heap:
            return -1
        return -max_heap[0][1]


# Your AuctionSystem object will be instantiated and called as such:
# obj = AuctionSystem()
# obj.addBid(userId,itemId,bidAmount)
# obj.updateBid(userId,itemId,newAmount)
# obj.removeBid(userId,itemId)
# param_4 = obj.getHighestBidder(itemId)