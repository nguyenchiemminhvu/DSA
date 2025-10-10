from typing import List, Dict, Tuple

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        groups = []

        d : Dict[Tuple[int], List[str]] = {}
        for s in strs:
            freq = [0] * 26
            for c in s:
                freq[ord(c) - ord('a')] += 1
            freq = tuple(freq)
            if freq in d:
                d[freq].append(s)
            else:
                d[freq] = [s]
        
        for key, val in d.items():
            groups.append(val)

        return groups