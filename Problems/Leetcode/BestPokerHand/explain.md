## Problem

https://leetcode.com/problems/best-poker-hand/description/

```
You are given an integer array ranks and a character array suits. You have 5 cards where the ith card has a rank of ranks[i] and a suit of suits[i].

The following are the types of poker hands you can make from best to worst:

"Flush": Five cards of the same suit.
"Three of a Kind": Three cards of the same rank.
"Pair": Two cards of the same rank.
"High Card": Any single card.
Return a string representing the best type of poker hand you can make with the given cards.

Note that the return values are case-sensitive.

Example 1:

Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
Output: "Flush"
Explanation: The hand with all the cards consists of 5 cards with the same suit, so we have a "Flush".

Example 2:

Input: ranks = [4,4,2,4,4], suits = ["d","a","a","b","c"]
Output: "Three of a Kind"
Explanation: The hand with the first, second, and fourth card consists of 3 cards with the same rank, so we have a "Three of a Kind".
Note that we could also make a "Pair" hand but "Three of a Kind" is a better hand.
Also note that other cards could be used to make the "Three of a Kind" hand.

Example 3:

Input: ranks = [10,10,2,12,9], suits = ["a","b","c","a","d"]
Output: "Pair"
Explanation: The hand with the first and second card consists of 2 cards with the same rank, so we have a "Pair".
Note that we cannot make a "Flush" or a "Three of a Kind".

Constraints:

ranks.length == suits.length == 5
1 <= ranks[i] <= 13
'a' <= suits[i] <= 'd'
No two cards have the same rank and suit.
```

## Observations

1. **Priority Order**: The poker hands have a clear hierarchy from best to worst:
   - Flush (all same suit)
   - Three of a Kind (3 cards same rank)
   - Pair (2 cards same rank)
   - High Card (no matching ranks or suits)

2. **Flush Check is First**: Since flush is the best possible hand with these rules, we check for it first by examining if all suits are the same.

3. **Frequency Analysis**: For non-flush hands, we only need to count the frequency of ranks to determine the best hand type.

4. **Greedy Approach**: We can determine the best hand by checking conditions in order of priority - once we find a valid hand type, we return it immediately.

5. **Counter Usage**: Python's Counter from collections makes frequency counting elegant and readable.

## Solution

**Algorithm:**

1. **Check for Flush**: Convert suits to a set and check if length is 1
   - If all suits are the same → return "Flush"

2. **Count Rank Frequencies**: Use Counter to count occurrences of each rank

3. **Find Maximum Frequency**: Sort the frequency values in descending order
   - If max frequency ≥ 3 → return "Three of a Kind"
   - If max frequency ≥ 2 → return "Pair"
   - Otherwise → return "High Card"

**Key Insights:**

- **Time Complexity**: O(1) - We always process exactly 5 cards
- **Space Complexity**: O(1) - Maximum 5 suits and 5 ranks to store
- **Elegant Logic**: The solution leverages Python's built-in data structures for clean, readable code
- **Order Matters**: We check conditions from best to worst hand type

**Why This Works:**

The algorithm correctly implements the poker hand hierarchy by checking the most valuable hands first. Since we're guaranteed exactly 5 cards, we can use simple frequency analysis to determine the best possible hand without complex logic.

# Tags

**Data Structures:** Hash Map (Counter), Set  
**Algorithms:** Frequency Counting, Greedy  
**Concepts:** Game Logic, Classification  
**Difficulty:** Easy  
**Time:** O(1), **Space:** O(1)

