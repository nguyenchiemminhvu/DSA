class Solution:
    def minimumDeletions(self, s: str) -> int:
        n = len(s)
        prefix_b = [0] * n
        suffix_a = [0] * n
        for i in range(1, n):
            prefix_b[i] = prefix_b[i - 1]
            if s[i - 1] == 'b':
                prefix_b[i] += 1
        for i in range(n - 2, -1, -1):
            suffix_a[i] += suffix_a[i + 1]
            if s[i + 1] == 'a':
                suffix_a[i] += 1
        
        removed = float('inf')
        for i in range(n):
            removed = min(removed, prefix_b[i] + suffix_a[i])
        return 0 if removed == float('inf') else removed