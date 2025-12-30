class Solution:
    def lengthLongestPath(self, input: str) -> int:
        arr = input.splitlines()
        res = 0
        st = []
        for sub in arr:
            idx = sub.count('\t')
            if idx >= len(st):
                st.append(sub)
            else:
                st[idx] = sub
            if sub.count('.'):
                path = "/".join(st[:idx + 1])
                num_tabs = idx * (idx + 1) // 2
                res = max(res, len(path) - num_tabs)
        return res