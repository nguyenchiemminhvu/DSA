from typing import List

class Solution:
    def shoppingOffers(self, price: List[int], special: List[List[int]], needs: List[int]) -> int:
        n = len(price)
        ns = len(special)

        filtered_offers = []
        for offer in special:
            original_price = sum(offer[i] * price[i] for i in range(n))
            if original_price > offer[-1]:
                filtered_offers.append(offer)
        
        memo = {}
        def dfs(state: tuple) -> int:
            if state in memo:
                return memo[state]

            base_cost = sum(state[i] * price[i] for i in range(n))
            best_price = base_cost

            for offer in filtered_offers:
                state_with_offer = []
                for i in range(n):
                    if offer[i] > state[i]:
                        state_with_offer = None
                        break
                    state_with_offer.append(state[i] - offer[i])
                if state_with_offer is not None:
                    best_price = min(best_price, offer[-1] + dfs(tuple(state_with_offer)))
            
            memo[state] = best_price
            return best_price
        
        return dfs(tuple(needs))