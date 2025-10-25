## Problem

https://leetcode.com/problems/sum-game/

```
Alice and Bob take turns playing a game, with Alice starting first.

You are given a string num of even length consisting of digits and '?' characters. On each turn, a player will do the following if there is still at least one '?' in num:

Choose an index i where num[i] == '?'.
Replace num[i] with any digit between '0' and '9'.
The game ends when there are no more '?' characters in num.

For Bob to win, the sum of the digits in the first half of num must be equal to the sum of the digits in the second half. For Alice to win, the sums must not be equal.

For example, if the game ended with num = "243801", then Bob wins because 2+4+3 = 8+0+1. If the game ended with num = "243803", then Alice wins because 2+4+3 != 8+0+3.
Assuming Alice and Bob play optimally, return true if Alice will win and false if Bob will win.

Example 1:

Input: num = "5023"
Output: false
Explanation: There are no moves to be made.
The sum of the first half is equal to the sum of the second half: 5 + 0 = 2 + 3.

Example 2:

Input: num = "25??"
Output: true
Explanation: Alice can replace one of the '?'s with '9' and it will be impossible for Bob to make the sums equal.

Example 3:

Input: num = "?3295???"
Output: false
Explanation: It can be proven that Bob will always win. One possible outcome is:
- Alice replaces the first '?' with '9'. num = "93295???".
- Bob replaces one of the '?' in the right half with '9'. num = "932959??".
- Alice replaces one of the '?' in the right half with '2'. num = "9329592?".
- Bob replaces the last '?' in the right half with '7'. num = "93295927".
Bob wins because 9 + 3 + 2 + 9 = 5 + 9 + 2 + 7.

Constraints:

2 <= num.length <= 105
num.length is even.
num consists of only digits and '?'.
```

## Observations

1. **Game Setup**: Alice and Bob take turns replacing '?' characters with digits 0-9. Alice goes first and wants the left half sum ≠ right half sum (to win). Bob wants left half sum = right half sum (to win).

2. **Key Insight**: Since Alice goes first, she gets to make moves on odd-numbered turns (1st, 3rd, 5th, ...) and Bob makes moves on even-numbered turns (2nd, 4th, 6th, ...).

3. **Critical Cases**:
   - If there are no '?' characters: The outcome is determined immediately
   - If total '?' count is odd: Alice gets the last move, giving her an advantage
   - If total '?' count is even: Both players get equal number of moves

4. **Optimal Strategy**: 
   - Alice wants to maximize the difference between left and right sums
   - Bob wants to minimize this difference (ideally to 0)
   - Alice will place 9's where they help her cause, 0's where they hurt Bob's cause
   - Bob will place 9's to counter Alice's strategy, 0's to minimize damage

5. **Mathematical Analysis**: The game outcome can be determined by analyzing the current state and the number of remaining moves for each player.

## Solution

The solution uses game theory and mathematical analysis to determine the winner without simulating the actual game:

**Algorithm**:
1. **Parse the string**: Count the sum of known digits and number of '?' in each half
2. **Handle base cases**:
   - No '?': Return whether sums are different
   - Odd total '?': Alice wins (gets last move)
   - Equal '?' in both halves: Return whether current sums are different
3. **Calculate the critical condition**: `2 * (left - right) != 9 * (var_right - var_left)`

**Key Mathematical Insight**:
- If Alice has more moves in one half, she'll maximize that half with 9's
- If Bob has more moves in one half, he'll try to balance by adding appropriate values
- The factor of 9 comes from the maximum value Alice can add (9) vs minimum (0)
- The factor of 2 accounts for the fact that each '?' can swing the difference by up to 9

**Time Complexity**: O(n) - single pass through the string
**Space Complexity**: O(1) - only using constant extra space

**Why this works**:
- When `var_left == var_right`: Both players get equal moves in each half, so current difference determines winner
- When `var_left != var_right`: The player with more moves in the advantageous half will win unless the mathematical condition balances out
- The condition `2 * (left - right) != 9 * (var_right - var_left)` captures when Bob can exactly balance the sums despite Alice's optimal play

## Tags

game theory, greedy, math