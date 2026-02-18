## Problem

https://leetcode.com/problems/design-a-food-rating-system/description/

Design a food rating system that can do the following:
- Modify the rating of a food item listed in the system.
- Return the highest-rated food item for a type of cuisine in the system.

Implement the `FoodRatings` class:
- `FoodRatings(String[] foods, String[] cuisines, int[] ratings)` - Initializes the system with n food items where:
  - `foods[i]` is the name of the ith food
  - `cuisines[i]` is the type of cuisine of the ith food
  - `ratings[i]` is the initial rating of the ith food
- `void changeRating(String food, int newRating)` - Changes the rating of the food item
- `String highestRated(String cuisine)` - Returns the name of the food item that has the highest rating for the given cuisine. If there is a tie, return the item with the lexicographically smaller name.

**Constraints:**
- 1 <= n <= 2 * 10^4
- All food names are distinct
- 1 <= ratings[i] <= 10^8
- At most 2 * 10^4 calls total to changeRating and highestRated

## Observations

1. **Multiple Operations Required:**
   - Need to efficiently query the highest-rated food for each cuisine type (O(log n) or O(1))
   - Need to update food ratings dynamically
   - Need to handle lexicographic ordering for tie-breaking

2. **Key Insights:**
   - Each cuisine type needs its own priority queue to track highest-rated foods
   - Python's heapq is a min-heap, so use negative ratings for max-heap behavior
   - For tie-breaking, tuples naturally sort lexicographically: `(-rating, food_name)` will sort by highest rating first, then alphabetically by name

3. **Lazy Deletion Strategy:**
   - Instead of removing old ratings from heaps (expensive O(n) operation), use lazy deletion
   - Keep stale entries in the heap and clean them up when accessing the top
   - Store current ratings separately to validate heap entries

## Solution

### Approach: Max Heap with Lazy Deletion

**Data Structures:**
- `map_type`: Dictionary mapping cuisine type → max heap of (negative_rating, food_name) tuples
- `map_food`: Dictionary mapping food_name → [current_rating, cuisine_type]

**Algorithm:**

1. **Initialization O(n log n):**
   - Create a heap for each unique cuisine type
   - For each food, store its rating and cuisine in `map_food`
   - Push (-rating, food_name) into the corresponding cuisine heap

2. **changeRating O(log n):**
   - Update the rating in `map_food` for the given food
   - Push a new entry with the updated rating to the cuisine's heap
   - Old entries remain but become "stale" (will be cleaned up later)

3. **highestRated O(k log n) where k = # of stale entries:**
   - Get the heap for the requested cuisine
   - **Lazy cleanup:** While the top entry's rating doesn't match the current rating in `map_food`, pop it (it's stale)
   - Return the food name at the top of the heap

**Why This Works:**
- Max heap (via negative ratings) ensures O(log n) insertions and O(1) peek
- Lazy deletion avoids expensive O(n) removal from middle of heap
- Lexicographic tie-breaking handled automatically by tuple comparison
- Cleanup happens only when needed (during highestRated calls)

**Time Complexity:**
- Init: O(n log n)
- changeRating: O(log n) per call
- highestRated: O(k log n) amortized, where k is stale entries cleaned

**Space Complexity:** O(n + m) where n = number of foods, m = total changeRating calls (due to lazy deletion creating duplicate entries)

**Note:** There's a bug in the provided condition. The while loop should be:
```python
while pq and -pq[0][0] != self.map_food[pq[0][1]][0]:
    heapq.heappop(pq)
```
This correctly removes entries where the heap rating doesn't match the current rating.

# Tags
#heap #priority-queue #hash-map #design #lazy-deletion #data-structures

