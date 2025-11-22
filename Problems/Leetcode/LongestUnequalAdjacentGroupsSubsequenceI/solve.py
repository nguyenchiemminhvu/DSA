from typing import List

class Solution:
    def getLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        arr = [(val, i) for i, val in enumerate(groups)]

        ia = 0
        for i in range(1, len(arr)):
            if arr[i][0] != arr[ia][0]:
                ia += 1
                arr[ia], arr[i] = arr[i], arr[ia]
        arr = arr[:ia + 1]

        return [words[pair[1]] for pair in arr]