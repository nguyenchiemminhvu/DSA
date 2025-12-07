class Solution:
    def generateTag(self, caption: str) -> str:
        words = caption.split()

        for i in range(len(words)):
            words[i] = words[i].lower()
            if i > 0:
                words[i] = words[i].capitalize()

        tag = "#" + "".join(words)

        cleaned = ["#"]
        for ch in tag[1:]:
            if ch.isalpha():
                cleaned.append(ch)
        result = "".join(cleaned)

        return result[:100]