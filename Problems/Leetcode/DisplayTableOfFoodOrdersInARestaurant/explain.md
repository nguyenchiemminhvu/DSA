## Problem

https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/description/

Given an array `orders` where each element is `orders[i] = [customerName, tableNumber, foodItem]`, return the restaurant's **display table**.

The display table is structured as follows:
- **First row (header):** `"Table"` followed by all food item names in **alphabetical order**.
- **Remaining rows:** Each row corresponds to a unique table number (in **numerically increasing order**), showing how many of each food item was ordered at that table.
- Customer names are **not** included.

**Example:**
```
Input: orders = [["David","3","Ceviche"],["Corina","10","Beef Burrito"],["David","3","Fried Chicken"],["Carla","5","Water"],["Carla","5","Ceviche"],["Rous","3","Ceviche"]]
Output: [["Table","Beef Burrito","Ceviche","Fried Chicken","Water"],
         ["3","0","2","1","0"],
         ["5","0","1","0","1"],
         ["10","1","0","0","0"]]
```

---

## Solution

### Key Observations

1. We need to collect two distinct sets of information: **which tables exist** and **which food items exist**.
2. For each table, we need a count of how many times each food item was ordered.
3. The food columns must be sorted **alphabetically** and the table rows sorted **numerically**.

### Approach — Hash Map of Hash Maps

Use a **nested default dictionary** `mp_table[table][food] → count` to accumulate orders, plus two sets to track all unique table numbers and food items.

#### Step 1 — Scan all orders

```python
for order in orders:
    name, table = order[:2]
    items = order[2:]          # always exactly one item per order
    table_set.add(table)
    for item in items:
        food_set.add(item)
        mp_table[table][item] += 1
```

For every order entry we:
- Record the table number in `table_set`.
- Record the food item in `food_set`.
- Increment the counter `mp_table[table][item]`.

Because `mp_table` is a `defaultdict(lambda: defaultdict(int))`, accessing a missing key automatically creates a zero-initialised inner dict, so no explicit initialisation is needed.

#### Step 2 — Sort the axes

```python
tables = sorted(list(table_set), key=lambda x: int(x))
foods  = sorted(list(food_set))
```

- Tables are strings (e.g. `"10"`, `"3"`), so we cast to `int` for the sort key to get numeric order (`3, 5, 10`) instead of lexicographic order (`10, 3, 5`).
- Food names are already strings, so plain `sorted()` gives alphabetical order.

#### Step 3 — Build the result grid

```python
res = [['Table'] + foods]           # header row

for table in tables:
    row = [str(table)]
    for food in foods:
        row.append(str(mp_table[table][food]))   # 0 if never ordered
    res.append(row)
```

For every `(table, food)` pair we look up the count. The `defaultdict(int)` guarantees a `0` for any food that was never ordered at that table, which is exactly the `"0"` fill required by the problem.

### Complexity

| | Value |
|---|---|
| **Time** | $O(N + T \cdot F)$ where $N$ = number of orders, $T$ = unique tables, $F$ = unique food items |
| **Space** | $O(T \cdot F)$ for the nested map |

The dominant term for building the table is $O(T \cdot F)$. Sorting costs $O(T \log T + F \log F)$, which is negligible given the constraints ($T \le 500$, $F \le$ number of orders $\le 5 \times 10^4$).

### Full Solution

```python
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
        foods  = sorted(list(food_set))

        res = [['Table'] + foods]
        for table in tables:
            counter = [str(mp_table[table][food]) for food in foods]
            res.append([str(table)] + counter)
        return res
```
