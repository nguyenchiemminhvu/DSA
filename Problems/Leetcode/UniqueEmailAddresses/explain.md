## Problem

https://leetcode.com/problems/unique-email-addresses/description/

```
Every valid email consists of a local name and a domain name, separated by the '@' sign. Besides lowercase letters, the email may contain one or more '.' or '+'.

For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com" is the domain name.
If you add periods '.' between some characters in the local name part of an email address, mail sent there will be forwarded to the same address without dots in the local name. Note that this rule does not apply to domain names.

For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same email address.
If you add a plus '+' in the local name, everything after the first plus sign will be ignored. This allows certain emails to be filtered. Note that this rule does not apply to domain names.

For example, "m.y+name@email.com" will be forwarded to "my@email.com".
It is possible to use both of these rules at the same time.

Given an array of strings emails where we send one email to each emails[i], return the number of different addresses that actually receive mails.

Example 1:

Input: emails = ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
Output: 2
Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails.

Example 2:

Input: emails = ["a@leetcode.com","b@leetcode.com","c@leetcode.com"]
Output: 3

Constraints:

1 <= emails.length <= 100
1 <= emails[i].length <= 100
emails[i] consist of lowercase English letters, '+', '.' and '@'.
Each emails[i] contains exactly one '@' character.
All local and domain names are non-empty.
Local names do not start with a '+' character.
Domain names end with the ".com" suffix.
Domain names must contain at least one character before ".com" suffix.
```

## Observations

1. **Email Structure**: Each email has two parts - local name (before @) and domain name (after @)

2. **Local Name Rules**:
   - All dots (.) are ignored and removed
   - Everything after the first plus (+) sign is ignored
   - These rules apply only to the local name, not the domain

3. **Domain Name Rules**:
   - Domain names are used as-is, no transformations applied
   - Multiple emails can have the same domain but different local names

4. **Uniqueness**: Two emails are considered the same if they have the same normalized local name AND the same domain

5. **Data Structure Choice**: Using a dictionary with domain as key and set of normalized local names as value efficiently groups emails by domain and automatically handles duplicates

## Solution

**Approach**: Normalize each email and group by domain, then count unique local names per domain.

**Algorithm**:
1. **Parse Email**: Split each email at '@' to get local name and domain
2. **Normalize Local Name**:
   - Split at first '+' and take only the part before it (removes everything after +)
   - Remove all dots (.) from the remaining part
3. **Group by Domain**: Use a dictionary where:
   - Key: domain name
   - Value: set of normalized local names for that domain
4. **Count Unique Emails**: Sum the size of each set across all domains

**Example Walkthrough**:
- `"test.email+alex@leetcode.com"` → normalized: `"testemail@leetcode.com"`
- `"test.e.mail+bob.cathy@leetcode.com"` → normalized: `"testemail@leetcode.com"` (same as above)
- `"testemail+david@lee.tcode.com"` → normalized: `"testemail@lee.tcode.com"`

Result: 2 unique emails

**Time Complexity**: O(n × m) where n is number of emails and m is average email length
**Space Complexity**: O(n × m) for storing normalized emails in the dictionary

**Key Insights**:
- The solution efficiently handles both email normalization rules in one pass
- Using sets automatically eliminates duplicates within each domain
- Grouping by domain first, then counting unique local names is more intuitive than using a single global set

# Tags
`string-manipulation` `hash-table` `set` `email-parsing` `normalization`

