class Solution:
    def decodeMessage(self, key: str, message: str) -> str:
        key = "".join(key.split(' '))
        d = {}
        skey = set()
        i = 0
        for c in key:
            if c not in skey:
                skey.add(c)
                d[c] = chr(ord('a') + i)
                i += 1
        d[' '] = ' '
        message = list(message)
        for i in range(len(message)):
            message[i] = d[message[i]]
        return "".join(message)