## Problem

https://leetcode.com/problems/encode-and-decode-tinyurl/description/

TinyURL is a URL shortening service where you enter a URL such as `https://leetcode.com/problems/design-tinyurl` and it returns a short URL such as `http://tinyurl.com/4e9iAk`.

Design a class to **encode** a URL and **decode** a tiny URL. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded back to the original URL.

**Implement the `Solution` class:**
- `Solution()` — Initializes the object.
- `String encode(String longUrl)` — Returns a tiny URL for the given `longUrl`.
- `String decode(String shortUrl)` — Returns the original long URL for the given `shortUrl`. It is guaranteed that the given `shortUrl` was encoded by the same object.

**Example:**
```
Input:  url = "https://leetcode.com/problems/design-tinyurl"
Output: "https://leetcode.com/problems/design-tinyurl"

Solution obj = new Solution()
tiny = obj.encode(url)   # returns a short URL like "http://tinyurl.com/4e9iAk"
ans  = obj.decode(tiny)  # returns back the original URL
```

**Constraints:**
- `1 <= url.length <= 10^4`
- `url` is guaranteed to be a valid URL.

---

## Observations

1. **No fixed format required** — The problem does not mandate a specific short URL format; we just need a consistent encode/decode pair.

2. **Bijective mapping** — We need a one-to-one mapping between the original URL and its short code. A hash map (dictionary) is the natural structure for this.

3. **Collision avoidance** — Whatever key we generate for the short URL, it must be unique per original URL to avoid decoding the wrong URL.

4. **Stateful object** — The `Codec` object must maintain state (the mapping table) between `encode` and `decode` calls, since `decode` must reverse what `encode` produced.

5. **Two maps are better than one** — Keeping both a `long → short` map and a `short → long` map allows O(1) lookup in both directions, and also lets us return the **same** short URL if the same long URL is encoded twice.

6. **Key generation strategies:**
   - **Counter-based:** Use an auto-incrementing integer as the key → simple, but predictable.
   - **Hash-based:** Use a hash of the URL → compact, but hash collisions must be handled.
   - **Random string:** Generate a random alphanumeric string of fixed length (e.g., 6 chars from 62-character alphabet) → best balance of simplicity and unpredictability.

---

## Solution Explanation

We use a **random 6-character alphanumeric key** as the short code and store two dictionaries:
- `encode_map`: `long_url → short_url`
- `decode_map`: `short_url → long_url`

### `encode(long_url)`
1. If `long_url` is already in `encode_map`, return the previously assigned short URL (idempotent).
2. Otherwise, generate a random 6-char key from `[A-Za-z0-9]` (62^6 ≈ 56 billion possibilities).
3. Regenerate if the key already exists (collision).
4. Store the mapping in both dictionaries and return `"http://tinyurl.com/" + key`.

### `decode(short_url)`
1. Extract the key from the short URL (everything after the last `/`).
2. Look up the key in `decode_map` and return the original long URL.

### Complexity
| | Time | Space |
|---|---|---|
| `encode` | O(k) amortized, k = key length | O(n) for n URLs stored |
| `decode` | O(1) | O(1) extra |

---

## Solution

```python
import random
import string

class Codec:

    def __init__(self):
        self.encode_map = {}  # long_url  -> short_url
        self.decode_map = {}  # short_key -> long_url
        self.base_url = "http://tinyurl.com/"
        self.key_len = 6
        self.alphabet = string.ascii_letters + string.digits  # A-Z a-z 0-9

    def encode(self, long_url: str) -> str:
        # Return existing short URL for the same long URL (idempotent)
        if long_url in self.encode_map:
            return self.encode_map[long_url]

        # Generate a unique random key
        while True:
            key = ''.join(random.choices(self.alphabet, k=self.key_len))
            if key not in self.decode_map:
                break

        short_url = self.base_url + key
        self.encode_map[long_url] = short_url
        self.decode_map[key] = long_url
        return short_url

    def decode(self, short_url: str) -> str:
        key = short_url.split('/')[-1]
        return self.decode_map[key]


# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.decode(codec.encode(url))
```
