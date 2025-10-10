from typing import List, Any

class HashTable:
    def __init__(self, init_size = 16):
        self._size = 0
        self._table = [[] for _ in range(0, init_size)]
    
    def insert(self, key: Any, val: Any) -> None:
        if self._get_factor() > 0.75:
            self._resize_table(len(self._table) * 2)
        
        bucket_index = self._hash_key(key)
        bucket = self._table[bucket_index]
        
        # Check if key already exists and update it
        for i, (k, v) in enumerate(bucket):
            if k == key:
                bucket[i] = (key, val)  # Update existing key
                return
        
        # If key doesn't exist, add new entry
        bucket.append((key, val))
        self._size += 1
    
    def remove(self, key: Any) -> None:
        bucket_index = self._hash_key(key)
        bucket = self._table[bucket_index]
        for (k, v) in bucket:
            if k == key:
                bucket.remove((k, v))
                self._size -= 1
                return
    
    def contains(self, key: Any) -> bool:
        bucket_index = self._hash_key(key)
        bucket = self._table[bucket_index]
        for (k, v) in bucket:
            if k == key:
                return True
        return False
    
    def _hash_key(self, key: Any) -> int:
        return hash(key) % len(self._table)
    
    def _get_factor(self) -> float:
        return self._size / len(self._table)
    
    def _resize_table(self, new_size: int) -> None:
        new_table = [[] for _ in range(0, new_size)]
        for bucket in self._table:
            for (key, value) in bucket:
                new_bucket_index = hash(key) % new_size
                new_table[new_bucket_index].append((key, value))
        self._table = new_table

class MyHashSet:

    def __init__(self):
        self._hash_table = HashTable()

    def add(self, key: int) -> None:
        self._hash_table.insert(key, True)

    def remove(self, key: int) -> None:
        self._hash_table.remove(key)

    def contains(self, key: int) -> bool:
        return self._hash_table.contains(key)

# Your MyHashSet object will be instantiated and called as such:
# obj = MyHashSet()
# obj.add(key)
# obj.remove(key)
# param_3 = obj.contains(key)