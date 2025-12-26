class Solution:
    def isValidSerialization(self, preorder: str) -> bool:
        slot = 1
        for s in preorder.split(','):
            slot -= 1
            if slot < 0:
                return False
            
            if s != '#':
                slot += 2
        
        return slot == 0