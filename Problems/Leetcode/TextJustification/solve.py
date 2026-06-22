class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        rows = []

        cur_len = 0
        cur_row = []
        for word in words:
            space_needed = len(cur_row)
            if cur_len + space_needed + len(word) > maxWidth:
                rows.append(cur_row)
                cur_len = 0
                cur_row = []

            cur_row.append(word)
            cur_len += len(word)
        
        if cur_row:
            rows.append(cur_row)
        
        res = []
        for i, row in enumerate(rows):
            # Check if it is the last row or a single-word row
            is_last_row = (i == len(rows) - 1)
            is_single_word = (len(row) == 1)
            
            if is_last_row or is_single_word:
                # Left-justify: join with 1 space, pad the rest to the right
                line = " ".join(row)
                line += " " * (maxWidth - len(line))
                res.append(line)
            else:
                # Fully justify: distribute spaces evenly
                total_words_len = sum(len(w) for w in row)
                total_spaces_needed = maxWidth - total_words_len
                space_slots = len(row) - 1
                
                # Base spaces between every word
                base_space = total_spaces_needed // space_slots
                # Leftover spaces to distribute 1-by-1 from the left
                extra_space = total_spaces_needed % space_slots
                
                # Build the line slot by slot
                line_segments = []
                for j in range(space_slots):
                    line_segments.append(row[j])
                    # Add base spaces + 1 extra space if we still have remainder
                    spaces_to_add = base_space + (1 if j < extra_space else 0)
                    line_segments.append(" " * spaces_to_add)
                
                # Append the last word of the row
                line_segments.append(row[-1])
                res.append("".join(line_segments))
                
        return res