## Problem

https://leetcode.com/problems/fruits-into-baskets-ii/description/

```
You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.

From left to right, place the fruits according to these rules:

Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
Each basket can hold only one type of fruit.
If a fruit type cannot be placed in any basket, it remains unplaced.
Return the number of fruit types that remain unplaced after all possible allocations are made.

Example 1:

Input: fruits = [4,2,5], baskets = [3,5,4]

Output: 1

Explanation:

fruits[0] = 4 is placed in baskets[1] = 5.
fruits[1] = 2 is placed in baskets[0] = 3.
fruits[2] = 5 cannot be placed in baskets[2] = 4.
Since one fruit type remains unplaced, we return 1.

Example 2:

Input: fruits = [3,6,1], baskets = [6,4,7]

Output: 0

Explanation:

fruits[0] = 3 is placed in baskets[0] = 6.
fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity) but can be placed in the next available basket, baskets[2] = 7.
fruits[2] = 1 is placed in baskets[1] = 4.
Since all fruits are successfully placed, we return 0.

Constraints:

n == fruits.length == baskets.length
1 <= n <= 100
1 <= fruits[i], baskets[i] <= 1000
```

## Observations

1. **Greedy Assignment**: The problem requires placing fruits in the leftmost available basket that can accommodate them. This suggests a greedy approach where we process fruits in order and assign each to the first suitable basket.

2. **First-Fit Strategy**: This is essentially a "first-fit" bin packing problem where:
   - Items (fruits) have sizes (quantities)
   - Bins (baskets) have capacities
   - Each bin can hold at most one item
   - We want to minimize unplaced items

3. **Sequential Processing**: We must process fruits from left to right (index 0 to n-1) and for each fruit, check baskets from left to right to find the first available one with sufficient capacity.

4. **State Tracking**: We need to track which baskets are already used to ensure each basket holds only one fruit type.

## Solution

**Approach: Greedy First-Fit Algorithm**

The solution uses a straightforward greedy approach:

1. **Initialize tracking**: Create a `used` array to track which baskets are occupied
2. **Process each fruit**: For each fruit in the fruits array (left to right)
3. **Find first suitable basket**: Scan baskets from left to right to find the first unused basket with sufficient capacity
4. **Place or count unplaced**: If found, mark the basket as used; otherwise, increment the unplaced counter

**Key Points:**
- **Time Complexity**: O(n²) - for each fruit, we may scan all baskets
- **Space Complexity**: O(n) - for the `used` array
- **For-Else Construct**: The `else` clause after the `for` loop executes only if the loop completes without hitting a `break`
- **Greedy Choice**: Always choose the leftmost available basket that fits, which ensures optimal placement according to the problem's rules

# Tags

