class Solution:
    def customSortString(self, order: str, s: str) -> str:
        mp = {}
        for i, c in enumerate(order):
            mp[c] = i
        
        non_order = []
        order = []
        for i, c in enumerate(s):
            if c not in mp:
                non_order.append(c)
            else:
                order.append(c)
        
        order.sort(key=lambda x : mp[x])

        return "".join(order + non_order)