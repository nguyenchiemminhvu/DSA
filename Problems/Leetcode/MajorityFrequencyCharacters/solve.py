from collections import Counter

class Solution:
    def majorityFrequencyGroup(self, s: str) -> str:
        f = Counter(list(s))
        
        groups = {}
        for k, val in f.items():
            if val not in groups:
                groups[val] = []
            groups[val].append(k)

        max_k = -1
        max_len = 0
        for k, arr in groups.items():
            if max_len < len(arr):
                max_k = k
                max_len = len(arr)
            elif max_len == len(arr):
                if max_k < k:
                    max_k = k

        return "".join(list(set(groups[max_k])))