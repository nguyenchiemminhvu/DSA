## Problem

https://leetcode.com/problems/accounts-merge/

```
Given a list of accounts where each element accounts[i] is a list of strings, where the
first element accounts[i][0] is a name, and the rest of the elements are emails representing
emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person
if there is some common email to both accounts. Note that even if two accounts have the same
name, they may belong to different people as people could have the same name. A person can
have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of
each account is the name, and the rest of the elements are emails in sorted order. The accounts
themselves can be returned in any order.

Example 1:
  Input:  accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],
                      ["John","johnsmith@mail.com","john00@mail.com"],
                      ["Mary","mary@mail.com"],
                      ["John","johnnybravo@mail.com"]]
  Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],
           ["Mary","mary@mail.com"],
           ["John","johnnybravo@mail.com"]]
  Explanation: The first and second John's are the same person as they share
               "johnsmith@mail.com". The third John and Mary share no emails with anyone.

Example 2:
  Input:  accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],
                      ["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
                      ["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
                      ["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
                      ["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
  Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],
           ["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"], ...]

Constraints:
  - 1 <= accounts.length <= 1000
  - 2 <= accounts[i].length <= 10
  - 1 <= accounts[i][j].length <= 30
  - accounts[i][0] consists of English letters.
  - accounts[i][j] (for j > 0) is a valid email.
```

---

## Observations

1. **Email as identity, not name**: Two accounts belong to the same person only when they
   share at least one email address. The name alone is not sufficient — multiple people can
   have the same name, so we must track connectivity through emails.

2. **Transitive merging**: Merging is transitive. If account A shares an email with B, and
   B shares an email with C, then A, B, and C all belong to the same person, even if A and C
   share no direct email. This is a classic connectivity problem.

3. **This is a graph/grouping problem**: Think of each email as a node. Each account adds
   edges between all the emails it lists (they're all connected to the same owner). The task
   is to find all connected components and collect their nodes (emails) together.

4. **Union-Find is a natural fit**: Because we need to repeatedly merge groups and query
   membership, the Disjoint Set Union (DSU / Union-Find) data structure handles both
   operations efficiently in near O(1) amortized time with path compression and union by rank.

5. **Email → index mapping**: DSU operates on integers. We assign each unique email a numeric
   index so we can apply union/find operations. We also keep a `mail_to_name` map so that
   after grouping we know which name to attach to each group.

6. **Grouping by root**: After all unions are performed, emails that belong to the same person
   all share the same root in the DSU. We group emails by their root index, sort each group,
   and prepend the owner's name.

---

## Approach — Union-Find (Disjoint Set Union)

### Step 1 — Assign each unique email a numeric ID

Collect all unique emails across all accounts and map each one to a unique integer index.
Also build a `mail_to_name` dictionary so we can recover the owner's name later.

```
all_mails  = { "johnsmith@mail.com": 0, "john_newyork@mail.com": 1,
               "john00@mail.com": 2,    "mary@mail.com": 3,
               "johnnybravo@mail.com": 4 }

mail_to_name = { "johnsmith@mail.com": "John", ... }
```

### Step 2 — Union all emails inside the same account

For each account, take the first email as the "anchor" and union every other email in
that account with the anchor. This connects all emails that definitely belong to the same
person (same account entry).

```
Account ["John", "johnsmith@mail.com", "john_newyork@mail.com"]
  → union(0, 0)   # johnsmith with itself (no-op)
  → union(0, 1)   # johnsmith ↔ john_newyork

Account ["John", "johnsmith@mail.com", "john00@mail.com"]
  → union(0, 0)   # no-op
  → union(0, 2)   # johnsmith ↔ john00
  # Now 0, 1, 2 are all in the same component
```

### Step 3 — Group emails by their DSU root

Iterate over every email, find its root via `find()`, and collect all emails that share
the same root into the same group. The name for the group is taken from `mail_to_name`.

```
root of index 0 → 0   (johnsmith, john_newyork, john00 all resolve to root 0)
root of index 3 → 3   (mary stands alone)
root of index 4 → 4   (johnnybravo stands alone)

groups = {
  0: ["John", {"johnsmith@mail.com", "john_newyork@mail.com", "john00@mail.com"}],
  3: ["Mary", {"mary@mail.com"}],
  4: ["John", {"johnnybravo@mail.com"}],
}
```

### Step 4 — Build the result

For each group, sort the email set and prepend the name:

```
["John", "john00@mail.com", "john_newyork@mail.com", "johnsmith@mail.com"]
["Mary", "mary@mail.com"]
["John", "johnnybravo@mail.com"]
```

---

### DSU Implementation Details

- **Path Compression** in `find()`: When traversing up to the root, set each visited node's
  parent directly to the root. This flattens the tree and speeds up future lookups.

  ```python
  def find(self, i):
      if self.parent[i] != i:
          self.parent[i] = self.find(self.parent[i])  # path compression
      return self.parent[i]
  ```

- **Union by Rank** in `union()`: Always attach the shorter tree under the taller one.
  This keeps the tree balanced and avoids degenerate linear chains.

  ```python
  def union(self, i, j):
      root_i, root_j = self.find(i), self.find(j)
      if root_i == root_j:
          return False
      if self.rank[root_i] >= self.rank[root_j]:
          self.parent[root_j] = root_i
          if self.rank[root_i] == self.rank[root_j]:
              self.rank[root_i] += 1
      else:
          self.parent[root_i] = root_j
      return True
  ```

---

### Complexity

| | |
|---|---|
| **Time** | $O(N \cdot E \cdot \alpha(N \cdot E) + N \cdot E \cdot \log(E))$ where $N$ = number of accounts, $E$ = max emails per account. The $\alpha$ factor comes from DSU operations (near constant); the $\log$ factor comes from sorting the final email lists. |
| **Space** | $O(N \cdot E)$ for the email-to-index map, DSU arrays, and grouping dictionary. |

---

## Tags

`Union-Find` `Disjoint Set Union` `Hash Map` `Graph` `String` `Sorting`
