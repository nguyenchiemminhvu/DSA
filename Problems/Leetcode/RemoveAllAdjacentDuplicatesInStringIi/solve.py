class Solution:
    def removeDuplicates(self, s: str, k: int) -> str:
        st = ['#']
        ist = 1
        count = [0]
        prev = '#'
        for c in s:
            if ist == len(st):
                st.append(c)
            else:
                st[ist] = c
            ist += 1
            if c == prev:
                count[-1] += 1
                while count and count[-1] == k:
                    ist -= k
                    count.pop()
                    prev = st[ist - 1]
            else:
                count.append(1)
                prev = c
        return "".join(st[1:ist])