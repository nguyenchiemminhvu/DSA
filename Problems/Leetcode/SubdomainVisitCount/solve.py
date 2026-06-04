from collections import defaultdict
from typing import List

class Solution:
    def subdomainVisits(self, cpdomains: List[str]) -> List[str]:
        mp = defaultdict(int)
        for domain in cpdomains:
            count, sub_domains = domain.split()
            
            subs = sub_domains.split('.')
            subs.reverse()
            key = ''
            for s in subs:
                key = (s) if not key else (s + '.' + key)
                mp[key] += int(count)
        
        res = []
        for k, v in mp.items():
            res.append(str(v) + ' ' + k)
        return res