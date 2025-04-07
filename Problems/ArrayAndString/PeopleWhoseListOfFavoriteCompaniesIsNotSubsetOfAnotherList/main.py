# https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/

from typing import List

class Solution:
    def peopleIndexes(self, favoriteCompanies: List[List[str]]) -> List[int]:
        set_companies = [set(favoriteCompanies[i]) for i in range(0, len(favoriteCompanies))]

        is_subset = []
        for i in range(0, len(set_companies)):
            for j in range(0, len(set_companies)):
                if (i != j):
                    if (set_companies[i].issubset(set_companies[j])):
                        is_subset.append(i)
                        break

        res = []
        for i in range(0, len(set_companies)):
            if (i not in is_subset):
                res.append(i)
        return res

if __name__ == "__main__":
    s = Solution()
    print(s.peopleIndexes([["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]))