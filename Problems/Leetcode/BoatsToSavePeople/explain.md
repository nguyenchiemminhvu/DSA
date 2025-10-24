## Problem

https://leetcode.com/problems/boats-to-save-people/

```
You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.

Example 1:

Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)

Example 2:

Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)

Example 3:

Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)

Constraints:

1 <= people.length <= 5 * 104
1 <= people[i] <= limit <= 3 * 104
```

## Observations

1. **Key Constraints:**
   - Each boat can carry **at most 2 people**
   - Total weight must not exceed `limit`
   - We want to minimize the number of boats

2. **Greedy Strategy:**
   - To minimize boats, we should try to pair people optimally
   - The heaviest person should be paired with the lightest person if possible
   - If the heaviest + lightest > limit, then the heaviest person must go alone

3. **Two Pointer Approach:**
   - Sort the array to enable efficient pairing
   - Use left pointer for lightest person, right pointer for heaviest person
   - Always move the right pointer (heaviest person always gets on a boat)
   - Only move left pointer if we can fit both people in the same boat

4. **Why This Works:**
   - If the heaviest person can't pair with the lightest, they can't pair with anyone
   - This greedy choice is optimal because we're always trying to maximize boat utilization

## Solution

1. **Sort the array** - O(n log n) to enable efficient pairing
2. **Initialize pointers** - `left` at start (lightest), `right` at end (heaviest)
3. **For each boat:**
   - Check if lightest + heaviest ≤ limit
   - If yes: both people get on the boat (move both pointers)
   - If no: only heaviest person gets on the boat (move right pointer only)
   - Increment boat count
4. **Continue until all people are rescued** (left > right)

**Time Complexity:** O(n log n) - dominated by sorting
**Space Complexity:** O(1) - only using constant extra space

**Example Walkthrough:**
```
people = [3,2,2,1], limit = 3
After sorting: [1,2,2,3]

left=0, right=3: people[0]+people[3] = 1+3 = 4 > 3
→ Only person with weight 3 gets on boat, right=2, boats=1

left=0, right=2: people[0]+people[2] = 1+2 = 3 ≤ 3  
→ Both people (weights 1,2) get on boat, left=1, right=1, boats=2

left=1, right=1: Same person, weight 2 ≤ 3
→ Person with weight 2 gets on boat, boats=3

Result: 3 boats
```

## Tags

array, greedy, two pointers, sorting