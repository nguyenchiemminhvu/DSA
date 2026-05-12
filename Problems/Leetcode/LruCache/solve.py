class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = self.next = None

class LRUCache:

    def __init__(self, capacity: int):
        self.cap = capacity
        self.cache = {} # key -> Node(key, value)
        self.head, self.tail = Node(0, 0), Node(0, 0) # dummy nodes
        self.head.prev, self.tail.next = self.tail, self.head
    
    def __insert(self, node: Node):
        prv = self.head.prev
        prv.next = node
        node.next = self.head
        self.head.prev = node
        node.prev = prv
    
    def __remove(self, node: Node):
        prv, nxt = node.prev, node.next
        prv.next, nxt.prev = nxt, prv

    def get(self, key: int) -> int:
        if key in self.cache:
            val = self.cache[key].value
            self.__remove(self.cache[key])
            self.__insert(self.cache[key])
            return val
        return -1

    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.__remove(self.cache[key])

        node = Node(key, value)
        self.cache[key] = node
        self.__insert(node)
        if len(self.cache) > self.cap:
            lru = self.tail.next
            self.__remove(lru)
            self.cache.pop(lru.key)


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)