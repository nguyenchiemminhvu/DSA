class Solution:
    def elevatorRequests(self, n: int, requests: list[int]) -> int:
        res = 0
        cur = 0
        for f in requests:
            diff = abs(f - cur)
            cur = f
            res += diff
        
        return res