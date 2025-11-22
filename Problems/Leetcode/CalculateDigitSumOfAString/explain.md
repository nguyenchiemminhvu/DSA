## Problem

https://leetcode.com/problems/calculate-digit-sum-of-a-string/

```
You are given a string s consisting of digits and an integer k.

A round can be completed if the length of s is greater than k. In one round, do the following:

Divide s into consecutive groups of size k such that the first k characters are in the first group, the next k characters are in the second group, and so on. Note that the size of the last group can be smaller than k.
Replace each group of s with a string representing the sum of all its digits. For example, "346" is replaced with "13" because 3 + 4 + 6 = 13.
Merge consecutive groups together to form a new string. If the length of the string is greater than k, repeat from step 1.
Return s after all rounds have been completed.

Example 1:

Input: s = "11111222223", k = 3
Output: "135"
Explanation: 
- For the first round, we divide s into groups of size 3: "111", "112", "222", and "23".
  ​​​​​Then we calculate the digit sum of each group: 1 + 1 + 1 = 3, 1 + 1 + 2 = 4, 2 + 2 + 2 = 6, and 2 + 3 = 5. 
  So, s becomes "3" + "4" + "6" + "5" = "3465" after the first round.
- For the second round, we divide s into "346" and "5".
  Then we calculate the digit sum of each group: 3 + 4 + 6 = 13, 5 = 5. 
  So, s becomes "13" + "5" = "135" after second round. 
Now, s.length <= k, so we return "135" as the answer.

Example 2:

Input: s = "00000000", k = 3
Output: "000"
Explanation: 
We divide s into "000", "000", and "00".
Then we calculate the digit sum of each group: 0 + 0 + 0 = 0, 0 + 0 + 0 = 0, and 0 + 0 = 0. 
s becomes "0" + "0" + "0" = "000", whose length is equal to k, so we return "000".

Constraints:

1 <= s.length <= 100
2 <= k <= 100
s consists of digits only.
```

## Observations

1. **Problem Structure**: We need to repeatedly process a string by dividing it into chunks of size `k` and replacing each chunk with the sum of its digits.

2. **Termination Condition**: The process continues until the string length becomes ≤ k.

3. **Chunking Strategy**: We divide the string into consecutive groups of size k, where the last group can be smaller than k if there aren't enough remaining characters.

4. **Sum Calculation**: For each chunk, we sum all the digit characters and replace the entire chunk with this sum as a string.

5. **Edge Cases**: 
   - All zeros result in "000..." pattern
   - Single digits remain unchanged if k ≥ string length initially

## Solution

1. **Main Loop**: Continue processing while string length > k
2. **Chunking**: Use list comprehension `[s[i:i+k] for i in range(0, len(s), k)]` to create chunks of size k
3. **Sum Calculation**: For each chunk, iterate through characters, convert to int, and sum them up
4. **Replacement**: Convert the sum back to string and replace the original chunk
5. **Reconstruction**: Join all processed chunks to form the new string
6. **Return**: When length ≤ k, return the final string

**Time Complexity**: O(n) where n is the original string length. In each round, we process all characters once, and the string length decreases significantly each round.

**Space Complexity**: O(n) for storing the chunks array and the new string in each iteration.

# Tags

