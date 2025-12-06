## Problem

https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/description/

**Description:**

You are entering a competition, and are given two positive integers `initialEnergy` and `initialExperience` denoting your initial energy and initial experience respectively.

You are also given two 0-indexed integer arrays `energy` and `experience`, both of length `n`.

You will face `n` opponents in order. The energy and experience of the ith opponent is denoted by `energy[i]` and `experience[i]` respectively. When you face an opponent, you need to have both **strictly greater** experience and energy to defeat them and move to the next opponent if available.

Defeating the ith opponent increases your experience by `experience[i]`, but decreases your energy by `energy[i]`.

Before starting the competition, you can train for some number of hours. After each hour of training, you can either choose to increase your initial experience by one, or increase your initial energy by one.

Return the minimum number of training hours required to defeat all `n` opponents.

**Example 1:**
```
Input: initialEnergy = 5, initialExperience = 3, energy = [1,4,3,2], experience = [2,6,3,1]
Output: 8
Explanation: You can increase your energy to 11 after 6 hours of training, and your experience to 5 after 2 hours of training.
You face the opponents in the following order:
- You have more energy and experience than the 0th opponent so you win.
  Your energy becomes 11 - 1 = 10, and your experience becomes 5 + 2 = 7.
- You have more energy and experience than the 1st opponent so you win.
  Your energy becomes 10 - 4 = 6, and your experience becomes 7 + 6 = 13.
- You have more energy and experience than the 2nd opponent so you win.
  Your energy becomes 6 - 3 = 3, and your experience becomes 13 + 3 = 16.
- You have more energy and experience than the 3rd opponent so you win.
  Your energy becomes 3 - 2 = 1, and your experience becomes 16 + 1 = 17.
You did a total of 6 + 2 = 8 hours of training before the competition, so we return 8.
```

**Example 2:**
```
Input: initialEnergy = 2, initialExperience = 4, energy = [1], experience = [3]
Output: 0
Explanation: You do not need any additional energy or experience to win the competition, so we return 0.
```

**Constraints:**
- `n == energy.length == experience.length`
- `1 <= n <= 100`
- `1 <= initialEnergy, initialExperience, energy[i], experience[i] <= 100`

## Observations

1. **Strict Inequality Requirement**: To defeat an opponent, we must have **strictly greater** energy and experience than them (not equal).

2. **Energy vs Experience Mechanics**:
   - **Energy**: Decreases after each battle (consumed resource)
   - **Experience**: Increases after each battle (accumulated resource)

3. **Energy Insight**: 
   - Since energy only decreases, we need enough initial energy to cover all battles
   - For energy, we need: `initialEnergy > sum(energy) + max(energy[i])` for the worst case
   - More precisely: `initialEnergy > energy[0]`, then `initialEnergy - energy[0] > energy[1]`, etc.
   - Simplified: We need `initialEnergy > sum(energy)` to ensure we have enough throughout

4. **Experience Insight**:
   - Experience accumulates, so it gets easier as we progress
   - However, we must have strictly greater experience than each opponent when we face them
   - We need to simulate the battles to know exactly how much initial experience is needed

5. **Greedy Simulation**:
   - We can simulate the competition and add training hours "on-the-fly" whenever we don't meet requirements
   - This gives us the minimum training needed

## Solution

### Approach: Greedy Simulation

**Strategy:**
1. Simulate each battle in order
2. Before each battle, check if we have strictly greater energy AND experience
3. If not, calculate the minimum training hours needed to meet the requirement
4. Update our current energy (decrease) and experience (increase) after winning
5. Sum up all training hours needed

**Key Points:**
- **Energy Check**: If `cur_energy <= op_energy`, we need `(op_energy - cur_energy + 1)` training hours
  - The `+1` ensures we have **strictly greater** energy
  - After training, set `cur_energy = op_energy + 1`
- **Experience Check**: If `cur_exp <= op_exp`, we need `(op_exp - cur_exp + 1)` training hours
  - The `+1` ensures we have **strictly greater** experience
  - After training, set `cur_exp = op_exp + 1`
- After checks, update resources:
  - `cur_energy -= op_energy` (energy consumed)
  - `cur_exp += op_exp` (experience gained)

**Time Complexity**: $O(n)$ where n is the number of opponents
**Space Complexity**: $O(1)$ - only using constant extra space

**Example Walkthrough (Example 1):**
- Initial: `energy=5, exp=3`, Opponents: `energy=[1,4,3,2], exp=[2,6,3,1]`

**Opponent 0**: `energy=1, exp=2`
- Energy check: `5 > 1` ✓
- Experience check: `3 > 2` ✓
- After battle: `energy=4, exp=5`

**Opponent 1**: `energy=4, exp=6`
- Energy check: `4 <= 4` ✗ → need `4 - 4 + 1 = 1` training, `energy=5`
- Experience check: `5 <= 6` ✗ → need `6 - 5 + 1 = 2` training, `exp=7`
- After battle: `energy=1, exp=13`

**Opponent 2**: `energy=3, exp=3`
- Energy check: `1 <= 3` ✗ → need `3 - 1 + 1 = 3` training, `energy=4`
- Experience check: `13 > 3` ✓
- After battle: `energy=1, exp=16`

**Opponent 3**: `energy=2, exp=1`
- Energy check: `1 <= 2` ✗ → need `2 - 1 + 1 = 2` training, `energy=3`
- Experience check: `16 > 1` ✓
- After battle: `energy=1, exp=17`

Total training: `1 + 2 + 3 + 2 = 8` hours ✓

# Tags
#greedy #simulation #array

