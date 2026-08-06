from typing import List

class Solution:
    def containsNearbyAlmostDuplicate(self, nums: List[int], indexDiff: int, valueDiff: int) -> bool:
        if valueDiff < 0: 
            return False
            
        buckets = {}
        # Width of each bucket
        w = valueDiff + 1
        
        for i, num in enumerate(nums):
            # Map number to its bucket ID
            bucket_id = num // w
            
            # Check current bucket
            if bucket_id in buckets:
                return True
                
            # Check adjacent lower bucket
            if (bucket_id - 1) in buckets and abs(num - buckets[bucket_id - 1]) <= valueDiff:
                return True
                
            # Check adjacent higher bucket
            if (bucket_id + 1) in buckets and abs(num - buckets[bucket_id + 1]) <= valueDiff:
                return True
                
            # Add to bucket
            buckets[bucket_id] = num
            
            # Evict old element outside window
            if i >= indexDiff:
                del buckets[nums[i - indexDiff] // w]
                
        return False
