## Problem

https://leetcode.com/problems/2-keys-keyboard/description

You have a notepad with a single character 'A' displayed. You can perform two operations:
1. **Copy All**: Copy all characters currently on the screen to clipboard
2. **Paste**: Paste the characters from clipboard to the screen

Given an integer `n`, return the **minimum number of operations** required to have exactly `n` 'A' characters on the screen.

**Constraints:**
- 1 ≤ n ≤ 1000

**Examples:**

Example 1: n = 3
- Step 1: Copy All (screen: "A", clipboard: "A")
- Step 2: Paste (screen: "AA", clipboard: "A")
- Step 3: Paste (screen: "AAA", clipboard: "A")
- **Output: 3 operations**

Example 2: n = 1
- Already have 'A' on screen
- **Output: 0 operations**

## Observations

1. **State Space**: The problem requires tracking two dimensions:
   - `i`: Current number of 'A's on the screen
   - `l`: Current number of 'A's in the clipboard
   
2. **Operations Available**:
   - From state (i, l), if l = 0 (clipboard empty): must copy first, which costs 2 operations total (Copy All + Paste once) to reach (2i, i)
   - From state (i, l), if l > 0: can either Paste (cost 1) to reach (i+l, l), or Copy All then Paste (cost 2) to reach (2i, i)

3. **Optimal Strategy Pattern**:
   - We should generally try to build up the clipboard with multiples, then use those multiples to paste efficiently
   - Pure multiplication (copy + paste repeatedly) is not always optimal
   - We need to explore all valid transitions to find the minimum path

4. **Mathematical Insight**:
   - The answer is related to the sum of divisors of n
   - Each time we "multiply" from i to 2i, we add 2 to the operation count
   - When we transition between different "multipliers," we may need to adjust our strategy

5. **Memoization Efficiency**:
   - The state space (i, l) is bounded since both i and l ≤ n
   - Many states are pruned (i > n leads to infinity)
   - Memoization prevents recalculating the same state multiple times

## Solution

### Approach: Top-Down Dynamic Programming with Memoization

The solution uses recursive memoization where `F(i, l)` returns the minimum operations needed to reach `n` 'A's starting from state (i, l):
- `i`: current count of 'A's on screen
- `l`: current count of 'A's in clipboard

**State Transitions:**
```
F(i, l) = minimum of:
  - If l == 0: 2 + F(i + i, i)  [must copy all first]
  - If l > 0:
    - 1 + F(i + l, l)  [paste once]
    - 2 + F(i + i, i)  [copy all, then paste]
```

**Base Cases:**
- `F(n, l) = 0` for any l (reached target, no more operations needed)
- `F(i, l) = ∞` if i > n (overshot target, invalid state)

**Why This Works:**

1. **Starting from (1, 0)**: We begin with 1 'A' on screen and empty clipboard
2. **Forced Copy**: When clipboard is empty, we must copy all (cost 2: select all + paste once)
3. **Two Choices with Clipboard**: Once we have something in clipboard, we can either:
   - Keep pasting the same amount (incremental growth)
   - Copy all again and update clipboard (exponential growth with new base)
4. **Exploration**: By trying both options and taking the minimum, we find the optimal path

**Example Walkthrough (n = 6):**
```
F(1, 0) [1 A on screen, clipboard empty]
  → Must do: Copy All + Paste = 2 operations → F(2, 2)
     - Paste: 1 + F(3, 2) → eventually F(4, 2)
       - Paste: 1 + F(5, 2) → eventually F(6, 2) = 0 (but need 5 pastes total)
       - Copy All: 2 + F(4, 4) → F(6, 4)... (6 = 4 + 2? No, need F(8, 4) overshot)
       - Copy All: 2 + F(4, 4) → F(6, 4)? No, F(4, 4) → 1 + F(6, 4) = 0, so total 2+1 = 3 from F(4,4)
     
The optimal path is: Copy (1 A) → Paste (2 A) → Copy All (2 in clipboard) → Paste (4 A) → Copy All → Paste (6 A)
Operations: 1 (Copy) + 1 (Paste) + 1 (Copy) + 1 (Paste) + 1 (Copy) + 1 (Paste) = 6 operations? 
Let's count properly:
- Start: 1 A
- Copy All: 1 A on screen, 1 in clipboard
- Paste: 2 A
- Copy All: 2 in clipboard
- Paste: 4 A
- Copy All: 4 in clipboard
- Paste: 6 A

Total: 6 operations (3 copy + 3 paste)
```

**Time Complexity:** O(n²) - State space is roughly O(n²), each state computed once
**Space Complexity:** O(n²) - Memoization dictionary stores up to O(n²) states

### Alternative Bottom-Up DP (Commented Out)

The code also shows a bottom-up tabulation approach:
- Iterate i from n down to 1
- For each i, iterate l from 0 to n
- Fill dp[i][l] by combining results from dp[i+i][i] and dp[i+l][l]
- Start with base case dp[n][l] = 0 for all l
- Return dp[1][0]

# Tags
Dynamic Programming | Memoization | State Machine | Graph Search | Optimization

