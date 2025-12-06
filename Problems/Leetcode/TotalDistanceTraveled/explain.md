## Problem

https://leetcode.com/problems/total-distance-traveled/description/

```
A truck has two fuel tanks. You are given two integers, mainTank representing the fuel present in the main tank in liters and additionalTank representing the fuel present in the additional tank in liters.

The truck has a mileage of 10 km per liter. Whenever 5 liters of fuel get used up in the main tank, if the additional tank has at least 1 liter of fuel, 1 liter of fuel will be transferred from the additional tank to the main tank.

Return the maximum distance which can be traveled.

Note: Injection from the additional tank is not continuous. It happens suddenly and immediately for every 5 liters consumed.

Example 1:
Input: mainTank = 5, additionalTank = 10
Output: 60
Explanation: 
After spending 5 litre of fuel, fuel remaining is (5 - 5 + 1) = 1 litre and distance traveled is 50km.
After spending another 1 litre of fuel, no fuel gets injected in the main tank and the main tank becomes empty.
Total distance traveled is 60km.

Example 2:
Input: mainTank = 1, additionalTank = 2
Output: 10
Explanation: 
After spending 1 litre of fuel, the main tank becomes empty.
Total distance traveled is 10km.

Constraints:
- 1 <= mainTank, additionalTank <= 100
```

## Observations

1. **Fuel consumption pattern**: The truck travels 10 km per liter of fuel
2. **Transfer trigger**: Every time the main tank consumes exactly 5 liters, we can transfer 1 liter from the additional tank (if available)
3. **Transfer constraint**: We can only transfer 1 liter at a time, and only if the additional tank has fuel
4. **Process is discrete**: The transfer happens instantly after every 5 liters consumed, not gradually

Key insights:
- We need to simulate the fuel consumption process
- Track how many complete cycles of 5 liters we can consume
- After each cycle, check if we can refill 1 liter from the additional tank
- Continue until the main tank has less than 5 liters
- Add the remaining fuel distance at the end

## Solution

### Approach: Simulation

The solution simulates the fuel consumption process step by step:

1. **Main loop**: While the main tank has at least 5 liters:
   - Consume 5 liters from the main tank
   - If the additional tank has fuel, transfer 1 liter to the main tank
   - Add 50 km to the total distance (5 liters × 10 km/liter)

2. **Final calculation**: After the loop, add the distance from remaining fuel in the main tank

### Example Walkthrough

**Example 1**: `mainTank = 5, additionalTank = 10`

| Step | Main Tank | Additional Tank | Distance | Action |
|------|-----------|----------------|----------|---------|
| Start | 5 | 10 | 0 | - |
| 1 | 5 - 5 = 0 | 10 | 50 | Consume 5L |
| 1a | 0 + 1 = 1 | 10 - 1 = 9 | 50 | Transfer 1L |
| 2 | 1 | 9 | 50 + 10 = 60 | Consume remaining 1L (no transfer possible) |

**Example 2**: `mainTank = 1, additionalTank = 2`

| Step | Main Tank | Additional Tank | Distance | Action |
|------|-----------|----------------|----------|---------|
| Start | 1 | 2 | 0 | - |
| End | 1 | 2 | 10 | Main tank < 5, consume remaining 1L |

### Complexity Analysis

- **Time Complexity**: O(mainTank / 5)
  - In the worst case, we iterate mainTank / 5 times
  - Each iteration is O(1)
  - The number of iterations depends on how many times we can consume 5 liters
  
- **Space Complexity**: O(1)
  - Only using a constant amount of extra space for variables

### Alternative Approach: Mathematical Formula

We could optimize this using a mathematical approach:
- Calculate how many complete transfers can happen: `min(mainTank // 5, additionalTank)`
- Total fuel used = `mainTank + transfers`
- Distance = `total_fuel × 10`

However, the simulation approach is clearer and easier to understand, and with the constraint that both tanks are ≤ 100, the performance difference is negligible.

# Tags

`simulation` `math` `greedy`

