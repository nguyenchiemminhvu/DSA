from typing import List

class DSU:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [1] * n

    def find(self, i: int) -> int:
        if self.parent[i] != i:
            self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def union(self, i: int, j: int) -> bool:
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i == root_j:
            return False

        if self.rank[root_i] > self.rank[root_j]:
            self.parent[root_j] = root_i
        elif self.rank[root_i] < self.rank[root_j]:
            self.parent[root_i] = root_j
        else:
            self.parent[root_j] = root_i
            self.rank[root_i] += 1

        return True

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        mail_to_name = {}
        all_mails = set()
        for acc_id, account in enumerate(accounts):
            name = account[0]
            for mail in account[1:]:
                all_mails.add(mail)
                if mail not in mail_to_name:
                    mail_to_name[mail] = name
        
        all_mails = { mail: i for i, mail in enumerate(list(all_mails)) }
        n_mail = len(all_mails)

        dsu = DSU(n_mail)
        for acc_id, account in enumerate(accounts):
            root_idx = all_mails[account[1]]
            for mail in account[1:]:
                dsu.union(root_idx, all_mails[mail])
        
        groups = {} # root_idx -> sorted(mails)
        for mail, i in all_mails.items():
            name = mail_to_name[mail]
            root_idx = dsu.find(i)
            if root_idx not in groups:
                groups[root_idx] = [name, set()]
            groups[root_idx][1].add(mail)
        
        res = []
        for root_idx, arr in groups.items():
            row = [arr[0]]
            row.extend(sorted(list(arr[1])))
            res.append(row)
        return res