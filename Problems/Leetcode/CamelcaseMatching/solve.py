class Solution:
    def camelMatch(self, queries: list[str], pattern: str) -> list[bool]:
        np = len(pattern)
        res = []
        for query in queries:
            nq = len(query)
            iq = 0
            ip = 0
            good = True
            while iq < nq and ip < np:
                if query[iq] == pattern[ip]:
                    ip += 1
                else:
                    if query[iq].isupper():
                        good = False
                        break
                iq += 1
            if any(c.isupper() for c in query[iq:]):
                good = False
            if ip < np:
                good = False
            res.append(good)
        return res