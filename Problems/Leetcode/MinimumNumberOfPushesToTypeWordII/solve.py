class Solution:
    def minimumPushes(self, word: str) -> int:
        freq = [0] * 26
        for c in word:
            freq[ord(c) - ord('a')] += 1
        
        sorted_freq = sorted([(f, chr(i + ord('a'))) for i, f in enumerate(freq)], reverse=True, key=lambda x: x[0])
        keys = [''] * 8
        key_len = [3] * 8
        key_len[5] = 4
        key_len[7] = 4
        ifreq = 0
        ikey = 0
        while ifreq < len(sorted_freq) and sorted_freq[ifreq][0] > 0:
            if len(keys[ikey]) < key_len[ikey]:
                keys[ikey] += (sorted_freq[ifreq][1])
                ifreq += 1
            ikey = (ikey + 1) % 8
        
        d = {}
        for key in keys:
            for i, c in enumerate(key):
                d[c] = i
        res = 0
        for c in word:
            res += d[c] + 1

        return res