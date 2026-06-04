## Problem

https://leetcode.com/problems/subdomain-visit-count/description/

A website domain like `"discuss.leetcode.com"` consists of multiple subdomains at different levels:
- Top level: `"com"`
- Second level: `"leetcode.com"`
- Third level: `"discuss.leetcode.com"`

Visiting a domain implicitly visits all of its parent domains as well.

A **count-paired domain** is a string in the format `"rep domain"` where `rep` is the number of times that domain was visited.

**Given** an array of count-paired domains `cpdomains`, **return** an array of count-paired domains representing the total visit count for every subdomain that appears.

**Example 1:**
```
Input:  ["9001 discuss.leetcode.com"]
Output: ["9001 discuss.leetcode.com", "9001 leetcode.com", "9001 com"]
```

**Example 2:**
```
Input:  ["900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"]
Output: ["901 mail.com", "50 yahoo.com", "900 google.mail.com", "5 wiki.org", "5 org", "1 intel.mail.com", "951 com"]
```

**Constraints:**
- `1 <= cpdomains.length <= 100`
- `1 <= cpdomains[i].length <= 100`
- Each entry follows the format `"repi d1i.d2i.d3i"` or `"repi d1i.d2i"`
- `repi` is an integer in `[1, 10^4]`
- Domain labels consist of lowercase English letters only

---

## Observations

1. **Each domain implicitly covers its parent domains.** For `"discuss.leetcode.com"` visited N times, both `"leetcode.com"` and `"com"` also receive N visits.

2. **Subdomains are suffixes of the full domain.** Every suffix obtained by stripping the leftmost label (up to a dot) is a valid subdomain we need to count.

3. **Counts must be accumulated.** Multiple input entries can contribute visits to the same subdomain (e.g., both `"google.mail.com"` and `"intel.mail.com"` contribute to `"mail.com"`).

4. **A hash map is the natural fit.** We need to map each unique subdomain string to a running total of visits — exactly what a dictionary provides in O(1) per lookup/update.

5. **Iterating subdomains from right to left** (bottom-up, starting from the top-level TLD) makes it easy to build each subdomain key incrementally by prepending the next label.

---

## Solution Explanation

```python
class Solution:
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:
        mp = defaultdict(int)
        for domain in cpdomains:
            count, sub_domains = domain.split()

            subs = sub_domains.split('.')
            subs.reverse()          # e.g. ["com", "leetcode", "discuss"]
            key = ''
            for s in subs:
                # Build subdomains from TLD outward:
                # iteration 1: key = "com"
                # iteration 2: key = "leetcode.com"
                # iteration 3: key = "discuss.leetcode.com"
                key = s if not key else (s + '.' + key)
                mp[key] += int(count)

        res = []
        for k, v in mp.items():
            res.append(str(v) + ' ' + k)
        return res
```

**Step-by-step walkthrough** for `"9001 discuss.leetcode.com"`:

| Iteration | `s`        | `key` built           | `mp` update                          |
|-----------|------------|-----------------------|--------------------------------------|
| 1         | `"com"`    | `"com"`               | `mp["com"] += 9001`                  |
| 2         | `"leetcode"` | `"leetcode.com"`    | `mp["leetcode.com"] += 9001`         |
| 3         | `"discuss"` | `"discuss.leetcode.com"` | `mp["discuss.leetcode.com"] += 9001` |

**Why reverse first?**  
Splitting `"discuss.leetcode.com"` on `'.'` gives `["discuss", "leetcode", "com"]`. Reversing to `["com", "leetcode", "discuss"]` lets us build each subdomain key by *prepending* a label to the current key. This ensures every key we construct is a valid subdomain (a suffix of the original domain), and we naturally accumulate counts from the broadest level down to the most specific.

**Complexity:**
- **Time:** O(N · L) where N = number of input domains, L = maximum domain length (at most 3 labels per domain, so effectively O(N))
- **Space:** O(N · L) for the hash map storing all unique subdomains
