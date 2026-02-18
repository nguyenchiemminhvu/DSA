from typing import List
import heapq

class FoodRatings:

    def __init__(self, foods: List[str], food_types: List[str], ratings: List[int]):
        all_food_types = set(food_types)
        self.map_type = {} # type -> max heap of food rating
        for food_type in all_food_types:
            self.map_type[food_type] = [] # (-rating, food)
        
        self.map_food = {} # food -> [rating, type]
        for i, food in enumerate(foods):
            self.map_food[food] = [ratings[i], food_types[i]]
            food_type = food_types[i]
            pq = self.map_type[food_type]
            heapq.heappush(pq, (-ratings[i], food))

    def changeRating(self, food: str, new_rating: int) -> None:
        food_type = self.map_food[food][1]
        self.map_food[food] = [new_rating, food_type]
        heapq.heappush(self.map_type[food_type], (-new_rating, food))

    def highestRated(self, food_type: str) -> str:
        pq = self.map_type[food_type]
        while pq and pq[0][1] in self.map_food[pq[0][1]] or -pq[0][0] != self.map_food[pq[0][1]][0]:
            heapq.heappop(pq)
        
        if pq:
            rating, food = pq[0][0], pq[0][1]
            return food
        
        return ""


# Your FoodRatings object will be instantiated and called as such:
# obj = FoodRatings(foods, cuisines, ratings)
# obj.changeRating(food,newRating)
# param_2 = obj.highestRated(cuisine)