class Codec:

    def encode(self, long_url: str) -> str:
        self.url = long_url

    def decode(self, short_url: str) -> str:
        return self.url

# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.decode(codec.encode(url))