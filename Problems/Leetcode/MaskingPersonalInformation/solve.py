class Solution:
    def maskPII(self, s: str) -> str:
        def mask_email(s: str):
            letters = []
            pivot = -1
            for i, c in enumerate(s):
                if c == '@' and pivot == -1:
                    pivot = i
                letters.append(c.lower())
            return ''.join(letters[:1] + list('*****') + letters[pivot - 1:])
        
        def mask_phone(s: str):
            digits = [c for c in s if c.isdigit()]
            n = len(digits)
            country_len = n - 10
            if country_len > 0:
                prefix = '+' + '*' * country_len + '-'
            else:
                prefix = ''
            return prefix + '***-***-' + ''.join(digits[-4:])
        
        if '@' in s:
            return mask_email(s)
        else:
            return mask_phone(s)