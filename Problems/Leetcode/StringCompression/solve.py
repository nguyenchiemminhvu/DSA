from typing import List

class Solution:
    def compress(self, chars: List[str]) -> int:
        n = len(chars)
        read = 0
        write = 0

        while read < n:
            cur = chars[read]
            count = 0
            while read < n and chars[read] == cur:
                read += 1
                count += 1
            
            chars[write] = cur
            write += 1
            if count > 1:
                s_count = str(count)
                for c in s_count:
                    chars[write] = c
                    write += 1
        
        return write