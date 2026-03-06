from typing import List
from collections import defaultdict

class TopVotedCandidate:

    def __init__(self, persons: List[int], times: List[int]):
        self.arr = [] # (t, top_person)
        freq = defaultdict(int)
        top_vote = 0
        top_person = -1
        for person, t in zip(persons, times):
            freq[person] += 1
            if freq[person] > top_vote:
                top_vote = freq[person]
                top_person = person
            elif freq[person] == top_vote:
                top_person = person
            self.arr.append((t, top_person))

    def q(self, t: int) -> int:
        def upper_bound(arr, t) -> int:
            n = len(arr)
            left = 0
            right = n - 1
            idx = n
            while left <= right:
                mid = left + (right - left) // 2
                if arr[mid][0] > t:
                    idx = mid
                    right = mid - 1
                else:
                    left = mid + 1
            return idx
        
        upper = upper_bound(self.arr, t) - 1
        return self.arr[upper][1]

# Your TopVotedCandidate object will be instantiated and called as such:
# obj = TopVotedCandidate(persons, times)
# param_1 = obj.q(t)