## Problem

https://leetcode.com/problems/two-city-scheduling/description/

```
A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person to city b is bCosti.

Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.

Example 1:

Input: costs = [[10,20],[30,200],[400,50],[30,20]]
Output: 110
Explanation: 
The first person goes to city A for a cost of 10.
The second person goes to city A for a cost of 30.
The third person goes to city B for a cost of 50.
The fourth person goes to city B for a cost of 20.

The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.

Example 2:

Input: costs = [[259,770],[448,54],[926,667],[184,139],[840,118],[577,469]]
Output: 1859

Example 3:

Input: costs = [[515,563],[451,713],[537,709],[343,819],[855,779],[457,60],[650,359],[631,42]]
Output: 3086

Constraints:

2 * n == costs.length
2 <= costs.length <= 100
costs.length is even.
1 <= aCosti, bCosti <= 1000
```

## Observations

1. **Problem Nature**: This is a classic optimization problem where we need to minimize total cost while satisfying a constraint (exactly n people in each city).

2. **Constraint Analysis**: We have 2n people total and must send exactly n to city A and n to city B.

3. **Key Insight**: The problem isn't about finding the absolute cheapest option for each person, but rather about finding the optimal assignment that minimizes the total cost.

4. **Greedy Strategy**: We should prioritize sending people to the city where they have the greatest cost advantage (or least cost disadvantage) compared to the alternative.

5. **Cost Difference**: The difference `costs[i][0] - costs[i][1]` represents how much more expensive it is to send person i to city A compared to city B:
   - Negative difference: City A is cheaper for this person
   - Positive difference: City B is cheaper for this person

6. **Sorting Strategy**: By sorting by cost difference, we can identify which people should go to city A (those with the most negative differences) and which should go to city B.

## Solution

1. **Sort by Cost Difference**: `costs.sort(key=lambda x: x[0] - x[1])`
   - This sorts people by `aCost - bCost` in ascending order
   - People with negative differences (city A cheaper) come first
   - People with positive differences (city B cheaper) come last

2. **Send First Half to City A**: `for i in range(n // 2)`
   - These are people for whom city A is relatively cheaper
   - Add their city A costs to the total

3. **Send Second Half to City B**: `for i in range(n // 2, n)`
   - These are people for whom city B is relatively cheaper
   - Add their city B costs to the total

### Why This Works

The key insight is that we want to **maximize savings**. If we must send n people to each city, we should:
- Send people to city A who have the greatest advantage (or least disadvantage) going to A vs B
- Send people to city B who have the greatest advantage going to B vs A

### Example Walkthrough

Using Example 1: `costs = [[10,20],[30,200],[400,50],[30,20]]`

1. **Calculate differences**:
   - Person 0: 10 - 20 = -10 (A is 10 cheaper)
   - Person 1: 30 - 200 = -170 (A is 170 cheaper)
   - Person 2: 400 - 50 = 350 (B is 350 cheaper)
   - Person 3: 30 - 20 = 10 (B is 10 cheaper)

2. **Sort by differences**: [-170, -10, 10, 350]
   - Sorted costs: [[30,200], [10,20], [30,20], [400,50]]

3. **Assignment**:
   - First n=2 to city A: persons with costs [30,200] and [10,20] → costs 30 + 10 = 40
   - Last n=2 to city B: persons with costs [30,20] and [400,50] → costs 20 + 50 = 70
   - Total: 40 + 70 = 110 ✓

### Time & Space Complexity

- **Time Complexity**: O(n log n) due to sorting
- **Space Complexity**: O(1) if we can modify the input array, O(n) otherwise

### Alternative Approach (Same Logic)

Think of it as: "What's the cost if everyone goes to city A?" Then we save money by sending the n people with the highest `aCost - bCost` to city B instead.

## Tags

- Greedy Algorithm
- Sorting
- Optimization
- Array Manipulation

