# Shopping Offers (LeetCode 638)

## Problem

https://leetcode.com/problems/shopping-offers/description/

In LeetCode Store, there are `n` items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.

**Given:**
- `price`: An integer array where `price[i]` is the price of the i-th item
- `needs`: An integer array where `needs[i]` is the number of pieces of the i-th item you want to buy
- `special`: A 2D array where `special[i]` is of size `n + 1`:
  - `special[i][j]` is the number of pieces of the j-th item in the i-th offer
  - `special[i][n]` is the price of the i-th offer

**Goal:** Return the lowest price you have to pay for exactly the items specified in `needs`.

**Rules:**
- You can use any special offer as many times as you want
- You cannot buy more items than you need (even if it would lower the price)

### Examples

**Example 1:**
```
Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
Output: 14

Explanation:
- Item A costs $2, Item B costs $5
- Offer 1: 3A + 0B for $5
- Offer 2: 1A + 2B for $10
- Optimal: Use Offer 2 ($10 for 1A + 2B) + buy 2A individually ($4)
- Total: $10 + $4 = $14
```

**Example 2:**
```
Input: price = [2,3,4], special = [[1,1,0,4],[2,2,1,9]], needs = [1,2,1]
Output: 11

Explanation:
- Item A: $2, Item B: $3, Item C: $4
- Offer 1: 1A + 1B + 0C for $4
- Offer 2: 2A + 2B + 1C for $9
- Optimal: Use Offer 1 ($4 for 1A + 1B) + buy 1B + 1C individually ($7)
- Total: $4 + $7 = $11
```

### Constraints
- `n == price.length == needs.length`
- `1 <= n <= 6`
- `0 <= price[i], needs[i] <= 10`
- `1 <= special.length <= 100`
- `special[i].length == n + 1`
- `0 <= special[i][j] <= 50`

## Observations

### 1. **Filter Useless Offers**
Not all special offers are actually beneficial. An offer is only worth considering if it costs less than buying the items individually.

```python
original_price = sum(offer[i] * price[i] for i in range(n))
if original_price > offer[-1]:  # Offer is beneficial
    filtered_offers.append(offer)
```

### 2. **State Space is Small**
- Maximum 6 items (`n <= 6`)
- Maximum 10 of each item (`needs[i] <= 10`)
- This makes the total state space manageable: at most 11^6 ≈ 1.7M states

### 3. **Optimal Substructure**
The problem exhibits optimal substructure:
- If we apply an offer, the remaining problem is the same but with reduced needs
- The optimal solution for the original needs can be constructed from optimal solutions of sub-problems

### 4. **Overlapping Sub-problems**
Different sequences of offers can lead to the same remaining needs state, which means we'll solve the same sub-problems multiple times → **Memoization** is beneficial.

### 5. **Greedy Doesn't Work**
We can't simply pick the "best" offer repeatedly because:
- The best offer for the full needs might not be optimal for the final solution
- We need to explore different combinations

## Solution

### Approach: Dynamic Programming with Memoization

**Algorithm:**

1. **Filter Offers**: Keep only offers that provide actual savings
2. **Define State**: Current needs tuple `(need[0], need[1], ..., need[n-1])`
3. **Base Case**: If we can't use any offers (or none improve the cost), buy items individually
4. **Recursive Case**: Try each applicable offer and take the minimum cost
5. **Memoization**: Cache results for each state to avoid recomputation

### Step-by-Step Walkthrough

```
State: (3, 2) - Need 3A and 2B
├─ Option 1: Buy all individually → Cost: 3*2 + 2*5 = 16
├─ Option 2: Use Offer 1 [3,0,5]
│  ├─ New state: (0, 2)
│  └─ Cost: 5 + dfs((0, 2))
│      └─ (0, 2): Buy individually → 0*2 + 2*5 = 10
│      └─ Total: 5 + 10 = 15
└─ Option 3: Use Offer 2 [1,2,10]
   ├─ New state: (2, 0)
   └─ Cost: 10 + dfs((2, 0))
       └─ (2, 0): Buy individually → 2*2 + 0*5 = 4
       └─ Total: 10 + 4 = 14 ✓ BEST
```

### Code Implementation

```python
class Solution:
    def shoppingOffers(self, price: List[int], special: List[List[int]], needs: List[int]) -> int:
        n = len(price)
        
        # Step 1: Filter offers that provide actual savings
        filtered_offers = []
        for offer in special:
            original_price = sum(offer[i] * price[i] for i in range(n))
            if original_price > offer[-1]:  # Offer is cheaper
                filtered_offers.append(offer)
        
        # Step 2: Memoization cache
        memo = {}
        
        # Step 3: DFS with memoization
        def dfs(state: tuple) -> int:
            # Check cache
            if state in memo:
                return memo[state]
            
            # Base case: cost of buying all items individually
            base_cost = sum(state[i] * price[i] for i in range(n))
            best_price = base_cost
            
            # Try each filtered offer
            for offer in filtered_offers:
                # Check if offer is applicable (won't exceed needs)
                state_with_offer = []
                for i in range(n):
                    if offer[i] > state[i]:  # Offer requires more than we need
                        state_with_offer = None
                        break
                    state_with_offer.append(state[i] - offer[i])
                
                # If offer is valid, calculate total cost
                if state_with_offer is not None:
                    best_price = min(best_price, offer[-1] + dfs(tuple(state_with_offer)))
            
            # Cache and return
            memo[state] = best_price
            return best_price
        
        return dfs(tuple(needs))
```

### Complexity Analysis

**Time Complexity: O(k × m × n)**
- **k**: Number of unique states (upper bound: `11^6` ≈ 1.7M, typically much less)
- **m**: Number of filtered offers (at most 100)
- **n**: Number of items (at most 6)
- For each state, we try each offer and check `n` items

**Space Complexity: O(k × n)**
- **Memoization**: O(k) states, each storing a tuple of size n
- **Recursion stack**: O(k) in worst case
- **Filtered offers**: O(m × n)

### Edge Cases

1. **No beneficial offers**: All offers cost the same or more than buying individually → Buy everything individually
2. **Empty needs**: `needs = [0, 0, ..., 0]` → Result: 0
3. **Offer contains 0 items**: Filtered out during preprocessing (not beneficial)
4. **Can use same offer multiple times**: Algorithm handles this by recursively exploring
5. **Single item**: `n = 1` → Still works correctly

### Key Insights

1. **Pruning**: Filtering offers before DFS saves significant computation
2. **State representation**: Using tuples (immutable) allows efficient hashing for memoization
3. **Early termination**: If we find a state in memo, we immediately return (no redundant work)
4. **Optimal substructure**: Best solution for state S = min(buy individually, best offer + best solution for remaining needs)

# Tags

Dynamic Programming, Memoization, Recursion, Optimization, State Space Search

