## Problem

https://leetcode.com/problems/divisor-game/description/

```
Alice and Bob take turns playing a game, with Alice starting first.

Initially, there is a number n on the chalkboard. On each player's turn, that player makes a move consisting of:

Choosing any integer x with 0 < x < n and n % x == 0.
Replacing the number n on the chalkboard with n - x.
Also, if a player cannot make a move, they lose the game.

Return true if and only if Alice wins the game, assuming both players play optimally.

Example 1:

Input: n = 2
Output: true
Explanation: Alice chooses 1, and Bob has no more moves.

Example 2:

Input: n = 3
Output: false
Explanation: Alice chooses 1, Bob chooses 1, and Alice has no more moves.

Constraints:

1 <= n <= 1000
```

## Observations

1. **Game Theory Insight**: This is a classic game theory problem where we need to determine the winner under optimal play.

2. **Key Pattern Discovery**: 
   - If Alice starts with an even number `n`, she can always choose `x = 1` (since 1 divides any number), leaving Bob with an odd number `n-1`.
   - If Alice starts with an odd number `n`, any divisor `x` of `n` must also be odd (since odd numbers only have odd divisors), so `n - x` (odd - odd) becomes even, giving Bob an even number.

3. **Winning Strategy**:
   - **Even numbers are winning positions**: The player can always force their opponent into an odd number.
   - **Odd numbers are losing positions**: The player is forced to give their opponent an even number.

4. **Mathematical Proof**:
   - Base cases: n=1 (Alice loses), n=2 (Alice wins by choosing x=1)
   - For any even n > 2: Alice chooses x=1, Bob gets odd n-1, Alice maintains control
   - For any odd n > 1: All divisors are odd, so Alice must give Bob an even number

## Solution

- The solution uses bitwise AND (`n & 1`) to check if n is odd
- `n & 1` returns 1 if n is odd, 0 if n is even
- `not (n & 1)` returns True if n is even, False if n is odd
- **Alice wins if and only if n is even**

**Time Complexity**: O(1) - constant time bit operation
**Space Complexity**: O(1) - no extra space needed

This elegant one-liner captures the mathematical essence: in optimal play, the parity (even/odd nature) of the starting number completely determines the winner.

# Tags
Game Theory, Math, Bit Manipulation, Dynamic Programming

