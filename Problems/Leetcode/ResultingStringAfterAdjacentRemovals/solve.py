class Solution:
    def resultingString(self, s: str) -> str:
        s = [ord(c) - ord('a') for c in s]
        
        st = []
        for val in s:
            if st and ((((val - 1) + 26) % 26) == st[-1] or ((val + 1) % 26) == st[-1]):
                st.pop()
            else:
                st.append(val)
        return "".join([chr(ord('a') + val) for val in st])