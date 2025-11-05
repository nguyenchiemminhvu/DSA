from typing import List, Dict, Set

class Solution:
    def numUniqueEmails(self, emails: List[str]) -> int:
        freq : Dict[str, Set[str]] = {}
        for email in emails:
            name, domain = email.split('@')
            name = name.split('+')[0].replace('.','')
            if domain not in freq:
                freq[domain] = set()
            freq[domain].add(name)
        
        res = sum(len(v) for k, v in freq.items())
        return res