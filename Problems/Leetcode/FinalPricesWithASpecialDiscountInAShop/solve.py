from typing import List

class Solution:
    def finalPrices(self, prices: List[int]) -> List[int]:
        n = len(prices)
        prefix = [-1] * n

        st = []
        for i in range(n - 1, -1, -1):
            while st and prices[st[-1]] > prices[i]:
                st.pop()
            if st:
                prefix[i] = st[-1]
            st.append(i)
        
        res = []
        for i in range(n):
            price = prices[i]
            if prefix[i] != -1:
                price -= prices[prefix[i]]
            res.append(price)
        return res