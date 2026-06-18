from collections import defaultdict
from typing import List

class Solution:
    def displayTable(self, orders: List[List[str]]) -> List[List[str]]:
        mp_table = defaultdict(lambda: defaultdict(int))
        food_set = set()
        table_set = set()

        for order in orders:
            name, table = order[:2]
            items = order[2:]
            table_set.add(table)
            for item in items:
                food_set.add(item)
                mp_table[table][item] += 1
        
        tables = sorted(list(table_set), key=lambda x: int(x))
        foods = sorted(list(food_set))

        res = []
        res.append(['Table'] + foods)
        for table in tables:
            counter = []
            for food in foods:
                counter.append(str(mp_table[table][food]))
            res.append([str(table)] + counter)
        return res