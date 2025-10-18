class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        counter = [0] * 128
        in_stack = set()
        st = []
        for ch in s:
            counter[ord(ch)] += 1
        
        for ch in s:
            counter[ord(ch)] -= 1
            if ch in in_stack:
                continue
            while st and st[-1] > ch and counter[ord(st[-1])] > 0:
                in_stack.remove(st.pop())
            st.append(ch)
            in_stack.add(ch)
        
        return "".join(st)